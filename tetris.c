#include "tetris.h"


void *game_loop(void * arg){
	//game data
	world * w =malloc(sizeof(world));
	tetromino * current_tetromino = create_tetromino(0,0,0);
	
	//control data
	int * input_key = (int*)arg;
	struct timeval *begin, *end, *tmp;
	unsigned long diff;//in us
	int key=27; //for temporary storage of input_key, b/c of race conditions
				//initialized with 27 to go to menu immediately
	
	begin=malloc(sizeof(struct timeval));
	end=malloc(sizeof(struct timeval));
	gettimeofday(begin, NULL);
	diff=0;
	
	draw();
	while(1){
		//input
		key=*input_key;
		if(key==-2){
			break;
		}else if(key==27){
			menu();
		}else if(key!=-1){
			*input_key=-1;//input read->reset
			switch(key){//TODO move block
			case KEY_UP: 	;break;//do nothin
			case KEY_DOWN:	;break;
			case KEY_LEFT: 	;break;
			case KEY_RIGHT: ;break;
			default: break;
			}
		}
		
		//game tick & time
		gettimeofday(end, NULL);
		diff+=(end->tv_sec-begin->tv_sec)*1000000 + end->tv_usec-begin->tv_usec;
		tmp=begin;
		begin=end;
		end=tmp;
		
		if(diff>=1000000){
			diff-=1000000;
			tick(current_tetromino, w);
		}
		
		//gui update
		draw();
		
		//sleep
		usleep(50*1000);
	}
	
	pthread_exit(NULL);
}

void draw(){
	draw_base();
	draw_blocks();
	refresh();
}

void draw_base(){
	clear();
	move(0,0);
	attrset(C(WHITE));
	printw("Tetris");
	
	attrset(C(E_WHITE));
	move(2,2);
	printw("                     ");
	move(20,2);
	printw("                     ");
	for(int i=3; i<20; i++){
		mvaddch(i,2,' ');
		mvaddch(i,22,' ');
	}
	
	
	attrset(C(WHITE));
}

void draw_blocks(){
	
}


void tick(tetromino * t, world* w){
	//TODO fall down (and add tetromino to world if at bottom)
	//TODO check for rows
	//TODO create new tetromino
}
