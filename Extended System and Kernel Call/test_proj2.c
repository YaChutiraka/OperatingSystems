#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


#ifndef _PLOG
int plog_state_start(int PID);
int plog_state_stop(int PID);
#endif


int debug = 0;
#define kids 6


#define CMDS "0=exit, 1=help, 2=start, 3=stop, 4=verbose, 5=silent"
enum cmd {EXIT, HELP, START, STOP, VERBOSE, SILENT, DEBUGT};
int verbose=1;
#define PROMPT "Enter command: "

int help()
{
	printf("%s\n",CMDS);
	return 0;
}

int get_command()
{
	int c;
	int rv;

	if (verbose) printf("%s", PROMPT);
	fflush(stdout);
	rv = scanf("%d",&c);
	if (debug) fprintf(stderr, "rv = %d\n", rv);
	if ((c<0) || (c>DEBUGT)) return HELP;
	else return c;
}

int start_case(){
	int pid;
	int rv;
	if (verbose) printf("Enter PID: ");
	fflush(stdout);
	rv = scanf("%d",&pid);
	if (debug) fprintf(stderr, "Start state by PID: %d\n", pid);
	rv = plog_state_start(pid);
	if (rv == 0){
		printf("PID %d started\n", pid);
	}else if (rv == 1){
		printf("PID %d was not found\n", pid);
	}else if (rv == 2){
		printf("PID %d is invalid (non-user process)\n", pid);
	}else{
		printf("File error\n");
	}
}

int stop_case(){
	int pid;
	int rv;
	if (verbose) printf("Enter PID: ");
	fflush(stdout);
	rv = scanf("%d",&pid);
	if (debug) fprintf(stderr, "Stop state by PID: %d\n", pid);
	rv = plog_state_stop(pid);
	if (rv == 0){
		printf("PID %d stoped \n", pid);
	}else if (rv == 1){
		printf("PID %d was not found\n", pid);
	}else if (rv == 2){
		printf("PID %d is invalid (non-user process)\n", pid);
	}else{
		printf("File error\n");
	}
}



int main(int argc, char *argv[])
{
int command;
pid_t pid;
int N;
int rv, s;
int i = 0;
long int start, finish;

	
	if (argc > 1)
	    if (argv[1][0] == 'q') verbose = 0;

	if (verbose)
		printf("%s\n", CMDS);

	while ((command = get_command())!=EXIT)
	{
	    switch(command)
	    {
		case EXIT:
		    return 0;
		    break;
		case HELP:
		    printf("%s\n", CMDS);
		    break;
		case START:
		    start_case();
		    break;
		case STOP:
		    stop_case();
		    break;
		case VERBOSE:
		    verbose=1;
		    break;
		case SILENT:
		    verbose=0;
		    break;
		case DEBUGT:
		    debug=1-debug;
		    break;
		default:
		    break;
	    }
	}
	return 0;

}




/*
#include <lib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


//#include "plog.h"

#ifndef _PLOG
int plog_state_start(int PID));
int plog_state_stop(int PID);
#endif


int debug = 0;
#define kids 6


#define CMDS "0=exit, 1=help, 2=start, 3=stop, 4=verbose, 5=silent"
enum cmd {EXIT, HELP, START, STOP, SILENT, DEBUGT};
int verbose=1;
#define PROMPT "Enter command: "

int help()
{
	printf("%s\n",CMDS);
	return 0;
}

int get_command()
{
	int c;
	int rv;

	if (verbose) printf("%s", PROMPT);
	fflush(stdout);
	rv = scanf("%d",&c);
	if (debug) fprintf(stderr, "rv = %d\n", rv);
	if ((c<0) || (c>DEBUGT)) return HELP;
	else return c;
}

int start_case(){
	int pid;
	int rv;
	if (verbose) printf("Enter PID: ");
	fflush(stdout);
	rv = scanf("%d",&pid);
	if (debug) fprintf(stderr, "Start state by PID: %d\n", pid);
	rv = plog_state_start(pid);
	if (rv == 0){
		printf("PID %d started\n", pid);
	}else if (rv == 1){
		printf("PID %d was not found\n", pid);
	}else if (rv == 2){
		printf("PID %d is invalid (non-user process)\n", pid);
	}else{
		printf("File error\n");
	}
}

int stop_case(){
	int pid;
	int rv;
	if (verbose) printf("Enter PID: ");
	fflush(stdout);
	rv = scanf("%d",&pid);
	if (debug) fprintf(stderr, "Stop state by PID: %d\n", pid);
	rv = plog_state_stop(pid);
	if (rv == 0){
		printf("PID %d stoped \n", pid);
	}else if (rv == 1){
		printf("PID %d was not found\n", pid);
	}else if (rv == 2){
		printf("PID %d is invalid (non-user process)\n", pid);
	}else{
		printf("File error\n");
	}
}


int main(int argc, char *argv[]){
	int command;
	int pid;
	int N;
	int rv, s;
	int i = 0;

	if (argc > 1)
	    if (argv[1][0] == 'q') verbose = 0;

	if (verbose)
		printf("%s\n", CMDS);

	while ((command = get_command())!=EXIT)
	{
	    switch(command)
	    {
		case EXIT:
		    return 0;
		    break;
		case HELP:
		    printf("%s\n", CMDS);
		    break;
		case START:
		    (void) start_case();
		    break;
		case STOP:
		    (void) stop_case();
		    break;
		case VERBOSE:
		    verbose=1;
		    break;
		case SILENT:
		    verbose=0;
		    break;
		case DEBUGT:
		    debug=1-debug;
		    break;
		default:
		    break;
	    }
	}
	return 0;

}

*/
