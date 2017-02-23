//file to write function names to format and then pring all outputs

#pragma once
#include "../info/system_info.h"
#include "../info/cpu_info.h"
#include "../info/load_average_info.h"
#include "../info/memory_info.h"
#include "../info/process_info.h"

void uptime_info(double uptime);
void loadavg_info(LoadAverageInfo& loadavg);
void cpu_info(SystemInfo& sys, size_t cpu_no);
void proc_info(SystemInfo& sys);
void thread_info(SystemInfo& sys);
void  memory_info();
void table_names();
void table_info(ProcessInfo& proc);

char * format_time(int seconds);
char * format_bytes(unsigned long long amt);


