#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_COUNT 200
#define BUFF 100

void childProc(){
	int i;
	for(i=1; i<=MAX_COUNT; i++)
		printf("This value is from child. Value = %d\n", i);
	
	printf("\n *** CHILD PROCESS IS COMPLETE *** \n");
}

void parentProc(){
	int i; 
	for(i=1; i<=MAX_COUNT; i++)
		printf("This value is from parent. Value = %d\n", i);

	printf("\n *** PARENT PROCESS IS COMPLETE *** \n");	
}

void main(){
	pid_t pid;
	pid = fork();
	
	if(pid == 0)
		childProc();
	else
		parentProc();
}
