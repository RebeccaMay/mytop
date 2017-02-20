//file to populate functions to format and then print all outputs
#include "format.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>


/*
char * uptime_info(double uptime);
char * loadavg_info(LoadAverageInfo& loadavg);
char * cpu_info(SystemInfo& sys, SystemInfo& sys_last, size_t cpu_no);
char * proc_info(SystemInfo& sys);
char * thread_info(SystemInfo& sys);
char * memory_info();
*/

void table_names(){
  static char tbl_names[250];
  sprintf(tbl_names, "%-5d %-7s %c %-1s %-5s %-8s %s", "PID", "Memory", "S", "CPU%", "Time", "Command" );

  printw("%s", tbl_names);
}
