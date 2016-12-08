#include <stdio.h>

#include "pm.h"
#include "mproc.h"
// Added by Ya for Project2 11/21/2016
#include <minix/syslib.h> 
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/endpoint.h>

#include "plog_buffer_entry.h"

#define PLOG_BUFFER_SIZE 1024

// declare a buffer
struct plog_buffer_entry plog_buffer[PLOG_BUFFER_SIZE];
int current; // is the same as plog_index
int plog_active_flag = 0;
int plog_buffer_full_flag = 0;
pid_t interested_pid;

/* function declarations */
const char* getStateName(enum State state);
int plog_active(int flag, pid_t pid);
void plog_clear_buffer();
time_t plog_get_time();
void plog_add_entry(pid_t pid, enum State from, enum State to, time_t timestamp);
void plog_terminate_state(pid_t pid, enum State to, time_t timestamp);
void print_buffer();
void plog_pid_to_kernel(int PID, int active_flag);

const char* getStateName(enum State state) {
   switch (state) {
	  case NEWLY_CREATED: return "NEWLY_CREATED";
	  case READY: return "READY";
	  case RUNNING: return "RUNNING";
	  case BLOCKED: return "BLOCKED";
	  case TERMINATED: return "TERMINATED";
   }
}



int do_plog(void) {
    int ret = 1;
	int thisPID = m_in.m7_i1;
	int startORstop = m_in.m7_i2; // stop is 0, start is 1
	
	// TODO when ret = 2 and 3 for invalid pid 
	
    switch(startORstop) {
        case 0: /* stop_plog */
			plog_active_flag = 0;
			plog_active(plog_active_flag, thisPID);
			if(plog_active(plog_active_flag, thisPID) == 0) {plog_pid_to_kernel(thisPID, plog_active_flag);}
			ret = find_pid(thisPID);
            break;
		case 1: /* start_plog */
			plog_active_flag = 1;
			interested_pid = thisPID;
		    if(plog_active(plog_active_flag, thisPID)) {plog_pid_to_kernel(thisPID, plog_active_flag);}
			ret = find_pid(thisPID);
            break;
    }
    return ret;
}

void plog_pid_to_kernel(int PID, int active_flag){
	int i;
	message m;
	for(i=0; i<NR_PROCS; i++){
		if(mproc[i].mp_pid == PID){
			m.m1_i1 = PID;
			m.m1_i2 = mproc[i].mp_endpoint;
			m.m1_i3 = active_flag;
			//sys_plog(PID); // no reference error??
			_kernel_call(SYS_PLOG, &m);
			return;
		}
	}
}

// DONE
int plog_active(int flag, pid_t pid) {
    int i;
    for(i=0; i<NR_PROCS; i++){
		if(mproc[i].mp_pid == pid){
			mproc[i].tracking_flag = flag;
			return flag;
		}
	}
	return 0; // not found pid, then just do not turn on the tracking

}

int find_pid(pid_t pid) {
	int i;
    for(i=0; i<NR_PROCS; i++){
		if(mproc[i].mp_pid == pid){
			return 0; // found pid
		}
	}
	return 1; // not found pid
}

// DONE
void plog_clear_buffer() {
	current = -1;
    plog_buffer_full_flag = 0;
}

// DONE
time_t plog_get_time() {
	/* get current time */
    clock_t uptime, boottime;
    int s;

    if ( (s=getuptime2(&uptime, &boottime)) != OK)
        panic("plog_get_time couldn't get uptime: %d", s);

    return (time_t) (boottime + (uptime/system_hz));
}

// DONE
void plog_add_entry(pid_t pid, enum State from, enum State to, time_t timestamp) {
	/* increment */
    current += 1;
    current %= PLOG_BUFFER_SIZE;

    /* fill entry */
	/*
    plog_buffer[current].thisPID = pid;
	plog_buffer[current].fromState = from;
	plog_buffer[current].toState = to;
	plog_buffer[current].timestamp = timestamp;
	*/

    /* check if full now */
    if (current + 1 == current)
        plog_buffer_full_flag = 1;
	
	// Ya
	/* test 
	int thisPID = m_in.m7_i1;
	start_case(thisPID);
	*/
}

void plog_terminate_state(pid_t pid, enum State to, time_t timestamp){
	/*
	for(int i=0; i<PLOG_BUFFER_SIZE; i++){
		if(plog_buffer[i].thisPID == pid){
			// fromState remains the same
			plog_buffer[i].toState = to; // toState = TERMINATED
			plog_buffer[i].timestamp = timestamp;
		}
	}
	*/
	return;
}

void print_buffer(){
	int i;
	printf("==============Processes and States====================\n");
	for(i=0; i<=current && i<PLOG_BUFFER_SIZE; i++){
		printf("PID %d  %d  %s  %s\n", plog_buffer[i].thisPID, plog_buffer[i].timestamp, getStateName(plog_buffer[i].fromState), getStateName(plog_buffer[i].toState));
	}
	printf("======================================================\n");
	return;
}