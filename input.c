#include "input.h"

void *input_handler(void * arg){
	int * input_key = (int*)arg;
	int key=0;
	while(1){
		key=getch();
		if(key=='e' || key=='q' || key==27){//27=ESC
			*input_key=-2;
			break;
		}
		*input_key=key;
	}
	
	pthread_exit(NULL);
}