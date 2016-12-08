#include <lib.h> // provides _syscall and message
#include <unistd.h>


int plog_state_stop(int PID) {
    message m;
    m.m7_i1 = PID;
	m.m7_i2 = 0; //onORoff
    int ret =_syscall(PM_PROC_NR, PLOG, &m);
    return ret;
}

int plog_state_start(int PID) {
    message m;
    m.m7_i1 = PID;
	m.m7_i2 = 1; // onORoff
    int ret = _syscall(PM_PROC_NR, PLOG, &m);
    return ret;
}

