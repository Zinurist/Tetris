#include "colors.h"
#include <stdint.h>

#define block 1
#define air 0

#define width 10
#define height 22 

typedef uint32_t cell; // left 16 bit = visible?, right 16 bit = color, use macros below

#define VISIBLE(c) (c&0xFFFF0000)
#define COLOR(c) (c&0x0000FFFF)
#define MAKE_VISIBLE(c) (c|0x0001FFFF)
#define MAKE_INVISIBLE(c) (c&0x0000FFFF)//same as color for now

typedef struct{
	int points;
	cell field[width][height];
} world;

typedef struct{
	cell field[4][4];
	int x,y;
} tetromino;



int go_down(tetromino * t, world * w);
int go_left(tetromino * t, world * w);
int go_right(tetromino * t, world * w);

tetromino * create_tetromino(int type, int x, int y);


//FIELDS for tetrominos

static const cell t1[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};