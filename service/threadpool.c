#include "head/threadpool.h"

void *thread_main(void *p){
	Status* status = (Status*)p;
	if(pthread_self() == status->thread_ids[0]){

	}
	if(pthread_self() == status->thread_ids[1]){

	}
	if(pthread_self() == status->thread_ids[2]){

	}
}
// 初始化共享的数据
Status* statusInit(int num){
	Status* status = (Status*)calloc(1,sizeof(Status));
	status->num = num;
	status->thread_ids = (pthread_t*)malloc(num*sizeof(pthread_t));
	threadInit(status);
	memset(&status->queue ,0,sizeof(Queue));
	pthread_mutex_init(&status->lock, NULL);
    pthread_cond_init(&status->cond, NULL);
	status->exit_flag = 0;
	return status;
}

// 启动子线程
void threadInit(Status *status){
	for(int i = 0 ; i < status->num ;i++){
		pthread_create(&status->thread_ids[i],NULL,thread_main,status);
	}
}

/*
void enQueue(Queue* pQueue, Command command){
	Node* p = (Node*)calloc(1,sizeof(Node));
	p->command = command;

	if(pQueue->size == 0){
		pQueue->head = p;
		pQueue->end = p;
	}
	else{
		pQueue->end->pNext = p;
		pQueue->end = p;
	}
	pQueue->size++;
}
void deQueue(Queue *pQueue){
	Node* p = pQueue->head;
	pQueue->head = p->pNext;
	if(pQueue->size == 1){
		 
	} 
}
*/

