#include "syslib.h"

int sys_fork(parent, child, child_endpoint, flags, msgaddr)
endpoint_t parent;		/* process doing the fork */
endpoint_t child;		/* which proc has been created by the fork */
endpoint_t *child_endpoint;
u32_t flags;
vir_bytes *msgaddr;
{
/* A process has forked.  Tell the kernel. */

  message m;
  int r;
  m.PR_ENDPT2 = parent;
  m.PR_SLOT2 = child;
  m.PR_FORK_FLAGS2 = flags;
  r = _kernel_call(SYS_FORK, &m);
  *child_endpoint = m.PR_ENDPT2;
  *msgaddr = (vir_bytes) m.PR_FORK_MSGADDR2;
  /*
  printf("--------------------libsys/sys_fork.c------------------------\n");
  printf("PR_ENDPT2             %d\n", m.PR_ENDPT2);
  printf("PR_ENDPT2             %d\n", m.PR_ENDPT2);
  printf("PR_ENDPT2     		%d\n", PR_ENDPT2);
  printf("PR_PID2               %d\n", m.PR_PID2);
  printf("-----------------------------------------------------------\n");
  */
  return r;
}
