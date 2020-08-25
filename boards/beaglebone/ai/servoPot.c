////////////////////////////////////////  
//  servoPot.c  
//      reads a pot and translates it to  
//      a servos position.  
//  Wiring: Jumper P8.19 to a servo signal through a 220ohm resistor  
//          Hook a potentiometers variable voltage to P9.03   
////////////////////////////////////////  

#include <stdio.h>  
#include <unistd.h>  
int analogRead(){  
    int i;  
    FILE * my_in_pin = fopen("/sys/bus/iio/devices/iio:device0/in_voltage7_raw", "r");//P9.33 on the BBAI  
    char the_voltage[5];//the characters in the file are 0 to 4095  
    fgets(the_voltage,6,my_in_pin);  
    fclose(my_in_pin);  
    printf("Voltage:  %s\n", the_voltage);  
    sscanf(the_voltage, "%d", &i);  
    return (i);  
}  
  
  
void setupPWM() {  
    FILE *period, *pwm;  
    pwm = fopen("/sys/class/pwm/pwm-0:0/enable", "w");  
    fseek(pwm,0,SEEK_SET);  
    fprintf(pwm,"%d",1);  
    fflush(pwm);  
    fclose(pwm);  
      
      
    period = fopen("/sys/class/pwm/pwm-0:0/period", "w");  
    fseek(period,0,SEEK_SET);  
    fprintf(period,"%d",20000000);//20ms  
    fflush(period);  
    fclose(period);  
      
}  
void pwm_duty(int the_duty_multiplier)  
{  
    FILE *duty; int duty_calc;  
    duty = fopen("/sys/class/pwm/pwm-0:0/duty_cycle", "w");  
    fseek(duty,0,SEEK_SET);  
    duty_calc=(600000 + (1700000*(float)((float)the_duty_multiplier/4095))) ;  
    printf("Duty: %d\n", duty_calc);//1ms  
    fprintf(duty,"%d",duty_calc);//1ms  
    fflush(duty);  
    fclose(duty);  
}  
  
  
int main() {  
     int ii=0;  
     printf("Setting up\n");  
     setupPWM();  
       
     while(1) {  
        ii=analogRead();  
        pwm_duty(ii);  
        usleep(20000);  
     }  
}  