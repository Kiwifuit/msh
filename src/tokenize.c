#include "tokenize.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *tokenize(char *str, const char *delim)
{
  static char *next_token = NULL;
  if (str != NULL)
  {
    next_token = str;
  }
  if (next_token == NULL || *next_token == '\0')
  {
    return NULL;
  }

  bool in_quote = false;
  char *token_start = next_token;

  while (*next_token && strchr(delim, *next_token))
  {
    next_token++;
  }

  if (*next_token == '\0')
  {
    return NULL;
  }

  token_start = next_token;

  while (*next_token)
  {
    if (*next_token == '"')
    {
      in_quote = !in_quote;
    }
    else if (!in_quote && strchr(delim, *next_token))
    {
      break;
    }
    next_token++;
  }

  if (*next_token)
  {
    *next_token = '\0';
    next_token++;
  }

  return token_start;
}
