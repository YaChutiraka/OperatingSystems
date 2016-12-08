#include <stdio.h>
#include "Buffer.h"
#include "pm.h"

struct Buffer buff[1024];
int on_off;
int curr_index;

int do_get_plog_byindex(){

	//TEST	
	int idx = (int)m_in.m1_p1;
//alter	long c_t = (long)m_in.m1_p2;
//nativ	long t_t = (long)m_in.m1_p3;
	
	long* c_t = (long *)m_in.m1_p2;
	long* t_t = (long *)m_in.m1_p3; 

	//works
	//printf ("idx = %d \n", idx);

	if(idx >= curr_index || idx < 0){
		//TESTED
		return 3; // fail
	}else{

		// the created address now stores times		
		*c_t = buff[idx].c_time;
		*t_t = buff[idx].t_time;		
		//TESTED
		//printf("------PID at that index = %d\n", buff[idx].this_pid);
		return 0; // success
	}

}

