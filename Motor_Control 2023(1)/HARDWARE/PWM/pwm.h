#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x_tim.h"

void TIM1_PWM_Init(u16 arr,u16 psc);
void PWM_Modulation(float duty);

#endif
