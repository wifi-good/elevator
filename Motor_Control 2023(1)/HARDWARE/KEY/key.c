#include "key.h"
#include "delay.h"

//按键初始化函数 
//PA12 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PA12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化PA12
	
	
	
	
 

	
} 

//KEY_Function
//KEY_Pre to KEY4_Pre's value: 1 2 3 4 5
//no priorites
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY==0)return KEY_PRES;
		if(KEY1==0)return KEY1_PRES;
		if(KEY2==0)return KEY2_PRES;
		if(KEY3==0)return KEY3_PRES;
		if(KEY4==0)return KEY4_PRES;
	}else if(KEY==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	     
	return 0;// 无按键按下
}

