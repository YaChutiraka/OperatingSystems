#include <stdio.h>
#include "Buffer.h"

struct Buffer buff[1024];
int on_off;
int curr_index;

void do_stop_plog(){
	//TESTED
	on_off = 0;
	return;
}

