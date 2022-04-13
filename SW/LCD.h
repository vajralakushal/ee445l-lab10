#ifndef LCD_DOT_H
#define LCD_DOT_H

#include <stdint.h>

void LCD_Init(void);
void Draw_Values(uint32_t rps, uint32_t e, uint32_t u);
void Draw_Graph(uint32_t val);

#endif
