#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	pid_t p;
	p = fork();
	
	if(p == -1){
		perror("Fork failed !");
		exit(EXIT_FAILURE);
	}
	
	if(p == 0){
		printf("Child process is running\n");
		char *args[] = {"/bin/ls", "-l", NULL};
		
		if(execvp("ls", args) == -1){
		    perror("execvp failed!\n");
		    exit(EXIT_FAILURE);
		}
	}else if(p>0){
		wait(NULL);
		printf("Child is complete\n");
	}
	return 0;
}
