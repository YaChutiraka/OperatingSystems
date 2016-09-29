#include <lib.h>
#include <unistd.h>

void start_plog(void){

	message m;
	_syscall(PM_PROC_NR, START_PLOG, &m);
}
