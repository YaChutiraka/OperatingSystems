/* spawn.c
 *
 * usage: 
 * print both consecutive lines if the next line is not exactly 1 greater than the previous line
 * int main(int argc, char *argv[]){
 *
 * Does not like files that do not have numbers in them.
 *
 * Author: Ya Chutiraka, University of Florida
 * Created: 9/24/2016
 * Modified: 9/24/2016
 */

 
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define NUM_CHILD 2

int main(int argc, char *argv[]){

	//printf("\n argv[1] is # of children =  %s", argv[1]);
	//printf("\n argv[2] is what to execute = %s", argv[2]);
	
	char* executable;
	char* to_inc;
	char* filename;
	
	executable = strtok (argv[2]," ");
	to_inc = strtok (NULL," ");
	filename = strtok (NULL," ");
	
	for(int i=0; i < atoi(argv[1]); i++){
		pid_t pid = fork();
		if(pid < 0){
			perror("fork failed");
			exit(1);
		}else if (pid ==0){
			//Child now exec's
			char *args[] = {"./increment", to_inc, filename, NULL};
			//argv[1] = # of children process we want
			//argv[2] = command to run a certain file in this case is "./increment 10 foo.txt"
			execv(args[0], args);
		}
	}	
	// parent is doing something
	//printf("--------------PARENT IS DOING STH---------");
	// Make parent wait for  child
	//wait(NULL);
	
	return 0;
}