#include <iostream>
#include <string>
#include <unistd.h>
#include "SimpleGPIO.h"
using namespace std;

unsigned int ButtonGPIO = 125;   // P8.16

int main(int argc, char *argv[]){

	cout << "Testing Button Input" << endl;
  
	gpio_export(ButtonGPIO);   // The push button switch
	gpio_set_dir(ButtonGPIO, INPUT_PIN);   // The push button input

	// Wait for the push button to be pressed
	cout << "Please press the button!" << endl;

	unsigned int value = LOW;
	do {
		gpio_get_value(ButtonGPIO, &value); 
		cout << ".";
		usleep(1000);      // sleep for one millisecond
	} while (value!=HIGH);
	cout << endl <<  "Button was just pressed!" << endl;

	cout << "Finished Button Input" << endl;

	gpio_unexport(ButtonGPIO);  // unexport the push button
	return 0;
}

