/**
 * @file 	wrapper_pwm.h
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for PWM testing 			**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __wrapper_gpio_H
#define __wrapper_gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "functional_test.pb.h"

void gpio_init(Command* message_in, GPIO_TypeDef* gpioPort, uint32_t gpioPin);
void gpio_test(Command* message_in, Command* message_out);
void gpio_deinit(GPIO_TypeDef* gpioPort, uint32_t gpioPin);
bool gpio_port_pin(gpioPins pinEnum, uint16_t* gpioPin, GPIO_TypeDef** gpioPort);
void gpio_error(Command* message_in, Command* message_out);


#ifdef __cplusplus
}
#endif
#endif /*__ wrapper_gpio_H */


