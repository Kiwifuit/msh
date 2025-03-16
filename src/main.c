#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#include "cmd.h"
#include "path.h"

int main()
{
  Commandline *cmdline = cmd_init();
  char *executable = NULL;

  if (cmdline == NULL)
  {
    perror("failed to initialize tokenizer");
    exit(EXIT_FAILURE);
  }

  printf(GREETING);
  do
  {
    errno = 0;
    printf("> ");

    if (read_line(cmdline))
    {
      printf("\rexit\n");
      break;
    }

    process_arg(cmdline, &executable);
    if (executable != NULL)
      executable = search_executable(cmdline, executable);
    if (errno)
    {
      perror("error while running");
    }
  } while (1);

  cmd_free(cmdline);
}