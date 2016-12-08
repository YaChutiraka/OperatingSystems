
#include "syslib.h"

#include <minix/vm.h>

//VMF_ENDPOINT			m10_i1
//VMF_SLOTNO			m10_i2
//VMF_CHILD_ENDPOINT	m10_i3	

/*===========================================================================*
 *                                vm_fork				     *
 *===========================================================================*/
int vm_fork(endpoint_t ep, int slot, endpoint_t *childep)
//int vm_fork(endpoint_t ep, int slot, endpoint_t *childep)
{
    message m;
    int result;
	
    m.VMF_ENDPOINT = ep;
    m.VMF_SLOTNO = slot;
    result = _taskcall(VM_PROC_NR, VM_FORK, &m);

    *childep = m.VMF_CHILD_ENDPOINT;
    return(result);
}

