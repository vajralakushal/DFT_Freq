// DAC.h
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Hardware connections
// PB0-3 are outputs to the dac

#ifndef DAC_H
#define DAC_H
#include <stdint.h>
// Header files contain the prototypes for public functions
// this file explains what the module does

// **************DACInit*********************
// Initialize TLV5616 12-bit DAC
// assumes bus clock is 80 MHz
// inputs: initial voltage output (0 to 4095)
// outputs:none
void DACInit(void);


// **************DAC_Out*********************
// send the 16-bit code to the SSI
void DAC_Out(uint16_t data);

#endif
