#include <ncurses.h>
#include "colors.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>


void game_loop(int * input_key);
void input_handler(int * input_key);
void draw();
void draw_base();
void draw_blocks();
void init_colors();
void init_game();