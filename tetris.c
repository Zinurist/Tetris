#include "tetris.h"

world_data world;
tetromino current_tetromino;
unsigned long tick_time;

void init_game(){
	world.points = 0;
	world.top_line = WORLD_HEIGHT;
	for(int x = 0; x < WORLD_WIDTH; x++){
		for(int y = 0; y < WORLD_HEIGHT; y++){
			world.field[x][y] = MAKE_INVISIBLE(0);
		}
	}
	fill_tetromino(&current_tetromino,rand()%7);
	tick_time = 700000;
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
			case KEY_DOWN:	
				reached_bottom = go_down(&current_tetromino, &world);
				break;
			case KEY_LEFT: 	
				if(!reached_bottom){
					go_left(&current_tetromino, &world);
				}
				break;
			case KEY_RIGHT: 
				if(!reached_bottom){
					go_right(&current_tetromino, &world);
				}
				break;
			case 27: /*ESC*/
				menu(input_key); 
				break;
			case 32: /*Space*/
				while(!go_down(&current_tetromino, &world));
				reached_bottom=1;
				diff=tick_time;
				break;
			case -2: 		
				free(begin);
				free(end);
				return;
			default: break;
			}
		}
		
		//game tick & time
		gettimeofday(end, NULL);
		diff+=(end->tv_sec-begin->tv_sec)*1000000 + end->tv_usec-begin->tv_usec;
		tmp=begin;
		begin=end;
		end=tmp;
		
		if(diff >= tick_time){
			diff -= tick_time;
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
	printw("Tetris     Points: %d", world.points);
	
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
	if(current_tetromino.visible){
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
}


void tick(int * reached_bottom){
	static int filled_lines[4];
	static int counter = 0;
	
	if(*reached_bottom){
		//new piece reached the bottom or gravity activated and things need to be rechecked
		*reached_bottom = 0;
		
		if(counter == 0){//only if call is not coming from gravity stuff
			write_to_world(&current_tetromino, &world);
		}
		
		counter = 0;
		//check for lines right here & gravity
		for(int i = WORLD_HEIGHT-1; i >= world.top_line; i--){
			if(check_line(i)){
				fill_line(i);
				filled_lines[counter] = i;
				counter++;
			}
		}
		
		world.points += 100*counter*counter;
		
		if(counter == 0){
			fill_tetromino(&current_tetromino,rand()%7);
		
			if(check_collision(&current_tetromino, &world)){
				//GAME OVER
				init_game();
			}
		}else{
			current_tetromino.visible = 0;//dont display it while removing lines
		}
		
	}else if(counter != 0){
		//lines to remove, gravity to activate
		//remove from top to bottom
		for(int i = counter-1; i >= 0; i--){
			remove_line(filled_lines[i]);
		}
		
		*reached_bottom = 1;
	}else{
		//just a normal turn, m8
		*reached_bottom = go_down(&current_tetromino, &world);//in the next tick: block is placed
	}
	
}

int check_line(int line){
	int block;
	for(int i = 0; i < WORLD_WIDTH; i++){
		block = world.field[i][line];
		
		if(!VISIBLE(block)){
			return 0;
		}
	}
	return 1;
}

void fill_line(int line){
	for(int i = 0; i < WORLD_WIDTH; i++){
		world.field[i][line] = MAKE_VISIBLE(E_WHITE);
	}
}

void remove_line(int start_line){
	//bottom to top: copy line above to current one
	for(int line = start_line; line > world.top_line; line--){
		for(int i = 0; i < WORLD_WIDTH; i++){
			world.field[i][line] = world.field[i][line-1];
		}
	}
	
	for(int i = 0; i < WORLD_WIDTH; i++){
		world.field[i][world.top_line] = MAKE_INVISIBLE(1);
	}
	
	world.top_line--;
}
