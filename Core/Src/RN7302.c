#include "RN7302.h"


uint8_t k[4];

void EnableRN7302(void)
{
	//дʹ��
	k[0] = 0xE5;
	RN7302_Write(0x0180, k, 1);
	//������ģʽתΪ����ģʽ SLM->EMM
	k[0] = 0xA2;
	RN7302_Write(0x0181, k, 1);
	//�����λ ��λ���Ա��ֹ���ģʽ ���ּĴ�������
	k[0] = 0xFA;
	RN7302_Write(0x0182, k, 1);
	HAL_Delay(500);
	//дʹ��
	k[0] = 0xE5;
	RN7302_Write(0x0180, k, 1);
	//������ģʽתΪ����ģʽ SLM->EMM
	k[0] = 0xA2;
	RN7302_Write(0x0181, k, 1);
	//ʹ�ܼ�������
	k[0]=0x77;
	k[1]=0x77;
	k[2]=0x77;
	RN7302_Write(0x0162,k,3);	//EMU ���ƼĴ���
}
//У��
void AdjustRegister(void)
{
	k[0]=0x25;
	k[1]=0x78;
	RN7302_Write(0x0100,k,2);	//HFConst1  ,��Ƶ��������Ĵ��� 1
	RN7302_Write(0x0101,k,2);	//HFConst2	,��Ƶ��������Ĵ��� 1

	k[0]=0x01;
	k[1]=0xD5;
	RN7302_Write(0x0102,k,2);	//IStart_PS ,�й���������������ֵ�Ĵ���
	RN7302_Write(0x0103,k,2);	//IStart_Q  ,�޹�����������ֵ�Ĵ���

	k[0]=0x14;
	k[1]=0xfb;
	RN7302_Write(0x0104,k,2);	//LostVoltT  ,ʧѹ��ֵ�Ĵ���

	k[0]=0x00;
	k[1]=0x49;
	RN7302_Write(0x0105,k,2);	//ZXOT  ,������ֵ�Ĵ���

	k[0]=0x00;
	k[1]=0x04;
	k[2]=0x0b;
	RN7302_Write(0x0158,k,3);	//SAGCFG ,��ѹ�ݽ���ֵ����

	k[0]=0x47;
	k[1]=0x33;
	RN7302_Write(0x0159,k,2);	//OVLVL  ,��ѹ��ֵ����

	k[0]=0x65;
	k[1]=0x32;
	RN7302_Write(0x015a,k,2);	//OILVL  ,������ֵ����

	k[0]=0x0F;								// ������Ԫ���üĴ���
	k[1]=0x21;
	k[2]=0x00;
	RN7302_Write(0x0161,k,3);/*******************************************************************/


	k[0]=0x17;
	k[1]=0x01;
	RN7302_Write(0x0113,k,2);	//GSUA  ,����ͨ�� UA ͨ������
	RN7302_Write(0x0114,k,2);	//GSUB  ,
	RN7302_Write(0x0115,k,2);	//GSUC  ,

	k[0]=0x86;
	k[1]=0x0d;
	RN7302_Write(0x0116,k,2);	//GSIA  ,����ͨ�� IA ͨ������
	RN7302_Write(0x0117,k,2);	//GSIB  ,
	RN7302_Write(0x0118,k,2);	//GSIC  ,

	k[0]=0x8A;
	RN7302_Write(0x010C,k,1);	//PHSUA ,����ͨ�� UA ��λУ���Ĵ���
	RN7302_Write(0x010D,k,1);	//PHSUB ,
	RN7302_Write(0x010E,k,1);	//PHSUC ,

	k[0]=0x80;
	k[1]=0x80;
	k[2]=0x80;
	RN7302_Write(0x010f,k,3);
	RN7302_Write(0x0110,k,3);
	RN7302_Write(0x0111,k,3);

	//���ص�ѹ��ЧֵС��У׼��OFFSET��
	k[0]=0x00;
	k[1]=0x00;
	RN7302_Write(0x0121,k,2);
	RN7302_Write(0x0122,k,2);
	RN7302_Write(0x0123,k,2);

	//���ص�����ЧֵС��У׼��OFFSET��
	k[0]=0xff;
	k[1]=0xf0;
	RN7302_Write(0x0124,k,2);
	RN7302_Write(0x0125,k,2);
	RN7302_Write(0x0126,k,2);

	//ʹ��ͨ���л��Ĵ���
	k[0]=0x42;
	RN7302_Write(0x0184,k,1);
	//���õ���ͨ���л��Ĵ���
	k[0]=0x00;
	RN7302_Write(0x0185,k,1);
	//ʧ��ͨ���л��Ĵ���
	k[0]=0x00;
	RN7302_Write(0x0184,k,1);
	//CF �������üĴ���
	k[0]=0x04;
	k[1]=0x32;
	k[2]=0x10;
	RN7302_Write(0x0160,k,3);

	// ��ղ������ݻ�����
	k[2]=0x10;
	RN7302_Write(0x0163,k,3);
	
	//дʧ��
	k[0]=0xDC;
	RN7302_Write(0x0180, k, 1);
}

uint8_t sub_data[] = "AT+QMTPUB=0,0,0,0,\"/h2sjd0zpIxZ/RN7302/user/data\"\r\n";
uint8_t temp[5];
uint16_t	IA,UA,IB,UB,IC,UC;
void readRegister(void)
{
	RN7302_Read(0x000B,temp);
	IA=((0x00000000|temp[0]<<24|temp[1]<<16|temp[2]<<8|temp[3])&0x0fffffff)/160;
	RN7302_Read(0x0007,temp);
	UA=((0x00000000|temp[0]<<24|temp[1]<<16|temp[2]<<8|temp[3])&0x0fffffff)/160;
	RN7302_Read(0x000C,temp);
	IB=((0x00000000|temp[0]<<24|temp[1]<<16|temp[2]<<8|temp[3])&0x0fffffff)/160;
	RN7302_Read(0x0008,temp);
	UB=((0x00000000|temp[0]<<24|temp[1]<<16|temp[2]<<8|temp[3])&0x0fffffff)/160;
	RN7302_Read(0x000D,temp);
	IC=((0x00000000|temp[0]<<24|temp[1]<<16|temp[2]<<8|temp[3])&0x0fffffff)/160;	
	RN7302_Read(0x0009,temp);
	UC=((0x00000000|temp[0]<<24|temp[1]<<16|temp[2]<<8|temp[3])&0x0fffffff)/160;
	
	//�����ⷢ����Ϣ
	Usart_SendString(sub_data);
	HAL_Delay(1000);
	printf("{\"nIa\":%8.3f,\r\n\"nUa\":%8.3f,\r\n",IA/1000.000,UA/1000.000);
	printf("\"nIb\":%8.3f,\r\n\"nUb\":%8.3f,\r\n",IB/1000.000,UB/1000.000);
	printf("\"nIc\":%8.3f,\r\n\"nUc\":%8.3f}",IC/1000.000,UC/1000.000);
	HAL_Delay(1000);
	printf("%c",0x1A);
	HAL_Delay(1000);
}

