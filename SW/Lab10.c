//Created 4/12/2022

#include <stdbool.h>
#include <stdint.h>

#include "./inc/tm4c123gh6pm.h"
#include "./inc/LaunchPad.h"
#include "./inc/PLL.h"
#include "./inc/CortexM.h"
#include "./inc/PWM.h"
#include "PulseWidthMeasure.h"
#include "Tach.h"
#include "LCD.h"
#include "Motor.h"
#include "PythonUART.h"

int main(void){           
  PLL_Init(Bus80MHz);     	// 80 MHz clock
  LaunchPad_Init();       	// activate port F
	PWM0A_Init(40000, 30000);	// 1000Hz, 75% duty cycle (period is 1ms and values are high from 300 to 39900)
  PWMeasure2_Init();      	// initialize 24-bit timer0A in capture mode
  EnableInterrupts();
  while(1){
    WaitForInterrupt();
  }
}