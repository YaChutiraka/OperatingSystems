#include <stdio.h>

extern struct Buffer{

	int this_pid;
	long c_time;
	long t_time;
};

extern struct Buffer buff[1024];
extern int on_off;
extern int curr_index;
