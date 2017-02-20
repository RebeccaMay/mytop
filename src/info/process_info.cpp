#include "process_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <vector>

using namespace std;

ProcessInfo get_process(int pid, const char* basedir) {
// TODO: implement me

	//declare ptr for stat file
	char *stat_file = (char *) alloca(strlen(basedir) + 18);
	sprintf(stat_file, "%s/%d/stat", basedir, pid);
	FILE *stat_fp = fopen(stat_file, "r");

	if (!stat_fp) {
        	return ProcessInfo();
	}
	
	//declare new ProcessInfo object to put in vector
	ProcessInfo pi;

	//scan in from file
	fscanf(stat_fp, "%d %s %c %d %d %d %d %d %u "\
		"%lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld "\
		"%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu "\
		"%d %d %u %u %llu %lu %ld",
		&(pi.pid),
		pi.comm,
		&(pi.state),
		&(pi.ppid),
		&(pi.pgrp),
		&(pi.session),
		&(pi.tty_nr),
		&(pi.tpgid),
		&(pi.flags),
		&(pi.minflt),
		&(pi.cminflt),
		&(pi.majflt),
		&(pi.cmajflt),
		&(pi.utime),
		&(pi.stime),
		&(pi.cutime),
		&(pi.cstime),
		&(pi.priority),
		&(pi.nice),
		&(pi.num_threads),
		&(pi.itrealvalue),
		&(pi.starttime),
		&(pi.vsize),
		&(pi.rss),
		&(pi.rsslim),
		&(pi.startcode),
		&(pi.endcode),
		&(pi.startstack),
		&(pi.kstkesp),
		&(pi.kstkeip),
		&(pi.signal),
		&(pi.blocked),
		&(pi.sigignore),
		&(pi.sigcatch),
		&(pi.wchan),
		&(pi.nswap),
		&(pi.cnswap),
		&(pi.exit_signal),
		&(pi.processor),
		&(pi.rt_priority),
		&(pi.policy),
		&(pi.delayacct_blkio_ticks),
		&(pi.guest_time),
		&(pi.cguest_time));
	//close file
    	fclose(stat_fp);

	//start same process over for statm file
	char *statm_fn = (char *) alloca(strlen(basedir) + 19);
	sprintf(statm_fn, "%s/%d/statm", basedir, pid);
	FILE *statm_fp = fopen(statm_fn, "r");

	if (!statm_fp) {
		return ProcessInfo();
	}
	
	fscanf(statm_fp, "%ld %ld %ld %ld %ld %ld %ld",
		&(pi.size),
		&(pi.resident),
		&(pi.share),
		&(pi.trs),
		&(pi.lrs),
		&(pi.drs),
		&(pi.dt));

	//close statm file
	fclose(statm_fp);

	//similar process for command line, which can be treated as a file
	char *cmdline_fn = (char *) alloca(strlen(basedir) + 21);
	sprintf(cmdline_fn, "%s/%d/cmdline", basedir, pid);
	FILE *cmdline_fp = fopen(cmdline_fn, "r");
	if (!cmdline_fp) {
		return ProcessInfo();
	}

	char c;
	while ((c = fgetc(cmdline_fp)) != EOF) {
		if (c) pi.command_line.push_back(c);
		else pi.command_line.push_back(' ');
	}

	if (!pi.command_line.length())
		pi.command_line = std::string(pi.comm + 1);
	pi.command_line.pop_back();

	//close command line
	fclose(cmdline_fp);

	//similar process again for task
	char *taskdir = (char *) alloca(strlen(basedir) + 18);
	sprintf(taskdir, "%s/%d/task", basedir, pid);
	pi.threads = get_all_processes(taskdir);

	for (size_t i = 0; i < pi.threads.size(); i++){
		pi.threads[i].tgid = pid;
	}

	return pi;
}


vector<ProcessInfo> get_all_processes(const char* basedir) {
// TODO: implement me

	DIR *temp;
	struct dirent *dirp;

	//if empty then return all the info we have as of now
	if ((temp = opendir(basedir)) == NULL) return vector<ProcessInfo>();
	
	//declare new vector to store all process Info object in	
	vector<ProcessInfo> pisvector;

	while ((dirp = readdir(temp)) != NULL) {

		for (char *p = dirp->d_name; *p; p++){
    			if (!isdigit(*p)) goto skip;
		}

		int pid;
		sscanf(dirp->d_name, "%d", &pid);

		//add to vector
		pisvector.push_back(get_process(pid, basedir));
	skip:
		//do nothing	
	;
	}	//end of while loop, because I'm bad at brackets

	//close file
	closedir(temp);

	return pisvector;
}
