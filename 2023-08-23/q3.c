#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void create_tree(int height, int current_height){
	if(current_height >= height)
		return;

	int i;
	for(i=0; i<=2; i++) {
		pid_t child_pid=fork();

		if(child_pid == -1) {
            perror("Fork failed !");
        }
		
		if(child_pid == 0) {
            printf("Child: %d\tPID: %d\tParent PID: %d\n", i+1, getpid(), getppid());
			create_tree(height, current_height+1);
			break;
        }
	}

	for(i=0; i<2; i++)
		wait(NULL);
}

int main(){
	printf("Parent PID: %d\n", getpid());
	create_tree(3,0);
	return 0;
}

