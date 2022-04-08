#ifndef SPEAKER_DOT_H
#define SPEAKER_DOT_H
#include <stdint.h>


/*
	void play()
	
	Function that plays the audio given in the audio packet struct through the speaker component.
*/
void SpeakerPlay(const uint16_t *pt, uint32_t count);

void SpeakerInit(void);

void Sound_Dire(void);

#endif
