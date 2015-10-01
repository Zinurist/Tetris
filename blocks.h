#pragma once

#include "colors.h"
#include <stdint.h>
#include <stdlib.h>

#define NUM_OF_TYPES 7//tetromino types

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 22 
#define TETROMINO_WIDTH 4
#define TETROMINO_HEIGHT 4

typedef uint32_t cell; // left 16 bit = visible?, right 16 bit = color, use macros below

#define VISIBLE(c) (c&0xFFFF0000)
#define COLOR(c) (c&0x0000FFFF)
#define MAKE_VISIBLE(c) (c|0x00010000)
#define MAKE_INVISIBLE(c) (c&0x0000FFFF)//same as color for now

typedef struct{
	int points, top_line, lines_removed;
	cell field[WORLD_WIDTH][WORLD_HEIGHT];
} world_data;

typedef struct{
	int x,y,width,height,visible;
	cell field[TETROMINO_WIDTH][TETROMINO_HEIGHT];
} tetromino;



int go_down(tetromino * t, world_data * w);
int go_left(tetromino * t, world_data * w);
int go_right(tetromino * t, world_data * w);

int rotate_left(tetromino * t, world_data * w);
int rotate_right(tetromino * t, world_data * w);

int check_collision(tetromino * t, world_data * w);

void write_to_world(tetromino * t, world_data * w);

//type range: 0-6 (7 tetrominos)
void fill_tetromino(tetromino * t, int type);

void copy_field(tetromino * dst, tetromino * src);


//FIELDS for tetrominos
//static: dont tell linker, use only here
//extern: tell linker for others to use, define array in .c file!

extern const cell t_L[TETROMINO_WIDTH][TETROMINO_HEIGHT];

extern const cell t_J[TETROMINO_WIDTH][TETROMINO_HEIGHT];

extern const cell t_Z[TETROMINO_WIDTH][TETROMINO_HEIGHT];

extern const cell t_S[TETROMINO_WIDTH][TETROMINO_HEIGHT];

extern const cell t_I[TETROMINO_WIDTH][TETROMINO_HEIGHT];

extern const cell t_O[TETROMINO_WIDTH][TETROMINO_HEIGHT];

extern const cell t_T[TETROMINO_WIDTH][TETROMINO_HEIGHT];
