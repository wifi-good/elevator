#ifndef __LSE_H
#define __LSE_H	
#include "stm32f10x_adc.h"
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define SecondFloor GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define ThirdFloor GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define FourthFloor GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)

void LSE_Init(void);
u8 Check_Floor(void);
void LSE_Stop(void);

#endif 
