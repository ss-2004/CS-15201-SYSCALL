#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	pid_t child_pid;
	child_pid = fork();

	if(child_pid == -1){
		perror("Fork failed !");
		return 1;
	}

	if(child_pid == 0){
		printf("Child Process : \n");
		printf("\tChild PID: \t%d\n", getpid());
		printf("\tParent PID: \t%d\n", getpid());
	} else {
		printf("Parent Process : \n");
		printf("\tPID: \t%d\n", getpid());
		printf("\tChild PID: \t%d\n", child_pid);
		printf("\tOwner PID: \t%d\n", getuid());
	
		int status;
		wait(&status);

		if(WIFEXITED(status))
			printf("Child Process exited with status: %d\n", WEXITSTATUS(status));
		else
			printf("Child Process did not exit normally\n");		
	}
	return 0;
}
