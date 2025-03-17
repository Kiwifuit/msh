#include "history.h"

#include <errno.h>

#include <readline/history.h>

#ifndef HISTFILE
#define HISTFILE ".msh_history"
#endif

void begin_history()
{
  using_history();
  if (read_history(HISTFILE) && errno != ENOENT)
    perror("unable to fetch history");
}

void end_history()
{
  if (write_history(HISTFILE))
    perror("unable to save history");
}

void add_entry(char *line)
{
  if (line && *line)
  {
    add_history(line);
  }
}