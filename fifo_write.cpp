#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE_PATH "./fifo_file.txt"

int main(int argc, char** argv){
	if( -1 == access(FIFO_FILE_PATH, F_OK)){
		printf("fifo file not exit\n");
		if ( 0 != mkfifo(FIFO_FILE_PATH, 777)){
			printf("create fifle error\n");
			return -1;
		}
	}

	int fd = open(FIFO_FILE_PATH,O_WRONLY);

	if( -1 == fd){
		printf("open fail\n");
		return -1;
	}

	const char* msg = "abcdefg";
	int len = strlen(msg);

	if( write(fd, msg, len) < len){
		printf(" only write");
	}

	return 0;
}
