#include <stdio.h>
#include "pm.h"
#include "mproc.h"

int do_printppid(){
	int idx = m_in.m1_i2;
	int n = m_in.m1_i3;

	while (n>0){
		int pid = mproc[idx].mp_pid;
		if(pid){
			int parent = mproc[mproc[idx].mp_parent].mp_pid;
			printf("proc: %s\n", mproc[idx].mp_name);
			printf("pid: %d, ppid: %d\n", pid, parent);
		}else{
			n=0;
		}
		idx++;
	}
	return 1;
}
