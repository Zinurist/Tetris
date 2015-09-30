#include "tetris.h"

world_data * world;
tetromino * current_tetromino;

void init_game(){
	world = malloc(sizeof(world_data));
	current_tetromino = create_tetromino(2,1,1);
}

void game_loop(int * input_key){
	//init game data
	init_game();
	
	//control data
	struct timeval *begin, *end, *tmp;
	unsigned long diff;//in us
	int key = 0; //for temporary storage of input_key, b/c of race conditions
	
	begin=malloc(sizeof(struct timeval));
	end=malloc(sizeof(struct timeval));
	gettimeofday(begin, NULL);
	diff = 0;
	
	draw();
	while(1){
		//input
		key=*input_key;
		if(key != -1){
			*input_key = -1;//input read->reset
			switch(key){//TODO move block
			case KEY_UP: 	time_to_dance(5);break;//do nothin
			case KEY_DOWN:	;break;
			case KEY_LEFT: 	;break;
			case KEY_RIGHT: ;break;
			case 27: 		menu(input_key); break;
			case -2: 		return;
			default: break;
			}
		}
		
		//game tick & time
		gettimeofday(end, NULL);
		diff+=(end->tv_sec-begin->tv_sec)*1000000 + end->tv_usec-begin->tv_usec;
		tmp=begin;
		begin=end;
		end=tmp;
		
		if(diff >= 1000000){
			diff -= 1000000;
			tick();
		}
		
		//gui update
		draw();
		
		//sleep
		usleep(50*1000);
	}
}

void draw(){
	clear();
	draw_base();
	draw_world();
	draw_block();
	refresh();
}

void draw_base(){
	move(0,0);
	attrset(C(PURE_WHITE));
	printw("Tetris");
	
	attrset(C(E_WHITE));
	move(BOARD_START_Y,BOARD_START_X);
	printw("                        ");//(WORLD_WIDTH+2)*2 spaces, +2 because of border, *2 because of double block size
	move(1+BOARD_START_Y+WORLD_HEIGHT,BOARD_START_X);
	printw("                        ");
	for(int i = BOARD_START_Y+1; i < WORLD_HEIGHT+BOARD_START_Y+1; i++){
		mvprintw(i,BOARD_START_X,"  ");
		mvprintw(i, WORLD_WIDTH*2 + BOARD_START_X+2,"  ");
	}
}

void draw_world(){
	int block;
	for(int x = 0; x < WORLD_WIDTH; x++){
		for(int y = 0; y < WORLD_HEIGHT; y++){
			block = world->field[x][y];
			if( VISIBLE(block) ){
				attrset( C(COLOR(block)) );
				mvprintw(BOARD_START_Y+1+y, BOARD_START_X+2+x*2, "  ");
			}
			
		}
		
	}
}

void draw_block(){
	//startx/y
	int sx = current_tetromino->x;
	int sy = current_tetromino->y;
	int block;
	
	move(sy,sx);
	
	for(int x = 0; x < TETROMINO_WIDTH; x++ ){
		for(int y = 0; y < TETROMINO_HEIGHT; y++ ){
			block = current_tetromino->field[y][x];
			if( VISIBLE(block) ){
				attrset( C(COLOR(block)) );
				mvprintw(BOARD_START_Y+1+y+sy, BOARD_START_X+2+(x+sx)*2, "  ");
			}
		}
	}
}


void tick(){
	//TODO fall down (and add tetromino to world if at bottom)
	//TODO check for rows
	//TODO create new tetromino
}
