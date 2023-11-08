/*
 * Q2 : 
 * Write a program to define a handler for SIGALRM signal.
 * In this program you need to set the alarm in main process as defined by the user in seconds. 
 * The process then generate SIGALRM signal after 2 seconds. 
 * The signal handler needs to identify the SIGALRM. 
 * This process needs to iterated for a maximum of 5 times. 
 * After setting the alarm for 5 times the program will terminate.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int alrmc = 0;

void sgnlHndlr(int signum) {
    if (signum == SIGALRM) {
        alrmc++;
        printf("\nReceived SIGALRM %d time(s)\n", alrmc);
        if (alrmc >= 5) {
            printf("\nMax alarm count reached!\n\tEXITING...\n");
            sleep(1);
            exit(0);
        }
    }
}

int main() {
    signal(SIGALRM, sgnlHndlr);
    int i, alrmint;
    printf("Enter alarm interval : ");
    scanf("%d", &alrmint);

    for (i = 0; i < 5; i++) {
        printf("Setting alarm for %ds...\n", alrmint);
        alarm(alrmint);
        pause();
    }
    return 0;
}
