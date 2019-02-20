#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tools.h"
#include "logger.h"
#include "fassert.h"

void tools_lua_fatal(lua_State* L)
{
  logger(TRC_FATAL, "%s", lua_tostring(L, -1));
  exit(EXIT_FAILURE);
}

void tools_execute_from(const char* filepath)
{
  char* last;
  char dirname[strlen(filepath) + 1];

  strcpy(dirname, filepath);
  last = strrchr(dirname, '/');
  if (last != NULL)
  {
    *last = 0;
    fassert(chdir(dirname) == 0);
  }
}
