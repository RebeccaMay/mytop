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

void cpu_info(SystemInfo& sys, SystemInfo& sys_last, size_t cpu_no){
  static char cpuinfo_buffer[80];
  
  double percent_user = (sys.cpus[cpu_no].user_time)/(double)(sys.cpus[cpu_no].total_time())*100;

  double percent_kernel = (sys.cpus[cpu_no].total_system_time()) / (double)(sys.cpus[cpu_no].total_time()) * 100;

  double percent_idle = (sys.cpus[cpu_no].total_idle_time()) / (double)(sys.cpus[cpu_no].total_time()) * 100;

  sprintf(cpuinfo_buffer, "Cpu%c: %5.1f%% user, %5.1f%% kernel, %5.1f%% idle", cpu_no?'0' + (char)cpu_no-1: 'T', percent_user, percent_kernel, percent_idle);

  printw("%s", cpuinfo_buffer);									   
}


void proc_info(SystemInfo& sys){
  static char proc_buffer[80];
  sprintf(proc_buffer, "%d total processes, %d running processes", sys.num_processes, sys.num_running);

  printw("%s", proc_buffer);
}


void thread_info(SystemInfo& sys){
  static char thread_buffer[80];
  sprintf(thread_buffer, "%d total threads, %d user threads, %d kernel", sys.num_threads, sys.num_user_threads, sys.num_kernel_threads);

  printw("%s", thread_buffer);
}


void  memory_info(){
  static char memory_buffer[80];
  MemoryInfo memory = get_memory_info();
  sprintf(memory_buffer, "MEM: %llu total, %llu used, %llu available", memory.total_memory, (memory.total_memory - memory.free_memory), memory.free_memory);

  printw("%s", memory_buffer);
}

void table_names(){
  static char tbl_names[250];
  sprintf(tbl_names, "%-5s %-7s %-1s %-5s %-8s %s", "PID", "Memory", "S", "CPU%", "Time", "Command");

  printw("%s", tbl_names);
}

void table_info(ProcessInfo& proc){
  static char table_line[256];
  sprintf(table_line, "%-5d %-7s %c %-5.1f %-8ul %.220s", proc.pid,format_bytes( proc.rss*sysconf(_SC_PAGESIZE)), proc.state, proc.cpu_percent, format_time((proc.utime + proc.stime)/sysconf(_SC_CLK_TCK)), proc.command_line.c_str());

   printw("%s", table_line);
}

char * format_time(int secs){
  static char buf[10];
  sprintf(buf, "%02d:%02d:%02d", secs/3600, (secs/60) % 60, secs % 60);
  return buf;
}

char * format_bytes(unsigned long long amt){
  static size_t state;
  static char buffers[16][24];
  char *buf = buffers[state++%16];

  if(!(amt >> 10)){
    sprintf(buf, "%lluB", amt);
    return buf;
  }

  if(!(amt >> 20)){
    sprintf(buf, "%.1fk", (double)amt/0x400);
    return buf;
  }

  if(!(amt >> 30)){
    sprintf(buf, "%.1fM", (double)amt/0x100000);
    return buf;
  }

  sprintf(buf, "%.1fG", (double)amt/0x40000000);
  return buf;
}
