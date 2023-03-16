#include "EC600N.h"

uint8_t Ua[] = "nUa";
uint8_t Ub[] = "nUb";
uint8_t Uc[] = "nUc";
uint8_t Ia[] = "nIa";
uint8_t Ib[] = "nIb";
uint8_t Ic[] = "nIc";

//开机
void PWK_Start(void)
{
	PWK_LOW();
	HAL_Delay(35);
	PWK_HIGH();
	HAL_Delay(535);
}
//关机
void PWK_ShutDown(void)
{
	PWK_LOW();
	HAL_Delay(55);
	PWK_HIGH();
	HAL_Delay(655);
	PWK_LOW();
	HAL_Delay(2005);
}

uint8_t str1[] = "AT+QMTCFG=\"aliauth\",0,\"h2sjd0zpIxZ\",\"RN7302\",\"d6f0e4902149f79257965bbc160ecdc5\"\r\n";
uint8_t str2[] = "AT+QMTOPEN=0,\"iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n";
uint8_t str3[] = "AT+QMTCONN=0,\"RN7302\"\r\n";

void Connect_AliYun(void)
{
	HAL_Delay(1000);
	Usart_SendString(str1);
	HAL_Delay(1000);
	Usart_SendString(str2);
	HAL_Delay(1000);
	Usart_SendString(str3);
}

//数据长度96
uint8_t str_post[] =	"AT+QMTPUBEX=0,0,0,0,\"/sys/h2sjd0zpIxZ/RN7302/thing/event/property/post\",96\r\n";
//数据内容
uint8_t str_data1[] =	"{\"method\":\"thing.service.property.set\",\"id\":\"284\",\"params\":{\"";
//uint8_t str_data2[] -> 电压/电流数据的来源对象
uint8_t str_data2[] =	"\":";
//uint8_t str_data4[]   -> 电压/电流数据的值+"},\"version\":\"1.0.0\"}\r\n"

void Send_Data_To_AliYun(uint8_t *object, uint16_t data)
{
//开始上报数据
	HAL_Delay(1000);
	Usart_SendString(str_post);
//数据
	HAL_Delay(1000);
	Usart_SendString(str_data1);
	//电压/电流数据来源对象
	Usart_SendString(object);
	Usart_SendString(str_data2);
	//电压/电流具体数值
	printf("%8.3f},\"version\":\"1.0.0\"}\r\n",data/1000.000);
	HAL_Delay(1000);
}
