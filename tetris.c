#include "tetris.h"

world_data world;
tetromino current_tetromino;

void init_game(){
	world.points = 0;
	for(int x = 0; x < WORLD_WIDTH; x++){
		for(int y = 0; y < WORLD_HEIGHT; y++){
			world.field[x][y] = MAKE_INVISIBLE(0);
		}
	}
	fill_tetromino(&current_tetromino,rand()%7);
}

void game_loop(int * input_key){
	//init game data
	init_game();
	
	//control data
	struct timeval *begin, *end, *tmp;
	unsigned long diff;//in us
	int key = 0; //for temporary storage of input_key, b/c of race conditions
	int reached_bottom = 0;
	
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
			case KEY_DOWN:	reached_bottom = go_down(&current_tetromino, &world);break;
			case KEY_LEFT: 	go_left(&current_tetromino, &world);break;
			case KEY_RIGHT: go_right(&current_tetromino, &world);break;
			case 27: /*ESC*/menu(input_key); break;
			case 32: /*Space*/
				while(!go_down(&current_tetromino, &world));
				reached_bottom=1;
				break;
			case -2: 		free(begin);free(end);return;
			default: break;
			}
		}
		
		//game tick & time
		gettimeofday(end, NULL);
		diff+=(end->tv_sec-begin->tv_sec)*1000000 + end->tv_usec-begin->tv_usec;
		tmp=begin;
		begin=end;
		end=tmp;
		
		if(diff >= 700000){
			diff -= 700000;
			tick(&reached_bottom);
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
			block = world.field[x][y];
			if( VISIBLE(block) ){
				attrset( C(COLOR(block)) );
				mvprintw(BOARD_START_Y+1+y, BOARD_START_X+2+x*2, "  ");
			}
			
		}
		
	}
}

void draw_block(){
	//startx/y
	int sx = current_tetromino.x;
	int sy = current_tetromino.y;
	int block;
	
	move(sy,sx);
	
	for(int x = 0; x < current_tetromino.width; x++ ){
		for(int y = 0; y < current_tetromino.height; y++ ){
			block = current_tetromino.field[x][y];
			if( VISIBLE(block) ){
				attrset( C(COLOR(block)) );
				mvprintw(BOARD_START_Y+1+y+sy, BOARD_START_X+2+(x+sx)*2, "  ");
			}
		}
	}
}


void tick(int * reached_bottom){
	
	if(*reached_bottom){
		write_to_world(&current_tetromino, &world);
		
		//TODO check for lines right here
		
		fill_tetromino(&current_tetromino,rand()%7);
	}else{
		*reached_bottom = go_down(&current_tetromino, &world);//in the next tick: block is placed
	}
	
}
