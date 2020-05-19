#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/msg.h>

//用于创建全局唯一的key
#define MSG_FILE "./msg.txt"

//消息结构体
struct msg_info{
	long m_Type;
	char mtext[256];
};

int main(){
	int msg_id;
	key_t key;
	struct msg_info msg;

	//获取key值
	if( (key = ftok(MSG_FILE, 1)) < 0){
		perror("ftok error");
		return 1;
	}

	printf("key = %d", key);

	if((msg_id = msgget(key, IPC_CREAT|777)) < 0){
		perror("msgget error");
		return -1;
	}

	printf("Msg id = %d, pid = %d\n", msg_id, getpid());

	while(1){
		msgrcv(msg_id, &msg, 256, 888, 0);
		printf("msg type = %d, msg = %s\n", msg.m_Type, msg.mtext);

		msg.m_Type = 999;
		sprintf(msg.mtext, "hello, I am server %d", getpid());
		msgsnd(msg_id, &msg, sizeof(msg.mtext), 0);
	}

	return 0;
}
