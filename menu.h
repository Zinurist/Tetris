#pragma once

#include <ncurses.h>
#include "colors.h"
#include <unistd.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void menu(int * input_key);
void activate_selection(int selection);
void draw_menu(int selection);

//extern char* options[]; 