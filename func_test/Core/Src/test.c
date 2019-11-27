/*
 * test.c
 *
 *  Created on: 2019. okt. 19.
 *      Author: Adam Golya
 */

#include "pb_encode.h"
#include "pb_decode.h"
#include "test.h"
#include "usart.h"



uint8_t buffer_string[128];
uint8_t rx_buffer[2];



/** @brief 	Encode message
 * @param[out]	pBuffer: pointer to encoded buffer
 * @param[in]	message_out: pointer to message to encode
 * @return	status: true, if encoding was successful
 */
bool encode_message(uint8_t* pBuffer,Command* message_out)
{
	bool status;
//	size_t message_length;
//	Command message_out_2 = Command_init_zero; // init_zero must be executed at declaration
	pb_ostream_t stream_out = pb_ostream_from_buffer(pBuffer,sizeof(pBuffer));
	status = pb_encode(&stream_out,Command_fields,message_out);
//	message_length = stream_out.bytes_written;
	return status;
}


/** @brief 	Decode message
 * @param[in]	pBuffer: pointer to buffer to decode
 * @param[out]	message_in: decoded message
 * @return	status: true, if encoding was successful
 */
bool decode_message(uint8_t* pBuffer, Command* message_in)
{
	bool status;
//	size_t message_length;
//	Command message_in = Command_init_zero; // init_zero must be executed at declaration
	pb_istream_t stream_in = pb_istream_from_buffer(pBuffer, sizeof(pBuffer));
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


void buffer_send(uint8_t* pBuffer, uint8_t pSize)
{
	HAL_UART_Transmit_DMA(&huart2,pBuffer, pSize);
}
