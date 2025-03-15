#pragma once

typedef struct cmd_t Commandline;

Commandline *cmd_init();
void cmd_free(Commandline *arg);
void cmd_tok_free(Commandline *cmdline);
void read_line(Commandline *cmdline);
char *get_arg(Commandline *cmdline);
