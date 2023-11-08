/*
 * Q1b :
 * Use the following Hare and Turtle process blueprint to implement IPC solutions by defining cooperating processes
 * First use fork() and execvp() to create the processes and develop the application using pthreads (shared memory).
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

long hare = 0;
long tortoise = 0;
long hare_time = 0;
long tortoise_time = 0;

const long TARGET = 5e8;
const long STEPS = 5;
const long MIN_DIST_FOR_SLEEP = 1e8;

pthread_mutex_t tortoise_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t hare_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t terminal_mutex = PTHREAD_MUTEX_INITIALIZER;

long getRandomPosition() {
    return rand() % (TARGET + 1);
}

void *tortoise_turn(void *args) {

    while (tortoise < TARGET) {
        pthread_mutex_lock(&tortoise_mutex);
        tortoise++;
        tortoise_time++;
        pthread_mutex_unlock(&tortoise_mutex);
    }
    return (void *) 0;

}

void *hare_turn(void *args) {
    while (hare < TARGET) {
        if (hare - tortoise >= MIN_DIST_FOR_SLEEP) {
            long sleep_time = rand() % (100000);
            hare_time += sleep_time;
            long random_sleep = rand() % 1000;
            usleep(random_sleep);
        }

        pthread_mutex_lock(&hare_mutex);
        hare += STEPS;
        hare_time++;
        pthread_mutex_unlock(&hare_mutex);
    }
    return (void *) 0;

}

void *reporter_turn(void *args) {
    while (tortoise < TARGET || hare < TARGET) {
        pthread_mutex_lock(&terminal_mutex);

        printf("\n================= RACE STATUS ==================\n");
        printf("\n Tortoise is at position : %ld\t, at time : %ld\n", tortoise, tortoise_time);
        printf("\n Hare is at position     : %ld\t, at time : %ld\n", hare, hare_time);

        pthread_mutex_unlock(&terminal_mutex);
        usleep(500);
    }
    return (void *) 0;

}

void *god_turn(void *args) {
    while (tortoise < TARGET || hare < TARGET) {
        pthread_mutex_lock(&terminal_mutex);
        pthread_mutex_lock(&tortoise_mutex);
        pthread_mutex_lock(&hare_mutex);

        if (((double) rand() / (RAND_MAX)) >= 0.75) {
            printf("\n God has changed positions...\n");
            printf("\n========= NEW POSITIONS ===========\n\n");
            if (tortoise < TARGET) {
                tortoise = getRandomPosition();
                printf(" Tortoise = %ld\n", tortoise);
            }
            if (hare < TARGET) {
                hare = getRandomPosition();
                printf(" Hare     = %ld\n", hare);
            }
        } else {
            pthread_mutex_unlock(&terminal_mutex);
            pthread_mutex_unlock(&tortoise_mutex);
            pthread_mutex_unlock(&hare_mutex);
            usleep(500);
            continue;

        }

        pthread_mutex_unlock(&terminal_mutex);
        pthread_mutex_unlock(&tortoise_mutex);
        pthread_mutex_unlock(&hare_mutex);

    }
    return (void *) 0;

}

int main() {
    srand(time(NULL));
    pthread_t tortoise_tid, hare_tid, reporter_tid, god_tid;

    pthread_create(&tortoise_tid, NULL, tortoise_turn, NULL);
    pthread_create(&hare_tid, NULL, hare_turn, NULL);
    pthread_create(&reporter_tid, NULL, reporter_turn, NULL);
    pthread_create(&god_tid, NULL, god_turn, NULL);

    pthread_join(tortoise_tid, NULL);
    pthread_join(hare_tid, NULL);
    pthread_join(reporter_tid, NULL);
    pthread_join(god_tid, NULL);

    printf("\n======================= RACE IS OVER ===========================\n");
    printf("\n The results are as follows : \n\n");
    printf("\tTime taken by tortoise : %ld iterations\n", tortoise_time);
    printf("\tTime taken by hare     : %ld iterations\n", hare_time);

    if (tortoise_time < hare_time) {
        printf("\n\tWINNER of the race is 'tortoise'\n");
    } else if (tortoise_time > hare_time) {
        printf("\n\tWINNER of the race is 'hare'.\n");
    } else {
        printf("\n\tThe race is drawn\n");
    }
    printf("\n================================================================\n");
    return 0;

}
