#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100

void *calSQRT(void *arg) {
    double *rslt = (double *) arg;
    for (int i = 0; i < SIZE; i++) {
        rslt[i] = sqrt((double) i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thrd;
    double rslt[SIZE];

    if (pthread_create(&thrd, NULL, calSQRT, rslt) != 0) {
        perror("Thread creation failed!\n");
        return 1;
    }

    printf("Num\tSqrt\n");
    pthread_join(thrd, NULL);
    for (int i = 0; i < SIZE; i++)
        printf("%d\t%f\n", i, rslt[i]);
    return 0;
}