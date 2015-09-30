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
	
	const cell * field;
	switch(type){
		case 0:
			field=t_L;
			break;
		case 1:
			field=t_J;
			break;
		case 2:
			field=t_Z;
			break;
		case 3:
			field=t_S;
			break;
		case 4:
			field=t_I;
			break;
		case 5:
			field=t_O;
			break;
		default: //= case 6 and any other number, "error handling"
			field=t_T;
			break;
	}
	
	memcpy(new_t->field, field, sizeof(cell)*TETROMINO_WIDTH*TETROMINO_HEIGHT );
	
	return new_t;
}