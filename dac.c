// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"

extern uint32_t Count1;
extern uint8_t SongCheck;

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){uint32_t volatile delay;
	SYSCTL_RCGC2_R |= 0x01;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTA_DIR_R |= 0xFC; // bits 7-2 output
	GPIO_PORTA_AFSEL_R &= ~0xFC;
	GPIO_PORTA_DEN_R |= 0xFC;
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(uint32_t data){
	if(SongCheck == 0){
	data = data << 2;
	GPIO_PORTA_DATA_R = data;
	} else {
	if(Count1 > 10000){
			data = data << 2;
			GPIO_PORTA_DATA_R = data;
	}
}
	
}
