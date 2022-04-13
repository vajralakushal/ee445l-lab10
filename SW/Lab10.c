//Created 4/12/2022

#include <stdbool.h>
#include <stdint.h>

#include "./inc/tm4c123gh6pm.h"
#include "./inc/LaunchPad.h"
#include "./inc/PLL.h"
#include "./inc/CortexM.h"
#include "Tach.h"
#include "LCD.h"
#include "Motor.h"
#include "PythonUART.h"

int main(void){           
  PLL_Init(Bus80MHz);   // 80 MHz clock
  LaunchPad_Init();     // activate port F
	LCD_Init();						
	Motor_Init(0);				// 0Hz
  Tach_Init();      		// initialize 24-bit timer0A in capture mode
  EnableInterrupts();
  while(1){
    WaitForInterrupt();
  }
}
