#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define MAX_CLIENTS 5
#define MAX_MESSAGE_SIZE 256

int main() {
    char client_fifo[MAX_CLIENTS][MAX_MESSAGE_SIZE];
    int client_fd[MAX_CLIENTS];
    int num_clients = 0;

    mkfifo(SERVER_FIFO, 0666);
    printf("Server created the FIFO: %s\n", SERVER_FIFO);

    int server_fd = open(SERVER_FIFO, O_RDWR);
    if (server_fd == -1) {
        perror("Server failed to open FIFO");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char message[MAX_MESSAGE_SIZE];

        if (read(server_fd, message, sizeof(message)) > 0) {
            printf("Received from client: %s\n", message);

            if (num_clients < MAX_CLIENTS) {
                sprintf(client_fifo[num_clients], "/tmp/client_fifo%d", num_clients);
                mkfifo(client_fifo[num_clients], 0666);
                client_fd[num_clients] = open(client_fifo[num_clients], O_WRONLY);
                if (client_fd[num_clients] == -1) {
                    perror("Server failed to open client FIFO");
                    exit(EXIT_FAILURE);
                }
                num_clients++;
            }

            for (int i = 0; i < num_clients; i++) {
                write(client_fd[i], message, strlen(message) + 1);
            }
        }
    }

    close(server_fd);
    unlink(SERVER_FIFO);
    return 0;
}
