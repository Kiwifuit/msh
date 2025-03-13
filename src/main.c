#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"

int main()
{
  Commandline *cmdline = cmd_init();
  char *current_arg;

  if (cmdline == NULL)
  {
    perror("failed to initialize tokenizer");
    exit(EXIT_FAILURE);
  }

  printf("Enter text: ");
  read_line(cmdline);

  for (int i = 0; current_arg != NULL; i++)
  {
    current_arg = get_arg(cmdline);

    if (current_arg == NULL)
    {
      break;
    }

    printf("[%d]:\t%s\n", i, current_arg);
  }

  cmd_free(cmdline);
}