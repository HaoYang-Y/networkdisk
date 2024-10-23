#include "head/socket.h"

int socketConnect(char* ip,char* port){
	int sockerId = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr4;
	addr4.sin_addr.s_addr = inet_addr(ip);
	addr4.sin_port = htons(atoi(port));
	addr4.sin_family = AF_INET;
	int err_connect = connect(sockerId,(struct sockaddr*)&addr4,sizeof(addr4));
	if(err_connect == -1){
		perror("connect fail : ");
		exit(1);
	}
	return sockerId;
}
