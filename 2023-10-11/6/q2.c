/*
 *  Q2 : 
 *  Implement program # 4 of assignment for week # 5, using sigaction()
 *  Modify the program to mask any other signal that appears, while the signal handler is busy processing a signal .
 *  Hint: Define the signal_handler in such a way, that it remains under execution for some time (loop may be used), when another signal gets generated.
 */

#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

sigset_t old_mask;

void signal_handler(int signo) {
    sigset_t block_mask;
    struct timespec sleep_time;
    sleep_time.tv_sec = 2;
    sleep_time.tv_nsec = 0;

    sigfillset(&block_mask);
    sigdelset(&block_mask, SIGQUIT);
    sigprocmask(SIG_BLOCK, &block_mask, &old_mask);

    switch (signo) {
        case SIGINT:
            printf("Child process: Received SIGINT\n");
            break;
        case SIGHUP:
            printf("Child process: Received SIGHUP\n");
            break;
        case SIGTERM:
            printf("Child process: Received SIGTERM\n");
            break;
    }

    printf("Child process: Simulating signal handling...\n");
    for (int i = 0; i < 5; i++) {
        printf("Child process: Working... (%d/5)\n", i + 1);
        nanosleep(&sleep_time, NULL);
    }
    sigprocmask(SIG_SETMASK, &old_mask, NULL);
}

int main() {
    pid_t child_pid;

    if ((child_pid = fork()) == 0) {
        struct sigaction sa;
        sa.sa_handler = signal_handler;
        sa.sa_flags = SA_RESTART;

        if (sigaction(SIGINT, &sa, NULL) == -1 ||
            sigaction(SIGHUP, &sa, NULL) == -1 ||
            sigaction(SIGTERM, &sa, NULL) == -1) {
            perror("sigaction failed");
            return 1;
        }

        while (1) {
            pause();
        }
    } else if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    } else {
        printf("Parent process: Sending signals to child (PID: %d).\n", child_pid);

        kill(child_pid, SIGINT);
        sleep(1);
        kill(child_pid, SIGHUP);
        sleep(1);
        kill(child_pid, SIGTERM);

        wait(NULL);
    }

    return 0;
}
