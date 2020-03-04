/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
#include "spi.h"

/* USER CODE BEGIN 0 */
SPI_HandleTypeDef hspi;
static uint8_t txBuffer[50];
static uint8_t rxBuffer[50];

/* USER CODE END 0 */



void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(spiHandle->Instance==SPI1)
	{
		/* USER CODE BEGIN SPI1_MspInit 0 */

		/* USER CODE END SPI1_MspInit 0 */
		/* SPI1 clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**SPI1 GPIO Configuration
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PA7     ------> SPI1_MOSI
		PA4     ------> SPI1_NSS
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI1_MspInit 1 */

		/* USER CODE END SPI1_MspInit 1 */
	}
	else if(spiHandle->Instance==SPI2)
	{
		/* USER CODE BEGIN SPI2_MspInit 0 */

		/* USER CODE END SPI2_MspInit 0 */
		/* SPI2 clock enable */
		__HAL_RCC_SPI2_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**SPI2 GPIO Configuration
		PC2     ------> SPI2_MISO
		PC3     ------> SPI2_MOSI
		PB10     ------> SPI2_SCK
		PB12     ------> SPI2_NSS
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI2_MspInit 1 */

		/* USER CODE END SPI2_MspInit 1 */
	}
	else if(spiHandle->Instance==SPI3)
	{
		/* USER CODE BEGIN SPI3_MspInit 0 */

		/* USER CODE END SPI3_MspInit 0 */
		/* SPI3 clock enable */
		__HAL_RCC_SPI3_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**SPI3 GPIO Configuration
		PC10     ------> SPI3_SCK
		PC11     ------> SPI3_MISO
		PC12     ------> SPI3_MOSI
		PA15     ------> SPI3_NSS
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI3_MspInit 1 */

		/* USER CODE END SPI3_MspInit 1 */
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

	if(spiHandle->Instance==SPI1)
	{
		/* USER CODE BEGIN SPI1_MspDeInit 0 */

		/* USER CODE END SPI1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI1_CLK_DISABLE();

		/**SPI1 GPIO Configuration
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PA7     ------> SPI1_MOSI
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

		/* USER CODE BEGIN SPI1_MspDeInit 1 */

		/* USER CODE END SPI1_MspDeInit 1 */
	}
	else if(spiHandle->Instance==SPI2)
	{
		/* USER CODE BEGIN SPI2_MspDeInit 0 */

		/* USER CODE END SPI2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI2_CLK_DISABLE();

		/**SPI2 GPIO Configuration
		PC2     ------> SPI2_MISO
		PC3     ------> SPI2_MOSI
		PB10     ------> SPI2_SCK
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_2|GPIO_PIN_3);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

		/* USER CODE BEGIN SPI2_MspDeInit 1 */

		/* USER CODE END SPI2_MspDeInit 1 */
	}
	else if(spiHandle->Instance==SPI3)
	{
		/* USER CODE BEGIN SPI3_MspDeInit 0 */

		/* USER CODE END SPI3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI3_CLK_DISABLE();

		/**SPI3 GPIO Configuration
		PC10     ------> SPI3_SCK
		PC11     ------> SPI3_MISO
		PC12     ------> SPI3_MOSI
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12);

		/* USER CODE BEGIN SPI3_MspDeInit 1 */

		/* USER CODE END SPI3_MspDeInit 1 */
	}
} 

/* USER CODE BEGIN 1 */


/**********************			SPI test				******************************/
/** @brief	SPI test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void spi_test(Command* message_in, Command* message_out)
{
	uint8_t command = message_in->spi.command;
	uint8_t dummyClocks = message_in->spi.dummyClocks;
	uint16_t writeValue = message_in->spi.writeValue;
	uint8_t writeSize = message_in->spi.writeSize;
	uint8_t slaveResponse = message_in->spi.slaveResponse;
	uint8_t txSize = 1 + dummyClocks + writeSize;

	HAL_StatusTypeDef status;
	bool firstMSB = false;
	bool success;

	// Motorola frameFormat
	if(message_in->spi.has_firstBit){
		if(message_in->spi.firstBit == spiFirstBit_SPI_FIRST_BIT_MSB){
			firstMSB = true;
		}
		else{
			firstMSB = false;
		}
	}

	// Fill txBuffer
	txBuffer[0] = command;
	if(dummyClocks > 0){
		uint8_t i;
		for(i = 0; i < dummyClocks; i++){
			txBuffer[1+i] = 0;
		}
	}
	if(writeSize > 0){
		uint8_t i;
		// MSB first
		if(firstMSB){
			for(i = 0; i < writeSize; i++){
				txBuffer[1+dummyClocks+i] = (uint8_t)(writeValue >> ((writeSize-1-i)*8));
			}
		}
		// LSB first
		else{
			for(i = 0; i < writeSize; i++){
				txBuffer[1+dummyClocks+i] = (uint8_t)(writeValue >> (i*8));
			}
		}

	}

	// Init SPI peripheral
	success = spi_init(message_in, &hspi);
	if(success == false){
		spi_error_handler(message_out);
		return;
	}

	// Perform SPI test and set response
	message_out->commandType = CommandTypeEnum_SPI_test;

	if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_FULL_DUPLEX_MASTER){
		uint8_t rxSize = txSize + slaveResponse;
		uint8_t txByte = 0xA5;

		status = HAL_SPI_Transmit(&hspi,&txByte, 1, TEST_TIMEOUT_DURATION);
//			status = HAL_SPI_TransmitReceive(&hspi,txBuffer,rxBuffer,rxSize, TEST_TIMEOUT_DURATION);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);
		if(status == HAL_TIMEOUT){
			spi_error_handler(message_out);
			return;
		}


		uint32_t resp = 0;
		// Motorola format only
		if(message_in->spi.frameFormat == spiFrameFormat_SPI_FRAME_FORMAT_MOTOROLA){
			// MSB first
			if(firstMSB){
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[txSize+i] << ((slaveResponse-1-i)*8));
				}
			}
			// LSB first
			else{
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[txSize+i] << (i*8));
				}
			}
		}

		message_out->has_response = true;
		message_out->response.has_responseRead = true;
		message_out->response.responseRead = resp;
	}

	else if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_HALF_DUPLEX_MASTER){
		uint8_t rxSize = slaveResponse;

		status = HAL_SPI_TransmitReceive(&hspi,txBuffer,rxBuffer,rxSize, TEST_TIMEOUT_DURATION);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);
		if(status == HAL_TIMEOUT){
			spi_error_handler(message_out);
			return;
		}


		uint32_t resp = 0;
		// Motorola format only
		if(message_in->spi.frameFormat == spiFrameFormat_SPI_FRAME_FORMAT_MOTOROLA){
			// MSB first
			if(firstMSB){
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[txSize+i] << ((slaveResponse-1-i)*8));
				}
			}
			// LSB first
			else{
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[txSize+i] << (i*8));
				}
			}
		}

		message_out->has_response = true;
		message_out->response.has_responseRead = true;
		message_out->response.responseRead = resp;

	}

	else if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_TRANSMIT_ONLY_MASTER){

		status = HAL_SPI_Transmit(&hspi, txBuffer,txSize,TEST_TIMEOUT_DURATION);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);

		if(status == HAL_TIMEOUT){
			spi_error_handler(message_out);
			return;
		}

		message_out->has_response = true;
		message_out->response.has_responseEnum = true;
		message_out->response.responseEnum = responseEnum_t_SPI_TRANSMISSION_OK;
	}
	else{
		// empty
	}


	// Deinit SPI peripheral
//	HAL_SPI_MspDeInit(&hspi);
}



/** @brief	SPI init
 *  @param	message_in: pointer to received message
 *  @param	hspi: pointer to SPI handler	**/
bool spi_init(Command* message_in, SPI_HandleTypeDef* hspi)
{
	switch(message_in->spi.bus){
	case spiBus_SPI1:
		hspi->Instance = SPI1;
		break;
	case spiBus_SPI2:
		hspi->Instance = SPI2;
		break;
	case spiBus_SPI3:
		hspi->Instance = SPI3;
		break;
	default:
		return false;
	}

	// Master mode only
	switch(message_in->spi.operatingMode){
	case spiOperatingMode_SPI_MODE_FULL_DUPLEX_MASTER:
		hspi->Init.Mode = SPI_MODE_MASTER;
		hspi->Init.Direction = SPI_DIRECTION_2LINES;
		break;
	case spiOperatingMode_SPI_MODE_HALF_DUPLEX_MASTER:
		hspi->Init.Mode = SPI_MODE_MASTER;
		hspi->Init.Direction = SPI_DIRECTION_1LINE;
		break;
	case spiOperatingMode_SPI_MODE_TRANSMIT_ONLY_MASTER:
		hspi->Init.Mode = SPI_MODE_MASTER;
		hspi->Init.Direction = SPI_DIRECTION_2LINES;
		break;
	}


	switch(message_in->spi.dataSize){
	case spiDataSize_SPI_DATA_SIZE_8_BITS:
		hspi->Init.DataSize = SPI_DATASIZE_8BIT;
		break;
	case spiDataSize_SPI_DATA_SIZE_16_BITS:
		hspi->Init.DataSize = SPI_DATASIZE_16BIT;
		break;
	default:
		break;
	}

	switch(message_in->spi.hardwareNSS){
	case spiHardwareNSS_DISABLE:
		hspi->Init.NSS = SPI_NSS_SOFT;
		break;
	case spiHardwareNSS_NSS_INPUT:
		hspi->Init.NSS = SPI_NSS_HARD_INPUT;
		break;
	case spiHardwareNSS_NSS_OUTPUT:
		hspi->Init.NSS = SPI_NSS_HARD_OUTPUT;
		break;
	}

	// Motorola frame format
	if(message_in->spi.frameFormat == spiFrameFormat_SPI_FRAME_FORMAT_MOTOROLA){
		hspi->Init.TIMode = SPI_TIMODE_DISABLED;

		switch(message_in->spi.firstBit){
		case spiFirstBit_SPI_FIRST_BIT_MSB:
			hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
			break;
		case spiFirstBit_SPI_FIRST_BIT_LSB:
			hspi->Init.FirstBit = SPI_FIRSTBIT_LSB;
			break;
		default:
			break;
		}

		switch(message_in->spi.clockMode){
		case clockMode_SPI_MODE_0:
			hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
			hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
			break;
		case clockMode_SPI_MODE_1:
			hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
			hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
			break;
		case clockMode_SPI_MODE_2:
			hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
			hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
			break;
		case clockMode_SPI_MODE_3:
			hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
			hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
			break;
		default:
			break;
		}


	}
	// TI frame forat
	else{
		hspi->Init.TIMode = SPI_TIMODE_ENABLED;


	}

	// Default settings
	hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi->Init.CRCPolynomial = 10;

	if (HAL_SPI_Init(hspi) != HAL_OK){
		return false;
	}

	HAL_SPI_MspInit(hspi);
	return true;
}


/** @brief	SPI error handler - set response
 *  @param  message_out: pointer to output message **/
void spi_error_handler(Command* message_out)
{
	message_out->commandType = CommandTypeEnum_SPI_test;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;
	message_out->response.responseEnum = responseEnum_t_SPI_TRANSMISSION_FAIL;
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
