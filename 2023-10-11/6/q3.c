/*
 * Q3 : 
 * Implement a program using sigaction() and signal_set to block any of the signals SIGINT, SIGHUP and SIGABRT. 
 * The program should also display the list of blocked/pending signals.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo) {
    printf("Signal %d received\n", signo);
}

int main() {
    sigset_t block_set, pending_set;
    struct sigaction sa;

    sigemptyset(&block_set);
    sigaddset(&block_set, SIGINT);
    sigaddset(&block_set, SIGHUP);
    sigaddset(&block_set, SIGABRT);

    if (sigprocmask(SIG_BLOCK, &block_set, NULL) == -1) {
        perror("sigprocmask failed");
        return 1;
    }

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction for SIGINT failed");
        return 1;
    }

    kill(getpid(), SIGINT);
    kill(getpid(), SIGHUP);
    kill(getpid(), SIGABRT);

    sigpending(&pending_set);
    printf("Blocked signals: SIGINT, SIGHUP, SIGABRT\n");
    printf("Pending signals: ");

    for (int i = 1; i < NSIG; i++) {
        if (sigismember(&pending_set, i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}
