#ifndef TACH_DOT_H
#define TACH_DOT_H

#include <stdint.h>

void Tach_Init(void);
void Calculate_Error(uint32_t desired_rps);
void Calculate_RPS(void);

#endif
