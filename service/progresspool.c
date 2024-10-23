#include "head/progresspool.h"

Progress* progressInit(int num){
	Progress* progress = (Progress*)calloc(num,sizeof(Progress));
	for(int i = 0 ; i < num ;i++){
		int local_socket[2];
		socketpair(AF_LOCAL, SOCK_STREAM, 0, local_socket);
		pid_t pid = fork();
		if(pid == 0){
			setpgid(0, 0);
            close(local_socket[0]);
            // 子进程
			progressWork(local_socket[1]);
		}
		else{
			close(local_socket[1]);
            // 父进程
            progress[i].pid = pid;
            progress[i].status = false;
            progress[i].socketId = local_socket[0];
		}
	}	
	return progress;
}


int progressSelect(Progress* progress,int num){
	for(int i = 0 ; i < num ; i++){
		if(progress[i].status == false){
			return i;
		}
	}
	return -1;
}


