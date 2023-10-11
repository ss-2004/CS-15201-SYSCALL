#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void sgnlHndlr(int signum){
	switch(signum){
		case SIGINT:
			printf("\nReceived SIGINT!\n");
			break;
		case SIGHUP:
			printf("\nReceived SIGHUP!\n");
			break;
		case SIGTERM:
			printf("\nReceived SIGTERM!\n");
			break;
		default : 
			printf("\nReceived unexpected signal!\n");
			break;
	}
}

int main() {
	pid_t childpid = fork();

    if (childpid == -1) {
        perror("fork\n");
        exit(1);
    } else if (childpid == 0) {
    	signal(SIGINT, sgnlHndlr);
		signal(SIGHUP, sgnlHndlr);
		signal(SIGTERM, sgnlHndlr);
		
		printf("Child executing at PID : %d\nWaiting for signal from parent...\n", getpid());
		while(1){
			sleep(1);
		}
    } else {
        printf("Parent at PID %d sending signals to child...\n", getpid());
        printf("To exit, send SIGQUIT ^\\ to child\n");
        
        while(1){
			kill(childpid, SIGINT);
			sleep(2);
			kill(childpid, SIGHUP);
			sleep(2);
			kill(childpid, SIGTERM);
			sleep(2);
    	}
    	wait(NULL);
    }
    
	return 0;
}

