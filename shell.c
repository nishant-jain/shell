#include<stdio.h>
#define TRUE 1
int main(int argc, char **argv){
	int status;
	while(TRUE){
	printf("shell $");
	read_command(command, parameters); 
	
	if(fork()!=0){
		/*parent code*/
		waitpid(-1,&status,0);

	}else{
		/*child code*/
		execv(command,parameters,0);
		}	
	}
	return 0;
}

void read_command(char *command, char **parameters){
	
	
}
