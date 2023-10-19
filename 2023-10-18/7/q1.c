#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THR 10
#define NUM_PRN 1

void *thrdFunc(void *arg) {
    int thrdnum = *((int *) arg);
    for (int i = 0; i < NUM_PRN; i++) {
        printf("Hello world from thread %d\n", thrdnum);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thrds[NUM_THR];
    int thrdargs[NUM_THR];

    for (int i = 0; i < NUM_THR; i++) {
        thrdargs[i] = i;
        int result = pthread_create(&thrds[i], NULL, thrdFunc, &thrdargs[i]);
        sleep(1);

        if (result != 0) {
            perror("Creation failure!\n");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THR; i++)
        pthread_join(thrds[i], NULL);
    printf("All threads have completed!\n");
    return 0;
}