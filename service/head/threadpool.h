#pragma once
#include <pthread.h>
#include <stdlib.h>
#include <string.h>



typedef struct command{
	char cmd[1024];
	char argv[1024];
}Command;
// 定义队列结点
typedef struct node_s{
	Command command;
	struct node_s *pNext;
}Node;

// 定义队列
typedef struct queue_s{
	Node *head;
	Node *end;
	int size;
}Queue;


typedef struct status_s{

	int num; // 子线程的个数
	pthread_t * thread_ids;// 线程的id

	Queue queue;

	pthread_mutex_t lock;
	pthread_cond_t cond;

	int exit_flag;// 退出标记位: 0正常, 1要求退出
}Status;

void *thread_main(void *p);

// 初始化共享的数据
Status* statusInit(int num);

// 启动子线程
void threadInit(Status *status);


void enQueue(Queue *pQueue, int net_fd);
void deQueue(Queue *pQueue);


