#include <ncurses.h>
#include "colors.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "blocks.h"


void game_loop(int * input_key);
void draw();
void draw_base();
void draw_blocks();
void tick(tetromino * t, world* w);