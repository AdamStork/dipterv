/**
 * @file 	wrapper_timer.c
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for Timers (PWM testing) 			**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __wrapper_timer_H
#define __wrapper_timer_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


extern TIM_HandleTypeDef htimFreq;
extern TIM_HandleTypeDef htimAct;


void pwm_timer_frequency_init(void);
void pwm_timer_activity_init(void);


#ifdef __cplusplus
}
#endif
#endif /*__ wrapper_timer_H */


