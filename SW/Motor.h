#ifndef MOTOR_DOT_H
#define MOTOR_DOT_H

#include <stdint.h>

// Initialize
void Motor_Init(uint32_t Hz);

// Input:
// The Motor module will receive desired rps/duty cycle from PIController module
void Receive_RPS(void);

// Task:
// The Motor module output new duty cycle to physical motor (via PWM folder in inc/)
void Motor_Set_Speed(uint32_t speed);

// Output: NA
// The Motor module will generate a square wave via the pin connected to the tach. The tach will reade that square wave in it's own module



// Not currently needed
//uint32_t Motor_Get_Actual_Speed(void);
//uint32_t Motor_Get_Desired_Speed(void);

#endif
