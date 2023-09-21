#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define MAX_MESSAGE_SIZE 256

int main() {
    char client_fifo[MAX_MESSAGE_SIZE];
    char message[MAX_MESSAGE_SIZE];

    printf("Enter your name: ");
    fgets(client_fifo, sizeof(client_fifo), stdin);
    client_fifo[strlen(client_fifo) - 1] = '\0';

    int server_fd = open(SERVER_FIFO, O_WRONLY);
    if (server_fd == -1) {
        perror("Client failed to open server FIFO");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter a message to send to the server (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);
        message[strlen(message) - 1] = '\0';

        if (strcmp(message, "exit") == 0) {
            break;
        }
        write(server_fd, message, strlen(message) + 1);

        int client_fd = open(client_fifo, O_RDONLY);
        if (client_fd == -1) {
            perror("Client failed to open client FIFO");
            exit(EXIT_FAILURE);
        }

        char echo[MAX_MESSAGE_SIZE];
        read(client_fd, echo, sizeof(echo));
        printf("Received echo from server: %s\n", echo);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
