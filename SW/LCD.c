#include <stdbool.h>
#include <stdint.h>
#include "./inc/tm4c123gh6pm.h"
#include "./inc/ST7735.h"
#include "./inc/Timer2A.h"
#include "LCD.h"
#include "Tach.h"

uint32_t current_rps;
uint32_t current_e;
uint32_t current_u;
uint32_t new_rps;
uint32_t new_e;
uint32_t new_u;
uint32_t count = 0;

void LCD_Init(void){
	current_rps = 0;
	current_e = 0;
	current_u = 0;
	new_rps = 0;
	new_e = 0;
	new_u = 0;
	
	ST7735_InitR(INITR_REDTAB);
  ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_FillScreen(0);
  ST7735_SetCursor(0, 0);
  ST7735_OutString("Lab 10 Test");
	
	//use timer to check if values have changed. If so, reflect that on LCD
	Timer2A_Init(Draw_Values, 80000000/1000, 1);
}

void Draw_Values(/*uint32_t rps, uint32_t e, uint32_t u*/void){
//	if (current_rps != rps) {
//		ST7735_OutString("RPS = ");
//		ST7735_OutUDec(rps);
//	}
//	
//	if (current_e != e) {
//		ST7735_OutString("E = ");
//		ST7735_OutUDec(e);
//	}
//  
//	if (current_rps != u) {
//		ST7735_OutString("U = ");
//		ST7735_OutUDec(u);
//	}
	
	Get_RPS();
	
  ST7735_SetCursor(0, 1);
  ST7735_OutString("current_RPS = ");
	ST7735_SetCursor(14, 1);
	ST7735_OutUDec(current_rps);
	
	ST7735_SetCursor(0, 2);
  ST7735_OutString("new_RPS = ");
	ST7735_SetCursor(14, 2);
	ST7735_OutUDec(new_rps);
	
	ST7735_SetCursor(0, 3);
  ST7735_OutString("E = ");
	ST7735_SetCursor(14, 3);
	ST7735_OutUDec(current_e);
  
	ST7735_SetCursor(0, 4);
  ST7735_OutString("U = ");
	ST7735_SetCursor(14, 4);
	ST7735_OutUDec(current_u);
	
	ST7735_SetCursor(0, 5);
  ST7735_OutString("count = ");
	ST7735_SetCursor(14, 5);
	ST7735_OutUDec(count);
	count++;
	
	current_rps = new_rps;
}

void Draw_Graph(uint32_t rps_val){
	//output new point on time vs rps plot/graph
	//most likely will have to do math in order to output to correct spot on 128x160 screen
}

void Get_RPS(void){
	new_rps = Send_RPS();
}
