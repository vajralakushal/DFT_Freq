#include "Speaker.h"
#include "DAC.h"
#include "../inc/Timer1A.h"
#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>

void DisableInterrupts(void);
const unsigned short wave[32] = {
	2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056,4095, 4056, 3939,
		3750, 3495, 3185, 2831, 2447, 2048, 1649, 1265, 911, 601, 346,
	157, 40, 1, 40, 157, 346, 601, 911, 1265, 1649
};
extern int song;
const uint16_t *SoundPt;
uint32_t Length;	
uint32_t soundIndex;
int isPlaying = 0;
	
	
//void OutputToDAC(void){
//		//output one (or 0) value to dac out
//		DAC_Out((wave[Index] * 0.08));
//		Index = (Index + 1) % 32;
//}

void SoundTask(void){
		if(isPlaying){
			DAC_Out(SoundPt[soundIndex]);
			soundIndex = (soundIndex + 1) % Length;
		}
		
}	
	
void SpeakerInit(void){
	Length = 0;
	soundIndex = 0;
	DACInit();
	isPlaying = 0;
	Timer1A_Init(&SoundTask, 80000000/11025, 1);
}

void SpeakerPlay(const uint16_t *pt, uint32_t count){
	Length = count;
	soundIndex = 0;
	SoundPt = pt;
	isPlaying = 1;
	NVIC_EN0_R = 1<<19;
}

void Sound_Dire(void){
	//SpeakerPlay(DDD3, 48000);
}
