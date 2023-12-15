#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

 

#define KEY   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//读取按键
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//读取按键
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//读取按键 
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//读取按键
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//读取按键

#define KEY_PRES	1//KEY
#define KEY1_PRES	2
#define KEY2_PRES	3
#define KEY3_PRES	4
#define KEY4_PRES	5

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
