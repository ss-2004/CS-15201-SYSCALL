/* Q2 : 
 * Redirecting Output: “ls -l | sort” 
 * Use FIFO to develop a program where one process will execute “ls -l”
 * The output of the command will act as input for other process which will execute “sort” on it.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char input_fifo[] = "input_fifo";
    char output_fifo[] = "output_fifo";

    mkfifo(input_fifo, 0666);
    mkfifo(output_fifo, 0666);
    pid_t pid_ls, pid_sort;

    if ((pid_ls = fork()) == -1) {
        perror("Fork for ls -l failed");
        exit(EXIT_FAILURE);
    } else if (pid_ls == 0) {
        int output_fd = open(output_fifo, O_WRONLY);
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);

        execlp("ls", "ls", "-l", NULL);
        perror("Exec ls -l failed");
        exit(EXIT_FAILURE);
    }

    if ((pid_sort = fork()) == -1) {
        perror("Fork for sort failed");
        exit(EXIT_FAILURE);
    } else if (pid_sort == 0) {
        int input_fd = open(output_fifo, O_RDONLY);
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);

        execlp("sort", "sort", NULL);
        perror("Exec sort failed");
        exit(EXIT_FAILURE);
    }

    close(input_fifo);
    close(output_fifo);
    waitpid(pid_ls, NULL, 0);
    waitpid(pid_sort, NULL, 0);
    return 0;
}
