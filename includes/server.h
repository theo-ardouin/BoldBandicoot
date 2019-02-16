#ifndef SERVER_H_
#define SERVER_H_

#include <lua.h>
#include <pthread.h>
#include <enet/enet.h>

#include "config.h"

#define AS_MSEC(x)  (x * 1000)
#define AS_USEC(x)  (x * 1000000)

#define MY_CAT_IS_FLYING 1

typedef struct server
{
  lua_State* lua;
  ENetHost* host;
  pthread_t net;
  config_t cfg;
} server_t;

void server_load(server_t*, int ac, char** av);
void server_run(server_t*);
void server_stop(server_t*);

#endif
