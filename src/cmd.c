#include "cmd.h"
#include "tokenize.h"

#define _XOPEN_SOURCE 500
#define IBUF_DENY " "

#ifndef IBUF_LEN
#define IBUF_LEN 256
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void read_line(Commandline *cmdline)
{
  if (!fgets(cmdline->buf, IBUF_LEN, stdin))
  {
    perror("unable to read to stdin");
    return;
  }

  cmdline->buf[strcspn(cmdline->buf, "\n")] = 0;
}

char *get_arg(Commandline *cmdline)
{
  if (cmdline->tok == NULL)
  {
    cmdline->tok = strdup(cmdline->buf);
    return tokenize(cmdline->tok, IBUF_DENY);
  }

  // tf why conditional statements the same as above?
  // if (cmdline->tok == NULL)
  // {
  //   printf("error: token was empty for some reason\n");
  //   return NULL;
  // }

  return tokenize(NULL, IBUF_DENY);
}