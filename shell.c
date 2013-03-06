#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include<unistd.h>
#define TRUE 1

int read_command (char *command, char *parameters[])
{
  char *buffer = malloc (sizeof (char) * 1024);
  int i = 0;

//    printf("hello\n");
  fgets (buffer, 1024, stdin);
  //  printf("%ld\n",strlen(buffer));
  buffer[strlen (buffer) - 1] = '\0';
//    printf("%s\n",buffer);
  char *pch = malloc (sizeof (char) * 1024);
  //space delimited string 'buffer'
  char *abc = strdup (buffer);
//    printf("%s\n",abc);
  pch = strtok (abc, " ");
  strcpy (command, pch);
  //strcpy(parameters[1],"abc");

  while (pch != NULL)
    {
      strcpy (parameters[i], pch);
      pch = strtok (NULL, " ");

      //segfault here
      i++;
    }
  //*parameters[i]=NULL;
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
     } */
  return i;
}


int main (int argc, char **argv)
{
  int status;
  int argcount;
  while (TRUE)
    {
      printf ("shell $");
      char *command = malloc (sizeof (char) * 100);
      char *parameters[8];
      parameters[0] = malloc (sizeof (char *) * 1);	//max 7 parameters, 8th null
      parameters[1] = malloc (sizeof (char *) * 1);
      parameters[2] = malloc (sizeof (char *) * 1);
      parameters[3] = malloc (sizeof (char *) * 1);
      parameters[4] = malloc (sizeof (char *) * 1);
      parameters[5] = malloc (sizeof (char *) * 1);
      parameters[6] = malloc (sizeof (char *) * 1);
      parameters[7] = malloc (sizeof (char *) * 1);
      argcount = read_command (command, parameters);
      //printf("out of read\n");
      //strcpy(parameters[0],"hello");
      if (fork () != 0)
	{
	  /*parent code */
//        printf("parent\n");
	  waitpid (-1, &status, 0);

	}
      else
	{
	  /*child code */
	  int i;
	  //printf("%s \n",command);
//        printf("argcount%d\n",argcount);
	  char *temp = malloc (sizeof (char) * 100);
//        strcpy(temp,parameters[argcount-1]);
	  //    strncpy(parameters[argcount-1],temp,strlen(temp));
//        parameters[argcount-1]="-l";
	  /*    for(i=0;i<argcount;i++){
	     printf("%dpara%sqara\n",i,parameters[i]);
	     }
	   */
	  parameters[argcount] = NULL;
	  char *root_path = "/bin/";
//        printf("%s %s\n",root_path, command);
	  char *path = malloc (sizeof (char) * 105);
	  strcat (path, root_path);
	  strcat (path, command);
	  //printf("hellooooooooooooooooooooooo%s\n",path);
	  execv (path, parameters);
	  //printf("%d %s\n",p,strerror(errno));
	}
    }
  return 0;
}
