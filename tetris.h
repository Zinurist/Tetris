#include <ncurses.h>
#include "colors.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "blocks.h"


void *game_loop(void * arg);
void draw();
void draw_base();
void draw_blocks();