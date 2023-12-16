#include "pid.h"

void PID_Init(PIDStructure_t* sptr, float kp, float ki, float kd, float N, float Ts, float outMin, float outMax, float outInit)  //限幅均为输出量纲
{
	sptr->kp = kp; 
	sptr->ki = ki; 
	sptr->kd = kd;
	sptr->N = N;
	sptr->accD = 0;
	sptr->Ts = Ts;
	sptr->outMax = outMax;
	sptr->outMin = outMin;
	sptr->accD_D1 = 0;
	sptr->error_D1 = 0;
	sptr->out = outInit;
}

float PID_Calc(PIDStructure_t* sptr, float fdb)
{
	float error = sptr->ref - fdb;
	sptr->out += 
	sptr->kp * (error - sptr->error_D1) + //这里加上之前的误差相当于消去了之前的误差
	sptr->ki * error * sptr->Ts +
	sptr->kd / sptr->N * (error - sptr->accD - sptr->error_D1 + sptr->accD_D1);

	sptr->error_D1 = error;
	sptr->accD_D1 = sptr->accD;
	sptr->accD += 1 / sptr->N * (error - sptr->accD);

	if(sptr->out >= sptr->outMax)
		sptr->out = sptr->outMax;
	if(sptr->out <= sptr->outMin)
		sptr->out = sptr->outMin;
	return(sptr->out); 
}

void PID_Clear(PIDStructure_t* sptr, float outInit)
{
	sptr->accD = 0;
	sptr->accD_D1 = 0;
	sptr->error_D1 = 0;
	sptr->out = outInit;
}



