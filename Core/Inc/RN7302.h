#ifndef _RN7302_H
#define _RN7302_H


#include "gpio.h"
#include "usart.h"
#include "spi.h"
#include "EC600N.h"

extern uint8_t temp[5];
extern uint8_t k[4];


void EnableRN7302(void);
void AdjustRegister(void);
void readRegister(void);
#endif /*_RN7302*/
