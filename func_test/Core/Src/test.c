/*
 * test.c
 *
 *  Created on: 2019. okt. 19.
 *      Author: Adam Golya
 */
#include <string.h>
#include <stdbool.h>
#include "pb_encode.h"
#include "pb_decode.h"
#include "usart.h"
#include "test.h"
#include "link_layer.h"
#include "functional_test.pb.h"


bool frameReady = false;
uint8_t receiveByte;
uint8_t transmitByte;
uint8_t receiveBuffer[50];
uint8_t transmitBuffer[50];
uint8_t receiveBufferLen;
link_layer_t linkLayer;
StateType deviceState;



/** @brief 	Encode message
 * @param[out]	pBuffer: pointer to encoded buffer
 * @param[in]	pBufferLen: length of buffer (max length of stream)
 * @param[in]	message_out: pointer to message to encode
 * @return	status: true, if encoding was successful
 */
bool encode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_out, uint8_t* bytesWritten)
{
	bool status;
	pb_ostream_t stream_out = pb_ostream_from_buffer(pBuffer, pBufferLen);
	status = pb_encode(&stream_out,Command_fields,message_out);
	*bytesWritten = (uint8_t)stream_out.bytes_written;
	return status;
}


/** @brief 	Decode message
 * @param[in]	pBuffer: pointer to buffer to decode
 * @param[in]	pBufferLen: length of buffer (max length of stream)
 * @param[out]	message_in: decoded message
 * @return	status: true, if encoding was successful
 */
bool decode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_in)
{
	bool status;
	pb_istream_t stream_in = pb_istream_from_buffer(pBuffer, pBufferLen);
	status = pb_decode(&stream_in, Command_fields,message_in);
	return status;
}


/** @brief 	Init buffer with zeros
 *  @param	pBuffer: pointer to buffer
 *  @param 	pSize: size of pBuffer
 */
void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize)
{
	for(int i = 0; i<pSize; i++){
		pBuffer[i] = 0;
	}

}


/** @brief 	Send out buffer via UART
 *  @param	pBuffer: pointer to buffer
 *  @param	pSize: size of buffer**/
void buffer_send(uint8_t* pBuffer, uint8_t pSize)
{
	HAL_UART_Transmit(&huart2,pBuffer, pSize, HAL_MAX_DELAY);
}

/** @brief  Resets command message to default
 *  @param	message: pointer to command message **/
void command_reset(Command* message)
{
	message->commandType = _CommandTypeEnum_MIN;

	// Reset I2C
	message->has_i2c = false;
	message->i2c.bus = _i2cBus_MIN;
	message->i2c.address = 0;
	message->i2c.reg = 0;
	message->i2c.direction = _i2cDirection_MIN;
	message->i2c.speedMode = _i2cSpeedMode_MIN;
	message->i2c.clockSpeed = 0;
	message->i2c.has_dutyCycle = false;
	message->i2c.dutyCycle = _i2cFastModeDutyCycle_MIN;

	// Reset SPI
	message->has_spi = false;
	message->spi.bus = _spiBus_MIN;
	message->spi.command = 0;
	message->spi.dummyclocks = 0;
	message->spi.operatingMode = _spiOperatingMode_MIN;
	message->spi.hardwareNSS = _spiHardwareNSS_MIN;
	message->spi.frameFormat = _spiFrameFormat_MIN;
	message->spi.dataSize = _spiDataSize_MIN;
	message->spi.has_firstBit = false;
	message->spi.firstBit = _spiFirstBit_MIN;
	message->spi.has_clockMode = false;
	message->spi.clockMode = _clockMode_MIN;

	// Reset USART
	message->has_usart = false;
	message->usart.bus = _usartBus_MIN;
	message->usart.mode = _usartMode_MIN;
	message->usart.baudRate = 0;
	message->usart.wordLength = _usartWordLength_MIN;
	message->usart.parity = _usartParity_MIN;
	message->usart.stopBits = _usartStopBits_MIN;
	message->usart.direction = _usartDirection_MIN;
	message->usart.command = 0;
	message->usart.has_clockPolarity = false;
	message->usart.clockPolarity = _usartClockPolarity_MIN;
	message->usart.has_clockPhase = false;
	message->usart.clockPhase = _usartClockPhase_MIN;
	message->usart.has_clockLastBit = false;
	message->usart.clockLastBit = _usartClockLastBit_MIN;
	message->usart.has_hwFlowControl = false;
	message->usart.hwFlowControl = _usartHardwareFlowControl_MIN;

	// Reset GPIO
	message->has_gpio = false;
	message->gpio.pin = _gpioPins_MIN;
	message->gpio.direction = _gpioDirection_MIN;
	message->gpio.state = _gpioPinState_MIN;
	message->gpio.pull = _gpioPull_MIN;

	// Reset analog_in
	message->has_analog_in = false;
	message->analog_in.instance = _adcInstance_MIN;
	message->analog_in.pin = _gpioPins_MIN;
	message->analog_in.resolution = _adcResolution_MIN;
	message->analog_in.clockPrescaler = _adcClockPrescaler_MIN;

	// Reset analog_out
	message->has_analog_out = false;
	message->analog_out.pin = _gpioPins_MIN;
	message->analog_out.frequency = 0;
	message->analog_out.dutyCycle = 0;
	message->analog_out.dependency = _pwmTimeDependency_MIN;
	message->analog_out.has_time = false;
	message->analog_out.time = 0;

	// Reset response
	message->has_response = false;
	message->response.has_responseRead = false;
	message->response.has_responseWrite = false;
	message->response.responseRead = 0;
	message->response.responseWrite = _successfulWrite_MIN;

	// Reset autoConfig
	message->has_autoConfig = false;
	message->autoConfig = false;


}

/** @brief Receive command via UART, and perform chosen test **/
void enter_processing_state(void)
{
	Command message_in = Command_init_zero;
	Command message_out = Command_init_zero;
	uint8_t bytesWritten = 0;
	buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
	bool messageDecodeSuccessful = false;
	deviceState = STATE_WAIT;

	while (1){
		switch(deviceState){
		case STATE_WAIT:
//			HAL_UART_Receive_DMA(&huart2,(uint8_t*)&receiveByte, 1);
			HAL_UART_Receive(&huart2,(uint8_t*)&receiveByte, 1,HAL_MAX_DELAY);
			deviceState = STATE_PROCESS;
			break;
		case STATE_PROCESS:
			link_parse_byte(&linkLayer, receiveByte);
			if(link_get_valid_frame(&linkLayer,receiveBuffer, &receiveBufferLen)){
				deviceState = STATE_DECODE;
			}
			else{
				deviceState = STATE_WAIT;
			}
			break;
		case STATE_DECODE:
			messageDecodeSuccessful = decode_message(receiveBuffer, sizeof(receiveBuffer), &message_in);
			buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
			if(messageDecodeSuccessful){
				deviceState = STATE_TEST;
			}
			else{
				deviceState = STATE_WAIT;
			}
			break;
		case STATE_TEST:
			switch(message_in.commandType){

			case CommandTypeEnum_I2C_test:
//				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
//				message_out.commandType = CommandTypeEnum_I2C_test;
				break;

			case CommandTypeEnum_SPI_test:
//				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
//				message_out.commandType = CommandTypeEnum_SPI_test;
				break;

			case CommandTypeEnum_USART_test:
//				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
//				message_out.commandType = CommandTypeEnum_USART_test;
				break;

			case CommandTypeEnum_GPIO_digital:
				gpio_test(&message_in, &message_out);
				break;

			case CommandTypeEnum_Analog_read:
//				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
//				message_out.commandType = CommandTypeEnum_Analog_read;
				break;

			case CommandTypeEnum_Analog_write:
//				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
//				message_out.commandType = CommandTypeEnum_Analog_write;
				break;

			default:
				break;
			} /* switch(message_in.commandType) */
			encode_message(transmitBuffer,sizeof(transmitBuffer), &message_out, &bytesWritten);
			link_set_phy_write_fn(&linkLayer,&buffer_send);
			link_write(&linkLayer,transmitBuffer,bytesWritten);

			// reset buffers and messages
			buffer_init_zero(transmitBuffer, sizeof(transmitBuffer));
			command_reset(&message_out);
			// progress state machine
			deviceState = STATE_WAIT;
			break;
		}  /* switch(deviceState) */
	} /* while(1) */
}



/** @brief	GPIO digital test **/
void gpio_test(Command* message_in, Command* message_out)
{
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	uint32_t gpioReadState = 0;		//message: responseRead is stored in uint32_t

	// choose GPIO port and pin
	gpioPort = gpio_port_pin(message_in, &gpioPin);

	// Initialize GPIO if CubeMX config file is not available
	if(message_in->has_autoConfig == false){
		if(message_in->autoConfig == false){
			gpio_init(message_in, gpioPort, gpioPin);
		}
	}

	// Set response commandType
	message_out->commandType = CommandTypeEnum_GPIO_digital;

	// Read or write the pin depending on message
	if(message_in->gpio.direction == gpioDirection_GPIO_OUTPUT){
		if(message_in->gpio.state == gpioPinState_GPIO_HIGH){
			HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_SET);
			message_out->has_response = true;
			message_out->response.has_responseWrite = true;
			message_out->response.responseWrite = successfulWrite_GPIO_SET_HIGH;
		}
		else if(message_in->gpio.state == gpioPinState_GPIO_LOW){
			HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);
			message_out->has_response = true;
			message_out->response.has_responseWrite = true;
			message_out->response.responseWrite = successfulWrite_GPIO_SET_LOW;
		}
	}
	else if(message_in->gpio.direction == gpioDirection_GPIO_INPUT){
		gpioReadState = HAL_GPIO_ReadPin(gpioPort, gpioPin);
		message_out->has_response = true;
		message_out->response.has_responseRead = true;
		message_out->response.responseRead = gpioReadState;
	}
	else{
		//empty
	}

	// Deinitialize GPIO if CubeMX config file is not available
//	if(message_in->has_autoConfig == false){
//		if(message_in->autoConfig == false){
//			gpio_deinit(gpioPort, gpioPin);
//		}
//	}
}


/** @brief	GPIO digital init **/
void gpio_init(Command* message_in, GPIO_TypeDef* gpioPort, uint32_t gpioPin)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Define GPIO_InitStruct
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Configure GPIO pin number
	GPIO_InitStruct.Pin = gpioPin;

	// Configure GPIO pin direction
	if(message_in->gpio.direction == gpioDirection_GPIO_OUTPUT){
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	}
	else if(message_in->gpio.direction == gpioDirection_GPIO_INPUT){
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//		GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	}
	else{
		// empty
	}

	// Configure GPIO pin Pull
	if(message_in->gpio.pull == gpioPull_GPIO_NO_PULL){
		GPIO_InitStruct.Pull = GPIO_NOPULL;
	}
	else if(message_in->gpio.pull == gpioPull_GPIO_PULL_UP){
		GPIO_InitStruct.Mode = GPIO_PULLUP;
	}
	else if(message_in->gpio.pull == gpioPull_GPIO_PULL_DOWN){
		GPIO_InitStruct.Mode = GPIO_PULLDOWN;
	}
	else{
		// empty
	}

	// GPIO speed set to default low frequency
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	// Initialize GPIO
	HAL_GPIO_Init(gpioPort, &GPIO_InitStruct);
}


/** @brief	GPIO digital deinit **/
void gpio_deinit(GPIO_TypeDef* gpioPort, uint32_t gpioPin)
{
	HAL_GPIO_DeInit(gpioPort, gpioPin);

	/* GPIO Ports Clock Disable */
	__HAL_RCC_GPIOC_CLK_DISABLE();
	__HAL_RCC_GPIOH_CLK_DISABLE();
	__HAL_RCC_GPIOA_CLK_DISABLE();
	__HAL_RCC_GPIOB_CLK_DISABLE();

}


/** @brief			Choose port & pin according to message
 * 	@param[in]		message_in: message received
 * 	@param[in/out]	gpioPin: pin [0-15]
 * 	@return			pointer to GPIO port [GPIOA, GPIOB...]	**/
GPIO_TypeDef* gpio_port_pin(Command* message_in, uint16_t* gpioPin)
{
	GPIO_TypeDef* gpioPort;

	switch(message_in->gpio.pin){

	case gpioPins_PA0:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_0;
		break;
	case gpioPins_PA1:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PA2:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_2;
		break;
	case gpioPins_PA3:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_3;
		break;
	case gpioPins_PA4:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_4;
		break;
	case gpioPins_PA5:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_5;
		break;
	case gpioPins_PA6:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_6;
		break;
	case gpioPins_PA7:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_7;
		break;
	case gpioPins_PA8:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_8;
		break;
	case gpioPins_PA9:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_9;
		break;
	case gpioPins_PA10:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_10;
		break;
	case gpioPins_PA11:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_11;
		break;
	case gpioPins_PA12:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_12;
		break;
	case gpioPins_PA13:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_13;
		break;
	case gpioPins_PA14:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_14;
		break;
	case gpioPins_PA15:
		gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_15;
		break;


	case gpioPins_PB0:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_0;
		break;
	case gpioPins_PB1:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PB2:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_2;
		break;
	case gpioPins_PB3:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_3;
		break;
	case gpioPins_PB4:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_4;
		break;
	case gpioPins_PB5:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_5;
		break;
	case gpioPins_PB6:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_6;
		break;
	case gpioPins_PB7:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_7;
		break;
	case gpioPins_PB8:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_8;
		break;
	case gpioPins_PB9:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_9;
		break;
	case gpioPins_PB10:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_10;
		break;
	case gpioPins_PB11:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_11;
		break;
	case gpioPins_PB12:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_12;
		break;
	case gpioPins_PB13:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_13;
		break;
	case gpioPins_PB14:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_14;
		break;
	case gpioPins_PB15:
		gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_15;
		break;


	case gpioPins_PC0:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PC1:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PC2:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_2;
		break;
	case gpioPins_PC3:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_3;
		break;
	case gpioPins_PC4:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_4;
		break;
	case gpioPins_PC5:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_5;
		break;
	case gpioPins_PC6:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_6;
		break;
	case gpioPins_PC7:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_7;
		break;
	case gpioPins_PC8:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_8;
		break;
	case gpioPins_PC9:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_9;
		break;
	case gpioPins_PC10:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_10;
		break;
	case gpioPins_PC11:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_11;
		break;
	case gpioPins_PC12:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_12;
		break;
	case gpioPins_PC13:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_13;
		break;
	case gpioPins_PC14:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_14;
		break;
	case gpioPins_PC15:
		gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_15;
		break;

	default:
		break;
	}

	return gpioPort;
}
