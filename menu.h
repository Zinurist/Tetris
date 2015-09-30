#pragma once

#include <ncurses.h>
#include "colors.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void menu(int * input_key);
void activate_selection();
void draw_menu();

//extern char* options[]; 