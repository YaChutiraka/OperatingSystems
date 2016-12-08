#include "kernel/system.h"
#include <minix/endpoint.h>
#include "kernel/glo.h"
/* The kernel call implemented in this file:
*   m_type:    SYS_PLOG       
*/


int do_plog(struct proc *caller_ptr, message *m_ptr){
	pid_t pid = m_ptr->m1_i1;
	endpoint_t ep = m_ptr->m1_i2;
	int active_flag = m_ptr->m1_i3;
	int i;
	for(i=0; i<NR_TASKS + NR_PROCS; i++){
		if(proc[i].p_endpoint == ep){
			proc[i].p_pid = pid;
			proc[i].p_isTracked = active_flag;
			interested = proc[i].p_endpoint;
			printf("\n -------- KEREL interested = %d, pid = %d, ep = %d, tracking flag = %d -----\n", interested, proc[i].p_pid, proc[i].p_endpoint, proc[i].p_isTracked);
		}
	}
	return (OK);
}
