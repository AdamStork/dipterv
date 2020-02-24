/**
  ******************************************************************************
  * File Name          : ADC.h
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "functional_test.pb.h"
#include "gpio.h"
/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */
bool analog_read_init(Command* message_in, ADC_HandleTypeDef* adcHandle, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void analog_read_test(Command* message_in, Command* message_out);
void analog_read_deinit(ADC_HandleTypeDef* adcHandler, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
uint32_t analog_read_choose_channel(Command* message_in);
void analog_read_error_handler(Command* message_out);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ adc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
