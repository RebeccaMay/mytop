#pragma once


enum sortby {PID, CPU, MEM, TIME};

struct progopts{
  int delay_tenths;
  enum sortby sort_key;
  int max_proc;
};

extern struct progopts opts;

static const char sortby_keys[4][5] = {"PID", "CPU", "MEM", "TIME"};

void opts_help(char **argv, int exit_status);

void opts_init(int argc, char **argv);

