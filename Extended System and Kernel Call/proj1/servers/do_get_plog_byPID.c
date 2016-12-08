#include <stdio.h>
#include "Buffer.h"
#include "pm.h"

struct Buffer buff[1024];
int curr_index;
int on_off;

int do_get_plog_byPID(){

	int this_pid = (int)m_in.m1_i1;
	long* c_t = (long *)m_in.m1_i2;
	long* t_t = (long *)m_in.m1_i3;
	for(int i=0; i<curr_index; i++){

		if(this_pid == buff[i].this_pid) {
			
			// get time and put in the address passed in
			*c_t = buff[i].c_time;
			*t_t = buff[i].t_time;
			
			return 0; // Found that pid
		}
	}
	// Not found
	return 2;
}

