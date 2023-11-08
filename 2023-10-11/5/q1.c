/*
 * Q1 : 
 * Write a program to handle different types of SIGNALS using the same handler function. 
 * In this program the process will receive different types of signals from system 
 * The process needs to handle SIGINT, SIGHUP, SIGTERM
 * For every interrupt the same handler should inform the type of SIGNAL occurred. 
 * The process need to keep running until it encounters SIGQUIT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void sgnlHndlr(int signum) {
    switch (signum) {
        case SIGINT:
            printf("\nReceived SIGINT!\n");
            break;
        case SIGHUP:
            printf("\nReceived SIGHUP!\n");
            break;
        case SIGTERM:
            printf("\nReceived SIGTERM!\n");
            break;
        default :
            printf("\nReceived unexpected signal!\n");
            break;
    }
}

int main() {
    signal(SIGINT, sgnlHndlr);
    signal(SIGHUP, sgnlHndlr);
    signal(SIGTERM, sgnlHndlr);

    while (1) {
        printf("\nSignal handling in progress...\nPress ^C to send signals\n");
        sleep(2);
    }
    return 0;
}
