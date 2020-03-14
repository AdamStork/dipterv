/**
 * @file 	wrapper_p.h
 * @author 	Adam Golya
 * @date   	13 03 2019
 * @brief 	Wrapper for PWM testing 			**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __wrapper_adc_H
#define __wrapper_adc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "functional_test.pb.h"
#include "gpio.h"



bool analog_read_init(Command* message_in, ADC_HandleTypeDef* adcHandle, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void analog_read_test(Command* message_in, Command* message_out);
void analog_read_deinit(ADC_HandleTypeDef* adcHandler, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
uint32_t analog_read_choose_channel(Command* message_in);
void analog_read_error_handler(Command* message_out);

#ifdef __cplusplus
}
#endif

#endif /*__ wrapper_adc_H */
