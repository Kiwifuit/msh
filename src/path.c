#include "path.h"

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t count_seps(char *path)
{
  // Count the number of separators in the $PATH variable
  size_t sep_count = 0;
  for (char *path_char = path; *path_char; path_char++)
  {
    if (*path_char == ':')
      sep_count++;
  }

  return sep_count;
}

void copy_paths(char *path, char **paths)
{
  char *current_path = strtok(path, ":");
  size_t indx;
  for (indx = 0; current_path; indx++)
  {
    paths[indx] = current_path;
    current_path = strtok(NULL, ":");
  }

  paths[indx] = NULL;
}

char **init_path(void)
{
  char *path = getenv("PATH");
  if (!path)
    return NULL;

  char *path_dup = strdup(path);
  if (!path_dup)
    return NULL;

  size_t sep_count = count_seps(path_dup);
  char **paths = (char **)malloc((sep_count + 1) * sizeof(char *));
  if (!paths)
  {
    free(path_dup);
    return NULL;
  }

  copy_paths(path_dup, paths);
  free(path_dup);
  return paths;
}

// char *get_path()
// {
//   static char *env_path = NULL;
//   static char *current_path = NULL;

//   if (!env_path)
//   {
//     char *path = getenv("PATH");
//     if (!path)
//       return NULL;

//     env_path = strdup(path);
//     if (!env_path)
//       return NULL;

//     current_path = strtok(env_path, ":");
//   }
//   else
//   {
//     current_path = strtok(NULL, ":");
//   }

//   if (!current_path)
//   {
//     free(env_path);
//     env_path = NULL;
//   }

//   return current_path;
// }