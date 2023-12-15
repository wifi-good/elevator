#include "encoder.h"

void TIM3_Encoder_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	// GPIO�ڳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	
	// ��ʱ��������ģʽ��ʼ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ��������Լ����ã���ʹ��Ĭ��ֵ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // ���������˱�����ģʽ
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0; // �˲�������������Լ����ã���ʹ��Ĭ��ֵ
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM3, 32768);
	TIM_Cmd(TIM3, ENABLE);
}


float GetMotorSpeed(void)	//1kHz
{
	static uint32_t cnt10 = 0;
	static int32_t dCntBuf[10] = {0};
	static int32_t index = 0;
	float speed;
	
	cnt10++;
	cnt10 %= 10;
	if(cnt10 == 0)
	{
		dCntBuf[index] = (int32_t)(TIM3->CNT) - 32768;
		index++;
		index %= 10;
		TIM3->CNT = 32768;
	}
	speed = 9.375f*(dCntBuf[0] + dCntBuf[1] + dCntBuf[2] + dCntBuf[3] + dCntBuf[4] + dCntBuf[5] + dCntBuf[6] + dCntBuf[7] + dCntBuf[8] + dCntBuf[9]);
	return speed;

}





