#ifndef PICONTROLLER_DOT_H
#define PICONTROLLER_DOT_H

#include <stdint.h>

// Input:
// The PI Controller takes in user input from PythonUART (K, I, desire rps, etc.)
void PIController_Init(void);

// Task:
// The PI Controller then does calculations (proportional, integral)
void PI_Calc(void);

// Output:
// The PI Conotroller then sends a new/adjusted duty cycle to the motor controller to adjust motor speed
uint32_t Send_RPS(void);

#endif
