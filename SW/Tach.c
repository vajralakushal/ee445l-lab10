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
#include "Tach.h"

uint32_t period;  // 24 bits, 12.5 ns units
uint32_t frequency;
uint32_t actual_rps;
int Done;                   // mailbox status set each falling
int Count;									// after a certain count value, motor has stopped rotating
int MotorStop;
int static First;						// Timer0A first edge, 12.5ns

//void Tach_Init(void){ // TM4C123 code
//  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
//  SYSCTL_RCGCGPIO_R |= 0x02;       // activate port B
//  Done = 0;                        // allow time to finish activating
//  GPIO_PORTB_DIR_R &= ~0x10;       // make PB4 input
//  GPIO_PORTB_DEN_R |= 0x10;        // enable digital PB4
//  GPIO_PORTB_AFSEL_R |= 0x10;      // enable alt funct on PB4
//  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFF0FFFF)+0x00070000;	//some PWM code
//  TIMER0_CTL_R &= ~0x00000101;     // disable timers 0A and 0B
//  TIMER0_CFG_R = 0x00000004;       // configure for 16-bit timer mode
//  // **** timer0A initialization ****
//  TIMER0_TAMR_R = 0x00000007;
//  TIMER0_CTL_R = (TIMER0_CTL_R&(~0x0C))+0x04; // falling edge
//  TIMER0_TAILR_R = 0x0000FFFF;     // start value
//  TIMER0_TAPR_R = 0xFF;            // activate prescale, creating 24-bit 
//  TIMER0_IMR_R |= 0x00000004;      // enable capture match interrupt
//  TIMER0_ICR_R = 0x00000004;       // clear timer0A capture match flag
//  // **** timer0B initialization ****
//  TIMER0_TBMR_R = 0x00000007;
//  TIMER0_CTL_R = (TIMER0_CTL_R&(~0x0C00))+0x00; // rising edge
//  TIMER0_TBILR_R = 0x0000FFFF;     // start value
//  TIMER0_TBPR_R = 0xFF;            // activate prescale, creating 24-bit 
//  TIMER0_IMR_R &= ~0x0700;         // disable all interrupts for timer0B
//  TIMER0_CTL_R |= 0x00000101;      // enable timers 0A and 0B 
//  // **** interrupt initialization ****
//  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x10000000; // Timer0=priority 0
//  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
//  EnableInterrupts();
//}

void Tach_Init(void){ // TM4C123 code
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  SYSCTL_RCGCGPIO_R |= 0x02;       // activate port B
  Done = 0;                        // allow time to finish activating
  GPIO_PORTB_DEN_R |= 0x10;        // enable digital PB4
  GPIO_PORTB_AFSEL_R |= 0x10;      // enable alt funct on PB4
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFF0FFFF)+0x00070000;	//some PWM code
  TIMER0_CTL_R &= ~0x00000101;     // disable timers 0A and 0B
  TIMER0_CFG_R = 0x00000004;       // configure for 16-bit timer mode
  // **** timer0A initialization ****
  TIMER0_TAMR_R = 0x00000007;
  TIMER0_CTL_R &= ~(0x000C);
  TIMER0_TAILR_R = 0x0000FFFF;     // start value
  TIMER0_IMR_R |= 0x00000004;      // enable capture match interrupt
  TIMER0_ICR_R = 0x00000004;       // clear timer0A capture match flag
  TIMER0_CTL_R |= 0x00000001;      // enable timers 0A and 0B 
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x10000000; // Timer0=priority 0
  NVIC_EN0_R = 0x00080000;              // enable interrupt 19 in NVIC
  EnableInterrupts();
}

//calculate distance between edges on tachometer
void Timer0A_Handler(void){
  PF2 = PF2^0x04;  // toggle PF2
  PF2 = PF2^0x04;  // toggle PF2
  TIMER0_ICR_R = 0x00000004;  // acknowledge timer0A capture flag
  //PW = (TIMER0_TBR_R-TIMER0_TAR_R)&0x00FFFFFF;// from rise to fall
  period = (First - TIMER0_TAR_R)&0x00FFFFFF;// from rise to fall
	Calculate_RPS();
	First = TIMER0_TAR_R;
  Done = 1;
	Count = 0;
  PF2 = PF2^0x04;  // toggle PF2
}

//calculate how much time has passed since input capture read value
void Timer0B_Handler(void){  
	Count++;
	if(Count == 1200){ //if been more than one second since capture, motor off 
		MotorStop = 1;
	}
}

void Calculate_Error(uint32_t desired_rps){
	//calculate error based on actual and desired frequency/speed of motor
	
}

void Calculate_RPS(void){
	frequency = period*(12.5*(10^9));
//	actual_rps = (12)*frequency;  //12pulses/rotation x (k seconds/pulse)
	actual_rps = 999;
	frequency = 1/frequency;
	Send_RPS();
}

uint32_t Send_RPS(void){
	return actual_rps;
}


