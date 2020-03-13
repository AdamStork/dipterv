/**
 * @file 	state_machine.h
 * @author 	Adam Golya
 * @date   	13 03 2019
 * @brief 	Wrapper main file header	**/


#ifndef INC_WRAPPER_MAIN_H_
#define INC_WRAPPER_MAIN_H_
#include <stdbool.h>
#include "functional_test.pb.h"

/** UART handle for communication with PC **/
#define UART_HANDLE huart2


/** State enum for state machine **/
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

/** Call this function in main.c before reaching while(1) **/
void enter_processing_state(void);


#endif /* INC_WRAPPER_MAIN_H_ */
