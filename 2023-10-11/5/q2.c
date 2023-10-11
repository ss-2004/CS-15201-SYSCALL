// Q2
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
