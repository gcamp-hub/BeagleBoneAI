////////////////////////////////////////  
// analogIn.c  
//      reports 0-3.3V on P9.33 as 0-4095  
//  Wiring: Jumper a 0-3.3V source to P9.33  
//  
////////////////////////////////////////  
#include <stdio.h>  
#include <unistd.h>  
  
  
int analogRead(){  
     FILE * my_in_pin = fopen("/sys/bus/iio/devices/iio:device0/in_voltage7_raw", "r");//P9.33 on the BBAI  
     char the_voltage[5];//the characters in the file are 0 to 4095  
     fgets(the_voltage,6,my_in_pin);  
     fclose(my_in_pin);  
     printf("Voltage:  %s\n", the_voltage);  
     return 0;  
}  
  
  
int main() {  
     while(1) {  
          analogRead();  
         usleep(1000000);  
      }  
}  