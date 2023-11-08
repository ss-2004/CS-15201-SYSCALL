/* Q1 : 
 * Write a C program to create a child process using fork() system call. 
 * Also use wait() system call in parent process such that it gets the return status of its child
 * return status must be printed on console. 
 * Hint: Use 
 * (i) WIFEXITED 
 * (ii) WEXITSTATUS 
 * (iii) WIFSIGNALED 
 * POSIX macros to print the exit status of child process. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t child_pid, wait_pid;
    child_pid = fork();
    int status;

    if (child_pid == -1) {
        perror("Fork failed !");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        printf("Child process is running\n");
        sleep(2);
        exit(42);
    } else {
        printf("Parent is waiting for child to finish...\n");
        wait_pid = wait(&status);

        if (wait_pid == -1) {
            perror("Wait failed!\n");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status))
            printf("Child process exited with status : %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Child process terminated by signal : %d\n", WTERMSIG(status));
    }
    return 0;
}
