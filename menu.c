#include "menu.h"

char* options[] = {
	"Play", "New Game", "Settings", "Exit", "spooky dont click"
};

void menu(int * input_key){
	int selection = 0;
	int key = -1;
	while(1){
		key = *input_key;
		if(key == -2){
			break;
		}else if (key != -1){
			*input_key = -1;//input read->reset
			switch(key){
			case KEY_UP: 	selection = (selection+1)%ARRAY_SIZE(options);break;
			case KEY_DOWN: 	selection = (selection-1)%ARRAY_SIZE(options);break;
			case KEY_ENTER:	activate_selection();break;
			default: break;
			}

			draw_menu(selection);
		}
	}
}

void activate_selection(){

}

void draw_menu(int selection){
	clear();
	attrset(C(WHITE));
	for(int i=0; i<ARRAY_SIZE(options); i++){
		move(i,0);
		if(selection==i){
			attrset(C(YELLOW));
			printw(options[i]);
			attrset(C(WHITE));
		}else{
			printw(options[i]);
		}
	}
}