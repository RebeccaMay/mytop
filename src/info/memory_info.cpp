#include "memory_info.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


MemoryInfo get_memory_info() {
  // TODO: implement me

	MemoryInfo memoryInfo;

	//set temp string to read in unnessary info, overwrite every time
	string temp = "";

	//Be sure to update with PROC ROOT
	ifstream memoryInfo_file(PROC_ROOT "/meminfo");

	if (!memoryInfo_file){
		cerr << "Unable to read from /proc/meminfo" << endl;
	}

	memoryInfo_file >> temp >> memoryInfo.total_memory >> temp;
	memoryInfo_file >> temp >> memoryInfo.free_memory >> temp;
	memoryInfo_file >> temp >> memoryInfo.buffers_memory >> temp;
	memoryInfo_file >> temp >> memoryInfo.cached_memory >> temp;
	
	//there are several unnessary lines in the code here
	for(int i = 0; i <= 8; i++){		
		memoryInfo_file >> temp >> temp >> temp;
	}
	
	memoryInfo_file >> temp >> memoryInfo.total_swap >> temp;		
	memoryInfo_file >> temp >> memoryInfo.free_swap;

	//close file
	memoryInfo_file.close();

  return memoryInfo;
}
