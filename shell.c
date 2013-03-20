#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include<unistd.h>
#define TRUE 1
#define STD_INPUT 0
#define STD_OUTPUT 1

int parse_command(char *abc, char* command, char *parameters[]){
int i=0;
  char * pch = malloc (sizeof (char) * 1024);
  pch = strtok (abc, " ");
  strcpy (command, pch);

  while (pch != NULL)
    {
      strcpy (parameters[i], pch);
      pch = strtok (NULL, " ");
      i++;
    }
parameters[i] = NULL;    
    return i;
}

int
read_command (char *command, char *parameters[],char *command1, char *parameters1[],int *flag)
{
  char *buffer = malloc (sizeof (char) * 1024);
  int i = 0;
  fgets (buffer, 1024, stdin);
  
  buffer[strlen (buffer) - 1] = '\0';
  if(strpbrk(buffer,"&")!=NULL)
	*flag=1;

  else
	*flag=0;
  char *new_buffer=strtok(buffer,"&");
  char *pipe;
  

  //space delimited string 'buffer'
  char *abc = strdup (new_buffer);
  pipe=strpbrk(abc,"|");
  if(pipe==NULL){
  return parse_command(abc,command,parameters);
}
	else{
	char *a=malloc(sizeof(char*));
	char *b=malloc(sizeof(char*));	
	char *c= strtok (abc, "|");
  strcpy (a, c);
  
     c = strtok (NULL, "|");
  strcpy (b, c);
parse_command(a,command,parameters);
parse_command(b,command1,parameters1);
return -1;
}
}

void pipeline (char *process1, char *parameters1[], char *process2,
	  char *parameters2[])
{ 
	//from minix3 textbook
  
  int status;
  if(fork()!=0){
  	waitpid (-1, &status, 0);
  }
  else{
  int fd[2];
  pipe (&fd[0]);
  if (fork () != 0)
    {
			/* The parent process executes these statements. */
      close (fd[0]);
			/* process 1 does not need to read from pipe */
      close (STD_OUTPUT);
			/* prepare for new standard output */
     dup (fd[1]);
			/* set standard output to fd[1] */
      close (fd[1]);
			/* this file descriptor not needed any more */
	char *root_path = "/bin/";
	  char *path = malloc (sizeof (char) * 105);
	  strcat (path, root_path);
	  strcat (path, process1);
	  execv (path, parameters1);

    }
  else
    {
			/* The child process executes these statements. */
      close (fd[1]);
			/* process 2 does not need to write to pipe */
      close (STD_INPUT);
			/* prepare for new standard input */
	printf("child %d",dup (fd[0]));
			/* set standard input to fd[0] */
      close (fd[0]);
			/* this file descriptor not needed any more */
	char *root_path = "/bin/";
	  char *path = malloc (sizeof (char) * 105);
	  strcat (path, root_path);
	  strcat (path, process2);
	  execv (path, parameters2);

    }
    close(fd[1]);
    close(fd[2]);
  }
}

void no_pipe(char *command,char *parameters[],int status,int flag){
      if (fork () != 0)
	{
	  /*parent code */
//        printf("parent\n");
	if(flag==0)
	  waitpid (-1, &status, 0);
	
	}
      else
	{
	  /*child code */
	  int i;
	 // char *temp = malloc (sizeof (char) * 100);
	  //parameters[argcount] = NULL;
	  char *root_path = "/bin/";
	  char *path = malloc (sizeof (char) * 105);
	  strcat (path, root_path);
	  strcat (path, command);
	  execv (path, parameters);
//        i=execl("/bin/ls","ls","-l",NULL);

	}
}


int
main (int argc, char **argv)
{
  int status;
  int argcount;
  int flag=0; //for running process in background
  while (TRUE)
    {
      printf ("nsh:$");
      char *command = malloc (sizeof (char) * 100);
      char *command1 = malloc (sizeof (char) * 100);
      char *parameters[8],*parameters1[8];
      parameters[0] = malloc (sizeof (char *) * 1);	//max 7 parameters, 8th null
      parameters[1] = malloc (sizeof (char *) * 1);
      parameters[2] = malloc (sizeof (char *) * 1);
      parameters[3] = malloc (sizeof (char *) * 1);
      parameters[4] = malloc (sizeof (char *) * 1);
      parameters[5] = malloc (sizeof (char *) * 1);
      parameters[6] = malloc (sizeof (char *) * 1);
      parameters[7] = malloc (sizeof (char *) * 1);
       parameters1[0] = malloc (sizeof (char *) * 1);	//max 7 parameters, 8th null
      parameters1[1] = malloc (sizeof (char *) * 1);
      parameters1[2] = malloc (sizeof (char *) * 1);
      parameters1[3] = malloc (sizeof (char *) * 1);
      parameters1[4] = malloc (sizeof (char *) * 1);
      parameters1[5] = malloc (sizeof (char *) * 1);
      parameters1[6] = malloc (sizeof (char *) * 1);
      parameters1[7] = malloc (sizeof (char *) * 1);
      argcount = read_command (command, parameters,command1,parameters1,&flag);
      
      if (strcmp (command, "quit") == 0)
	{
	  printf ("Bye\n");
	  break;
	}
	if(argcount==-1){
	printf("pipe\n %s \n %s \n",command, command1);
	
	pipeline(command,parameters,command1,parameters1);
	}else
      no_pipe(command,parameters,status,flag);
    }
  return 0;
}
