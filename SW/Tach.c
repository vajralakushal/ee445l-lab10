// Tach.c
// Runs on LM4F120/TM4C123
// Use Timer0A in 24-bit edge time mode to request interrupts on the falling
// edge of PB6 (T0CCP0). 
// Use Timer0B in 24-bit edge time mode rising edge of PB7(T0CCP1) is latched, and 
// the system measures pulse between pulses.
// Daniel Valvano
// April 2, 2018

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018
   Example 6.5, Program 6.5

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
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

// external signal connected to PB6 (T0CCP0) (trigger on rising edge)
#include <stdint.h>
#include "./inc/tm4c123gh6pm.h"
#include "./inc/PLL.h"
#include "./inc/CortexM.h"
#include "./inc/LaunchPad.h"
#include "./inc/PWM.h"
#include "./inc/Timer1A.h"
#include "Tach.h"

uint32_t period;  // 24 bits, 12.5 ns units
uint32_t frequency;
uint32_t actual_rps = 111;
int Done;                   // mailbox status set each falling
int Count;									// after a certain count value, motor has stopped rotating
int MotorStop;
int static First;						// Timer0A first edge, 12.5ns

//calculate distance between edges on tachometer
void Tach_Task(void){
  PF2 = PF2^0x04;  // toggle PF2
  PF2 = PF2^0x04;  // toggle PF2
  TIMER1_ICR_R = 0x00000004;  // acknowledge timer0A capture flag
  //PW = (TIMER0_TBR_R-TIMER0_TAR_R)&0x00FFFFFF;// from rise to fall
  period = (First - TIMER1_TAR_R)&0x00FFFFFF;// from rise to fall
	Calculate_RPS();
	First = TIMER1_TAR_R;
  Done = 1;
	Count = 0;
  PF2 = PF2^0x04;
}

void Tach_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
//  SYSCTL_RCGCTIMER_R |= 0x02;      // activate timer0
  Done = 0;                        // allow time to finish activating
  GPIO_PORTB_DEN_R |= 0x10;        // enable digital PB4
	GPIO_PORTB_AFSEL_R |= 0x10;      // enable alt funct on PB4
	GPIO_PORTB_DIR_R &= ~0x10;       // make PB4 input
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFF0FFFF)+0x00070000;	//some PWM code
	GPIO_PORTB_AMSEL_R &= 0x7F;
	Timer1A_Init(&Tach_Task, 0, 3);
}

//calculate how much time has passed since input capture read value
//void Timer0B_Handler(void){  
//	Count++;
//	if(Count == 1200){ //if been more than one second since capture, motor off 
//		MotorStop = 1;
//	}
//}

void Calculate_Error(uint32_t desired_rps){
	//calculate error based on actual and desired frequency/speed of motor
	
}

//	actual_rps = (12)*frequency;  //12pulses/rotation x (k seconds/pulse)
void Calculate_RPS(void){
	frequency = period*(12.5*(10^9));
	actual_rps = 999;
	frequency = 1/frequency;
}

uint32_t Send_RPS(void){
	return actual_rps;
}
