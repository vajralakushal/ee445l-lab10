#ifndef TACH_DOT_H
#define TACH_DOT_H

#include <stdint.h>

// Input:
// The Tach module will read in a square wave from the motor module
void Tach_Init(void);

// Task:
// The Tach module will measure edge-to-edge frequency and calculate the motor period/frequency/rps
void Calculate_RPS(void);

// Output:
// The Tach module will send measured/actual speed/rps to the PIController
uint32_t Send_RPS(void);

#endif
