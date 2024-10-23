#include "head/socket.h"
#include "head/epoll.h"
#include "head/progresspool.h"

#define NumProgress 4
int main()
{
	/*
	 * 服务器等待客户端的连接
	 * 创建多个进程池
	 * 子进程创建多个线程
	 * 如果客户发送请求
	 * 吧客户放入队列中
	 * 等在空闲子进程
	 * 子进程根据客户端的请求
	 * 分配给子线程
	 */
	// 监听并绑定
	int socketId = socketBind("192.168.233.128","8080");
	int err_listen = listen(socketId,10);
	if(err_listen == -1){
		perror("listen fail : ");
		exit(1);
	}
	// 加入epoll
	int epollId = epoll_create(1);
	epollAdd(epollId,socketId);
	// 对进程初始化
	Progress* progresses = progressInit(NumProgress);
	while(1){
		struct epoll_event events[10];
		memset(events,0,sizeof(events));
		int num = epoll_wait(epollId,events,10,-1);
		for(int i = 0 ; i < num ; i++){
			if(events[i].data.fd == socketId){
				int clientId = accept(socketId,NULL,NULL);
				/*
				 * 分给某个进程
				 */
				printf("client=%d\n",clientId);
				int index = progressSelect(progresses,NumProgress);
				while(index == NumProgress){
					index = progressSelect(progresses,NumProgress);
				}
				progresses[index].status = true;
				local_send(progresses[index].socketId,clientId,0);
				close(clientId);
			}
			else{
				char buff[60] = {0};
				recv(events[i].data.fd,buff,sizeof(buff),0);
				for(int k = 0 ; k < NumProgress ; k++){
					if(events[i].data.fd == progresses[k].socketId){
						progresses[k].status = false;
						break;
					}
				}
			}
		}
	}
	return 0;
}

