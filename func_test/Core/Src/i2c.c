/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  if(i2cHandle->Instance==I2C1)
	  {
	  /* USER CODE BEGIN I2C1_MspInit 0 */

	  /* USER CODE END I2C1_MspInit 0 */

	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    /**I2C1 GPIO Configuration
	    PB8     ------> I2C1_SCL
	    PB9     ------> I2C1_SDA
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    /* I2C1 clock enable */
	    __HAL_RCC_I2C1_CLK_ENABLE();
	  /* USER CODE BEGIN I2C1_MspInit 1 */

	  /* USER CODE END I2C1_MspInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C2)
	  {
	  /* USER CODE BEGIN I2C2_MspInit 0 */

	  /* USER CODE END I2C2_MspInit 0 */

	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    /**I2C2 GPIO Configuration
	    PB10     ------> I2C2_SCL
	    PB3     ------> I2C2_SDA
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_10;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF9_I2C2;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    /* I2C2 clock enable */
	    __HAL_RCC_I2C2_CLK_ENABLE();
	  /* USER CODE BEGIN I2C2_MspInit 1 */

	  /* USER CODE END I2C2_MspInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C3)
	  {
	  /* USER CODE BEGIN I2C3_MspInit 0 */

	  /* USER CODE END I2C3_MspInit 0 */

	    __HAL_RCC_GPIOC_CLK_ENABLE();
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    /**I2C3 GPIO Configuration
	    PC9     ------> I2C3_SDA
	    PA8     ------> I2C3_SCL
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_9;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_8;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    /* I2C3 clock enable */
	    __HAL_RCC_I2C3_CLK_ENABLE();
	  /* USER CODE BEGIN I2C3_MspInit 1 */

	  /* USER CODE END I2C3_MspInit 1 */
	  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

	  if(i2cHandle->Instance==I2C1)
	  {
	  /* USER CODE BEGIN I2C1_MspDeInit 0 */

	  /* USER CODE END I2C1_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_I2C1_CLK_DISABLE();

	    /**I2C1 GPIO Configuration
	    PB8     ------> I2C1_SCL
	    PB9     ------> I2C1_SDA
	    */
	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

	  /* USER CODE BEGIN I2C1_MspDeInit 1 */

	  /* USER CODE END I2C1_MspDeInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C2)
	  {
	  /* USER CODE BEGIN I2C2_MspDeInit 0 */

	  /* USER CODE END I2C2_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_I2C2_CLK_DISABLE();

	    /**I2C2 GPIO Configuration
	    PB10     ------> I2C2_SCL
	    PB3     ------> I2C2_SDA
	    */
	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_3);

	  /* USER CODE BEGIN I2C2_MspDeInit 1 */

	  /* USER CODE END I2C2_MspDeInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C3)
	  {
	  /* USER CODE BEGIN I2C3_MspDeInit 0 */

	  /* USER CODE END I2C3_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_I2C3_CLK_DISABLE();

	    /**I2C3 GPIO Configuration
	    PC9     ------> I2C3_SDA
	    PA8     ------> I2C3_SCL
	    */
	    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);

	    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);

	  /* USER CODE BEGIN I2C3_MspDeInit 1 */

	  /* USER CODE END I2C3_MspDeInit 1 */
	  }
} 

/* USER CODE BEGIN 1 */



/**********************			I2C test				******************************/
/** @brief	I2C test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void i2c_test(Command* message_in, Command* message_out)
{
	I2C_HandleTypeDef hi2c;
	uint16_t deviceAddress = message_in->i2c.address;
	uint8_t deviceRegister = message_in->i2c.reg;
	HAL_StatusTypeDef status;
	bool success;

	// Init I2C peripheral
	success = i2c_init(message_in, &hi2c);
	if(success == false){
		i2c_error_handler(message_in, message_out);
		return;
	}

	// Perform I2C test and set response
	message_out->commandType = CommandTypeEnum_I2C_test;
	// I2C write
	if(message_in->i2c.direction == i2cDirection_I2C_write){
		uint8_t writeSize = message_in->i2c.size;
		uint8_t writeBuff[writeSize + 1];
		uint8_t i;

		// Place writeValue into buffer
		uint32_t writeValue_32 = message_in->i2c.writeValue;
		writeBuff[0] = deviceRegister;
		for(i = 0; i<writeSize; i++){
			writeBuff[1+i] = (uint8_t)(writeValue_32 >> (i*8));
		}

		// Send out data via I2C
		status = HAL_I2C_Master_Transmit(&hi2c,deviceAddress,writeBuff, sizeof(writeBuff), TEST_TIMEOUT_DURATION);
		message_out->has_response = true;
		message_out->response.has_responseEnum = true;
		if(status == HAL_OK){
			message_out->response.responseEnum = responseEnum_t_I2C_WRITE_OK;
		}
		else{
			message_out->response.responseEnum = responseEnum_t_I2C_WRITE_FAIL;
		}
	}
	// I2C read
	else{
		uint8_t* readBuff;
		uint8_t readSize = message_in->i2c.size;

		// Read out data via I2C
		status = HAL_I2C_Master_Transmit(&hi2c, deviceAddress, &deviceRegister, 1, TEST_TIMEOUT_DURATION);
		status &= HAL_I2C_Master_Receive(&hi2c, deviceAddress, readBuff, readSize, TEST_TIMEOUT_DURATION);
		message_out->has_response = true;

		if(status == HAL_OK){
			uint32_t readValue_32 = 0;
			uint8_t i;

			for(i = 0; i<readSize; i++){
				readValue_32 |= (readBuff[i] << (i*8));
			}
			message_out->response.has_responseRead = true;
			message_out->response.responseRead = readValue_32;
		}
		else{
			message_out->response.has_responseEnum = true;
			message_out->response.responseEnum = responseEnum_t_I2C_READ_FAIL;
		}

	}


	// Deinit I2C peripheral
	HAL_I2C_MspDeInit(&hi2c);
}



/** @brief	I2C init
 *  @param	message_in: pointer to received message
 *  @param	hi2c: pointer to I2C handler	**/
bool i2c_init(Command* message_in, I2C_HandleTypeDef* hi2c)
{
	switch(message_in->i2c.bus){
	case i2cBus_I2C1:
		hi2c->Instance = I2C1;
		break;
	case i2cBus_I2C2:
		hi2c->Instance = I2C2;
		break;
	case i2cBus_I2C3:
		hi2c->Instance = I2C3;
		break;
	default:
		return false;
	}

	hi2c->Init.ClockSpeed = message_in->i2c.clockSpeed;

	if(message_in->i2c.speedMode == i2cSpeedMode_I2C_SPEED_MODE_FAST){
		switch(message_in->i2c.dutyCycle){
		case i2cFastModeDutyCycle_I2C_DUTY_CYCLE_TLOW_THIGH_2:
			hi2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
			break;
		case i2cFastModeDutyCycle_I2C_DUTY_CYCLE_TLOW_THIGH_16_9:
			hi2c->Init.DutyCycle = I2C_DUTYCYCLE_16_9;
			break;
		default:
			break;
		}
	}
	else{ // Standard mode
		hi2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
	}


	//	Default settings
	hi2c->Init.OwnAddress1 = 0;
	hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c->Init.OwnAddress2 = 0;
	hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(hi2c) != HAL_OK){
		return false;
	}

	return true;
}


/** @brief	I2C error handler - set response
 *  @param  message_out: pointer to output message **/
void i2c_error_handler(Command* message_in, Command* message_out)
{
	message_out->commandType = CommandTypeEnum_I2C_test;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;
	if(message_in->i2c.direction == i2cDirection_I2C_write){
		message_out->response.responseEnum = responseEnum_t_I2C_WRITE_FAIL;
	}
	else{
		message_out->response.responseEnum = responseEnum_t_I2C_READ_FAIL;
	}
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
