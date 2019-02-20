#include <stdlib.h>
#include <unistd.h>

#include <lualib.h>
#include <lauxlib.h>

#include "api.h"
#include "tools.h"
#include "server.h"
#include "logger.h"
#include "fassert.h"

static void server_lua_load(server_t* server, const char* filepath)
{
  int lua_file_loading;
  server->lua = luaL_newstate();

  luaL_openlibs(server->lua);
  api_load(server->lua);
  lua_file_loading = luaL_loadfile(server->lua, filepath);
  if (lua_file_loading == LUA_ERRSYNTAX)
  {
    tools_lua_fatal(server->lua);
  }
  fassert(lua_file_loading == 0);
  tools_execute_from(filepath);
  if (lua_pcall(server->lua, 0, 0, 0))
  {
    tools_lua_fatal(server->lua);
  }
}

static void server_host_load(server_t* server, unsigned short port)
{
  ENetAddress address;

  address.host = ENET_HOST_ANY;
  address.port = port;
  fassert(enet_initialize() == 0);
  server->host = fassertp(enet_host_create(&address, 32, 2, 0, 0));
}

static void server_update(server_t* server, float dt)
{
  lua_getglobal(server->lua, "onUpdate");
  lua_pushlightuserdata(server->lua, server);
  lua_pushnumber(server->lua, dt);
  if (lua_pcall(server->lua, 2, 0, 0))
  {
    logger(TRC_ERR, "onUpdate - %s", lua_tostring(server->lua, -1));
  }
}

static void server_connect(server_t* server, ENetPeer* peer)
{
  lua_getglobal(server->lua, "onConnect");
  lua_pushlightuserdata(server->lua, server);
  lua_pushlightuserdata(server->lua, peer);
  if (lua_pcall(server->lua, 2, 0, 0))
  {
    logger(TRC_ERR, "onConnect - %s", lua_tostring(server->lua, -1));
  }
}

static void server_disconnect(server_t* server, ENetPeer* peer)
{
  lua_getglobal(server->lua, "onDisconnect");
  lua_pushlightuserdata(server->lua, server);
  lua_pushlightuserdata(server->lua, peer);
  if (lua_pcall(server->lua, 2, 0, 0))
  {
    logger(TRC_ERR, "onDisconnect - %s", lua_tostring(server->lua, -1));
  }
}

static void server_packet(server_t* server, ENetPeer* peer, ENetPacket* packet)
{
  lua_getglobal(server->lua, "onPacket");
  lua_pushlightuserdata(server->lua, server);
  lua_pushlightuserdata(server->lua, peer);
  lua_pushlightuserdata(server->lua, packet);
  if (lua_pcall(server->lua, 3, 0, 0))
  {
    logger(TRC_ERR, "onPacket - %s", lua_tostring(server->lua, -1));
  }
}

static void server_host_update(server_t* server)
{
  ENetEvent event;

  while (enet_host_service(server->host, &event, AS_MSEC(server->cfg.timeout)) > 0)
  {
    switch (event.type)
    {
    case ENET_EVENT_TYPE_CONNECT:
      server_connect(server, event.peer);
      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      server_disconnect(server, event.peer);
      break;
    case ENET_EVENT_TYPE_RECEIVE:
      server_packet(server, event.peer, event.packet);
      enet_packet_destroy(event.packet);
      break;
    default:
      break;
    }
  }
}

static void* server_net_update(void* server)
{
  while (MY_CAT_IS_FLYING)
  {
    server_host_update(server);
  }
  return NULL;
}

void server_load(server_t* server, int ac, char** av)
{
  config_load(&server->cfg, ac, av);
  server_lua_load(server, server->cfg.script);
  server_host_load(server, server->cfg.port);
  fassert(pthread_create(&server->net, NULL, server_net_update, server) == 0);
}

void server_run(server_t* server)
{
  while (MY_CAT_IS_FLYING)
  {
    usleep(AS_USEC(server->cfg.tickrate));
    server_update(server, server->cfg.tickrate);
  }
  fassert(pthread_join(server->net, NULL) == 0);
}

void server_stop(server_t* server)
{
  enet_host_destroy(server->host);
  enet_deinitialize();

  lua_close(server->lua);

  exit(EXIT_SUCCESS);
}
