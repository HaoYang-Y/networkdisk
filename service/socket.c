#include "head/socket.h"

int socketBind(char* ip,char* port){
	int socketId = socket(AF_INET,SOCK_STREAM,0);
	int reuse = 1;
	setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	struct sockaddr_in addr4;
	addr4.sin_addr.s_addr = inet_addr(ip);
	addr4.sin_port = htons(atoi(port));
	addr4.sin_family = AF_INET;

	int err_bind = bind(socketId,(struct sockaddr*)&addr4,sizeof(addr4));
	if(err_bind == -1){
		perror("bind fail : ");
		exit(1);
	}
	return socketId;
}

void local_send(int progressId, int clientId, int flag){

	struct msghdr msg;// 控制本地socket发送的数据
	memset(&msg, 0, sizeof(msg));

	// 正文信息
	struct iovec iov[1];
	iov[0].iov_base = &flag;
	iov[0].iov_len = sizeof(int);

	msg.msg_iov = iov;
	msg.msg_iovlen =1;

	// 控制信息
	struct cmsghdr *cms = (struct cmsghdr *) malloc( CMSG_LEN(sizeof(int)) );
	cms->cmsg_len = CMSG_LEN(sizeof(int));
	cms->cmsg_level = SOL_SOCKET;
	cms->cmsg_type = SCM_RIGHTS;

	void *p =  CMSG_DATA(cms);
	int *fd = (int *)p;
	*fd = clientId;

	msg.msg_control = cms;
	msg.msg_controllen = CMSG_LEN(sizeof(int));


	sendmsg(progressId,  &msg,  0);
}

void local_recv(int progrssId, int *clientId, int *status){

	struct msghdr msg;// 控制本地socket发送的数据
	memset(&msg, 0, sizeof(msg));

	// 正文信息
	int *flag = (int *)malloc(sizeof(int));
	struct iovec iov[1];
	iov[0].iov_base = flag;
	iov[0].iov_len = sizeof(int);

	msg.msg_iov = iov;
	msg.msg_iovlen =1;


	// 控制信息
	struct cmsghdr *cms = (struct cmsghdr *) malloc( CMSG_LEN(sizeof(int)) );
	cms->cmsg_len = CMSG_LEN(sizeof(int));
	cms->cmsg_level = SOL_SOCKET;
	cms->cmsg_type = SCM_RIGHTS;


	msg.msg_control = cms;
	msg.msg_controllen = CMSG_LEN(sizeof(int));

	// 接收数据: 从本地socket
	recvmsg(progrssId, &msg, 0);

	*status = *flag;

	void *p =  CMSG_DATA(cms);
	int *fd = (int *)p;

	*clientId = *fd;
}
