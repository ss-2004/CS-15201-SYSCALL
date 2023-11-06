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
    int read_driver = open(driver_reporter_wr, O_RDONLY);
    int write_driver = open(driver_reporter_rw, O_WRONLY);

    int share_msg = 0;
    int tortoise, hare;

    while (1) {
        read(read_driver, &tortoise, sizeof(int));
        read(read_driver, &hare, sizeof(int));

        printf("\n========= STATUS ===========\n");
        printf("Tortoise = %d\n", tortoise);
        printf("Hare = %d\n", hare);

        write(write_driver, &share_msg, sizeof(int));
        if (tortoise >= 50 || hare >= 50)
            break;
    }

    close(read_driver);
    return 0;
}