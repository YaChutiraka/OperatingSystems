#include <lib.h>
#include <unistd.h>

int get_plog_byPID(int pid, long* c_time, long* t_time){
	message m;
	m.m1_i1 = pid;
	m.m1_i2 = c_time;
	m.m1_i3 = t_time;	

	return _syscall(PM_PROC_NR, GET_PLOG_BYPID, &m);
}
