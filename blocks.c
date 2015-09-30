#include "blocks.h"


int go_down(tetromino * t, world_data * w){
	t->y++;
	if(t->y+t->height > WORLD_HEIGHT || check_collision(t,w)){//TODO do not use y, but lowest block in tetromino
		t->y--;
		return 1;
	}
	return 0;
}

int go_left(tetromino * t, world_data * w){
	t->x--;
	if(t->x < 0 || check_collision(t,w)){//using x is ok, unless tetros arent aligned to the left side!!
		t->x++;
		return 1;
	}
	return 0;
}

int go_right(tetromino * t, world_data * w){
	t->x++;
	if(t->x+t->width > WORLD_WIDTH || check_collision(t,w)){//TODO do not use x, but most right block in tetromino
		t->x--;
		return 1;
	}
	return 0;
}


int check_collision(tetromino * t, world_data * w){
	int block_t, block_w;
	int sx = t->x;
	int sy = t->y;
	for(int x = 0; x < t->width; x++ ){
		for(int y = 0; y < t->height; y++ ){
			block_t = t->field[x][y];
			block_w = w->field[x+sx][y+sy];
			
			if( VISIBLE(block_t) && VISIBLE(block_w) ){
				return 1;
			}
		}
	}
	
	return 0;
}


void write_to_world(tetromino * t, world_data * w){
	int block_t;
	int sx = t->x;
	int sy = t->y;
	for(int x = 0; x < t->width; x++ ){
		for(int y = 0; y < t->height; y++ ){
			block_t = t->field[x][y];
			
			if( VISIBLE(block_t) ){
				w->field[x+sx][y+sy] = block_t;
				
				if(y+sy < w->top_line){
					w->top_line = y+sy;
				}
			}
		}
	}
}


void fill_tetromino(tetromino * t, int type){
	t->visible = 1;
	t->y = 0;
	const cell (*field)[TETROMINO_HEIGHT];
	switch(type){
		case 0:
			field = t_L;
			t->x = WORLD_WIDTH/2-2;
			t->width = 3;
			t->height = 2;
			break;
		case 1:
			field = t_J;
			t->x = WORLD_WIDTH/2-2;
			t->width = 3;
			t->height = 2;
			break;
		case 2:
			field = t_Z;
			t->x = WORLD_WIDTH/2-2;
			t->width = 3;
			t->height = 2;
			break;
		case 3:
			field = t_S;
			t->x = WORLD_WIDTH/2-2;
			t->width = 3;
			t->height = 2;
			break;
		case 4:
			field = t_I;
			t->x = WORLD_WIDTH/2-1;
			t->width = 1;
			t->height = 4;
			break;
		case 5:
			field = t_O;
			t->x = WORLD_WIDTH/2-1;
			t->width = 2;
			t->height = 2;
			break;
		default: //= case 6 and any other number, "error handling"
			field = t_T;
			t->x = WORLD_WIDTH/2-2;
			t->width = 3;
			t->height = 2;
			break;
	}
	
	for(int i = 0; i < TETROMINO_WIDTH; i++){
		for(int k = 0; k < TETROMINO_HEIGHT; k++){
			t->field[i][k] = field[i][k];
		}
	}
}





//TETROMINOS
const cell t_L[TETROMINO_WIDTH][TETROMINO_HEIGHT] = {
{MAKE_VISIBLE(E_YELLOW),MAKE_VISIBLE(E_YELLOW),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_YELLOW),MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_YELLOW),MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)}
};

const cell t_J[TETROMINO_WIDTH][TETROMINO_HEIGHT] = {
{MAKE_VISIBLE(E_BLUE),	MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_BLUE),	MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_BLUE),	MAKE_VISIBLE(E_BLUE),MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1)}
};

const cell t_Z[TETROMINO_WIDTH][TETROMINO_HEIGHT] = {
{MAKE_VISIBLE(E_GREEN),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_GREEN),	MAKE_VISIBLE(E_GREEN),	MAKE_INVISIBLE(1),	MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_VISIBLE(E_GREEN),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)}
};

const cell t_S[TETROMINO_WIDTH][TETROMINO_HEIGHT] = {
{MAKE_INVISIBLE(1),		MAKE_VISIBLE(E_RED),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_RED),	MAKE_VISIBLE(E_RED),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_RED),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)}
};

const cell t_I[TETROMINO_WIDTH][TETROMINO_HEIGHT] = {
{MAKE_VISIBLE(E_CYAN),	MAKE_VISIBLE(E_CYAN),	MAKE_VISIBLE(E_CYAN),	MAKE_VISIBLE(E_CYAN)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)}
};

const cell t_O[TETROMINO_WIDTH][TETROMINO_HEIGHT] = {
{MAKE_VISIBLE(E_WHITE),	MAKE_VISIBLE(E_WHITE),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_WHITE),	MAKE_VISIBLE(E_WHITE),	MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)}
};

const cell t_T[TETROMINO_WIDTH][TETROMINO_HEIGHT] = {
{MAKE_VISIBLE(E_MAGENTA),MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_MAGENTA),MAKE_VISIBLE(E_MAGENTA),MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_VISIBLE(E_MAGENTA),MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)},
{MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1),		MAKE_INVISIBLE(1)}
};