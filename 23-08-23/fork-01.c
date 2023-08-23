#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_COUNT 200
#define BUFF 100

void main()
{
	pid_t pid;
	int i;
	char buff[BUFF];

	fork();
	pid=getpid();
	for(i=1; i<=MAX_COUNT; i++){
		sprintf(buff, "This line is from pid %d, value = %d\n", pid, i);
		write(1, buff, strlen(buff));
	}
}
