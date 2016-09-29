#include <lib.h>
#include <unistd.h>

int get_plog_byindex(int index, long* c_time, long* t_time){
	message m;
	m.m1_p1 = index;
	m.m1_p2 = c_time;
	m.m1_p3 = t_time;
	return _syscall(PM_PROC_NR, GET_PLOG_BYINDEX, &m);
}
