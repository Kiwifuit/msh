#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#include "cmd.h"
#include "path.h"

int main()
{
  Commandline *cmdline = cmd_init();
  char *executable, *current_arg, *path_dir = NULL;

  if (cmdline == NULL)
  {
    perror("failed to initialize tokenizer");
    exit(EXIT_FAILURE);
  }

    errno = 0;
    do
  {
    printf("> ");

    if (read_line(cmdline))
    {
      printf("\rexit\n");
      break;
    }

    current_arg = get_arg(cmdline);
    executable = current_arg;

    if (executable == NULL)
    {
      continue;
    }

    printf("Executable: %s\n", executable);
    for (int i = 0; current_arg != NULL; i++)
    {
      current_arg = get_arg(cmdline);

      // Sometimes this becomes NULL
      // as this loop is executing
      if (current_arg == NULL)
        break;

      printf("\t%-3d: %s\n", i, current_arg);
    }

    printf("Searching $PATH for `%s`\n", executable);

    do
    {
      path_dir = get_path();
      if (path_dir == NULL)
        break;

      printf("\t%s\n", path_dir);
    } while (path_dir != NULL);

    if (errno)
    {
      perror("error while running");
    }

  } while (1);

  cmd_free(cmdline);
}