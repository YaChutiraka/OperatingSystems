/* consecutive.c
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
 #define debug 0
 #define USAGE "usage: print both consecutive lines if the next line is not exactly 1 greater than the previous line"
 int main(int argc, char *argv[]){
	//FILE *pToFile = fopen("bar.txt", "r");
	
	char file[30];
	scanf("%s", file);
	
	FILE *pToFile = fopen(file, "r");
	FILE *pToFileNext = fopen(file, "r");
	
	//FILE *pToFile = fopen(argv[1], "r");
	//FILE *pToFileNext = fopen(argv[1], "r");
	
	int line=0;
	char input[10];
	char inputNext[10];
		 
	fgets(inputNext, 10, pToFileNext); // offset to start at the second
		 
	while(fgets(input, 10, pToFile)){
		line++;
		//printf("%d : %s", line, input);
		if(fgets(inputNext, 10, pToFileNext)){
			line++;
			//printf("%d : %s", line, inputNext);
			if((atoi(input)+1)!=atoi(inputNext)){
				printf("%d : %s", line-1, input);
				printf("%d : %s", line, inputNext);
			}
			line--; // back to original line
		}
		//printf("\n Each While\n");
	}
	 //printf("\n END");
	fclose(pToFile);
	fclose(pToFileNext); 
	 
	return 0;
 }
 
