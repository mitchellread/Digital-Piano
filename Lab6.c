// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 1/24/2015 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "dac.h"
#include "PLL.h"
#include "Music.h"
#include "Timer0A.h"

#define	C	19111
#define	D	17026
#define	E	15169
#define	F	14317
#define	G	12755
#define	A	11364
#define	B	10124
#define half 666 // half-note
#define quarter 333 // quarter-note 


const uint8_t wave [16] = {8,10,13,14,15,14,13,10,8,5,2,1,0,1,2,5};
uint8_t Index = 0;

struct song {
	uint32_t note;
	uint32_t tempo;
};

typedef struct song song_t;

const song_t Song1[23] = {
	{G, half},	
	{E, half},	
	{G, quarter},	
	{G, quarter},	
	{E, half},	
	{G, quarter},	
	{G, quarter},	
	{E, quarter},	
	{A, quarter},	
	{G, quarter},	
	{G, quarter},	
	{E, half},	
	{F, half},	
	{D, half},	
	{F, quarter},	
	{F, quarter},	
	{D, half},	
	{F, half},	
	{D, quarter},
	{G, quarter},	
	{E, quarter},
	{E, quarter},	
	{C, half}	
};
uint32_t SongIndex = 0;
uint32_t SongIndexMax;
uint8_t ButtonCheck = 0;
uint32_t Count1 = 0;
uint8_t SongCheck = 0;

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void SysTick_Handler(void){
	GPIO_PORTF_DATA_R ^= 0x04;	// PF2 is heartbeat for interrupts
	DAC_Out(wave[Index]);
	Index = (Index + 1) & 0x0F;
}
			
void Song1Task(void){
	SongIndex = SongIndex+1;
	if(SongIndex > SongIndexMax){
		SongIndex = 0;
	}
	ButtonCheck = 0;
	Song_Play(Song1[SongIndex].tempo);
	Count1 = 0;
}

void HeartBeat_Init(void){ uint32_t volatile delay;
	SYSCTL_RCGC2_R |= 0x20;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_DIR_R |= 0x0C;		// PF2-3 heartbeat LEDs
	GPIO_PORTF_DEN_R |= 0x0C;
	GPIO_PORTF_AFSEL_R &= ~0x0C;
}

int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PA5432,ScopeOn);    // bus clock at 80 MHz
	HeartBeat_Init();
  Piano_Init();
  Sound_Init(80000);
	Timer0A_Init(&Song1Task,80000);
  EnableInterrupts();
	
	
	
  while(1){   
		GPIO_PORTF_DATA_R |= 0x08;	// PF3 is heartbeat for main program
		uint32_t key = Piano_In();
	switch(key){
		
		case 0x01: EnableInterrupts(); Sound_Play(11364); break;	// A note
		
		case 0x02: EnableInterrupts(); Sound_Play(10124); break;	// B note
		
		case 0x03: EnableInterrupts(); SongCheck = 1; SongIndexMax = 22; Sound_Play(Song1[SongIndex].note); 
		Count1++; if(ButtonCheck == 0) {Song_Play(Song1[SongIndex].tempo); ButtonCheck = 1;} break;
		
		case 0x04: EnableInterrupts(); Sound_Play(9560); break;	// C note
		
		default: DisableInterrupts(); SongCheck = 0; GPIO_PORTF_DATA_R &= ~0x04; Sound_Play(0); break;
  }         
  }         
}
