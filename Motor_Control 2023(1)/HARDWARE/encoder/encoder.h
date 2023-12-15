#ifndef __ENCODER_H
#define __ENCODER_H
#include "stm32f10x_tim.h"

void TIM3_Encoder_Init(void);
float GetMotorSpeed(void);

#endif
