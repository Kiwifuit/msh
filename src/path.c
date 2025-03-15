#include "path.h"

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *get_path()
{
  static char *env_path = NULL;
  static char *current_path = NULL;

  if (!env_path)
  {
    char *path = getenv("PATH");
    if (!path)
      return NULL;

    env_path = strdup(path);
    if (!env_path)
      return NULL;

    current_path = strtok(env_path, ":");
  }
  else
  {
    current_path = strtok(NULL, ":");
  }

  if (!current_path)
  {
    free(env_path);
    env_path = NULL;
  }

  return current_path;
}