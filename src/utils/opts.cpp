#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "opts.h"
#include <ncurses.h>

struct progopts opts;

/**
 * print help
 */
void opts_help(char **argv, int exit_status) {

  printf("This program is an implemtation of the top command. The flag -d or --delay followed by an integer will cause a delay in updates of that many seconds. The flag -s or --sort-key can sort the table by the following: PID, CPU, MEM, or TIME. The flag -h or --help shows you this window." );
  
    exit(exit_status);
}

/**
 * initialize opts from argc and argv
 */
void opts_init(int argc, char **argv) {
    const static struct option longopts[] = {
        {"delay", required_argument, NULL, 'd'},
        {"sort-key", required_argument, NULL, 's'},
        {"max-proc", required_argument, NULL, 'm'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };
    opts.delay_tenths = 10;
    opts.sort_key = CPU;
    opts.max_proc = 0;
    int i, optchar;
    while ((optchar = getopt_long(argc, argv, "d:s:m:h", longopts, &i)) != -1) {
        switch (optchar) {
            case 0:
                break;
            case 'm':
                sscanf(optarg, "%d", &opts.max_proc);
                break;
            case 'd':
                sscanf(optarg, "%d", &opts.delay_tenths);
                if (opts.delay_tenths < 1) {
                    fprintf(stderr, "Delay too small!\n\n");
                    opts_help(argv, 2);
                }
                break;
            case 's':
                if (!strcmp(optarg, "PID")) {
                    opts.sort_key = PID;
                    break;
                }
                if (!strcmp(optarg, "CPU")) {
                    opts.sort_key = CPU;
                    break;
                }
                if (!strcmp(optarg, "MEM")) {
                    opts.sort_key = MEM;
                    break;
                }
                if (!strcmp(optarg, "TIME")) {
                    opts.sort_key = TIME;
                    break;
                }
                printf("Unknown option for sort-key!\n\n");
                opts_help(argv, 2);
            case 'h':
                opts_help(argv, 0);
            default:
                printf("Unknown option\n\n");
                opts_help(argv, 2);
        }
    }
}
