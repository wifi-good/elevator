#include "key.h"
#include "delay.h"

//������ʼ������ 
//PA12 ���ó�����
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PA12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��PA12
 

	
} 

//KEY_Function
//KEY_Pre to KEY4_Pre's value: 1 2 3 4 5
//no priorites
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY==0)return KEY_PRES;
		if(KEY1==0)return KEY1_PRES;
		if(KEY2==0)return KEY2_PRES;
		if(KEY3==0)return KEY3_PRES;
		if(KEY4==0)return KEY4_PRES;
	}else if(KEY==1)key_up=1; 	     
	return 0;// �ް�������
}

//make elevator to the certain floor
void Floor(void)
{
	
}