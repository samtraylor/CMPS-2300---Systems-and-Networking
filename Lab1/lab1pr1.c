#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	printf("Hello world, i'm (pid:%d)\n", (int) getpid());
	int rc = fork();
	rc = fork();
	if (rc == 0) {//child
		printf("hello, i'm (pid:%d)\n ", (int) getpid());
	}
	else {
		printf("hello, i'm (pid:%d)\n ", (int) getpid());
	} 
return 0;
}