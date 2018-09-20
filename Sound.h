// Sound.h
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 10/5/2014 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections

// Header files contain the prototypes for public functions
// this file explains what the module does

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//    	Units of period are 12.5ns
//    	Maximum is 2^24 - 1
//    	Minimum is determined by length of ISR
// Output: none
void Sound_Init(uint32_t period);


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//    	Units of period are 12.5ns
//    	Maximum is 2^24 - 1
//    	Minimum is determined by length of ISR
//         input of zero disable sound output
// Output: none
void Sound_Play(uint32_t period);
