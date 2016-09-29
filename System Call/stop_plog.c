#include <lib.h>
#include <unistd.h>

void stop_plog(){
	message m;
	_syscall(PM_PROC_NR, STOP_PLOG, &m);
}
