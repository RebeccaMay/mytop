#include "system_info.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unordered_map>

using namespace std;


double get_uptime() {
  // TODO: implement me

	FILE *filename = fopen(PROC_ROOT "/uptime", "r");
	

	if (!filename){
		cerr << "Can not get /uptime" << endl;
		exit(1);
	}

	double ut;

	fscanf(filename, "%lf", &ut);

	//close file after uptime is gotten
	fclose(filename);

	return ut;
}


SystemInfo get_system_info() {
  // TODO: implement me
	SystemInfo sysi;

	FILE *filep = fopen(PROC_ROOT "/stat", "r");
	if (ferror(filep)) {
		cerr << "Unable to open /stat" << endl;
	}

	//declare character array to hold processes
	char item[25];
	while(!feof(filep) && !ferror(filep)){
		fscanf(filep, "%s", item);

		if(!strcmp(item, "procs_running")){
			fscanf(filep, "%u", &sysi.num_running);
		}

		fscanf(filep, "%*[^\n]");
	}

	fclose(filep);

	//Call previously populated functions
	sysi.load_average = get_load_average();
	sysi.cpus = get_cpu_info();
	sysi.memory_info = get_memory_info();
	sysi.processes = get_all_processes(PROC_ROOT);
	sysi.uptime = get_uptime();
	sysi.num_processes = sysi.processes.size();

	//set initial values to 0
	sysi.num_kernel_threads = 0;
	sysi.num_user_threads = 0;
	for (ProcessInfo proc: sysi.processes){
		for (ProcessInfo th: proc.threads){
			if (th.is_user_thread()) sysi.num_user_threads++;
			else if (th.is_kernel_thread()) sysi.num_kernel_threads++;
		}
	}

	//add user and kernel threaads for total threads
	sysi.num_threads = sysi.num_user_threads + sysi.num_kernel_threads;

  return sysi;
}



