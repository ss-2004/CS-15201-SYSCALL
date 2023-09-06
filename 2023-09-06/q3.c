#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	pid_t child_pid;
	child_pid = fork();
	int status;

	if(child_pid == -1){
		perror("Fork failed !");
		exit(EXIT_FAILURE);
	}
	
	if(child_pid == 0){
		printf("Child process is running\n");
		char *args[] = {"ls", "-l", NULL};
		
		if(execvp("ls", args) == -1){
		    perror("execvp failed!\n");
		    exit(EXIT_FAILURE);
		}
	}else{
		printf("Parent is continuing to execute\n");
		wait(&status);
		
		if(WIFEXITED(status))
		    printf("Child process exited with status : %d\n", WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
		    printf("Child process terminated by signal : %d\n", WTERMSIG(status));
	}
	return 0;
}
