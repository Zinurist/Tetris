#include "tetris.h"

int main(){
	//http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
	initscr();
	clear();
	cbreak();
	noecho();
	curs_set(0);
	
	//color error messages & exit, TODO no-color mode?
	if(!has_colors()){endwin();printf("no colors, exiting...\n");return -1;}
	start_color();
	use_default_colors();
	init_colors();
	
	keypad(stdscr,1);
	
	init_game();
	
	endwin();
	return 0;
}

void init_game(){
	int input_key;
	struct pthread_t loop_thread, input_thread;
	//input_handler(&input_key);
	game_loop(&input_key);
}

void game_loop(int * input_key){
	struct timeval *begin, *end, *tmp;
	unsigned long diff;//in us
	int key=-1; //for temporary storage of input_key, b/c of race conditions
	
	begin=malloc(sizeof(struct timeval));
	end=malloc(sizeof(struct timeval));
	gettimeofday(begin, NULL);
	diff=0;
	
	draw();
	while(key!='e' && key!='q' && key!=27){//27=ESC
		//input
		key=*input_key;
		if(key!=-1){
			switch(key){
			case KEY_UP: 	;break;
			case KEY_DOWN:	;break;
			case KEY_LEFT: 	;break;
			case KEY_RIGHT: ;break;
			default: break;
			}
			key=-1;//input read->reset
		}
		
		//game tick & time
		gettimeofday(end, NULL);
		diff+=(end->tv_sec-begin->tv_sec)*1000000 + end->tv_usec-begin->tv_usec;
		tmp=begin;
		begin=end;
		end=tmp;
		
		if(diff>=1000000){
			diff-=1000000;
			//tick
		}
		
		//gui update
		draw();
		
		//sleep
		usleep(50*1000);
	}
}

void input_handler(int * input_key){
	while(1){
		*input_key=getch();
	}
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

void init_colors(){
	//colors: white, black, red, blue, green, yellow, cyan, magenta
	init_pair(WHITE, 	COLOR_WHITE, 	-1);
	init_pair(BLACK, 	COLOR_BLACK, 	-1);
	init_pair(RED, 		COLOR_RED, 		-1);
	init_pair(BLUE, 	COLOR_BLUE, 	-1);
	init_pair(GREEN, 	COLOR_GREEN, 	-1);
	init_pair(YELLOW, 	COLOR_YELLOW, 	-1);
	init_pair(CYAN, 	COLOR_CYAN, 	-1);
	init_pair(MAGENTA, 	COLOR_MAGENTA, 	-1);
	//for background/drawing blocks
	init_pair(E_WHITE, 	-1,COLOR_WHITE);
	init_pair(E_BLACK, 	-1,COLOR_BLACK);
	init_pair(E_RED, 	-1,COLOR_RED);
	init_pair(E_BLUE, 	-1,COLOR_BLUE);
	init_pair(E_GREEN, 	-1,COLOR_GREEN);
	init_pair(E_YELLOW, -1,COLOR_YELLOW);
	init_pair(E_CYAN, 	-1,COLOR_CYAN);
	init_pair(E_MAGENTA,-1,COLOR_MAGENTA);
}

