#include "cmd.h"

#define IBUF_DENY " "

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <readline/readline.h>

#include "history.h"
#include "tokenize.h"
#include "path.h"

struct cmd_t
{
  char *buf;
  char *tok;
  char **bin_dirs;
  char *path_buf;
};

void clear_input(Commandline *cmdline)
{
  if (cmdline->tok)
  {
    free(cmdline->tok);
    cmdline->tok = NULL;
  }
  if (cmdline->buf)
  {
    free(cmdline->buf);
    cmdline->buf = NULL;
  }
}

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

  return args;
}

void cmd_free(Commandline *cmdline)
{
  clear_input(cmdline);

  free(cmdline->path_buf);
  free(cmdline->bin_dirs);
  free(cmdline);

  end_history();
}

int read_line(Commandline *cmdline)
{
  // After every line is read, whatever remains
  // inside `tok` and `buf` should be cleared
  // and reset
  clear_input(cmdline);

  cmdline->buf = readline("> ");

  add_entry(cmdline->buf);

  if (cmdline->buf)
    return 0;
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