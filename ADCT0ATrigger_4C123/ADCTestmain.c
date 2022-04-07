// ADCTestmain.c
// Runs on LM4F120/TM4C123
// Provide a function that initializes Timer0A to trigger ADC
// SS0 conversions and request an interrupt when the conversion
// is complete.
// Daniel Valvano
// January 19, 2020

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2020

 Copyright 2020 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// center of X-ohm potentiometer connected to PE3/AIN0
// bottom of X-ohm potentiometer connected to ground
// top of X-ohm potentiometer connected to +3.3V through X/10-ohm ohm resistor
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/ADCT0ATrigger.h"
#include "../inc/PLL.h"
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/Texas.h"
#include "math.h"

#define BUFFER_SIZE 500


//debug code
//
// This program periodically samples ADC0 channel 0 and stores the
// result to a global variable that can be accessed with the JTAG
// debugger and viewed with the variable watch feature.
int k;
int frequency;

int maxIdx = -1;

void calculateDFT(int len, uint32_t *buffer, double *output){
    int xn[len];
    float Xr[len];
    float Xi[len];
    int i, n, N = 0;
	  double maxSoFar = -1.0;
  
    for (i = 0; i < len; i++) {
  
        xn[i] = buffer[i];
    }
  
		N = len;
		
		
    for (k = 0; k < N; k++) {
        Xr[k] = 0;
        Xi[k] = 0;
        for (n = 0; n < len; n++) {
            Xr[k]
                = (Xr[k]
                   + xn[n] * cos(2 * 3.141592 * k * n / N));
            Xi[k]
                = (Xi[k]
                   + xn[n] * sin(2 * 3.141592 * k * n / N));
        }
		
				double val = sqrt((Xr[k] * Xr[k]) + (Xi[k] * Xi[k]));
				output[k] = val;
				if(val > maxSoFar){
					maxIdx = k;
					maxSoFar = val;
				}
    }
}


void calculateFreq(double *output, int samplingRate){
	frequency = maxIdx * samplingRate / BUFFER_SIZE;
}


uint32_t ADCvalue;
uint32_t buffer[BUFFER_SIZE];
double output[BUFFER_SIZE];
uint32_t idx = 0;

void RealTimeTask(uint32_t data){
  PF3 ^= 0x04;           // toggle LED
  ADCvalue = data;
	if(idx < BUFFER_SIZE){
		buffer[idx] = ADCvalue;
		idx++;
	}else if(idx >= BUFFER_SIZE && k < BUFFER_SIZE){
		//calculateDFT(BUFFER_SIZE, buffer, output);
	} else{
		//calculateFreq(output, 2000);
	}
}
int main(void){
	TExaS_Init(SCOPE_PD2);
  PLL_Init(Bus80MHz);                      // 80 MHz system clock
  LaunchPad_Init();                        // activate port F
  ADC0_InitTimer0ATriggerSeq0(3, 2000,&RealTimeTask); // ADC channel 3, 100 Hz sampling
  PF2 = 0;              // turn off LED
  EnableInterrupts();
  while(1){
    PF2 ^= 0x04;           // toggle LED
  }
}

