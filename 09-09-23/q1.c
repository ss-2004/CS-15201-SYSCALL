#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_SIZE 100

void push(int value) {
    int fd = open("stack.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[20];
    int n = snprintf(buffer, sizeof(buffer), "%d\n", value);
    write(fd, buffer, n);

    close(fd);
}

int pop() {
    int value;
    int fd = open("stack.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("Error seeking file");
        close(fd);
        exit(1);
    }

    off_t offset = size - 2;
    while (offset >= 0) {
        lseek(fd, offset, SEEK_SET);
        if (read(fd, &value, sizeof(int)) != sizeof(int)) {
            perror("Error reading from file");
            close(fd);
            exit(1);
        }
        if (value == '\n') {
            offset -= 2;
            continue;
        }
        break;
    }

    ftruncate(fd, offset);

    close(fd);
    return value;
}

int main() {
    int choice, value;

    while (1) {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                printf("%d pushed to stack.\n", value);
                break;
            case 2:
                if (access("stack.txt", F_OK) == -1) {
                    printf("Stack is empty.\n");
                } else {
                    value = pop();
                    printf("%d popped from stack.\n", value);
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please select again.\n");
        }
    }

    return 0;
}
