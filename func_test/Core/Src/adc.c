/**
  ******************************************************************************
  * File Name          : ADC.c
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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();


  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC1 GPIO Configuration    
    PA0-WKUP     ------> ADC1_IN0 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/**********************			Analog read 			******************************/
/** @brief	Analog read (ADC) test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void analog_read_test(Command* message_in, Command* message_out)
{
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	ADC_HandleTypeDef adcHandle;
	bool success;

	// choose GPIO port and pin
	success = gpio_port_pin(message_in->analog_in.pin, &gpioPin, &gpioPort);
	if(success == false){
		analog_read_error_handler(message_out);
    	return;
	}

	// Initialize ADC & GPIO if CubeMX config file is not available
	success &= analog_read_init(message_in, &adcHandle, gpioPort, gpioPin);
	if(success == false){
		analog_read_error_handler(message_out);
    	return;
	}

	// ADC test
	if(HAL_ADC_Start(&adcHandle) != HAL_OK){
		analog_read_error_handler(message_out);
    	return;
	}

	uint32_t adcValue = HAL_ADC_GetValue(&adcHandle);

	// Set response
	message_out->commandType = CommandTypeEnum_Analog_read;
	message_out->has_response = true;
	message_out->response.has_responseRead = true;
	message_out->response.responseRead = 3300*adcValue/4096;

	// ADC deinit
	analog_read_deinit(&adcHandle, gpioPort, gpioPin);
}


/** @brief	Analog read (ADC) peripheral init
 *  @param	message_in: pointer to received message
 *  @param  gpioPort: pointer to GPIO port handler
 *  @param	gpioPin: GPIO pin number [0-15]				**/
bool analog_read_init(Command* message_in, ADC_HandleTypeDef* adcHandle, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	// Configure ADC instance
	if(message_in->analog_in.instance == adcInstance_ADC1){
		adcHandle->Instance = ADC1;
	    __HAL_RCC_ADC1_CLK_ENABLE();
	}
	else{
		// Invalid ADC instance
    	return false;
	}

	// Configure ADC clock prescaler
	switch(message_in->analog_in.clockPrescaler){
	case adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_4:
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
		break;
	case adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_6:
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
		break;
	case adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_8:
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
		break;
	default:
		break;
	}


	// Configure ADC resolution
	switch(message_in->analog_in.resolution){
	case adcResolution_ADC_12_BITS:
		adcHandle->Init.Resolution = ADC_RESOLUTION_12B;
		break;
	case adcResolution_ADC_10_BITS:
		adcHandle->Init.Resolution = ADC_RESOLUTION_10B;
		break;
	case adcResolution_ADC_8_BITS:
		adcHandle->Init.Resolution = ADC_RESOLUTION_8B;
		break;
	case adcResolution_ADC_6_BITS:
		adcHandle->Init.Resolution = ADC_RESOLUTION_6B;
		break;
	default:
		break;
	}


	adcHandle->Init.ScanConvMode = DISABLE;
	adcHandle->Init.ContinuousConvMode = DISABLE;
	adcHandle->Init.DiscontinuousConvMode = DISABLE;
	adcHandle->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	adcHandle->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	adcHandle->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adcHandle->Init.NbrOfConversion = 1;
	adcHandle->Init.DMAContinuousRequests = DISABLE;
	adcHandle->Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(adcHandle) != HAL_OK){
		return false;
	}

	// Pin configuration
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = gpioPin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(gpioPort, &GPIO_InitStruct);


	// Define ADC Channel handler
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. **/
	sConfig.Channel = analog_read_choose_channel(message_in);
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(adcHandle, &sConfig) != HAL_OK){
		return false;
	}

	return true;
}


/** @brief	ADC error handler - set response
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to output message **/
void analog_read_error_handler(Command* message_out)
{
	message_out->commandType = CommandTypeEnum_Analog_read;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;
	message_out->response.responseEnum = responseEnum_t_ADC_READ_FAIL;
}


/** @brief	ADC peripheral deinit
 *  @param	message_in: pointer to received message
 *  @param  gpioPort: pointer to GPIO port handler
 *  @param	gpioPin: GPIO pin number [0-15]				**/
void analog_read_deinit(ADC_HandleTypeDef* adcHandle,GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	if(adcHandle->Instance == ADC1){
		__HAL_RCC_ADC1_CLK_DISABLE();
		HAL_GPIO_DeInit(gpioPort, gpioPin);
		HAL_ADC_DeInit(adcHandle);
	}
}



/** @brief	choose ADC channel
 *  @param	message_in: pointer to received message
 *  @param  adcChannel: pointer to adc channel		**/
uint32_t analog_read_choose_channel(Command* message_in)
{
	uint32_t adcChannel = 0;

	switch(message_in->analog_in.channel){
	case adcChannel_ADC_CHANNEL_IN0:
		adcChannel = ADC_CHANNEL_0;
		break;
	case adcChannel_ADC_CHANNEL_IN1:
		adcChannel = ADC_CHANNEL_1;
		break;
	case adcChannel_ADC_CHANNEL_IN2:
		adcChannel = ADC_CHANNEL_2;
		break;
	case adcChannel_ADC_CHANNEL_IN3:
		adcChannel = ADC_CHANNEL_3;
		break;
	case adcChannel_ADC_CHANNEL_IN4:
		adcChannel = ADC_CHANNEL_4;
		break;
	case adcChannel_ADC_CHANNEL_IN5:
		adcChannel = ADC_CHANNEL_5;
		break;
	case adcChannel_ADC_CHANNEL_IN6:
		adcChannel = ADC_CHANNEL_6;
		break;
	case adcChannel_ADC_CHANNEL_IN7:
		adcChannel = ADC_CHANNEL_7;
		break;
	case adcChannel_ADC_CHANNEL_IN8:
		adcChannel = ADC_CHANNEL_8;
		break;
	case adcChannel_ADC_CHANNEL_IN9:
		adcChannel = ADC_CHANNEL_9;
		break;
	case adcChannel_ADC_CHANNEL_IN10:
		adcChannel = ADC_CHANNEL_10;
		break;
	case adcChannel_ADC_CHANNEL_IN11:
		adcChannel = ADC_CHANNEL_11;
		break;
	case adcChannel_ADC_CHANNEL_IN12:
		adcChannel = ADC_CHANNEL_12;
		break;
	case adcChannel_ADC_CHANNEL_IN13:
		adcChannel = ADC_CHANNEL_13;
		break;
	case adcChannel_ADC_CHANNEL_IN14:
		adcChannel = ADC_CHANNEL_14;
		break;
	case adcChannel_ADC_CHANNEL_IN15:
		adcChannel = ADC_CHANNEL_15;
		break;
	case adcChannel_ADC_CHANNEL_TEMP:
		adcChannel = ADC_CHANNEL_16;
		break;
	case adcChannel_ADC_CHANNEL_VREFINT:
		adcChannel = ADC_CHANNEL_VREFINT;
		break;
	case adcChannel_ADC_CHANNEL_VBAT:
		adcChannel = ADC_CHANNEL_VBAT;
		break;
	default:
		break;
	}

	return adcChannel;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
