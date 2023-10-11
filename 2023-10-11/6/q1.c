// Q1
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void sigchld_handler(int signo, siginfo_t *info, void *context) {
    if (info->si_code == CLD_EXITED) {
        printf("\nChild PID %d exited with status: %d\n", info->si_pid, info->si_status);
    }
}

int main() {
    pid_t child_pid;
    struct sigaction sa;
    int c=5;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigchld_handler;
    sigaction(SIGCHLD, &sa, NULL);

    if ((child_pid = fork()) == 0) {
        printf("\n\tChild performing random tasks...\n");
        sleep(1);
        exit(123);
    } else if (child_pid == -1) {
        perror("Fork failed\n");
        return 1;
    }

    printf("\nParent process waiting for child (PID: %d) to terminate...\n", child_pid);
    while (c) {
        printf("\n\tParent performing random tasks...\n");
        sleep(5);
        c--;
    }

    return 0;
}

