#include "cmd.h"

#define _XOPEN_SOURCE 500
#define IBUF_DENY " "

#ifndef IBUF_LEN
#define IBUF_LEN 32
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

struct cmd_t
{
  char *buf;
  char *tok;
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

  return args;
}

void cmd_free(Commandline *cmdline)
{
  if (cmdline->tok != NULL)
    free(cmdline->tok);

  free(cmdline->buf);
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