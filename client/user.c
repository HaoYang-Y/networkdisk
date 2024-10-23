#include "head/user.h"

User* userInit(){
	User* user = (User*) calloc(1,sizeof(User));
	if(user == NULL){
		perror("calloc fail : ");
		exit(1);
	}
	user->sigStatus = true;
	return user;
}
