// Q1 : Using pipe() system call to send a string of characters from parent process to child process. 
// Child process will read the string and print the string in child process itself.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char msg[] = "Hello from child process!";
    char buf[100];

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
        close(fd[1]);
        read(fd[0], buf, sizeof(buf));
        printf("Child process received : %s\n", buf);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);
    }

    return 0;
}
