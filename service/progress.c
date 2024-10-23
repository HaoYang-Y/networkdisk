#include "head/progresspool.h"
#include "head/socket.h"
#include "head/threadpool.h"

#define  NumThread 3

void progressWork(int progressId){
	while(1){
		int clientId;
		int flag;
		local_recv(progressId,&clientId,&flag);
		// 创建状态
		Status* status = statusInit(NumThread);
		printf("clientId = %d\n",clientId);
		char message[1024];
		while(1){
			recv(clientId,&message,sizeof(message),-1);
			if(true){//下载

			}
			else if(true){//上传


			}
			else{//普通命令

			}
		}
	}
}
