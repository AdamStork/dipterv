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
				HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
				message_out.commandType = CommandTypeEnum_GPIO_digital;
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

