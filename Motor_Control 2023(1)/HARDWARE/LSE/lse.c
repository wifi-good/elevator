#include "lse.h"
#include "key.h"

extern float duty;

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
	if(SecondFloor==0) duty=0;
	if(ThirdFloor==0) duty=0;
	if(FourthFloor==0) duty=0;
}

//check the floor
u8 Check_Floor(void)
{
	if(SecondFloor==1) return 2;
	else if(ThirdFloor==1) return 3;
	else if(FourthFloor==1) return 4;
	else if(SecondFloor==0&&ThirdFloor==0&&FourthFloor==0)return 1;
	return 0;
}
