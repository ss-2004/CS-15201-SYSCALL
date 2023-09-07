#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed !");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        printf("Child process is running\n");
        exit(0);
    } else {
        printf("Parent process is sleeping...\n");
        sleep(15);
        wait(NULL);

        printf("Parent process collected child exit status\n");
        sleep(5);
        printf("Parent process is completed\n");
    }
    return 0;
}