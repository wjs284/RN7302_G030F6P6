/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
#include "main.h"
#include "usart.h"
/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/*
 *¶ÁÈ¡RN7302¼Ä´æÆ÷ÐÅÏ¢
 */
uint8_t RN7302_Read(uint16_t wReg,uint8_t *pBuf)						//00¼ÆÁ¿²ÎÊý¼Ä´æÆ÷£¬01ÅäÖÃºÍ×´Ì¬¼Ä´æÆ÷
{
	uint8_t temp;
	CS_LOW();
	temp = (uint8_t)wReg;
//	printf("wReg %02X\n",temp);
	HAL_SPI_TransmitReceive(&hspi1, &temp, &pBuf[0], 1, 1000);
	temp = ((uint8_t)(wReg >> 4)) & 0xf0;
//	printf("temp %02X\n",temp);
	HAL_SPI_TransmitReceive(&hspi1, &temp, &pBuf[0], 1, 1000);
	delay_us(10);
	HAL_SPI_TransmitReceive(&hspi1, "0xff", &pBuf[0], 1, 1000);	
	HAL_SPI_TransmitReceive(&hspi1, "0xff", &pBuf[1], 1, 1000);
	HAL_SPI_TransmitReceive(&hspi1, "0xff", &pBuf[2], 1, 1000);
	HAL_SPI_TransmitReceive(&hspi1, "0xff", &pBuf[3], 1, 1000);
	CS_HIGH();	
  return(1);
}
/*
 *Ð´ÈëRN7302¼Ä´æÆ÷
 */
void RN7302_Write(uint16_t wReg,uint8_t *cmd,uint8_t DatLen)			//00¼ÆÁ¿²ÎÊý¼Ä´æÆ÷£¬01ÅäÖÃºÍ×´Ì¬¼Ä´æÆ÷
{
	uint8_t temp,num;
	uint8_t cs;
	uint8_t pBuf[1];
	
	CS_LOW();
	temp = (uint8_t)wReg;
//	printf("wReg %02X\n",temp);
	HAL_SPI_TransmitReceive(&hspi1, &temp, &pBuf[0], 1, 1000);	
	temp = (((uint8_t)(wReg >> 4)) & 0xf0) + 0x80;
//	printf("temp %02X\n",temp);
	HAL_SPI_TransmitReceive(&hspi1, &temp, &pBuf[0], 1, 1000);	
	cs=wReg+temp;
	delay_us(10);
	for(num=0;num<DatLen;num++)
	{
		HAL_SPI_TransmitReceive(&hspi1, &cmd[num], &pBuf[0], 1, 1000);	
//	  printf("cmd %02X\n",cmd[num]);
		cs += cmd[num];
	}
	cs = ~cs;
//	printf("cs %02X\n",cs);
	HAL_SPI_TransmitReceive(&hspi1, &cs, &pBuf[0], 1, 1000);	
	CS_HIGH();	
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
