#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
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

int main() {
    int read_driver = open(driver_hare_wr, O_RDONLY);
    int write_driver = open(driver_hare_rw, O_WRONLY);
    int read_tortoise = open(hare_tortoise, O_RDONLY);

    int hare = 0;
    int tortoise = 0;
    const int steps = 3;
    const int MIN_DIST_FOR_SLEEP = 10;
    const int SLEEP_TIME = 5;
    int sleep_counter = -1;

    while (1) {
        if (sleep_counter != -1) {
            sleep_counter++;

            read(read_driver, &hare, sizeof(int));
            read(read_tortoise, &tortoise, sizeof(int));
            write(write_driver, &hare, sizeof(int));

            if (sleep_counter >= SLEEP_TIME) {
                sleep_counter = -1;
            }
            continue;
        }
        read(read_driver, &hare, sizeof(int));
        read(read_tortoise, &tortoise, sizeof(int));

        hare += steps;
        write(write_driver, &hare, sizeof(int));

        if (hare - tortoise >= MIN_DIST_FOR_SLEEP)
            sleep_counter = 0;
    }

    close(read_driver);
    close(write_driver);
    close(read_tortoise);
    return 0;
}