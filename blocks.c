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
	
	cell **field;
	switch(type){
		case 0:
			field=(cell**)t_L;
			break;
		case 1:
			field=(cell**)t_J;
			break;
		case 2:
			field=(cell**)t_Z;
			break;
		case 3:
			field=(cell**)t_S;
			break;
		case 4:
			field=(cell**)t_I;
			break;
		case 5:
			field=(cell**)t_O;
			break;
		default: //= case 6 and any other number, "error handling"
			field=(cell**)t_T;
			break;
	}
	
	for(int i=0; i<TETROMINO_WIDTH; i++){
		for(int k=0; k<TETROMINO_HEIGHT; k++){
			new_t->field[i][k]=field[i][k];
		}
	}
	
	return new_t;
}