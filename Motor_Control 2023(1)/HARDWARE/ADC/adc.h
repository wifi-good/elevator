#ifndef __ADC_H
#define __ADC_H	
#include "stm32f10x_adc.h"
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
extern uint16_t dmaadc[2];		
extern float Ivalue;
void ADC1_Init(void);
float GetADC1Voltage(void);

#endif 
