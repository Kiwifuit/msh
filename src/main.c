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

  do
  {
    current_arg = get_arg(cmdline);

    if (current_arg == NULL)
    {
      break;
    }

    printf("%s\n", current_arg);
  } while (current_arg != NULL);

  cmd_free(cmdline);
}