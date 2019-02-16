#include "config.h"
#include "logger.h"

void config_load(config_t* cfg, int ac, char** av)
{
  // TODO Load from ac, av
  (void)ac;
  (void)av;
  cfg->script = DEFAULT_SCRIPT;
  logger(TRC_INFO, "Configuration: script=%s", cfg->script);

  cfg->port = DEFAULT_PORT;
  logger(TRC_INFO, "Configuration: port=%d", cfg->port);

  cfg->tickrate = DEFAULT_TICKRATE;
  logger(TRC_INFO, "Configuration: tickrate=%.2f", cfg->tickrate);

  cfg->timeout = DEFAULT_TIMEOUT;
  logger(TRC_INFO, "Configuration: timeout=%.2f", cfg->timeout);
}
