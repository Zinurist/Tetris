#pragma once

#include <ncurses.h>
#include "colors.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "blocks.h"
#include "menu.h"
#include "spooky.h"

#define BOARD_START_X 4
#define BOARD_START_Y 2

void game_loop(int * input_key);
void draw();
void draw_world();
void draw_base();
void draw_block();
void tick(tetromino * t, world* w);