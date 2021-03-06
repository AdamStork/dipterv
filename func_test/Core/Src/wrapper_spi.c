/**
 * @file 	wrapper_spi.c
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for SPI testing 			**/

/* Includes ------------------------------------------------------------------*/
#include <wrapper_main.h>
#include "peripheral_config.h"
#include "wrapper_spi.h"

SPI_HandleTypeDef hspi;
static uint8_t txBuffer[50];
static uint8_t rxBuffer[50];
static bool invalidPeripheral = false;



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
	buffer_init_zero(rxBuffer, sizeof(rxBuffer));
	buffer_init_zero(txBuffer, sizeof(txBuffer));

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

	// 4-wire SPI Full-duplex mode
	if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_FULL_DUPLEX_MASTER){
		uint8_t totalSize = txSize + slaveResponse;

		status = HAL_SPI_TransmitReceive(&hspi, txBuffer,rxBuffer,totalSize,1000);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);

		if(status == HAL_TIMEOUT){
			HAL_SPI_DeInit(&hspi);
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
		// TI mode protocol
		else{
			for(uint8_t i = 0; i<slaveResponse; i++){
				resp |= (rxBuffer[txSize+i] << ((slaveResponse-1-i)*8));
			}
		}

		message_out->has_response = true;
		message_out->response.has_responseRead = true;
		message_out->response.responseRead = resp;
	}

	// 4-wire SPI transmit only mode
	else if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_TRANSMIT_4WIRE_MASTER){
		status = HAL_SPI_Transmit(&hspi, txBuffer,txSize,TEST_TIMEOUT_DURATION);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);

		if(status == HAL_TIMEOUT){
			HAL_SPI_DeInit(&hspi);
			spi_error_handler(message_out);
			return;
		}

		message_out->has_response = true;
		message_out->response.has_responseEnum = true;
		message_out->response.responseEnum = responseEnum_t_SPI_TRANSMISSION_OK;
	}

	// 4-wire SPI receive only mode
	else if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_RECEIVE_4WIRE_MASTER){
		uint8_t rxSize = slaveResponse;

		status = HAL_SPI_Receive(&hspi, rxBuffer, rxSize, 1000);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);
		if(status == HAL_TIMEOUT){
			HAL_SPI_DeInit(&hspi);
			spi_error_handler(message_out);
			return;
		}

		uint32_t resp = 0;
		// Motorola format only
		if(message_in->spi.frameFormat == spiFrameFormat_SPI_FRAME_FORMAT_MOTOROLA){
			// MSB first
			if(firstMSB){
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[i] << ((slaveResponse-1-i)*8));
				}
			}
			// LSB first
			else{
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[i] << (i*8));
				}
			}
		}

		message_out->has_response = true;
		message_out->response.has_responseRead = true;
		message_out->response.responseRead = resp;
	}

	// 3-wire SPI Half-duplex mode: Master MOSI <---> Slave MISO
	else if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_HALF_DUPLEX_TX_MASTER){
		status = HAL_SPI_Transmit(&hspi, txBuffer, txSize, TEST_TIMEOUT_DURATION);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);

		if(status == HAL_TIMEOUT){
			HAL_SPI_DeInit(&hspi);
			spi_error_handler(message_out);
			return;
		}

		message_out->has_response = true;
		message_out->response.has_responseEnum = true;
		message_out->response.responseEnum = responseEnum_t_SPI_TRANSMISSION_OK;
	}

	// 3-wire SPI Half-duplex mode: Master MOSI <---> Slave MISO
	else if(message_in->spi.operatingMode == spiOperatingMode_SPI_MODE_HALF_DUPLEX_RX_MASTER){
		uint8_t rxSize = slaveResponse;

		status = HAL_SPI_Receive(&hspi, rxBuffer, rxSize, 1000);
		while(HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY);
		if(status == HAL_TIMEOUT){
			HAL_SPI_DeInit(&hspi);
			spi_error_handler(message_out);
			return;
		}

		uint32_t resp = 0;
		// Motorola format only
		if(message_in->spi.frameFormat == spiFrameFormat_SPI_FRAME_FORMAT_MOTOROLA){
			// MSB first
			if(firstMSB){
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[i] << ((slaveResponse-1-i)*8));
				}
			}
			// LSB first
			else{
				for(uint8_t i = 0; i<slaveResponse; i++){
					resp |= (rxBuffer[i] << (i*8));
				}
			}
		}

		message_out->has_response = true;
		message_out->response.has_responseRead = true;
		message_out->response.responseRead = resp;
	}

	else{
		HAL_SPI_DeInit(&hspi);
		spi_error_handler(message_out);
		return;
	}


	// Deinit SPI peripheral
	HAL_SPI_DeInit(&hspi);
}



/** @brief	SPI init
 *  @param	message_in: pointer to received message
 *  @param	hspi: pointer to SPI handler	**/
bool spi_init(Command* message_in, SPI_HandleTypeDef* hspi)
{
	switch(message_in->spi.bus){
	case spiBus_SPI1:
#ifdef HAS_SPI1
		hspi->Instance = SPI1;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case spiBus_SPI2:
#ifdef HAS_SPI2
		hspi->Instance = SPI2;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case spiBus_SPI3:
#ifdef HAS_SPI3
		hspi->Instance = SPI3;
#else
		invalidPeripheral = true;
		return false;
#endif
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
	case spiOperatingMode_SPI_MODE_HALF_DUPLEX_TX_MASTER:
	case spiOperatingMode_SPI_MODE_HALF_DUPLEX_RX_MASTER:
		hspi->Init.Mode = SPI_MODE_MASTER;
		hspi->Init.Direction = SPI_DIRECTION_1LINE;
		break;
	case spiOperatingMode_SPI_MODE_TRANSMIT_4WIRE_MASTER:
	case spiOperatingMode_SPI_MODE_RECEIVE_4WIRE_MASTER:
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

	if(invalidPeripheral == true){
		invalidPeripheral = false;
		message_out->response.responseEnum = responseEnum_t_INVALID_PERIPHERAL;
	}
	else{
		message_out->response.responseEnum = responseEnum_t_SPI_TRANSMISSION_FAIL;
	}
}

