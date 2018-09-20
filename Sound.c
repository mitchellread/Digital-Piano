// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "tm4c123gh6pm.h"

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//    	Units of period are 12.5ns
//    	Maximum is 2^24 - 1
//    	Minimum is determined by length of ISR
// Output: none
void Sound_Init(uint32_t period){
	DAC_Init();     
  NVIC_ST_CTRL_R = 0;    		// disables SysTick 
  NVIC_ST_RELOAD_R = period - 1;	// reload value	
  NVIC_ST_CURRENT_R = 0;  	// timer 	
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x80000000;  // priority 4
  NVIC_ST_CTRL_R = 0x0007; // enable SysTick with core clock and interrupts
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//    	Units of period are 12.5ns
//    	Maximum is 2^24 - 1
//    	Minimum is determined by length of ISR
//         input of zero disable sound output
// Output: none
void Sound_Play(uint32_t period){
	NVIC_ST_RELOAD_R = period - 1;
}
