#include <ncurses.h>
#include <signal.h>
#include "tetris.h"
#include "input.h"

int init_threads(pthread_t * input_thread, pthread_t * loop_thread, int * input_key);
void init_colors();