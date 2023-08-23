#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int i;

	for(i=0; i<5; i++) {
		pid_t child_pid=fork();
		if(child_pid == -1){
    	    perror("Fork failed !");
        	return 1;
    	}
		if(child_pid == 0){
        	printf("Child: %d\tPID: %d\tParent PID: %d\n", i+1, getpid(), getppid());
			break;
    	}

		if(i==4) {
			printf("Parent PID: %d\n", getpid());
		    for(i=0; i<5; i++)
        		wait(NULL);
		}
		
	}

    //printf("Parent PID: %d\n", getpid());
	//for(i=0; i<5; i++)
	//	wait(NULL);
	return 0;
}

