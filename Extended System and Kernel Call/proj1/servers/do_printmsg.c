#
#include <stdio.h>
#include "pm.h" // provide global variable such as m_in
int do_printmsg(){
	int i = m_in.m1_i1;
	printf("System call do_printmsg called with value %d\n", i);
	return 0;
}
