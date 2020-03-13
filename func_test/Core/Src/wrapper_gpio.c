/**
 * @file 	wrapper_pwm.h
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for PWM testing 			**/

/* Includes ------------------------------------------------------------------*/
#include "wrapper_gpio.h"



/**********************			GPIO digital 			******************************/
/** @brief	GPIO peripheral test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void gpio_test(Command* message_in, Command* message_out)
{
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	uint32_t gpioReadState = 0;		//message: responseRead is stored in uint32_t
	bool success;

	// choose GPIO port and pin
	success = gpio_port_pin(message_in->gpio.pin, &gpioPin, &gpioPort);
	if(success == false){
		gpio_error(message_in, message_out);
		return;
	}


	// Initialize GPIO
	gpio_init(message_in, gpioPort, gpioPin);

	// Set response commandType
	message_out->commandType = CommandTypeEnum_GPIO_digital;

	// Read or write the pin depending on message
	if(message_in->gpio.direction == gpioDirection_GPIO_OUTPUT){
		if(message_in->gpio.state == gpioPinState_GPIO_HIGH){
			HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_SET);
			message_out->has_response = true;
			message_out->response.has_responseEnum = true;
			message_out->response.responseEnum = responseEnum_t_GPIO_SET_HIGH;
		}
		else if(message_in->gpio.state == gpioPinState_GPIO_LOW){
			HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);
			message_out->has_response = true;
			message_out->response.has_responseEnum = true;
			message_out->response.responseEnum = responseEnum_t_GPIO_SET_LOW;
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

	// Deinitialize GPIO in case of GPIO read
	if(message_in->gpio.direction == gpioDirection_GPIO_INPUT){
		gpio_deinit(gpioPort, gpioPin);
	}
}


/** @brief	GPIO error handler - set response
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to output message **/
void gpio_error(Command* message_in, Command* message_out)
{
	message_out->commandType = CommandTypeEnum_GPIO_digital;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;
	if(message_in->gpio.direction == gpioDirection_GPIO_OUTPUT){
		message_out->response.responseEnum = responseEnum_t_GPIO_SET_FAIL;
	}
	else{
		message_out->response.responseEnum = responseEnum_t_GPIO_READ_FAIL;
	}
}


/** @brief	GPIO peripheral init
 *  @param	message_in: pointer to received message
 *  @param  gpioPort: pointer to GPIO port handler
 *  @param	gpioPin: GPIO pin number [0-15]
 *  @return	true, if init is successful	**/
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
	switch(message_in->gpio.direction){
	case gpioDirection_GPIO_OUTPUT:
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		break;
	case gpioDirection_GPIO_INPUT:
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		break;
	default:
		break;
	}


	// Configure GPIO pin Pull
	switch(message_in->gpio.pull){
	case gpioPull_GPIO_NO_PULL:
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		break;
	case gpioPull_GPIO_PULL_UP:
		GPIO_InitStruct.Mode = GPIO_PULLUP;
		break;
	case gpioPull_GPIO_PULL_DOWN:
		GPIO_InitStruct.Mode = GPIO_PULLDOWN;
		break;
	default:
		break;
	}


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
 * 	@param[in/out]	gpioPort: pointer to GPIO port [GPIOA, GPIOB...]
 * 	@return			true, if pinEnum is valid	**/
bool gpio_port_pin(gpioPins pinEnum, uint16_t* gpioPin, GPIO_TypeDef** gpioPort)
{
	switch(pinEnum){

	case gpioPins_PA0:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_0;
		break;
	case gpioPins_PA1:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PA2:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_2;
		break;
	case gpioPins_PA3:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_3;
		break;
	case gpioPins_PA4:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_4;
		break;
	case gpioPins_PA5:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_5;
		break;
	case gpioPins_PA6:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_6;
		break;
	case gpioPins_PA7:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_7;
		break;
	case gpioPins_PA8:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_8;
		break;
	case gpioPins_PA9:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_9;
		break;
	case gpioPins_PA10:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_10;
		break;
	case gpioPins_PA11:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_11;
		break;
	case gpioPins_PA12:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_12;
		break;
	case gpioPins_PA13:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_13;
		break;
	case gpioPins_PA14:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_14;
		break;
	case gpioPins_PA15:
		*gpioPort = GPIOA;
		*gpioPin = GPIO_PIN_15;
		break;


	case gpioPins_PB0:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_0;
		break;
	case gpioPins_PB1:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PB2:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_2;
		break;
	case gpioPins_PB3:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_3;
		break;
	case gpioPins_PB4:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_4;
		break;
	case gpioPins_PB5:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_5;
		break;
	case gpioPins_PB6:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_6;
		break;
	case gpioPins_PB7:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_7;
		break;
	case gpioPins_PB8:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_8;
		break;
	case gpioPins_PB9:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_9;
		break;
	case gpioPins_PB10:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_10;
		break;
	case gpioPins_PB11:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_11;
		break;
	case gpioPins_PB12:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_12;
		break;
	case gpioPins_PB13:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_13;
		break;
	case gpioPins_PB14:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_14;
		break;
	case gpioPins_PB15:
		*gpioPort = GPIOB;
		*gpioPin = GPIO_PIN_15;
		break;


	case gpioPins_PC0:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PC1:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_1;
		break;
	case gpioPins_PC2:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_2;
		break;
	case gpioPins_PC3:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_3;
		break;
	case gpioPins_PC4:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_4;
		break;
	case gpioPins_PC5:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_5;
		break;
	case gpioPins_PC6:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_6;
		break;
	case gpioPins_PC7:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_7;
		break;
	case gpioPins_PC8:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_8;
		break;
	case gpioPins_PC9:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_9;
		break;
	case gpioPins_PC10:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_10;
		break;
	case gpioPins_PC11:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_11;
		break;
	case gpioPins_PC12:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_12;
		break;
	case gpioPins_PC13:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_13;
		break;
	case gpioPins_PC14:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_14;
		break;
	case gpioPins_PC15:
		*gpioPort = GPIOC;
		*gpioPin = GPIO_PIN_15;
		break;

	default:
		return false;
		break;
	}

	return true;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
