/**
 * @file 	wrapper_pwm.h
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for PWM testing 			**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __wrapper_i2c_H
#define __wrapper_i2c_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "functional_test.pb.h"

bool i2c_init(Command* message_in, I2C_HandleTypeDef* hi2c);
void i2c_test(Command* message_in, Command* message_out);
void i2c_error_handler(Command* message_in, Command* message_out);

#ifdef __cplusplus
}
#endif
#endif /*__ wrapper_i2c_H */


