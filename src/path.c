#include "path.h"

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <string.h>

char *get_path()
{
  static char *path = NULL;

  if (!path)
  {
    path = getenv("PATH");
    return strtok(path, ":");
  }

  return strtok(NULL, ":");
}