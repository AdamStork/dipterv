/**
 * @file 	wrapper_adc.c
 * @author 	Adam Golya
 * @date   	19 10 2019
 * @brief 	Wrapper for ADC testing 			**/


#include "peripheral_config.h"
#include "wrapper_adc.h"
#include "wrapper_gpio.h"


static bool invalidPeripheral = false;
ADC_HandleTypeDef adcHandle;


/**********************			Analog read 			******************************/
/** @brief	Analog read (ADC) test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void analog_read_test(Command* message_in, Command* message_out)
{
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;

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
		analog_read_deinit(&adcHandle, gpioPort, gpioPin);
		analog_read_error_handler(message_out);
    	return;
	}

	uint32_t adcValue = HAL_ADC_GetValue(&adcHandle);


	// Set response
	message_out->commandType = CommandTypeEnum_Analog_read;
	message_out->has_response = true;
	message_out->response.has_responseRead = true;
	switch(message_in->analog_in.resolution){
	case adcResolution_ADC_12_BITS:
		message_out->response.responseRead = 3300*adcValue/4096;
		break;
	case adcResolution_ADC_10_BITS:
		message_out->response.responseRead = 3300*adcValue/1024;
		break;
	case adcResolution_ADC_8_BITS:
		message_out->response.responseRead = 3300*adcValue/256;
		break;
	case adcResolution_ADC_6_BITS:
		message_out->response.responseRead = 3300*adcValue/64;
		break;
	}


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
	switch(message_in->analog_in.instance == adcInstance_ADC1){
	case adcInstance_ADC1:
#ifdef HAS_ADC1
		adcHandle->Instance = ADC1;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	default:
		return false;
		break;
	}


	// Configure ADC clock prescaler
	switch(message_in->analog_in.clockPrescaler){
	case adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_2:
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
		break;
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
		adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
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
 *  @param  message_out: pointer to output message **/
void analog_read_error_handler(Command* message_out)
{
	message_out->commandType = CommandTypeEnum_Analog_read;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;

	if(invalidPeripheral == true){
		invalidPeripheral = false;
		message_out->response.responseEnum = responseEnum_t_INVALID_PERIPHERAL;
	}
	else{
		message_out->response.responseEnum = responseEnum_t_ADC_READ_FAIL;
	}
}


/** @brief	ADC peripheral deinit
 *  @param	message_in: pointer to received message
 *  @param  gpioPort: pointer to GPIO port handler
 *  @param	gpioPin: GPIO pin number [0-15]				**/
void analog_read_deinit(ADC_HandleTypeDef* adcHandle,GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
#ifdef HAS_ADC1
	if(adcHandle->Instance == ADC1){
		__HAL_RCC_ADC1_CLK_DISABLE();
		HAL_GPIO_DeInit(gpioPort, gpioPin);
		HAL_ADC_DeInit(adcHandle);
	}
#endif
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
