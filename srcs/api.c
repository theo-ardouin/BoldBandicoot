#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <pthread.h>

#include "server.h"

pthread_mutex_t _mutex_send = PTHREAD_MUTEX_INITIALIZER;

static int api_send(lua_State* L)
{
  ENetPeer* peer = lua_touserdata(L, 1);
  const char* str = luaL_checkstring(L, 2);
  int channelId = luaL_optnumber(L, 3, 0);

  if (peer == NULL)
  {
    return luaL_error(L, "Expected lightuserdata <Peer>");
  }

  pthread_mutex_lock(&_mutex_send);

  ENetPacket* packet = enet_packet_create(str, strlen(str) + 1, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(peer, channelId, packet);

  pthread_mutex_unlock(&_mutex_send);
  return 0;
}

static int api_send_all(lua_State* L)
{
  server_t* server = lua_touserdata(L, 1);
  const char* str = luaL_checkstring(L, 2);
  int channelId = luaL_optnumber(L, 3, 0);

  if (server == NULL)
  {
    return luaL_error(L, "Expected lightuserdata <Server>");
  }

  pthread_mutex_lock(&_mutex_send);

  ENetPacket* packet = enet_packet_create(str, strlen(str) + 1, ENET_PACKET_FLAG_RELIABLE);
  enet_host_broadcast(server->host, channelId, packet);

  pthread_mutex_unlock(&_mutex_send);
  return 0;
}

static int api_str_packet(lua_State* L)
{
  ENetPacket* packet = lua_touserdata(L, 1);

  if (packet == NULL)
  {
    return luaL_error(L, "Expected lightuserdata <Packet>");
  }
  char str[packet->dataLength + 1];

  memcpy(str, packet->data, packet->dataLength);
  str[packet->dataLength] = 0;
  lua_pushstring(L, str);
  return 1;
}

static int api_disconnect(lua_State* L)
{
  ENetPeer* peer = lua_touserdata(L, 1);
  int reason = luaL_optnumber(L, 2, 0);

  if (peer)
  {
    enet_peer_disconnect(peer, reason);
  }
  return 0;
}

static int api_force_disconnect(lua_State* L)
{
  ENetPeer* peer = lua_touserdata(L, 1);

  if (peer)
  {
    enet_peer_reset(peer);
  }
  return 0;
}

void api_load(lua_State* L)
{
  static const struct luaL_Reg funcs[] = {
    { "Send", api_send },
    { "SendAll", api_send_all },
    { "StrPacket", api_str_packet },
    { "Disconnect", api_disconnect },
    { "ForceDisconnect", api_force_disconnect },
    { NULL,  NULL }
  };
  luaL_newlib(L, funcs);
  lua_setglobal(L, "api");
}
