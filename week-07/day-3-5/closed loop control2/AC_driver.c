/*
 * AC_driver.c
 *
 * Created: 2017. 06. 13. 17:17:12
 *  Author: Peeter
 */ 

 #include <avr/io.h>
#include "AC_driver.h"
#include "freq_meas.h"
 volatile float prev_rpm = 0;

void AC_driver_init()
{
	/*************
	 * AC CONFIG *
	 *************/
	// TODO:
	// Disable the digital input buffers on AN0 and AN1 to reduce power consumption.
	// See the DIDR1 register description for more info.
	DIDR1 |= (1 << AIN0D) | (1 << AIN1D);

	// TODO:
	// Connect the AC output to the AC0 pin.
	// The datasheet if screwed up. It says "Analog Comparator Control and Status Register C", meanwhile the name of this register is "ACSR0",
	// but in the avr/io.g header this register can be reached with the "ACSRB" macro.
	ACSRB |= 1 << ACOE;
	
	// TODO:
	// Configure the rest settings properly :)
	// AC output connected to TC1 input capture
	ACSR = 0;
	ACSR |= 1 << ACIC;
}

// TODO:
// Write this function. It returns the measured rotation speed in RPM
float get_rpm()
{
	float freq = get_freq();
	float rpm = 0;
	if (freq == -1) {
		rpm = prev_rpm;
	}
	else {
		rpm = (60 * get_freq());
		prev_rpm = rpm;
	}
	return rpm;
}