#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) { 
    int fd[2];
    if(pipe(fd) == -1) {
        perror("Pipe error!\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork;
    if(pid == -1) {
        perror("Fork failed!\n");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        perror("execlp failed!\n");
        exit(EXIT_FAILURE);
    } else {
        close(fd[1]);
        dup2(fd[0], STDOUT_FILENO);
        close(fd[0]);
        execlp(argv[2], argv[2], NULL);
        perror("execlp failed!\n");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    return 0;
}