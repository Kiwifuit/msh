#pragma once

typedef struct cmd_t Commandline;

Commandline *cmd_init();
void cmd_free(Commandline *arg);
void read_line(Commandline *cmdline);
char *get_arg(Commandline *cmdline);
