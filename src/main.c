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

  cmd_free(cmdline);
}