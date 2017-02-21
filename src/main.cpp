/**
 * Contains the main() routine of what will eventually be your version of top.
 */

#include <cstdlib>
#include <ncurses.h>
#include "../src/utils/format.h"

using namespace std;


/**
 * Gets a character from the user, waiting for however many milliseconds that
 * were passed to timeout() below. If the letter entered is q, this method will
 * exit the program.
 */
void exit_if_user_presses_q() {
  char c = getch();

  if (c == 'q') {
    endwin();
    exit(EXIT_SUCCESS);
  }
}


/**
 * Entry point for the program.
 */
int main() {
  // ncurses initialization
  initscr();

  // Don't show a cursor.
  curs_set(FALSE);

  // Set getch to return after 1000 milliseconds; this allows the program to
  // immediately respond to user input while not blocking indefinitely.
  timeout(1000);

  while (true) {
    wclear(stdscr);

    SystemInfo current_sys = get_system_info();
    uptime_info(current_sys.uptime);
    printw("\n");
    loadavg_info(current_sys.load_average);
    printw("\n");
    proc_info(current_sys);
    printw("\n");
    thread_info(current_sys);
    printw("\n");
    memory_info();
    printw("\n");
    table_names();

    // for (ProcessInfo temp: current_sys.processes){
    // printw("\n");
    // table_info(temp);
    // }
      
    
    // Redraw the screen.
    refresh();

    // End the loop and exit if Q is pressed
    exit_if_user_presses_q();
  }

  // ncurses teardown
  endwin();

  return EXIT_SUCCESS;
}
