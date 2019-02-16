#ifndef CONFIG_H_
#define CONFIG_H_

#define DEFAULT_SCRIPT    "scripts/main.lua"
#define DEFAULT_PORT      8173
#define DEFAULT_TICKRATE  0.2
#define DEFAULT_TIMEOUT   1

typedef struct config
{
  const char* script;
  unsigned short port;
  float tickrate;
  float timeout;
} config_t;

void config_load(config_t*, int ac, char** av);

#endif
