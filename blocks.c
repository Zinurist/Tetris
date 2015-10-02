#include "blocks.h"


int go_down(tetromino * t, world_data * w){
	t->y++;
	if(t->y+t->height > WORLD_HEIGHT || check_collision(t,w)){
		t->y--;
		return 1;
	}
	return 0;
}

int go_left(tetromino * t, world_data * w){
	t->x--;
	if(t->x < 0 || check_collision(t,w)){
		t->x++;
		return 1;
	}
	return 0;
}

int go_right(tetromino * t, world_data * w){
	t->x++;
	if(t->x+t->width > WORLD_WIDTH || check_collision(t,w)){
		t->x--;
		return 1;
	}
	return 0;
}

tetromino rotate_tmp;

int rotate(tetromino * t, world_data * w, int left){
	rotate_tmp.x = t->x;
	rotate_tmp.y = t->y;
	empty_tetromino_field(&rotate_tmp);
	
	int max_size = t->width > t->height ? t->width:t->height;
	if(max_size == 2) return 0;//square piece
	else if(max_size == 4){//I piece 
		//OXXX
		//OXXX
		//OXXX
		//OXXX
		//to:
		//XXXX
		//OOOO
		//XXXX
		//XXXX
		//with x--
		if(VISIBLE(t->field[0][0])){//I -> _
			rotate_tmp.x--;//because of bad positioning: IXXX, but should be XIXX, XIXX fucks up go_left though
			for(int i = 0; i < TETROMINO_WIDTH; i++){
				rotate_tmp.field[i][1] = MAKE_VISIBLE(E_CYAN);
			}
			rotate_tmp.width = 4;
			rotate_tmp.height = 2;
		}else{//_ -> I
			fill_tetromino(&rotate_tmp, 4);
			rotate_tmp.x = t->x+1;
			rotate_tmp.y = t->y;
			rotate_tmp.width = 1;
			rotate_tmp.height = 4;
			
		}
	}else{//other pieces
		//123
		//804
		//765
		//to:
		//781
		//602
		//543 (or other way round, depending on left=1/0)
		rotate_tmp.field[1][1] = t->field[1][1]; //middle unchanged
		if(left){
			rotate_tmp.field[0][0] = t->field[2][0];
			rotate_tmp.field[1][0] = t->field[2][1];
			rotate_tmp.field[2][0] = t->field[2][2];
			rotate_tmp.field[2][1] = t->field[1][2];
			rotate_tmp.field[2][2] = t->field[0][2];
			rotate_tmp.field[1][2] = t->field[0][1];
			rotate_tmp.field[0][2] = t->field[0][0];
			rotate_tmp.field[0][1] = t->field[1][0];
		}else{
			rotate_tmp.field[0][0] = t->field[0][2];
			rotate_tmp.field[1][0] = t->field[0][1];
			rotate_tmp.field[2][0] = t->field[0][0];
			rotate_tmp.field[2][1] = t->field[1][0];
			rotate_tmp.field[2][2] = t->field[2][0];
			rotate_tmp.field[1][2] = t->field[2][1];
			rotate_tmp.field[0][2] = t->field[2][2];
			rotate_tmp.field[0][1] = t->field[1][2];
		}
		rotate_tmp.width = t->height;
		rotate_tmp.height = t->width;
		//change x/y accordingly
		//important: double parantheses because of macro!
		
		//first row empty
		if( !VISIBLE((rotate_tmp.field[0][0] | rotate_tmp.field[0][1] | rotate_tmp.field[0][2]))  ){
			if(left) rotate_tmp.x++;
			//move rows by one to the left (and around)
			//dont worry about bounds, it's 4*4 after all
			for(int i = 0; i < 3; i++){
				rotate_tmp.field[i][0] = rotate_tmp.field[i+1][0];
				rotate_tmp.field[i][1] = rotate_tmp.field[i+1][1];
				rotate_tmp.field[i][2] = rotate_tmp.field[i+1][2];
			}
		}
		
		//first line empty
		if( !VISIBLE((rotate_tmp.field[0][0] | rotate_tmp.field[1][0] | rotate_tmp.field[2][0]))  ){
			if(!left) rotate_tmp.y++;
			//move lines by one to the top (and around)
			for(int i = 0; i < 3; i++){
				rotate_tmp.field[0][i] = rotate_tmp.field[0][i+1];
				rotate_tmp.field[1][i] = rotate_tmp.field[1][i+1];
				rotate_tmp.field[2][i] = rotate_tmp.field[2][i+1];
			}
		}
	}
	
	if(check_collision(&rotate_tmp,w) || check_boundaries(&rotate_tmp)){
		return 1;
	}
	
	copy_tetromino(t, &rotate_tmp);
	return 0;
}

void copy_tetromino(tetromino * dst, tetromino * src){
	dst->x = src->x;
	dst->y = src->y;
	dst->width = src->width;
	dst->height = src->height;
	for(int i = 0; i < TETROMINO_WIDTH; i++){
		for(int k = 0; k < TETROMINO_HEIGHT; k++){
			dst->field[i][k] = src->field[i][k];
		}
	}
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

int check_boundaries(tetromino * t){
	if(t->x < 0) return 1;
	if(t->x+t->width > WORLD_WIDTH) return 1;
	if(t->y+t->height > WORLD_HEIGHT) return 1;
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

void empty_tetromino_field(tetromino * t){
	for(int i = 0; i < TETROMINO_WIDTH; i++){
		for(int k = 0; k < TETROMINO_HEIGHT; k++){
			t->field[i][k] = MAKE_INVISIBLE(1);
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