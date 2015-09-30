#include "main.h"

int main(){
	//http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
	initscr();
	clear();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr,1);
	
	//color error messages & exit, TODO no-color mode?
	if(!has_colors()){endwin();printf("no colors, exiting...\n");return -1;}
	start_color();
	use_default_colors();
	init_colors();
	
	int input_key = -1;//TODO change to 27
	pthread_t input_thread;
	
	if(pthread_create(&input_thread, NULL, input_handler, &input_key)){
		fprintf(stderr,"Error when creating input handler thread");
		return -1;
	}
	
	game_loop(&input_key);
	
	endwin();
	return 0;
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