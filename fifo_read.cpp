#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE_PATH "./fifo_file.txt"
#define MAX_FIFO_MSG_SIZE 1024

int main(int argc, char** argv){
	if( -1 == access(FIFO_FILE_PATH,F_OK)){
		printf("fifo file is not exit\n");
		if( 0 != mkfifo(FIFO_FILE_PATH, 444)){
			return -1;
		}
	}

	int fd = open(FIFO_FILE_PATH, O_RDONLY);
	char buffer[MAX_FIFO_MSG_SIZE] = {0};
	int len = read(fd, buffer, MAX_FIFO_MSG_SIZE);
	
	if( len < 0){
		printf(" read fifo file error\n");
		return -1;
	}

	printf("read msg %s\n",buffer);

	return 0;
}

