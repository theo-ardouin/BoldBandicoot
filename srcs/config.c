#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "logger.h"

static const char* config_find(int ac, char** av,
  const char* key)
{
  size_t len = strlen(key);
  for (int i = 0; i < ac; ++i)
  {
    if (strncmp(av[i], key, len) == 0 && av[i][len] == '=')
    {
      return av[i] + len + 1;
    }
  }
  return NULL;
}

static const char* config_get(int ac, char** av,
  const char* key,
  const char* def)
{
  const char* s = config_find(ac, av, key);
  const char* val = s ? s : def;
  logger(TRC_INFO, "%s = %s", key, val);
  return val;
}

void config_load(config_t* cfg, int ac, char** av)
{
  ac -= 1;
  av += 1;
  cfg->script = config_get(ac, av, "script", DEFAULT_SCRIPT);
  cfg->port = atoi(config_get(ac, av, "port", DEFAULT_PORT));
  cfg->tickrate = atof(config_get(ac, av, "tickrate", DEFAULT_TICKRATE));
  cfg->timeout = atof(config_get(ac, av, "timeout", DEFAULT_TIMEOUT));
}
