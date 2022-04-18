//Created 4/12/2022

#include <stdbool.h>
#include <stdint.h>

#include "./inc/tm4c123gh6pm.h"
#include "./inc/LaunchPad.h"
#include "./inc/PLL.h"
#include "./inc/CortexM.h"
#include "./inc/Texas.h"
#include "Tach.h"
#include "LCD.h"
#include "Motor.h"
#include "PythonUART.h"
#include "PIController.h"

int main(void){           
  PLL_Init(Bus80MHz);   // 80 MHz clock
  LaunchPad_Init();     // activate port F
  TExaS_Init(SCOPE_PD2);
	// initializations not necessarily in the right order
	LCD_Init();	
  Tach_Init();      		// initialize 24-bit timer0A in capture mode
	Motor_Init(40000);				// 1000Hz
//	PythonUART_Init();
//	PIController_Init();
	
  EnableInterrupts();
  while(1){
    WaitForInterrupt();
  }
}
