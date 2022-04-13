#ifndef PYTHONUART_DOT_H
#define PYTHONUART_DOT_H

#include <stdint.h>

// Initialize
void PythonUART_Init(void);

// Input:
// The PythonUART module allows the user to interface with the terminal/cmd in order to set desired rps, K, I, etc.
// i.e. the PythonUART module takes in input from the user via UART
void User_In(void);

// Task:
// The PythonUART module converts string data into data that the other modules can use (uint32_t for example)
// most likely will re-assign some global variables
void Convert_String(void);

// Output:
// The PythonUART module sends that data to the PI Controller
uint32_t Send_User_Input(void);

#endif
