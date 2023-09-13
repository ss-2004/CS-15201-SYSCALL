#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    int fd[2];
    if(pipe(fd) == -1) {
        perror("Pipe error!\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if(pid == -1) {
        perror("Fork failed!\n");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        close(fd[0]);
        dup(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed!\n");
        exit(EXIT_FAILURE);
    } else {
        close(fd[1]);
        dup(fd[0]);
        execlp("sort", "sort", NULL);
        perror("execlp failed!\n");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    return 0;
}