#include<stdio.h>
#include<unistd.h>
#include<string.h>

#define READ 0
#define WRITE 1

int main() 
{
   int pipefd[2],pipefd1[2];
   int returnstatus;
   char writemessages[100];
   char writemessages2[100];
   char readmessage[100];
   char readmessage2[100];
   returnstatus = pipe(pipefd);
   if (returnstatus == -1) 
   {
      printf("Unable to create pipe\n");
      return 1;
   }
   int pid = fork();
	while(1)
	{
    // Child process
    	if (pid == 0) 
    	{
      	read(pipefd[READ], readmessage, sizeof(readmessage));
	printf("\nMessage from Parent:%s\n",readmessage);
        printf("Enter Child message:\n");
      	fgets(writemessages2,sizeof(writemessages2),stdin);
      	write(pipefd1[WRITE], writemessages2, sizeof(writemessages2));
    	}
    	else    
    	{ //Parent process
	printf("Enter the Parent message:\n");
        fgets(writemessages,sizeof(writemessages),stdin);
      	write(pipefd[WRITE], writemessages, sizeof(writemessages));	
	read(pipefd1[READ], readmessage2, sizeof(readmessage2));
	printf("\nMessage from Child:%s\n",readmessage2);
    	}
	}
    return 0;
}
