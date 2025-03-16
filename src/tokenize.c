#include "tokenize.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static char *skip_delim(char *s, const char *delim)
{
  while (*s && strchr(delim, *s))
  {
    s++;
  }
  return s;
}

static char *find_tokend(char *s, const char *delim)
{
  bool quoted = false;

  while (*s)
  {
    if (*s == '\"')
      quoted = !quoted;
    else if (!quoted && strchr(delim, *s))
      break;

    s++;
  }

  return s;
}

static char *strip_quotes(char *tok)
{
  size_t tok_len = strlen(tok);
  if (tok_len >= 2 && tok[0] == '\"' && tok[tok_len - 1] == '\"')
  {
    tok[tok_len - 1] = '\0';
    return tok + 1;
  }
  return tok;
}

char *tokenize(char *str, const char *delim)
{
  static char *next_token = NULL;
  if (str != NULL)
    next_token = str;

  if (next_token == NULL)
    return NULL;

  next_token = skip_delim(next_token, delim);
  if (*next_token == '\0')
    return NULL;

  char *token_start = next_token;
  char *token_end = find_tokend(next_token, delim);

  if (*token_end)
  {
    *token_end = '\0';
    next_token = token_end + 1;
  }
  else
  {
    next_token = NULL;
  }

  return strip_quotes(token_start);
}