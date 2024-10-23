#include "head/socket.h"
#include "head/user.h"

int main()
{
	/*
	 * 客户端和服务器连接
	 * while(1)
	 * 如果用户没有登入
	 *	提示登入、注册、退出
	 * 如果用户以登入
	 * 提示用户可以进行的操作
	 */
	//客户端和服务器连接
	int socketId = socketConnect("192.168.233.128","8080");
	User* user = userInit();
	while(1){
		if(user->sigStatus == false){

		}
		else{

		}
	}
	return 0;
}

