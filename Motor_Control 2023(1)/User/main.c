#include "main.h"

/*	
按下按键KEY可顺序切换以下4种模式，对应LED指示如下：
STOPMODE:       LED灭
OPENLOOPMODE:   LED常亮
SPEEDMODE:      LED慢闪烁
POSITIONMODE:   LED快闪烁
*/
int TFlag=1;
int NumFloor = 0;//to check the floor
int KeyFlag = 0;//to show the value of key
int KeyFloor = 2;//KeyFloor-1 is the floor to the key
float speed = 0, refVoltage = 0, duty = 0,position=0,Ivalue=0;
PIDStructure_t speedPIDStructure = {0},positionPIDStructure = {0},IPIDStructure = {0};
float debugData[11];
Mode_t mode = STOPMODE;

void SpeedModeUP_Init(void)
{
	speedPIDStructure.ref = (refVoltage - 1.65f) * 3409.f;
	duty = PID_Calc(&speedPIDStructure, speed);
}

void SpeedModeDOWN_Init(void)
{
	speedPIDStructure.ref = (refVoltage - 1.65f) * 3409.f;
	duty = -PID_Calc(&speedPIDStructure, speed);
}

void SpeedModeKEEP_Init(void)
{
	duty=0;
}

void POSModeUP_Init(void)
{
	positionPIDStructure.ref = (refVoltage - 1.65f) * 50.f;
	speedPIDStructure.ref =PID_Calc(&positionPIDStructure, position);
	duty = -PID_Calc(&speedPIDStructure, speed);
}

void POSModeDOWN_Init(void)
{
	positionPIDStructure.ref = (refVoltage - 1.65f) * 50.f;
	speedPIDStructure.ref = PID_Calc(&positionPIDStructure, position);
	duty = PID_Calc(&speedPIDStructure, speed);
}

void POSModeKEEP_Init(void)
{
	duty = 0;
}

int Direction(int KeyFloor,int NumFloor)
{
	
	if(KeyFloor!=0&&KeyFloor!=1)
	{
		if(NumFloor>KeyFloor-1)return DOWN;
		if(NumFloor==KeyFloor-1)return KEEP;
		if(NumFloor<KeyFloor-1)return UP;
	}
	return 0;//mean keeping
}

int Check_KeyFloor(void)
{
	KeyFlag = KEY_Scan(0);
		
	if(KeyFlag==KEY1_PRES)return KEY1_PRES;
	if(KeyFlag==KEY2_PRES)return KEY2_PRES;
	if(KeyFlag==KEY3_PRES)return KEY3_PRES;
	if(KeyFlag==KEY4_PRES)return KEY4_PRES;
	return 1;
}

int main(void)
{	
	delay_init();//延时函数初始化
  uart_init(115200);//串口初始化，波特率设置为115200，也可以自己设置	  
	ADC1_Init();//adc初始化
	TIM3_Encoder_Init();//TIM3编码器模式初始化
	
	PID_Init(&positionPIDStructure,1000, 400, 0, 0, 0.001,-5000, 5000, 0);//参考一下pid.c了解这几个参数的意义。
	PID_Init(&speedPIDStructure,10.3, 6.8, 0, 0, 0.001,-0.98, 0.98, 0);//  提示！！当加入电流环时需要修改速度环-0.98与0.98，可以参考pid的过程以及具体代码思考一下应改为多少？
	PID_Init(&IPIDStructure,0, 1, 0, 0, 0.001,-0.98, 0.98, 0);//
	TIM1_PWM_Init(3599,0);//TIM1输出初始化。不分频。PWM频率=72000/(3599+1)=20kHz 
	TIM2_Int_Init(7199,10);//TIM2中断初始化。中断频率=72000000/10/7200=1kHz
	LED_Init();
	KEY_Init();
	LSE_Init();
	NumFloor=1;//Initilize the floor
  while(1)
	{
		static u16 count=0;//LED显示计数
		int Dir =  Direction(KeyFloor,NumFloor);
		delay_ms(1);
		debugData[0] = position;
		debugData[1] = positionPIDStructure.ref;
		debugData[2] = PID_Calc(&positionPIDStructure, position);//speedPIDStructure.ref;
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
//		else if(KeyFlag==KEY1_PRES||KeyFlag==KEY2_PRES||KeyFlag==KEY3_PRES||KeyFlag==KEY4_PRES)
//		{
//			mode=SPEEDMODE;
//		}
		
		//LED指示工作模式
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


void mainControl(void)	//tim2定时器，频率1kHz
{
	
	speed =-GetMotorSpeed();//获取电机实际转速
	position+=speed*0.000104719755f;
	
	refVoltage = GetADC1Voltage();
	
	
	
	
	if(mode == STOPMODE)
	{
		duty = 0;
	}
	else if(mode == OPENLOOPMODE)
	{
		duty = (refVoltage - 1.65f) * 0.303f;
	}
	else if(mode == SPEEDMODE)//以下速度环程序是未加入电流环的，如果需要加入电流环，请参考讲义自行增改。
	{
		if(Direction(KeyFloor,NumFloor)==UP) SpeedModeUP_Init();
		else if(Direction(KeyFloor,NumFloor)==DOWN)
		{
			if(NumFloor==2&&KeyFloor==2)
			{
				SpeedModeDOWN_Init();
				TFlag++;
				if(TFlag%3300==0)
				{
					TFlag=1;
					NumFloor=1;
					duty=0;
					mode = STOPMODE;
				}
				
			}
			else SpeedModeDOWN_Init();
		}
			
		else if(Direction(KeyFloor,NumFloor)==KEEP) SpeedModeKEEP_Init();
	}
	else if(mode == POSITIONMODE)//以下位置环程序是未加入电流环的，如果需要加入电流环，请参考讲义自行增改。
	{
		if(Direction(KeyFloor,NumFloor)==UP) POSModeUP_Init();
		else if(Direction(KeyFloor,NumFloor)==DOWN)
		{
			if(NumFloor==2&&KeyFloor==2)
			{
				POSModeDOWN_Init();
				TFlag++;
				if(TFlag%4000==0)
				{
					TFlag=1;
					NumFloor=1;
					duty=0;
					mode = STOPMODE;
				}
				
			}
			else POSModeDOWN_Init();
		}
			
		else if(Direction(KeyFloor,NumFloor)==KEEP) POSModeKEEP_Init();
	}
	
	
	
	PWM_Modulation(duty);//PA8为TIM1_CH1 PA9为TIM1_CH2 最终效果是互补输出
}
//    TIM_SetCompare1(TIM1,(0.5f+duty*0.5f)*3600.f);
//		TIM_SetCompare2(TIM1,(0.5f+duty*0.5f)*3600.f);

