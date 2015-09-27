#include "colors.h"

#define block 1
#define air 0

struct world{
	int width, height;
	struct tetromino ** tets;
};

struct tetromino{
	char field[4][4];
	int color;
	int x,y;
	void (*go_left)(struct world * w);
	void (*go_right)(struct world * w);
	void (*go_down)(struct world * w);
};
