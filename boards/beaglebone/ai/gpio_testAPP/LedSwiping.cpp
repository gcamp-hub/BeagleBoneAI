#include <iostream>
#include <string>
#include <unistd.h>
#include "SimpleGPIO.h"
using namespace std;

unsigned int LEDGPIO = 166;   // P8.08


int main(int argc, char *argv[]){

	cout << "Testing the GPIO Pins" << endl;

            gpio_export(LEDGPIO);    // The LED
	gpio_set_dir(LEDGPIO, OUTPUT_PIN);   // The LED is an output
		
	// Flash the LED 10 times
	for(int i=0; i<10; i++){
		cout << "Setting the LED on" << endl;
                        gpio_set_value(LEDGPIO, HIGH);
		usleep(200000);         // on for 200ms
		cout << "Setting the LED off" << endl;
                        gpio_set_value(LEDGPIO, LOW);
		usleep(200000);         // off for 200ms
	}

	
	cout << "Finished Testing the GPIO Pins" << endl;
	gpio_unexport(LEDGPIO);     // unexport the LED
	
	return 0;
}

