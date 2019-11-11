/*
 * test.c
 *
 *  Created on: 2019. okt. 19.
 *      Author: Golyszi
 */


#include <string.h>
#include "pb_encode.h"
#include "pb_decode.h"
//#include "sensor.pb.h"
//#include "simple.pb.h"
#include "test.pb.h"
#include <stdbool.h>

extern char* buff;
uint8_t buffer[128];
uint8_t buffer_string[128];
uint8_t rx_buffer[2];
uint8_t status;
size_t message_length;

int luckNum;

char rx_startCh[2];
char rx_endCh[2];
char rx_data[40];

//void UART_encode(void)
//{
//	// create string message
//    UART_msg message_out = UART_msg_init_zero;
//    pb_ostream_t stream_out = pb_ostream_from_buffer(buffer_string, sizeof(buffer_string));
//    strcpy( message_out.cmd1, "Hello");
//    strcpy( message_out.cmd2, "\n\r");
//    status = pb_encode(&stream_out, UART_msg_fields, &message_out);
//
//    // Create advanced message
//    Command cmd_msg = Command_init_zero;
//    pb_ostream_t stream_cmd = pb_ostream_from_buffer(buffer, sizeof(buffer));
//    cmd_msg.commandType = CommandTypeEnum_GET_TEMPERATURE_DATA;
//    cmd_msg.has_commandValue = true;
//    cmd_msg.commandValue = 150;
//    status = pb_encode(&stream_cmd, Command_fields, &cmd_msg);
//
//
////    message_length = stream_out.bytes_written;
//}

// parameternek megkaphatna rx_buffert, return: status..
//void UART_decode(void)
//{
////	UART_msg message_in = UART_msg_init_zero;
//	SimpleMessage message_in = SimpleMessage_init_zero;
//	pb_istream_t stream_in = pb_istream_from_buffer(rx_buffer, sizeof(rx_buffer));
//	status = pb_decode(&stream_in, SimpleMessage_fields,&message_in);
//
//	strcpy(rx_startCh, message_in.startChar);
//	strcpy(rx_endCh, message_in.endChar);
//	strcpy(rx_data,message_in.data);
////	luckNum = message_in.luckyNumber;
//}

//void UART_decode(void)
//{
////	UART_msg message_in = UART_msg_init_zero;
//	SimpleMessage message_in = SimpleMessage_init_zero;
//	pb_istream_t stream_in = pb_istream_from_buffer(rx_buffer, sizeof(rx_buffer));
//	status = pb_decode(&stream_in, SimpleMessage_fields,&message_in);
//
//	luckNum = message_in.luckyNum;
//}

void UART_encode(void)
{
	// create string message
//    UART_msg message_out = UART_msg_init_zero;
//    pb_ostream_t stream_out = pb_ostream_from_buffer(buffer_string, sizeof(buffer_string));
//    strcpy( message_out.cmd, "Hello\n\r");
//    status = pb_encode(&stream_out, UART_msg_fields, &message_out);

//    message_length = stream_out.bytes_written;
}

void UART_decode(void)
{
	Command message_in = Command_init_zero;
	pb_istream_t stream_in = pb_istream_from_buffer(rx_buffer, sizeof(rx_buffer));
	status = pb_decode(&stream_in, Command_fields, &message_in);

	Command decodedMsg;
	decodedMsg.commandType = message_in.commandType;
}
