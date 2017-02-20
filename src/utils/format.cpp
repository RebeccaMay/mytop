//file to populate functions to format and then print all outputs
#include "format.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>



void uptime_info(double uptime){
  static char uptime_buffer[80];
  int secs = (int)uptime % 60;
  int mins = ((int)(uptime/60) % 60);
  int hrs = ((int)(uptime/3600) % 60);
  int days = uptime / 86400;
  sprintf(uptime_buffer, "up %d day%s, %02d:%02d:%02d", days, days==1?"":"s", hrs, mins, secs);
  printw("%s", uptime_buffer); 
}
	      
void loadavg_info(LoadAverageInfo& loadavg){
  static char loadavg_buffer[36];
  sprintf(loadavg_buffer, "load average: %.2f %.2f %.2f", loadavg.one_min, loadavg.five_mins, loadavg.fifteen_mins);

  printw("%s", loadavg_buffer);
}

void cpu_info(SystemInfo& sys, SystemInfo& sys_last, size_t cpu_no);       //FIXME*******


void proc_info(SystemInfo& sys){
  static char proc_buffer[80];
  sprintf(proc_buffer, "%d total processes, %d running processes", sys.num_processes, sys.num_running);

  printw("%s", proc_buffer);
}


void thread_info(SystemInfo& sys);                //FIXME*************


void  memory_info();                                  //FIXME******

void table_names(){
  static char tbl_names[250];
  sprintf(tbl_names, "%-5s %-7s %c %-1s %-5s %-8s %s", "PID", "Memory", "S", "CPU%", "Time", "Command");

  printw("%s", tbl_names);
}

void table_info(ProcessInfo& proc);

