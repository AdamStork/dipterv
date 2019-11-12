/*
 * test.c
 *
 *  Created on: 2019. okt. 19.
 *      Author: Adam Golya
 */

#include "pb_encode.h"
#include "pb_decode.h"
#include "test.h"



uint8_t buffer_string[128];
uint8_t rx_buffer[2];



/** @brief 	Encode message
 * @param	pBuffer: pointer to buffer
 * @return	status: true, if encoding was successful
 */
bool encode_message(uint8_t* pBuffer)
{
	bool status;
	size_t message_length;
	Command message_out = Command_init_zero;
	pb_ostream_t stream_out = pb_ostream_from_buffer(pBuffer,sizeof(pBuffer));
	// Fill message with data
	//todo
	//Encode message: result will be stored in pBuffer
	status = pb_encode(&stream_out,Command_fields,&message_out);
	message_length = stream_out.bytes_written;
	return status;
}

/** @brief 	Decode message
 * @param	pBuffer: pointer to buffer
 * @param	message_in: decoded message
 * @return	status: true, if encoding was successful
 */
bool decode_message(uint8_t* pBuffer, Command* message_in)
{
	bool status;
	size_t message_length;
//	Command message_in = Command_init_zero; // init_zero must be executed at declaration
	pb_istream_t stream_in = pb_istream_from_buffer(pBuffer, sizeof(pBuffer));
	//Copy message from strem
	// todo: cmd = message_in.commandType
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

