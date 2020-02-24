/**
 * @file 	state_machine.c
 * @author 	Adam Golya
 * @date   	19 10 2019
 * @brief 	State machine			**/


#ifndef INC_TEST_H_
#define INC_TEST_H_
#include <stdbool.h>
#include "functional_test.pb.h"

typedef enum{
	STATE_WAIT,
	STATE_PROCESS,
	STATE_DECODE,
	STATE_TEST
} StateType;




bool encode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_out, uint8_t* bytesWritten);
bool decode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_in);

void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);
void command_reset(Command* message);
void buffer_send(uint8_t* pBuffer, uint8_t pSize);

void enter_processing_state(void);


#endif /* INC_TEST_H_ */
