#include "cmd.h"

#define IBUF_DENY " "

#ifndef IBUF_LEN
#define IBUF_LEN 32
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>
// #include <readline/

#include "tokenize.h"
#include "path.h"

struct cmd_t
{
  char *buf;
  char *tok;
  char **bin_dirs;
  char *path_buf;
};

Commandline *cmd_init()
{
  Commandline *args = (Commandline *)malloc(sizeof(Commandline));

  if (args == NULL)
  {
    return NULL;
  }

  // args->buf = (char *)malloc(IBUF_LEN);
  args->buf = NULL;
  args->tok = NULL;

  args->bin_dirs = init_path(args->path_buf);

  using_history();
  if (read_history(".msh_history") && errno != ENOENT)
    perror("unable to fetch history");

  return args;
}

void cmd_free(Commandline *cmdline)
{
  if (cmdline->tok)
    free(cmdline->tok);
  if (cmdline->buf)
    free(cmdline->buf);

  free(cmdline->path_buf);
  free(cmdline->bin_dirs);
  free(cmdline);
}

int read_line(Commandline *cmdline)
{
  if (cmdline->buf)
  {
    free(cmdline->buf);
    cmdline->buf = NULL;
  }

  if (cmdline->tok)
  {
    // After every line is read, whatever remains
    // inside `tok` should be cleared
    free(cmdline->tok);
    cmdline->tok = NULL;
  }

  cmdline->buf = readline("> ");
  if (cmdline->buf)
  {
    char *history = strdup(cmdline->buf);

    add_history(history);

    free(history);
    return 0;
  }
  return 1;
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

  // return tokenize(cmdline->buf, IBUF_DENY);
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