/* Simple send message example for communicating with the
*  UART that is connected to a desktop PC.  */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>

// dev/ttyS2
//P9.21 CPU_TX <-> TTL RX
//P9.22 CPU RX <-> TTL_TX
//P9.0  <-> TTL GND
int main(int argc, char *argv[]){
   int file, count;
   if(argc!=2){
       printf("Please pass a message string to send, exiting!\n");
       return -2;
   }
   if ((file = open("/dev/ttyS2", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the device.\n");
      return -1;
   }
   struct termios options;
   tcgetattr(file, &options);
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;
   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);

   // send the string plus the null character
   if ((count = write(file, argv[1], strlen(argv[1])+1))<0){
      perror("UART: Failed to write to the output.\n");
      return -1;
   }
   close(file);
   printf("Finished sending the message, exiting.\n");
   return 0;
}
