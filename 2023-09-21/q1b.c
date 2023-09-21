#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_REQUEST "request_fifo"
#define FIFO_RESPONSE "response_fifo"
#define MAX_BUFFER_SIZE 1024

int main() {
    char file_name[MAX_BUFFER_SIZE];
    int request_fd, response_fd;

    mkfifo(FIFO_REQUEST, 0666);
    mkfifo(FIFO_RESPONSE, 0666);

    request_fd = open(FIFO_REQUEST, O_RDONLY);
    if (request_fd == -1) {
        perror("Failed to open request FIFO");
        exit(EXIT_FAILURE);
    }

    read(request_fd, file_name, sizeof(file_name));
    close(request_fd);

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    response_fd = open(FIFO_RESPONSE, O_WRONLY);
    if (response_fd == -1) {
        perror("Failed to open response FIFO");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        write(response_fd, buffer, bytes_read);
    }

    fclose(file);
    close(response_fd);
    return 0;
}
