#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;			   
//��Ȩ���У�����ؾ���
//Copyright@����쾣���̭���������������������ʤ
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 
/*	
���°���KEY��˳���л�����4��ģʽ����ӦLEDָʾ���£�
STOPMODE:       LED��
OPENLOOPMODE:   LED����
SPEEDMODE:      LED����˸
POSITIONMODE:   LED����˸
*/

int NumFloor = 0;//to check the floor
int KeyFlag = 0;//to show the value of key
int KeyFloor = 0;
float speed = 0, refVoltage = 0, duty = 0,position=0,Ivalue=0;
PIDStructure_t speedPIDStructure = {0},positionPIDStructure = {0},IPIDStructure = {0};
float debugData[11];
Mode_t mode = STOPMODE;


int Direction(int KeyFloor)
{
	NumFloor = Check_Floor();
	if(KeyFloor!=0&&KeyFloor!=1)
	{
		if(NumFloor>KeyFloor-1)return DOWN;
		if(NumFloor==KeyFloor-1)return KEEP;
		if(NumFloor<KeyFloor-1)return UP;
	}
	return 0;//mean keeping
}


int main(void)
{	
	delay_init();//��ʱ������ʼ��
  uart_init(115200);//���ڳ�ʼ��������������Ϊ115200��Ҳ�����Լ�����	  
	ADC1_Init();//adc��ʼ��
	TIM3_Encoder_Init();//TIM3������ģʽ��ʼ��
	
	PID_Init(&positionPIDStructure,0, 0, 0, 0, 0.001,-5000, 5000, 0);//�ο�һ��pid.c�˽��⼸�����������塣
	PID_Init(&speedPIDStructure,0, 10.3, 6.89, 0, 0.001,-0.98, 0.98, 0);//  ��ʾ���������������ʱ��Ҫ�޸��ٶȻ�-0.98��0.98�����Բο�pid�Ĺ����Լ��������˼��һ��Ӧ��Ϊ���٣�
	PID_Init(&IPIDStructure,0, 1, 0, 0, 0.001,-0.98, 0.98, 0);//
	TIM1_PWM_Init(3599,0);//TIM1�����ʼ��������Ƶ��PWMƵ��=72000/(3599+1)=20kHz 
	TIM2_Int_Init(7199,10);//TIM2�жϳ�ʼ�����ж�Ƶ��=72000000/10/7200=1kHz
	LED_Init();
	KEY_Init();
	LSE_Init();
  while(1)
	{
		static u16 count=0;//LED��ʾ����
		int Dir =  Direction(KeyFloor);
		delay_ms(1);
		debugData[0] = position;
		debugData[1] = positionPIDStructure.ref;
		debugData[2] = speedPIDStructure.ref;
		debugData[3] = speed;
		debugData[4] = duty;
		debugData[5] = Ivalue;
		debugData[6] = IPIDStructure.ref;
		debugData[7] = NumFloor;
		debugData[8] = KeyFloor-1;
		debugData[9] = Dir;
		debugData[10] = mode;
		Debug_SendData(debugData, 11);
		
		KeyFlag = KEY_Scan(0);
		
		if(KeyFlag==KEY1_PRES)KeyFloor=KEY1_PRES;
		if(KeyFlag==KEY2_PRES)KeyFloor=KEY2_PRES;
		if(KeyFlag==KEY3_PRES)KeyFloor=KEY3_PRES;
		if(KeyFlag==KEY4_PRES)KeyFloor=KEY4_PRES;
		
		
		LSE_Stop();
		
		if(KeyFlag==KEY_PRES)
		{
			mode ++;
			mode %= 4;
			PID_Clear(&speedPIDStructure, 0);
			PID_Clear(&positionPIDStructure, 0);
			position = 0;
		}
		else if(KeyFlag==KEY1_PRES||KeyFlag==KEY2_PRES||KeyFlag==KEY3_PRES||KeyFlag==KEY4_PRES)
		{
			if(Direction(KeyFlag)==UP)
			{
//				refVoltage = GetADC1Voltage();
//				duty = (refVoltage - 1.65f) * 0.303f;
					mode=SPEEDMODE;
			}
			else if(Direction(KeyFlag)==DOWN)
			{
//				refVoltage = GetADC1Voltage();
//				duty = -(refVoltage - 1.65f) * 0.303f;
					mode=SPEEDMODE;
			}
			else if(Direction(KeyFlag)==KEEP)duty=0;
		}
		//LEDָʾ����ģʽ
		if(mode == STOPMODE)
		{
			LED0=1;
		}
		else if(mode == OPENLOOPMODE)
		{
			LED0=0;
		}
		else if(mode == SPEEDMODE)
		{
			if(count>=500)
			{
				LED0=!LED0;
				count=0;
			}
		}
		else if(mode == POSITIONMODE)
		{
			 if(count>=100)
			{
				LED0=!LED0;
				count=0;
			}
		}
		count++;
	} 		
}


void mainControl(void)	//tim2��ʱ����Ƶ��1kHz
{
	
	speed =-GetMotorSpeed();//��ȡ���ʵ��ת��
	position+=speed*0.000104719755f;
	
	refVoltage = GetADC1Voltage();
	NumFloor=Check_Floor();
	
	if(mode == STOPMODE)
	{
		duty = 0;
	}
	else if(mode == OPENLOOPMODE)
	{
		duty = (refVoltage - 1.65f) * 0.303f;
	}
	else if(mode == SPEEDMODE)//�����ٶȻ�������δ����������ģ������Ҫ�������������ο������������ġ�
	{
		speedPIDStructure.ref = (refVoltage - 1.65f) * 3409.f;
		duty = PID_Calc(&speedPIDStructure, speed);
	}
	else if(mode == POSITIONMODE)//����λ�û�������δ����������ģ������Ҫ�������������ο������������ġ�
	{
		positionPIDStructure.ref = (refVoltage - 1.65f) * 50.f;
		speedPIDStructure.ref = PID_Calc(&positionPIDStructure, position);
		duty = PID_Calc(&speedPIDStructure, speed);
	}
	
	
	PWM_Modulation(duty);//PA8ΪTIM1_CH1 PA9ΪTIM1_CH2 ����Ч���ǻ������
}
//    TIM_SetCompare1(TIM1,(0.5f+duty*0.5f)*3600.f);
//		TIM_SetCompare2(TIM1,(0.5f+duty*0.5f)*3600.f);

