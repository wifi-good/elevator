#ifndef __MAIN_H
#define __MAIN_H
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "adc.h"
#include "pid.h"
#include "timer.h"
#include "encoder.h"
#include "usart.h"
#include "key.h"
#include "led.h"
#include "debug_JustFloat.h"
#include "lse.h"


extern float speed, refVoltage;
extern PIDStructure_t speedPIDStructure;

typedef enum 
{
	STOPMODE = 0,
	OPENLOOPMODE,
	SPEEDMODE,
	POSITIONMODE
}Mode_t;

void mainControl(void);

#define UP 1
#define DOWN 2
#define KEEP 0

#define OPEN_LOOP_DEBUG	0

#endif
