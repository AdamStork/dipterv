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


bool frameReady = false;
uint8_t receiveByte;
uint8_t transmitByte;
uint8_t receiveBuffer[90];
uint8_t transmitBuffer[128];
uint8_t receiveBufferLen;
link_layer_t linkLayer;
StateType deviceState;


/** @brief 	Encode message
 * @param[out]	pBuffer: pointer to encoded buffer
 * @param[in]	message_out: pointer to message to encode
 * @return	status: true, if encoding was successful
 */
bool encode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_out)
{
	bool status;
	pb_ostream_t stream_out = pb_ostream_from_buffer(pBuffer, pBufferLen);
	status = pb_encode(&stream_out,Command_fields,message_out);
	return status;
}


/** @brief 	Decode message
 * @param[in]	pBuffer: pointer to buffer to decode
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


/** @brief Receive command via UART, and perform chosen test **/
void enter_processing_state(void)
{
	Command message_in = Command_init_zero;
	Command message_out = Command_init_zero;
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
				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
				message_out.commandType = CommandTypeEnum_I2C_test;
				break;

			case CommandTypeEnum_SPI_test:
				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
				message_out.commandType = CommandTypeEnum_SPI_test;
				break;

			case CommandTypeEnum_USART_test:
				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
				message_out.commandType = CommandTypeEnum_USART_test;
				break;

			case CommandTypeEnum_GPIO_digital:
				gpio_test(&message_in);
				break;

			case CommandTypeEnum_Analog_read:
				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
				message_out.commandType = CommandTypeEnum_Analog_read;
				break;

			case CommandTypeEnum_Analog_write:
				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
				message_out.commandType = CommandTypeEnum_Analog_write;
				break;

			default:
				break;
			} /* switch(message_in.commandType) */
			encode_message(transmitBuffer,sizeof(transmitBuffer), &message_out);
			link_set_phy_write_fn(&linkLayer,&buffer_send);
			link_write(&linkLayer,transmitBuffer,strlen((char*)transmitBuffer));
			buffer_init_zero(transmitBuffer, sizeof(transmitBuffer));
			deviceState = STATE_WAIT;
			break;
		}  /* switch(deviceState) */
	} /* while(1) */
}



/** @brief	GPIO digital test **/
void gpio_test(Command* message_in)
{
	GPIO_TypeDef *gpioPort;
	uint32_t gpioPin;
	uint8_t gpioReadState = 0;

	// choose GPIO port and pin
	gpioPort = gpio_port_pin(message_in, &gpioPin);

	// Initialize GPIO if CubeMX config file is not available
	if(message_in->has_autoConfig == false){
		if(message_in->autoConfig == false){
			gpio_init(message_in, gpioPort, gpioPin);
		}
	}

	// Read or write the pin depending on message
	if(message_in->gpio.direction == gpioDirection_GPIO_OUTPUT){
		if(message_in->gpio.state == gpioPinState_GPIO_HIGH){
			HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_SET);
		}
		else if(message_in->gpio.state == gpioPinState_GPIO_LOW){
			HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);
		}
	}
	else if(message_in->gpio.direction == gpioDirection_GPIO_INPUT){
		gpioReadState = HAL_GPIO_ReadPin(gpioPort, gpioPin);
	}
	else{
		//empty
	}



//	message_out.commandType = CommandTypeEnum_GPIO_digital;

	// If direction == write: set output,
		// return: message_out response: pin set, pin reset (set Low), set Fail?
	//if read : read pin: result: L/H.

	// Transmit result


	// Deinitialize GPIO if CubeMX config file is not available
//	if(message_in->has_autoConfig == false){
//		if(message_in->autoConfig == false){
//			gpio_deinit(message_in);
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
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	// Initialize GPIO
	HAL_GPIO_Init(gpioPort, &GPIO_InitStruct);
}


/** @brief	GPIO digital deinit **/
void gpio_deinit(Command* message_in)
{
//	HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)


	/* GPIO Ports Clock Disable */
//	__HAL_RCC_GPIOC_CLK_DISABLE();
//	__HAL_RCC_GPIOH_CLK_DISABLE();
//	__HAL_RCC_GPIOA_CLK_DISABLE();
//	__HAL_RCC_GPIOB_CLK_DISABLE();

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
