#include <stdbool.h>
#include <stdint.h>
#include "./inc/tm4c123gh6pm.h"
#include "Motor.h"
#include "./inc/PWM.h"

uint32_t actual_speed;
uint32_t desired_speed;

void Motor_Init(uint32_t Hz){
	PWM0A_Init(Hz, 10000);	// 75% duty cycle (period is 1ms and values are high from 300 to 39900)
}

void Motor_Set_Speed(uint32_t rps){
	//adjust duty cycle based on formula
	//Ex: uint32_t k = -1;
	//    uint32_t duty = rps * k;
	//    PWM0A_Duty(duty);
}

uint32_t Motor_Get_Actual_Speed(void){
	return actual_speed;
}

uint32_t Motor_Get_Desired_Speed(void){
	return desired_speed;
}
