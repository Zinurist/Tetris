#include "menu.h"

char* options[] = {
	"Play", "New Game", "Settings", "Exit", "spooky dont click"
};

void menu(int * input_key){
	int selection = 0;
	int key = 0;
	clear();
	draw_menu(selection);
	while(1){
		key = *input_key;
		if(key == -2){
			break;
		}else if (key != -1){
			*input_key = -1;//input read->reset
			switch(key){
			case KEY_UP: 	selection = (selection-1)%(ARRAY_SIZE(options));break;
			case KEY_DOWN: 	selection = (selection+1)%(ARRAY_SIZE(options));break;
			case KEY_ENTER:	activate_selection(selection);break;
			case 27: return;/*ESC*/
			default: break;
			}

			draw_menu(selection);
		}

		usleep(50*1000);
	}
}

void activate_selection(int selection){
	switch(selection){
		case 0:break;//Play
		case 1:break;//New Game
		case 2:break;//Settings
		case 3:break;//Exit
		case 4:break;//spooky dont click
	}
}

void draw_menu(int selection){
	attrset(C(WHITE));
	for(int i=0; i<ARRAY_SIZE(options); i++){
		move(i,0);
		if(selection == i){
			attrset(C(YELLOW));
			printw(options[i]);
			attrset(C(WHITE));
		}else{
			printw(options[i]);
		}
	}
	refresh();
}