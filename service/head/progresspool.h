#pragma once
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/socket.h>


typedef struct progress{
	pid_t pid;
	bool status;
	int socketId;
}Progress;

Progress* progressInit(int num);
int progressSelect(Progress* progress,int num);
void progressWork(int progressId);
