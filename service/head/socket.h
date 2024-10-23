#pragma once

#include <sys/socket.h>
#include <netinet/in.h>                                                                                                           
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int socketBind(char* ip,char* port);
void local_send(int progressId, int clientId, int flag);
void local_recv(int progrssId, int *clientId, int *status);
