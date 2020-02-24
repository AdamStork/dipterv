/**
  ******************************************************************************
  * File Name          : pwm.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pwm.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

GPIO_TypeDef *gpioPortPWM;
uint16_t gpioPinPWM;
uint32_t pwmCounter;
uint8_t pwmDuty;



/**********************			PWM test				******************************/
/** @brief	Analog write (PWM) test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void pwm_test(Command* message_in, Command* message_out)
{
	bool success;
	// choose GPIO port and pin
	success = gpio_port_pin(message_in->analog_out.pin, &gpioPinPWM, &gpioPortPWM);
	if(success == false){
		pwm_error_handler(message_out);
		return;
	}

	// Initialize and start PWM (GPIO + Timer)
	success &= pwm_init(message_in);
	if(success == false){
		pwm_error_handler(message_out);
		return;
	}

	// Set response commandType
	message_out->commandType = CommandTypeEnum_Analog_write;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;
	message_out->response.responseEnum = responseEnum_t_PWM_SET_OK;
}


/** @brief	Analog read (ADC) peripheral init
 *  @param	message_in: pointer to received message		**/
bool pwm_init(Command* message_in)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();


	// Pin configuration
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = gpioPinPWM;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(gpioPortPWM, &GPIO_InitStruct);

    // Timer2 set new period
    pwmCounter = 0;
    pwmDuty = message_in->analog_out.dutyCycle;
    htim2.Init.Period = ((1000/(message_in->analog_out.frequency))/PWM_DUTY_MAX) - 1;
    if(HAL_TIM_Base_Init(&htim2) != HAL_OK){
    	return false;
    }

    // Init and start Timer3 if PWM time dependency is enabled (active for given time only)
	if((message_in->analog_out.has_time == true) && (message_in->analog_out.dependency == pwmTimeDependency_PWM_TIME_DEPENDENCY_ENABLED)){
		htim3.Init.Period = (message_in->analog_out.time) - 1;
	    if(HAL_TIM_Base_Init(&htim3) != HAL_OK){
	    	return false;
	    }

		if(HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_1)){
			return false;
		}
	}

	if(HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1) != HAL_OK){
		return false;
	}

	return true;
}

/** @brief	PWM error handler - set response
 *  @param  message_out: pointer to output message **/
void pwm_error_handler(Command* message_out)
{
	message_out->commandType = CommandTypeEnum_Analog_write;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;
	message_out->response.responseEnum = responseEnum_t_PWM_SET_FAIL;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
