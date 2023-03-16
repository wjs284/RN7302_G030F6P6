#ifndef _EC600N_H
#define _EC600N_H

#include "usart.h"
#include "gpio.h"
#include "stm32g0xx_hal.h"

//¶ÁÍøÂç×´Ì¬
#define NET_State_Read()				HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);

#define PWK_HIGH()							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
#define PWK_LOW()								HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);   
#define PEN_Power_ON()					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
#define PEN_Power_OFF()					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

extern uint8_t Ua[];
extern uint8_t Ub[];
extern uint8_t Uc[];
extern uint8_t Ia[];
extern uint8_t Ib[];
extern uint8_t Ic[];

void PWK_Start(void);
void PWK_ShutDown(void);
void Connect_AliYun(void);
void Send_Data_To_AliYun(uint8_t *object, uint16_t data);

#endif /*_EC600N_H*/
