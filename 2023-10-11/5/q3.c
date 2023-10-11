// Q3
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int alrmc = 0;

void sgnlHndlr(int signum) {
    if (signum == SIGCHLD) {
        printf("\nReceived SIGCHLD!\n");
        int status;
        pid_t childpid = wait(&status);

        if (WIFEXITED(status)) {
            printf("\n\tChild process PID : %d\n\tExited with status : %d\n", childpid, WIFEXITED(status));
        }
    }
}

int main() {
    signal(SIGCHLD, sgnlHndlr);
    pid_t childpid = fork();

    if (childpid == -1) {
        perror("fork\n");
        exit(1);
    } else if (childpid == 0) {
        printf("Child executing at PID : %d\n", getpid());
        sleep(3);
        exit(42);
    } else {
        printf("Parent at PID %d waiting for child to exit...\n", getpid());
    }

    while (1) {}

    return 0;
}
