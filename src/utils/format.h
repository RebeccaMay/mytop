//file to write function names to format and then pring all outputs

#pragma once
#include "../info/system_info.h"
#include "../info/cpu_info.h"
#include "../info/load_average_info.h"
#include "../info/memory_info.h"
#include "../info/process_info.h"

char * uptime_info(double uptime);
char * loadavg_info(LoadAverageInfo& loadavg);
char * cpu_info(SystemInfo& sys, SystemInfo& sys_last, size_t cpu_no);
char * proc_info(SystemInfo& sys);
char * thread_info(SystemInfo& sys);
char * memory_info();

void table_names();
