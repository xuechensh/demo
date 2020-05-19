#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MSG_FILE "./msg.txt"

struct msg_info{
	long mtype;
	char mtext[256];
};

int main(){
	int msgid;
	key_t key;
	struct msg_info msg;
	
	if((key = ftok(MSG_FILE, 1)) < 0){
		perror("ftok error");
		return 1;
	}


	if((msgid = msgget(key, IPC_CREAT)) == -1){
		perror("get msg id error");
		return 1;
	}

	msg.mtype = 888;
	sprintf(msg.mtext, "i am client %d", getpid());
	msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

	msgrcv(msgid, &msg, 256, 999, 0);
	printf("type %d , test %s\n",msg.mtype, msg.mtext);

	return 0;
}
