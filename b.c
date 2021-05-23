#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"
#define FIFO_FILE2 "MYFIFO2"
int main() {
   int fd,fd1;
   char readbuf[80];
   char end[10];
   int to_end;
   int read_bytes;
   mknod(FIFO_FILE, S_IFIFO|0640, 0);
   strcpy(end, "end");
   int end_process;
   int stringlen;
   char end_str[5];
   printf("FIFO_CLIENT B: Sends messages to C Received from A infinitely\n");
   fd1 = open(FIFO_FILE2, O_CREAT|O_WRONLY);
   strcpy(end_str, "end");
   while(1) 
   {
      fd = open(FIFO_FILE, O_RDONLY);
      memset(readbuf,0,sizeof(readbuf)); 	
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      printf("Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      to_end = strcmp(readbuf, end);
      stringlen = strlen(readbuf);
      readbuf[stringlen] = '\0';
      end_process = strcmp(readbuf, end_str);
      if (end_process != 0) 
      {
         write(fd1, readbuf, strlen(readbuf));
         printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
      } 
      else 
      {
         write(fd1, readbuf, strlen(readbuf));
         printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd);
         close(fd1);
         break;
      }
   }
   return 0;
}
