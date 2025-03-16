#pragma once

typedef struct cmd_t Commandline;

Commandline *cmd_init();
void cmd_free(Commandline *arg);
int read_line(Commandline *cmdline);
char *search_executable(Commandline *cmdline, const char *executable);
void process_arg(Commandline *cmdline, char **executable);
