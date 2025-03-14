// Configuration
// ------------------
// Input Buffer Length
#define IBUF_LEN 256

#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "path.h"

int main()
{
  Commandline *cmdline = cmd_init();
  char *executable, *current_arg;

  if (cmdline == NULL)
  {
    perror("failed to initialize tokenizer");
    exit(EXIT_FAILURE);
  }

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

    // FIXME: This shit broken af :/
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
  } while (1);

  cmd_free(cmdline);
}