#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "path.h"

int main()
{
  Commandline *cmdline = cmd_init();
  char *current_arg, *curr_path = NULL;

  if (cmdline == NULL)
  {
    perror("failed to initialize tokenizer");
    exit(EXIT_FAILURE);
  }

  do
  {
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

    printf("$PATH raw: %s\n", getenv("PATH"));
    printf("$PATH dump:\n");
    curr_path = get_path();
    for (int i = 0; curr_path != NULL; i++)
    {
      printf("%d\t:%s\n", i, curr_path);
      curr_path = get_path();
    }

  } while (1);

  cmd_free(cmdline);
}