#include "syslib.h"

int sys_plog(pid_t pid)
pid_t pid;
{
	message m;
	m.m7_i1 = pid;
	return(_kernel_call(SYS_PLOG, &m));
}
