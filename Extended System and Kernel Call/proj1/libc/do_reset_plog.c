#include <stdio.h>
#include "Buffer.h"

struct Buffer buff[1024];
int curr_index;
int on_off;

void do_reset_plog(){

	curr_index = 0;
	return;
}

