/* The kernel call implemented in this file:
 *   m_type:	SYS_FORK
 *
 * The parameters for this kernel call are:
 *    m7_i1:	PR_ENDPT2	(parent, process that forked)
 *    m7_i2:	PR_SLOT2	(child's process table slot)
 *    m7_p2:	PR_MEM_PTR2	(new memory map for the child)
 *    m7_i3:	PR_FORK_FLAGS2	(fork flags)
 */

#include "kernel/system.h"
#include "kernel/vm.h"
#include <signal.h>
#include <string.h>
#include <assert.h>

#include <minix/endpoint.h>
#include <minix/u64.h>
// Added by Ya Chutiraka for proj2 11/21/2016
#include "glo.h"
#include "kernel/proc.h"
#include "kernel/clock.h"

struct buffer_plog buffer_plog[BUFFER_SIZE];
int current;
endpoint_t interested; //endpoint of the proc we want to track
const char* getStateName_2(enum State state);

const char* getStateName_2(enum State state) {
   switch (state) {
	  case NEWLY_CREATED: return "NEWLY_CREATED";
	  case READY: return "READY";
	  case RUNNING: return "RUNNING";
	  case BLOCKED: return "BLOCKED";
	  case TERMINATED: return "TERMINATED";
   }
}

#if USE_FORK

/*===========================================================================*
 *				do_fork					     *
 *===========================================================================*/
int do_fork(struct proc * caller, message * m_ptr)
{
/* Handle sys_fork().  PR_ENDPT has forked.  The child is PR_SLOT. */
#if defined(__i386__)
  char *old_fpu_save_area_p;
#endif
  register struct proc *rpc;		/* child process pointer */
  struct proc *rpp;			/* parent process pointer */
  int gen;
  int p_proc;
  int namelen;

  if(!isokendpt(m_ptr->PR_ENDPT, &p_proc))
	return EINVAL;

  rpp = proc_addr(p_proc);
  rpc = proc_addr(m_ptr->PR_SLOT);
  if (isemptyp(rpp) || ! isemptyp(rpc)) return(EINVAL);

  assert(!(rpp->p_misc_flags & MF_DELIVERMSG));

  /* needs to be receiving so we know where the message buffer is */
  if(!RTS_ISSET(rpp, RTS_RECEIVING)) {
	printf("kernel: fork not done synchronously?\n");
	return EINVAL;
  }

  /* make sure that the FPU context is saved in parent before copy */
  save_fpu(rpp);
  /* Copy parent 'proc' struct to child. And reinitialize some fields. */
  gen = _ENDPOINT_G(rpc->p_endpoint);
#if defined(__i386__)
  old_fpu_save_area_p = rpc->p_seg.fpu_state;
#endif
  *rpc = *rpp;				/* copy 'proc' struct */
#if defined(__i386__)
  rpc->p_seg.fpu_state = old_fpu_save_area_p;
  if(proc_used_fpu(rpp))
	memcpy(rpc->p_seg.fpu_state, rpp->p_seg.fpu_state, FPU_XFP_SIZE);
#endif
  if(++gen >= _ENDPOINT_MAX_GENERATION)	/* increase generation */
	gen = 1;			/* generation number wraparound */
  rpc->p_nr = m_ptr->PR_SLOT;		/* this was obliterated by copy */
  rpc->p_endpoint = _ENDPOINT(gen, rpc->p_nr);	/* new endpoint of slot */

  rpc->p_reg.retreg = 0;	/* child sees pid = 0 to know it is child */
  rpc->p_user_time = 0;		/* set all the accounting times to 0 */
  rpc->p_sys_time = 0;

  rpc->p_misc_flags &=
	~(MF_VIRT_TIMER | MF_PROF_TIMER | MF_SC_TRACE | MF_SPROF_SEEN | MF_STEP);
  rpc->p_virt_left = 0;		/* disable, clear the process-virtual timers */
  rpc->p_prof_left = 0;

  /* Mark process name as being a forked copy */
  namelen = strlen(rpc->p_name);
#define FORKSTR "*F"
  if(namelen+strlen(FORKSTR) < sizeof(rpc->p_name))
	strcat(rpc->p_name, FORKSTR);

  /* the child process is not runnable until it's scheduled. */
  RTS_SET(rpc, RTS_NO_QUANTUM);
  reset_proc_accounting(rpc);

  make_zero64(rpc->p_cpu_time_left);
  make_zero64(rpc->p_cycles);
  make_zero64(rpc->p_kcall_cycles);
  make_zero64(rpc->p_kipc_cycles);

  /* If the parent is a privileged process, take away the privileges from the 
   * child process and inhibit it from running by setting the NO_PRIV flag.
   * The caller should explicitely set the new privileges before executing.
   */
  if (priv(rpp)->s_flags & SYS_PROC) {
      rpc->p_priv = priv_addr(USER_PRIV_ID);
      rpc->p_rts_flags |= RTS_NO_PRIV;
  }

  /* Calculate endpoint identifier, so caller knows what it is. */
  m_ptr->PR_ENDPT = rpc->p_endpoint;
  m_ptr->PR_FORK_MSGADDR = (char *) rpp->p_delivermsg_vir;

  /* Don't schedule process in VM mode until it has a new pagetable. */
  if(m_ptr->PR_FORK_FLAGS & PFF_VMINHIBIT) {
  	RTS_SET(rpc, RTS_VMINHIBIT);
  }

  /* 
   * Only one in group should have RTS_SIGNALED, child doesn't inherit tracing.
   */
  RTS_UNSET(rpc, (RTS_SIGNALED | RTS_SIG_PENDING | RTS_P_STOP));
  (void) sigemptyset(&rpc->p_pending);

#if defined(__i386__)
  rpc->p_seg.p_cr3 = 0;
  rpc->p_seg.p_cr3_v = NULL;
#elif defined(__arm__)
  rpc->p_seg.p_ttbr = 0;
  rpc->p_seg.p_ttbr_v = NULL;
#endif
  
  //Added by Ya Chutiraka for Project2
  if(rpc->p_endpoint == interested &&rpc->p_isTracked == 1){
    current = current + 1;
    if(current >= BUFFER_SIZE){
       /*
		message m;
		m.m1_p1 = (char *) &(buffer_plog[0]);
		m.m1_i2 = (endpoint_lookup(KERNEL))->p_endpoint;
		m.m_type = KERNEL_TO_VFS;
		mini_send(endpoint_lookup(KERNEL), VFS_PROC_NR, &m, FROM_KERNEL);
	    */
	    current = 0;
	}
    
    buffer_plog[current].thisPID = rpc->p_pid;
	buffer_plog[current].fromState = NEWLY_CREATED;
	buffer_plog[current].toState = NEWLY_CREATED;
	buffer_plog[current].timestamp = get_uptime();
	rpc->p_prev_state = 0;
	/*
	printf("\nFORK pid = %d", rpc->p_pid);
	printf("\ncurrent = %d, from = %s, toState = %s, timestamp = %ld", current, getStateName_2(buffer_plog[current].fromState), getStateName_2(buffer_plog[current].toState), (long)buffer_plog[current].timestamp);
	*/
  }  
  return OK;
}

#endif /* USE_FORK */

