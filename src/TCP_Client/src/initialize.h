#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "stm32f4xx.h"

void InitializeDelay(void);
void InitializeButtons(void);
void InitializeInterruptions(void);

void Delay(uint32_t miliseconds);

#endif

