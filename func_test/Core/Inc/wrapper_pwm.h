/**
 * @file 	wrapper_pwm.h
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for PWM testing 			**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __wrapper_pwm_H
#define __wrapper_pwm_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "functional_test.pb.h"
#include "gpio.h"

#define PWM_DUTY_MAX 100


bool pwm_init(Command* message_in);
void pwm_test(Command* message_in, Command* message_out);
void pwm_error_handler(Command* message_out);

#ifdef __cplusplus
}
#endif
#endif /*__ wrapper_pwm_H */


