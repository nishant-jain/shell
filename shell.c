#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TRUE 1

void read_command(char *command, char parameters[8][100]){
	char *buffer=malloc(sizeof(char)*1024);
	int i=0;
//	printf("hello\n");
	fgets(buffer,1024,stdin);
//	printf("%s\n",buffer);
	char *pch;
	//space delimited string 'buffer'
	char *abc=strdup(buffer);
	printf("%s\n",abc);
	pch=strtok(abc," ");
	strcpy(command,pch);
	while(pch!=NULL){	
		pch = strtok(NULL, " ");
		//strcpy(parameters[i],pch); //segfault here
		i++;
	}
	
	/*for(i=0;i<1024;i++){
		if(buffer[i]==' '){
			strcpy(command,buffer,i);
			break();
			}
	}
	int j=i;
	int k=0;
	for(;i<1024;i++){
		if(buffer[i]==' '){
			strcpy(parameters[k],buffer[i],
			}
	}*/
}


int main(int argc, char **argv){
	int status;
	while(TRUE){
	printf("shell $");
	char *command=malloc(sizeof(char)*100); 
	char parameters[8][100]; //max 8 parameters
	read_command(command, parameters); 
	printf("out of read\n");
	if(fork()!=0){
		/*parent code*/
		printf("parent\n");
		waitpid(-1,&status,0);

	}else{
		/*child code*/
		int i;
		printf("%s\n",command);
		//for(i=0;i<8;i++){
		//	printf("%s ",parameters[i]);
		//}
		//execv(command,parameters,0);
		}	
	}
	return 0;
}


