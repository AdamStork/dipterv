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
	message->analog_in.channel = _adcChannel_MIN;
	message->analog_in.pin = _gpioPins_MAX;
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
	message->response.responseWrite = _responseWriteEnum_MIN;

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
				analog_read_test(&message_in, &message_out);
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




/**********************			Analog read 			******************************/
/** @brief	Analog read (ADC) test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void analog_read_test(Command* message_in, Command* message_out)
{
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	ADC_HandleTypeDef adcHandle;


	// choose GPIO port and pin
	if(message_in->analog_in.pin != gpioPins_P_INVALID){
		gpioPort = gpio_port_pin(message_in->analog_in.pin, &gpioPin);
	}

	// Initialize ADC & GPIO if CubeMX config file is not available
	analog_read_init(message_in, &adcHandle, gpioPort, gpioPin);

	// ADC test
	HAL_ADC_Start(&adcHandle);
	uint32_t adcValue = HAL_ADC_GetValue(&adcHandle);
	// Set response
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
void analog_read_init(Command* message_in, ADC_HandleTypeDef* adcHandle, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Pin configuration
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = gpioPin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(gpioPort, &GPIO_InitStruct);

	// Configure ADC instance
	if(message_in->analog_in.instance == adcInstance_ADC1){
		adcHandle->Instance = ADC1;
	    __HAL_RCC_ADC1_CLK_ENABLE();
	}
	else if(message_in->analog_in.instance == adcInstance_ADC2){
//		adcHandle->Instance = ADC2;
//	    __HAL_RCC_ADC2_CLK_ENABLE();
	}
	else if(message_in->analog_in.instance == adcInstance_ADC3){
//		adcHandle->Instance = ADC3;
//	    __HAL_RCC_ADC3_CLK_ENABLE();
	}

	// Configure ADC clock prescaler
	if(message_in->analog_in.clockPrescaler == adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_4){
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	}
	else if(message_in->analog_in.clockPrescaler == adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_6){
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
	}
	else if(message_in->analog_in.clockPrescaler == adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_8){
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
	}

	// Configure ADC resolution
	if(message_in->analog_in.resolution == adcResolution_ADC_12_BITS){
		adcHandle->Init.Resolution = ADC_RESOLUTION_12B;
	}
	else if(message_in->analog_in.resolution == adcResolution_ADC_10_BITS){
		adcHandle->Init.Resolution = ADC_RESOLUTION_10B;
	}
	else if(message_in->analog_in.resolution == adcResolution_ADC_8_BITS){
		adcHandle->Init.Resolution = ADC_RESOLUTION_8B;
	}
	else if(message_in->analog_in.resolution == adcResolution_ADC_6_BITS){
		adcHandle->Init.Resolution = ADC_RESOLUTION_6B;
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
		Error_Handler();
	}


	// Define ADC Channel handler
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. **/
	sConfig.Channel = analog_read_choose_channel(message_in);
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(adcHandle, &sConfig) != HAL_OK){
		Error_Handler();
	}
}


/** @brief	GPIO peripheral deinit
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
/**********************			GPIO digital 			******************************/
/** @brief	GPIO peripheral test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void gpio_test(Command* message_in, Command* message_out)
{
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	uint32_t gpioReadState = 0;		//message: responseRead is stored in uint32_t

	// choose GPIO port and pin
	gpioPort = gpio_port_pin(message_in->gpio.pin, &gpioPin);

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
			message_out->response.responseWrite = responseWriteEnum_GPIO_SET_HIGH;
		}
		else if(message_in->gpio.state == gpioPinState_GPIO_LOW){
			HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);
			message_out->has_response = true;
			message_out->response.has_responseWrite = true;
			message_out->response.responseWrite = responseWriteEnum_GPIO_SET_LOW;
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


/** @brief	GPIO peripheral init
 *  @param	message_in: pointer to received message
 *  @param  gpioPort: pointer to GPIO port handler
 *  @param	gpioPin: GPIO pin number [0-15]				**/
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



/** @brief	GPIO peripheral deinit
 *  @param	message_in: pointer to received message
 *  @param  gpioPort: pointer to GPIO port handler
 *  @param	gpioPin: GPIO pin number [0-15]				**/
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
GPIO_TypeDef* gpio_port_pin(gpioPins pinEnum, uint16_t* gpioPin)
{
	GPIO_TypeDef* gpioPort;

	switch(pinEnum){

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
