#ifndef MOTOR_DOT_H
#define MOTOR_DOT_H

#include <stdint.h>

void Motor_Init(uint32_t Hz);
void Motor_Set_Speed(uint32_t speed);
uint32_t Motor_Get_Actual_Speed(void);
uint32_t Motor_Get_Desired_Speed(void);

#endif
