#include "head/epoll.h"

void epollAdd(int epollId,int id){
	struct epoll_event event;
	event.data.fd = id;
	event.events = EPOLLIN;

	epoll_ctl(epollId,EPOLL_CTL_ADD,id,&event);
}
