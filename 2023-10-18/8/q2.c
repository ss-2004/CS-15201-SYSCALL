/*
 * Q2 : 
 * The Program should demonstrate the use of several Pthread condition variable
 * The main routine creates three threads. 
 * Two of the threads perform work and update a variable "race".
 * The first thread add 3 in the “race” and second thread subtract 1 from the “race”. 
 * The third thread waits until the count variable reaches 100.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TARGET_VALUE 100

int race = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void *increment_thread(void *arg) {
    for (int i = 0; i < TARGET_VALUE; i++) {
        pthread_mutex_lock(&mutex);
        race += 3;
        printf("Incremented: race = %d\n", race);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condition);
        usleep(10000);
    }
    pthread_exit(NULL);
}

void *decrement_thread(void *arg) {
    for (int i = 0; i < TARGET_VALUE; i++) {
        pthread_mutex_lock(&mutex);
        race -= 1;
        printf("Decremented: race = %d\n", race);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condition);
        usleep(10000);
    }
    pthread_exit(NULL);
}

void *wait_thread(void *arg) {
    pthread_mutex_lock(&mutex);
    while (race < TARGET_VALUE)
        pthread_cond_wait(&condition, &mutex);
    printf("Waiting thread: race = %d (reached 100)\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2, thread3;

    if (pthread_create(&thread1, NULL, increment_thread, NULL) != 0) {
        perror("Error creating thread 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, decrement_thread, NULL) != 0) {
        perror("Error creating thread 2");
        return 1;
    }

    if (pthread_create(&thread3, NULL, wait_thread, NULL) != 0) {
        perror("Error creating thread 3");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    return 0;
}
