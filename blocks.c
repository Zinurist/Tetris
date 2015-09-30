#include "blocks.h"


int go_down(tetromino * t, world * w){
	
	return 0;
}

int go_left(tetromino * t, world * w){
	
	return 0;
}

int go_right(tetromino * t, world * w){
	
	return 0;
}


tetromino * create_tetromino(int type, int x, int y){
	tetromino * new_t=malloc(sizeof(tetromino));
	
	new_t->x=x;
	new_t->y=y;
	
	switch(type){
		
	}
	
	return new_t;
}