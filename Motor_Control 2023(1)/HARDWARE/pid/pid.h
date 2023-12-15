#ifndef _PID_H
#define _PID_H

typedef struct
{
	float ref;
	float kp; 
	float ki; 
	float kd;
	float N;
	float accD;
	float Ts;
	float out;
	float outMax;
	float outMin;
	float accD_D1;
	float error_D1;
} PIDStructure_t;

void PID_Init(PIDStructure_t* sptr, float kp, float ki, float kd, float N, float Ts, float outMin, float outMax, float outInit);
float PID_Calc(PIDStructure_t* sptr, float fdb);
void PID_Clear(PIDStructure_t* sptr, float outInit);
	
#endif
