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
    printf("Enter the name of the file you want to retrieve from the server: ");
    scanf("%s", file_name);

    request_fd = open(FIFO_REQUEST, O_WRONLY);
    if (request_fd == -1) {
        perror("Failed to open request FIFO");
        exit(EXIT_FAILURE);
    }
    write(request_fd, file_name, strlen(file_name) + 1);
    close(request_fd);

    response_fd = open(FIFO_RESPONSE, O_RDONLY);
    if (response_fd == -1) {
        perror("Failed to open response FIFO");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(response_fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    close(response_fd);

    return 0;
}
