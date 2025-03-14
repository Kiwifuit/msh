// ty chatgpt
#include "tokenize.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Supports only `"` since adding `'` will add more headaches
// ! there is that one strange bug when it cuts the end
char *tokenize(char *str, const char *delim)
{
  static char *next_token = NULL;
  if (str != NULL)
  {
    next_token = str;
  }

  if (next_token == NULL)
  {
    return NULL;
  }

  while (*next_token && strchr(delim, *next_token))
  {
    next_token++;
  }

  if (*next_token == '\0')
  {
    return NULL;
  }

  char *token_start = next_token;
  bool in_quotes = false;

  while (*next_token)
  {
    if (*next_token == '\"')
    {
      in_quotes = !in_quotes;
    }
    else if (!in_quotes && strchr(delim, *next_token))
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
  else
  {
    next_token = NULL;
  }

  if (*token_start == '\"')
  {
    token_start++;
    char *end = strchr(token_start, '\0') - 1;
    if (*end == '\"')
    {
      *end = '\0';
    }
  }

  return token_start;
}