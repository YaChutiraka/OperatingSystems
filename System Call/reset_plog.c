#include <lib.h>
#include <unistd.h>

void reset_plog(){
	message m;
	_syscall(PM_PROC_NR, RESET_PLOG, &m);
}
