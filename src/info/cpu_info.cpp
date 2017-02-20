#include "cpu_info.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


vector<CpuInfo> get_cpu_info() {
  // TODO: implement me

	CpuInfo cpuInfo;

	//temp string to read in unnecessary information
	string temp;

	vector<CpuInfo> info;

	//update to PROC ROOT before submitting
	ifstream cpuInfo_file(PROC_ROOT "/stat");

	if (!cpuInfo_file){
		cerr << "Unable to reach /proc/stat" << endl;
	}

	cpuInfo_file >> temp;	

	while(temp[0] == 'c' && temp[1] == 'p'){ 	
	cpuInfo_file
		>> cpuInfo.user_time
		>> cpuInfo.nice_time
		>> cpuInfo.system_time
		>> cpuInfo.idle_time
		>> cpuInfo.io_wait_time
		>> cpuInfo.irq_time
		>> cpuInfo.softirq_time
		>> cpuInfo.steal_time
		>> cpuInfo.guest_time
		>> cpuInfo.guest_nice_time;

		//add to vector of info
		info.push_back(cpuInfo);

		//read in beginning of next line to see if another cpu
		cpuInfo_file >> temp;
	}	

  return info;
}


CpuInfo operator -(const CpuInfo& lhs, const CpuInfo& rhs) {
  // TODO: implement me

	CpuInfo result;
	result.user_time = lhs.user_time - rhs.user_time;
	result.nice_time = lhs.nice_time - rhs.user_time;
	result.system_time = lhs.system_time - rhs.system_time;
	result.idle_time = lhs.idle_time - rhs.idle_time;
	result.io_wait_time = lhs.io_wait_time - rhs.io_wait_time;
	result.irq_time = lhs.irq_time - rhs.irq_time;
	result.softirq_time = lhs.softirq_time - rhs.softirq_time;
	result.steal_time = lhs.steal_time - rhs.steal_time;
	result.guest_time = lhs.guest_time - rhs.guest_time;
	result.guest_nice_time = lhs.guest_nice_time - rhs.guest_nice_time;
	
  return result;
}
