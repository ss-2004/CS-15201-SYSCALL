// Q2 : Write a program to create a thread with default attributes and then change the priority to HIGHPRIORITY.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define HYPR 10

void *thrdFunc(void *arg) {
    printf("This is the thread function\n");
    return NULL;
}

int main() {
    pthread_t thrd;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    if (pthread_create(&thrd, &attr, thrdFunc, NULL) != 0) {
        perror("Thread creation failure!\n");
        return 1;
    }

    struct sched_param param;
    param.sched_priority = HYPR;
    if (pthread_setschedparam(thrd, SCHED_OTHER, &param) != 0) {
        perror("Priority setting failed!\n");
        return 1;
    }

    int policy;
    pthread_getschedparam(thrd, &policy, &param);
    printf("Thread priority now set to : %d\n", param.sched_priority);

    pthread_join(thrd, NULL);
    printf("Thread has completed!\n");
    return 0;

}
