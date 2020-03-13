/**
 * @file 	state_machine.c
 * @author 	Adam Golya
 * @date   	19 10 2019
 * @brief 	State machine 			**/

#include "pb_encode.h"
#include "pb_decode.h"
#include "test.h"
#include "link_layer.h"

#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "wrapper_adc.h"
#include "wrapper_pwm.h"
#include "tim.h"


bool frameReady = false;
uint8_t receiveByte;
//uint8_t transmitByte;
uint8_t receiveBuffer[50];
uint8_t transmitBuffer[50];
uint8_t receiveBufferLen;
link_layer_t linkLayer;
StateType deviceState;





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
				i2c_test(&message_in, &message_out);
				break;

			case CommandTypeEnum_SPI_test:
				spi_test(&message_in, &message_out);
				break;

			case CommandTypeEnum_USART_test:
				usart_test(&message_in, &message_out);
				break;

			case CommandTypeEnum_GPIO_digital:
				gpio_test(&message_in, &message_out);
				break;

			case CommandTypeEnum_Analog_read:
				analog_read_test(&message_in, &message_out);
				break;

			case CommandTypeEnum_Analog_write:
				pwm_test(&message_in, &message_out);
				break;

			default:
				break;
			} /* switch(message_in.commandType) */
			encode_message(transmitBuffer,sizeof(transmitBuffer), &message_out, &bytesWritten);
			link_write(&linkLayer,transmitBuffer,bytesWritten);
			HAL_UART_Transmit(&huart2, linkLayer.tx_buffer,linkLayer.tx_buffer_size, HAL_MAX_DELAY);

			// reset buffers and messages
			buffer_init_zero(transmitBuffer, sizeof(transmitBuffer));
			command_reset(&message_out);
			// progress state machine
			deviceState = STATE_WAIT;
			break;
		}  /* switch(deviceState) */
	} /* while(1) */
}



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
	message->spi.operatingMode = _spiOperatingMode_MIN;
	message->spi.command = 0;
	message->spi.dummyClocks = 0;
	message->spi.writeValue = 0;
	message->spi.writeSize = 0;
	message->spi.slaveResponse = 0;
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
	message->response.has_responseEnum = false;
	message->response.responseRead = 0;
	message->response.responseEnum = _responseEnum_t_MIN;

	// Reset autoConfig
	message->has_autoConfig = false;
	message->autoConfig = false;


}
