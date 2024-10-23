#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct user{
	char username[256];
	char password[256];
	bool sigStatus;
	char nowpath[1024];
}User; 

User* userInit();
