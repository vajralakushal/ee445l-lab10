#include <stdbool.h>
#include <stdint.h>
#include "./inc/tm4c123gh6pm.h"
#include "./inc/ST7735.h"
#include "./inc/Timer1A.h"
#include "LCD.h"

uint32_t current_rps;
uint32_t current_e;
uint32_t current_u;

void LCD_Init(void){
	current_rps = 0;
	current_e = 0;
	current_u = 0;
	
	ST7735_InitR(INITR_REDTAB);
  ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_FillScreen(0);
  ST7735_SetCursor(0, 0);
  ST7735_OutString("Lab 10 Test");
	
	//use timer to check if values have changed. If so, reflect that on LCD
	//Timer1A_Init(void(*task)(void), uint32_t period, uint32_t priority){
}

void Draw_Values(uint32_t rps, uint32_t e, uint32_t u){
	if (current_rps != rps) {
		ST7735_OutString("RPS = ");
		ST7735_OutUDec(rps);
	}
	
	if (current_e != e) {
		ST7735_OutString("E = ");
		ST7735_OutUDec(e);
	}
  
	if (current_rps != u) {
		ST7735_OutString("U = ");
		ST7735_OutUDec(u);
	}
}

void Draw_Graph(uint32_t rps_val){
	//output new point on time vs rps plot/graph
	//most likely will have to do math in order to output to correct spot on 128x160 screen
}
