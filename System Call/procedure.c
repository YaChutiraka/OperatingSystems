#include <lib.h> //provides _syscall and message
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	// This is a test for library function
	
	printf("\n\n ********* reset_plog called");
	reset_plog(); // recent the current index keep track of buffer;
	
	printf("\n\n ********* start_plog called");
	start_plog();
	
	printf("\n ********* 1st process created");
	int pid = fork();	// create a new child process
	if(pid != 0)	wait(0) ; // make sure parent is still active

	else	 exit(0); // make child hault right away
	
	int index = 0;
	//printf("**** MAIN fork() = %d VS getpid = %d VS getppid() = %d \n\n\n", pid, getpid(), getppid());
	long c1; 
	long t1;
	long c2; // long *c2 alternative and remove &
	long t2;
	
	printf("\n\n ********* get_plog_byPID called");
	int errorCode_byPID = get_plog_byPID(getpid(), &c1, &t1);
	printf("\n\n ********* get_plog_byindex called");
	int errorCode_byindex = get_plog_byindex(index, &c2, &t2);
	int size = get_plog_size(); // always 1024
	printf("\n");
	printf("- pid = %d\n", getpid());
	printf("- byPID code = %d\n", errorCode_byPID);
	printf("- index = %d\n", index);
	printf("- byindex = %d\n", errorCode_byindex);
	printf("- buffer size = %d\n", size);
	printf("\n");
	printf("\n");
	

	printf("\n ********* 2nd process created");
	pid = fork();	
	if(pid != 0)	wait(0) ; 

	else	 exit(0); 
	
	index = 1;
	long c3; 
	long t3;
	long c4; 
	long t4;
	
	printf("\n\n ********* get_plog_byPID called");
	errorCode_byPID = get_plog_byPID(getpid(), &c3, &t3);
	printf("\n\n ********* get_plog_byindex called");
	errorCode_byindex = get_plog_byindex(index, &c4, &t4);
	size = get_plog_size(); // always 1024
	printf("\n");
	printf("- pid = %d\n", getpid());
	printf("- byPID code = %d\n", errorCode_byPID);
	printf("- index = %d\n", index);
	printf("- byindex code = %d\n", errorCode_byindex);
	printf("- buffer size = %d\n", size);
	printf("\n");
	printf("\n");
	
	
	printf("\n ********* 3rd process created");
	pid = fork();	
	if(pid != 0)	wait(0) ; 

	else	 exit(0); 
	
	index = 2;
	long c5; 
	long t5;
	long c6; 
	long t6;
	
	printf("\n\n ********* get_plog_byPID called");
	errorCode_byPID = get_plog_byPID(getpid(), &c5, &t5);
	printf("\n\n ********* get_plog_byindex called");
	errorCode_byindex = get_plog_byindex(index, &c6, &t6);
	size = get_plog_size(); // always 1024
	printf("\n");
	printf("- pid = %d\n", getpid());
	printf("- byPID code = %d\n", errorCode_byPID);
	printf("- index = %d\n", index);
	printf("- byindex code = %d\n", errorCode_byindex);
	printf("- buffer size = %d\n", size);
	printf("\n");
	printf("\n");
	
	printf("\n\n ********* stop_plog called");
	stop_plog();
	
	printf("\n ********* 4th process created");
	pid = fork();	
	if(pid != 0)	wait(0) ; 

	else	 exit(0); 
	
	index = 3;
	long c7; 
	long t7;
	long c8; 
	long t8;
	
	printf("\n\n ********* get_plog_byPID called");
	errorCode_byPID = get_plog_byPID(getpid(), &c7, &t7);
	printf("\n\n ********* get_plog_byindex called");
	errorCode_byindex = get_plog_byindex(index, &c8, &t8);
	size = get_plog_size(); // always 1024
	printf("\n");
	printf("- pid = %d\n", getpid());
	printf("- byPID code = %d\n", errorCode_byPID);
	printf("- index = %d\n", index);
	printf("- byindex code = %d\n", errorCode_byindex);
	printf("- buffer size = %d\n", size);
	printf("\n");
	printf("\n");
	
	printf("\n ********* try random access");
	int beyond_index = 5;
	int random_pid = 5000;
	long c9; 
	long t9;
	long c10; 
	long t10;
	
	printf("\n\n ********* get_plog_byPID called");
	errorCode_byPID = get_plog_byPID(random_pid, &c9, &t9);
	printf("\n\n ********* get_plog_byindex called");
	errorCode_byindex = get_plog_byindex(beyond_index, &c10, &t10);
	size = get_plog_size(); // always 1024
	printf("\n");
	printf("- random test pid = %d\n", random_pid);
	printf("- byPID code = %d\n", errorCode_byPID);
	printf("- beyond curr_index index = %d\n", beyond_index);
	printf("- byindex code = %d\n", errorCode_byindex);
	printf("- buffer size = %d\n", size);
	printf("\n");
	printf("\n");
	
/*	
	
	// This is a test for system call
	message m; // Minix uses message to pass parameters to a system call
	
	// TESTED set curr_index = 0 
	_syscall(PM_PROC_NR, RESET_PLOG, &m);

	// what to do?
	// _syscall(PM_PROC_NR, STOP_PLOG, &m);
	
	// TESTED set on_off = 1
	_syscall(PM_PROC_NR, START_PLOG, &m); 
	
	// TESTEDreturns SIZE fine
	// printf("SIZE = %d \n",_syscall(PM_PROC_NR, GET_PLOG_SIZE, &m));

	// TESTED, works, but no real PID found
	// For testing
	//m.m1_i1 = 1; // pretend it is buff[0].this_pid = 1;
	//buff[0].c_time = 2;
	//buff[0].t_time = 20;
	_syscall(PM_PROC_NR, GET_PLOG_BYPID, &m);
	
	//TESTED but still invalid index, no real pid
	_syscall(PM_PROC_NR, GET_PLOG_BYINDEX, &m);
*/
}

