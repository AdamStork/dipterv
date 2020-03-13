/**
 * @file 	wrapper_usart.h
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for USART testing 			**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __wrapper_usart_H
#define __wrapper_usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "functional_test.pb.h"



#define INVALID_FRAME_CNTR_MAX	20

bool uart_init(Command* message_in, UART_HandleTypeDef* huart);
bool usart_init(Command* message_in, USART_HandleTypeDef* husart);
void usart_test(Command* message_in, Command* message_out);
void usart_deinit(USART_TypeDef* husart);
void usart_error_handler(Command* message_in, Command* message_out);

#ifdef __cplusplus
}
#endif
#endif /*__ wrapper_usart_H */


