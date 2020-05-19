#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define MAX_MSG_SIZE 1024

int main(int argc, char** argv){
	pid_t pid = -1;

	int pipefd[2] = {0};


	if(0 != pipe(pipefd)){
		printf("create pipe error\n");
		return 0;
	}

	pid = fork();

	if( pid < 0){
		printf("call fork error\n");
	}
	else if( pid > 0){
		char msg[MAX_MSG_SIZE] = {0};
		close(pipefd[1]);
		read(pipefd[0], msg, MAX_MSG_SIZE);
		printf("Recv: %s\n",msg);
	}
	else{
		const char* msg = "hello world";
		close(pipefd[0]);
		write(pipefd[1], msg, strlen(msg));
	}

	printf(" exit pid = %d\n",getpid());
	return 0;

}

