#include "lse.h"
#include "key.h"

extern duty;

void LSE_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	 
                          
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

}

//make elevator stop
void LSE_Stop(void)
{
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0) duty=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 0) duty=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == 0) duty=0;
}

