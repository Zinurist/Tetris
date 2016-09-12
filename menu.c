#include "menu.h"

char* optionlist[] = {
	"Continue", "New Game", "Exit"
};

int options = ARRAY_SIZE(optionlist);

int menu(int * input_key){
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
			case KEY_UP:
				//shitty workaround for actual modulo operation in C
				selection = (((selection - 1) % options) + options) % options;break;
			case KEY_DOWN:
				selection = (((selection + 1) % options) + options) % options;break;
			case '\n':
				switch(selection){
					case 0:return 0;//Play
					case 1:return 1;//New Game
					case 2:return -1;//Exit
				}
				break;
			case 27:/*ESC*/
				return 0;
			default:
				break;
			}

			draw_menu(selection);
		}

		usleep(50 * 1000);
	}
	return 0;
}

void draw_menu(int selection){
	attrset(C(WHITE));
	for(int i = 0; i < options; i++){
		move(i,0);
		if(selection == i){
			attrset(C(YELLOW));
			printw(optionlist[i]);
			attrset(C(WHITE));
		}else{
			printw(optionlist[i]);
		}
	}
	refresh();
}