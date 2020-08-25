#include <iostream>
#include <string>
#include <unistd.h>
#include "SimpleGPIO.h"
using namespace std;

unsigned int LEDGPIO = 166;   // P8.08
unsigned int ButtonGPIO = 125;   // P8.16

int main(int argc, char *argv[]){
             unsigned int cnt = 0;
	//cout << "Testing the GPIO Pins" << endl;

             gpio_export(LEDGPIO);    // The LED
             gpio_export(ButtonGPIO);   // The push button switch
             gpio_set_dir(LEDGPIO, OUTPUT_PIN);   // The LED is an output
	 gpio_set_dir(ButtonGPIO, INPUT_PIN);   // The push button input

	// Wait for the push button to be pressed
	cout << "Please press the button!" << endl;

	unsigned int value = LOW;
             
	do {
		gpio_get_value(ButtonGPIO, &value); 
		cout << ".";
		usleep(1000);      // sleep for one millisecond
		 
		if(value) {			
			gpio_set_value(LEDGPIO, HIGH);
			usleep(200000);         // on for 200ms
                                      cnt++;
                                      cout <<  "Button was just pressed!"  << endl;
                                      
                                      if (cnt > 10)  break;
		}else {
		            gpio_set_value(LEDGPIO, LOW);
			usleep(200000);         // on for 200ms
              	}
		
		cout << "LED on count: " << cnt << endl;

            } while ( 1  );

	//cout << "Button was just pressed!" << endl;

	cout << "Finished Testing." << endl;
	gpio_unexport(LEDGPIO);     // unexport the LED
	gpio_unexport(ButtonGPIO);  // unexport the push button
	return 0;
}

