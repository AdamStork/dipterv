/**
 * @file 	wrapper_pwm.h
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for PWM testing 			**/

/* Includes ------------------------------------------------------------------*/
#include "test.h"
#include "peripheral_config.h"
#include "wrapper_i2c.h"


I2C_HandleTypeDef hi2c;
static uint8_t writeBuff[5];
static uint8_t readBuff[5];
static bool invalidPeripheral = false;


/**********************			I2C test				******************************/
/** @brief	I2C test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void i2c_test(Command* message_in, Command* message_out)
{
	uint8_t deviceAddress = (message_in->i2c.address) << 1; // use 8-bit address
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
		uint8_t writeSize = message_in->i2c.size;	// WriteValue size (1 or 2 bytes)

		// Place writeValue into buffer
		uint32_t writeValue_32 = message_in->i2c.writeValue;
		writeBuff[0] = deviceRegister;
		for(uint8_t i = 0; i<writeSize; i++){
			writeBuff[1+i] = (uint8_t)(writeValue_32 >> (i*8));
		}

		// Send out data via I2C
		status = HAL_I2C_Master_Transmit(&hi2c,(uint16_t)deviceAddress,writeBuff, writeSize+1, TEST_TIMEOUT_DURATION);		// wait: IsDeviceReady
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
		uint8_t readSize = message_in->i2c.size;	// Number of bytes expected to sent back by slave
		writeBuff[0] = deviceRegister;

		// Read out data via I2C
		status = HAL_BUSY;
		while(status != HAL_OK){
			status = HAL_I2C_Master_Transmit(&hi2c, (uint16_t)deviceAddress, writeBuff, 1, TEST_TIMEOUT_DURATION);		// wait: IsDeviceReady
			if(status == HAL_TIMEOUT){
				i2c_error_handler(message_in, message_out);
				return;
			}
		}

		status = HAL_BUSY;
		while(status != HAL_OK){
			status = HAL_I2C_Master_Receive(&hi2c, (uint16_t)deviceAddress, readBuff, readSize, TEST_TIMEOUT_DURATION);		// wait: IsDeviceReady
			if(status == HAL_TIMEOUT){
				i2c_error_handler(message_in, message_out);
				return;
			}
		}

		uint32_t readValue_32 = 0;

		for(uint8_t i = 0; i<readSize; i++){
			readValue_32 |= (readBuff[i] << (i*8));
		}
		message_out->has_response = true;
		message_out->response.has_responseRead = true;
		message_out->response.responseRead = readValue_32;
	}


	// Deinit I2C peripheral
//	HAL_I2C_MspDeInit(&hi2c_2);
	buffer_init_zero(writeBuff, sizeof(writeBuff));
	buffer_init_zero(readBuff, sizeof(readBuff));
}



/** @brief	I2C init
 *  @param	message_in: pointer to received message
 *  @param	hi2c: pointer to I2C handler	**/
bool i2c_init(Command* message_in, I2C_HandleTypeDef* hi2c)
{
	switch(message_in->i2c.bus){
	case i2cBus_I2C1:
#ifdef HAS_I2C1
		hi2c->Instance = I2C1;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case i2cBus_I2C2:
#ifdef HAS_I2C2
		hi2c->Instance = I2C2;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case i2cBus_I2C3:
#ifdef HAS_I2C3
		hi2c->Instance = I2C3;
#else
		invalidPeripheral = true;
		return false;
#endif
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
	if(invalidPeripheral == true){
		invalidPeripheral = false;
		message_out->response.responseEnum = responseEnum_t_INVALID_PERIPHERAL;
	}
	else if(message_in->i2c.direction == i2cDirection_I2C_write){
		message_out->response.responseEnum = responseEnum_t_I2C_WRITE_FAIL;
	}
	else{
		message_out->response.responseEnum = responseEnum_t_I2C_READ_FAIL;
	}
}

