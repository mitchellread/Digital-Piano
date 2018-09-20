// Music.c

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Timer0A.h"

// **************Song_Play*********************
// Receives input that defines song to play 
// Uses input to set tempo of song 
void Song_Play(uint32_t tempo){
	TIMER0_TAILR_R = (tempo*80000)-1;
}
