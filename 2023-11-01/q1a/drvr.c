/*
 * Q1a : 
 * Use the following Hare and Turtle process blueprint to implement IPC solutions by defining cooperating processes 
 * First use fork() and execvp() to create the processes and develop the application using FIFO files.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

const char *driver_god = "/tmp/driver_god";
const char *driver_tortoise_rw = "/tmp/driver_tortoise_rw";
const char *driver_tortoise_wr = "/tmp/driver_tortoise_wr";
const char *driver_hare_rw = "/tmp/driver_hare_rw";
const char *driver_hare_wr = "/tmp/driver_hare_wr";
const char *hare_tortoise = "/tmp/hare_tortoise";
const char *driver_reporter_wr = "/tmp/driver_reporter_wr";
const char *driver_reporter_rw = "/tmp/driver_reporter_rw";

char *tortoise_args[] = {"./t.out", NULL};
char *hare_args[] = {"./h.out", NULL};
char *reporter_args[] = {"./r.out", NULL};
char *god_args[] = {"./g.out", NULL};

int main() {
    mkfifo(driver_god, 0666);
    mkfifo(driver_tortoise_rw, 0666);
    mkfifo(driver_tortoise_wr, 0666);
    mkfifo(driver_hare_rw, 0666);
    mkfifo(driver_hare_wr, 0666);
    mkfifo(hare_tortoise, 0666);
    mkfifo(driver_reporter_rw, 0666);
    mkfifo(driver_reporter_wr, 0666);

    int tortoise = 0;
    int hare = 0;
    const int TARGET = 50;
    int pid_tortoise, pid_hare, pid_reporter, pid_god;
    if ((pid_tortoise = fork()) == 0)
        execv(tortoise_args[0], tortoise_args);

    int write_tortoise = open(driver_tortoise_wr, O_WRONLY);
    int read_tortoise = open(driver_tortoise_rw, O_RDONLY);
    write(write_tortoise, &tortoise, sizeof(int));
    if ((pid_hare = fork()) == 0)
        execv(hare_args[0], hare_args);

    int write_hare = open(driver_hare_wr, O_WRONLY);
    int read_hare = open(driver_hare_rw, O_RDONLY);
    write(write_hare, &hare, sizeof(int));
    if ((pid_reporter = fork()) == 0)
        execv(reporter_args[0], reporter_args);


    int write_reporter = open(driver_reporter_wr, O_WRONLY);
    int read_reporter = open(driver_reporter_rw, O_RDONLY);

    int winner = 0;
    int share_msg = 0;

    while (1) {
        read(read_tortoise, &tortoise, sizeof(int));
        read(read_hare, &hare, sizeof(int));

        char choice;
        printf("God, do you want to change positions ? (y/n)\n >> ");
        scanf("%c", &choice);

        if (choice == 'y') {
            if ((pid_god = fork()) == 0)
                execv(god_args[0], god_args);

            int read_god = open(driver_god, O_RDONLY);
            read(read_god, &tortoise, sizeof(int));
            read(read_god, &hare, sizeof(int));

            close(read_god);
            wait(NULL);
        }

        if (hare >= TARGET) {
            winner = 1;
            break;
        } else if (tortoise >= TARGET)
            break;

        write(write_reporter, &tortoise, sizeof(int));
        write(write_reporter, &hare, sizeof(int));
        write(write_tortoise, &tortoise, sizeof(int));
        write(write_hare, &hare, sizeof(int));
        read(read_reporter, &share_msg, sizeof(int));
    }

    printf("\nWinner is : %s", (winner == 0) ? "Tortoise\n" : "Hare\n");
    kill(pid_tortoise, SIGTERM);
    kill(pid_hare, SIGTERM);
    kill(pid_reporter, SIGTERM);

    close(write_reporter);
    close(read_hare);
    close(read_tortoise);
    close(write_hare);
    close(write_tortoise);
    return 0;
}
