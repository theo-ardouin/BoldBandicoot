#include <stdlib.h>
#include <signal.h>

#include "server.h"

static server_t _server;

static void on_stop(int signum)
{
  (void)signum;
  server_stop(&_server);
}

int main(int ac, char** av)
{
  signal(SIGINT, on_stop);

  server_load(&_server, ac, av);
  server_run(&_server);
  return EXIT_SUCCESS;
}
