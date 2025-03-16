#include "cmd.h"

#define _XOPEN_SOURCE 500
#define IBUF_DENY " "

#ifndef IBUF_LEN
#define IBUF_LEN 32
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "path.h"

struct cmd_t
{
  char *buf;
  char *tok;
  char **bin_dirs;
};

Commandline *cmd_init()
{
  Commandline *args = (Commandline *)malloc(sizeof(Commandline));

  if (args == NULL)
  {
    return NULL;
  }

  args->buf = (char *)malloc(IBUF_LEN);
  args->tok = NULL;

  if (args->buf == NULL)
  {
    return NULL;
  }

  args->bin_dirs = init_path();

  return args;
}

void cmd_free(Commandline *cmdline)
{
  if (cmdline->tok != NULL)
    free(cmdline->tok);

  free(cmdline->buf);
  free(cmdline->bin_dirs);
  free(cmdline);
}

int read_line(Commandline *cmdline)
{
  if (!fgets(cmdline->buf, IBUF_LEN, stdin))
  {
    if (!feof(stdin))
      perror("unable to read to stdin");

    return 1;
  }

  // After every line is read, whatever remains
  // inside `tok` should be cleared
  free(cmdline->tok);
  cmdline->tok = NULL;

  cmdline->buf[strcspn(cmdline->buf, "\n")] = 0;
  return 0;
}

char *get_arg(Commandline *cmdline)
{
  if (cmdline->tok == NULL)
  {
    cmdline->tok = strdup(cmdline->buf);

    if (!cmdline->tok)
    {
      return NULL;
    }

    return strtok(cmdline->tok, IBUF_DENY);
  }

  return strtok(NULL, IBUF_DENY);
}

char *search_executable(Commandline *cmdline, const char *executable)
{
  char *path_dir = NULL;

  printf("Searching $PATH for `%s`\n", executable);
  // FIXME: This shouldn't remain here, only for debugging purposes
  int pathno = 0;
  do
  {
    printf("[%3d]", pathno);
    path_dir = cmdline->bin_dirs[++pathno];

    if (path_dir)
      printf("\t%s\n", path_dir);
  } while (path_dir != NULL);

  // FIXME: This should return `executable`'s real path
  return NULL;
}

void process_arg(Commandline *cmdline, char **executable)
{
  char *current_arg = get_arg(cmdline);

  *executable = current_arg;
  if (current_arg == NULL)
    return;

  printf("Executable: %s\n", *executable);
  for (int i = 0; current_arg != NULL; i++)
  {
    current_arg = get_arg(cmdline);

    // Sometimes this becomes NULL
    // as this loop is executing
    if (current_arg == NULL)
      break;

    printf("\t%-3d: %s\n", i, current_arg);
  }
}