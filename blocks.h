#include "colors.h"

#define block 1
#define air 0

#define width 10
#define height 22 

typedef struct{
	int color;
	char visible;	
} cell;

typedef struct{
	cell field[width][height];
} world;

typedef struct{
	char field[4][4];
	int color;
	int x,y;
} tetromino;


int go_down(tetromino * t, world * w);
int go_left(tetromino * t, world * w);
int go_right(tetromino * t, world * w);