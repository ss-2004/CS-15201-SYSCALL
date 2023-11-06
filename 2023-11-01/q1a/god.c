#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

const char *driver_god = "/tmp/driver_god";

int main() {
    int tortoise, hare;
    int write_god = open(driver_god, O_WRONLY);

    printf("Give new position for tortoise : ");
    scanf("%d", &tortoise);
    printf("Give new position for hare : ");
    scanf("%d", &hare);

    write(write_god, &tortoise, sizeof(int));
    write(write_god, &hare, sizeof(int));

    close(write_god);
    return 0;

}