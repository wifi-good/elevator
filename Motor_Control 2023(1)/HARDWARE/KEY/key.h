#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

 

#define KEY   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//��ȡ����
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ���� 
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//��ȡ����
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����

#define KEY_PRES	1//KEY
#define KEY1_PRES	2
#define KEY2_PRES	3
#define KEY3_PRES	4
#define KEY4_PRES	5

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
