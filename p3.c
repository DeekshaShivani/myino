#include<stdio.h>
#include<unistd.h>
#define READ 0
#define WRITE 1
int main() {

int pipefds[2];
int pipefds11[2];
   int returnstatus;
   int pid=-1, pid2=-1;
   int pid3=-1,pid4=-1;
   
   char writemessages[2][30];
    for(int i=0;i<2;i++)
    {
       printf("Enter a string %d:",i+1);
       scanf(" %[^\n]",writemessages[i]);
    }
    
   
   char readmessage[30];
   returnstatus = pipe(pipefds);
  
   if (returnstatus == -1) {
      printf("Unable to create pipe\n");
      return 1;
   }
  
   pid = fork();
   // Child process
   if (pid == 0) {
	 printf("pid %d \n",pid);	
      read(pipefds[READ], readmessage, sizeof(readmessage));
      printf("Child1 Process - Reading from pipe – Message 1 is %s\n", readmessage);
      
      printf("Parent Process - Writing to pipe - Message 2 is %s\n", writemessages[1]);
      write(pipefds[WRITE], writemessages[1], sizeof(writemessages[1]));
      
   
   }
   else { //Parent process
	 printf("pid %d \n",pid);	
      printf("Parent Process - Writing to pipe - Message 1 is %s\n", writemessages[0]);
      write(pipefds[WRITE], writemessages[0], sizeof(writemessages[0]));
       close(pipefds[0]);
      	
      read(pipefds[READ], readmessage, sizeof(readmessage));
      printf("Child1 Process - Reading from pipe – Message 2 is %s\n", readmessage);
      
     }
   return 0;
}

