#include "main.h"

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