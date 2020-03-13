/**
 * @file 	wrapper_usart.c
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for USART testing 			**/

/* Includes ------------------------------------------------------------------*/
#include <wrapper_main.h>
#include "link_layer.h"
#include "simple_message.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "peripheral_config.h"
#include "wrapper_usart.h"

bool decode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_in);
bool encode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_out, uint8_t* bytesWritten);

uint8_t rxBufferUART[50];
uint8_t rxBufferUARTLen;
uint8_t rxByteUART;
uint8_t txBufferUART[50];
link_layer_t linkLayerInner;
static bool invalidPeripheral = false;


/**********************			USART test				******************************/
/** @brief	USART test
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to transmit message	**/
void usart_test(Command* message_in, Command* message_out)
{
	UART_HandleTypeDef huart;
	USART_HandleTypeDef husart;
	HAL_StatusTypeDef status;
	bool success;

	// Initialize UART/USART
	if(message_in->usart.mode == usartMode_USART_MODE_ASYNCHRONOUS){
		success = uart_init(message_in,&huart);
		if(success == false){
			usart_error_handler(message_in, message_out);
			return;
		}
	}
	else{
		success = usart_init(message_in,&husart);
		if(success == false){
			usart_error_handler(message_in, message_out);
			return;
		}
	}

	// Perform test and set response
	message_out->commandType = CommandTypeEnum_USART_test;

	// USART/UART TX
	if(message_in->usart.direction == usartDirection_USART_TX){
		SimpleMessage simplMsgOut = SimpleMessage_init_zero;
		uint8_t txBytesWritten = 0;

		buffer_init_zero(txBufferUART, sizeof(txBufferUART));
		message_out->has_response = true;
		message_out->response.has_responseEnum = true;

		// Encode message - set reseponse to fail if not successful
		simplMsgOut.msg = message_in->usart.command;
		bool success = encode_simplemessage(txBufferUART,sizeof(txBufferUART), &simplMsgOut, &txBytesWritten);
		if(success == false){
			message_out->response.responseEnum = responseEnum_t_USART_TX_FAIL;
			return;
		}

		// Frame data
		link_write(&linkLayerInner,txBufferUART,txBytesWritten);

		// Send data
		if(message_in->usart.mode == usartMode_USART_MODE_ASYNCHRONOUS){
			status = HAL_UART_Transmit(&huart, linkLayerInner.tx_buffer,linkLayerInner.tx_buffer_size, TEST_TIMEOUT_DURATION);
		}
		else{
			status = HAL_USART_Transmit(&husart, linkLayerInner.tx_buffer,linkLayerInner.tx_buffer_size, TEST_TIMEOUT_DURATION);
		}

		// Frame and send data and set response
		if(status == HAL_OK){
			message_out->response.responseEnum = responseEnum_t_USART_TX_OK;
		}
		else{
			message_out->response.responseEnum = responseEnum_t_USART_TX_FAIL;
		}

	}

	// USART/UART RX
	else if(message_in->usart.direction == usartDirection_USART_RX){
		bool messageDecodeSuccessful = false;
		SimpleMessage simplMsgIn = SimpleMessage_init_zero;
		uint8_t invalidFrameCounter = 0;
		buffer_init_zero(rxBufferUART, sizeof(rxBufferUART));

		while(messageDecodeSuccessful != true){
			// Receive frame byte-by-byte
			if(message_in->usart.mode == usartMode_USART_MODE_ASYNCHRONOUS){
				status = HAL_UART_Receive(&huart,(uint8_t*)&rxByteUART, 1,TEST_TIMEOUT_DURATION);
			}
			else{
				status = HAL_USART_Receive(&husart,(uint8_t*)&rxByteUART, 1,TEST_TIMEOUT_DURATION);
			}

			// Get frame and decode message
			link_parse_byte(&linkLayerInner, rxByteUART);
			if(link_get_valid_frame(&linkLayerInner,rxBufferUART, &rxBufferUARTLen)){
				messageDecodeSuccessful = decode_simplemessage(rxBufferUART, sizeof(rxBufferUART), &simplMsgIn);
				buffer_init_zero(rxBufferUART, sizeof(rxBufferUART));
			}
			else{
				invalidFrameCounter++;
				if(invalidFrameCounter == INVALID_FRAME_CNTR_MAX){
					break;
				}
			}

			// If status NOT OK: send fail response
			if(status != HAL_OK){
				break;
			}

		}

		message_out->has_response = true;
		if(status == HAL_OK){
			message_out->response.has_responseRead = true;
			message_out->response.responseRead = simplMsgIn.msg;
		}
		else{
			message_out->response.has_responseEnum = true;
			message_out->response.responseEnum = responseEnum_t_USART_RX_FAIL;
		}
	}

	// USART/UART TX + RX
	else{
		bool messageDecodeSuccessful = false;
		SimpleMessage simplMsgIn = SimpleMessage_init_zero;
		SimpleMessage simplMsgOut = SimpleMessage_init_zero;
		uint8_t invalidFrameCounter = 0;
		uint8_t txBytesWritten = 0;

		buffer_init_zero(rxBufferUART, sizeof(rxBufferUART));
		buffer_init_zero(txBufferUART, sizeof(txBufferUART));


		// Encode message - set reseponse to fail if not successful
		simplMsgOut.msg = message_in->usart.command;
		bool success = encode_simplemessage(txBufferUART,sizeof(txBufferUART), &simplMsgOut, &txBytesWritten);
		if(success == false){
			message_out->has_response = true;
			message_out->response.has_responseEnum = true;
			message_out->response.responseEnum = responseEnum_t_USART_TX_RX_FAIL;
			return;
		}

		// Frame data
		link_write(&linkLayerInner,txBufferUART,txBytesWritten);

		// Send data
		if(message_in->usart.mode == usartMode_USART_MODE_ASYNCHRONOUS){
			status = HAL_UART_Transmit(&huart, linkLayerInner.tx_buffer,linkLayerInner.tx_buffer_size, TEST_TIMEOUT_DURATION);
		}
		else{
			status = HAL_USART_Transmit(&husart, linkLayerInner.tx_buffer,linkLayerInner.tx_buffer_size, TEST_TIMEOUT_DURATION);
		}

		message_out->has_response = true;
		if(status != HAL_OK){
			message_out->response.has_responseEnum = true;
			message_out->response.responseEnum = responseEnum_t_USART_TX_RX_FAIL;
		}


		// Read back response
		while(messageDecodeSuccessful != true){
			// Receive frame byte-by-byte
			if(message_in->usart.mode == usartMode_USART_MODE_ASYNCHRONOUS){
				status = HAL_UART_Receive(&huart,(uint8_t*)&rxByteUART, 1,TEST_TIMEOUT_DURATION);
			}
			else{
				status = HAL_USART_Receive(&husart,(uint8_t*)&rxByteUART, 1,TEST_TIMEOUT_DURATION);
			}

			// Get frame and decode message
			link_parse_byte(&linkLayerInner, rxByteUART);
			if(link_get_valid_frame(&linkLayerInner,rxBufferUART, &rxBufferUARTLen)){
				messageDecodeSuccessful = decode_simplemessage(rxBufferUART, sizeof(rxBufferUART), &simplMsgIn);
				buffer_init_zero(rxBufferUART, sizeof(rxBufferUART));
			}
			else{
				invalidFrameCounter++;
				if(invalidFrameCounter == INVALID_FRAME_CNTR_MAX){
					break;
				}
			}

			// If status NOT OK: send fail response
			if(status != HAL_OK){
				break;
			}

		}

		message_out->has_response = true;
		if(status == HAL_OK){
			message_out->response.has_responseRead = true;
			message_out->response.responseRead = simplMsgIn.msg;
		}
		else{
			message_out->response.has_responseEnum = true;
			message_out->response.responseEnum = responseEnum_t_USART_TX_RX_FAIL;
		}

	}


	// Deinit UART/USART
	if(message_in->usart.mode == usartMode_USART_MODE_ASYNCHRONOUS){
//		HAL_UART_MspDeInit(&huart);
		HAL_UART_DeInit(&huart);
	}
	else{
//		HAL_USART_MspDeInit(&husart);
		HAL_USART_DeInit(&husart);
	}

}

/** @brief 	Decode message
 * @param[in]	pBuffer: pointer to buffer to decode
 * @param[in]	pBufferLen: length of buffer (max length of stream)
 * @param[out]	message_in: decoded message
 * @return	status: true, if encoding was successful
 */
bool decode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_in)
{
	bool status;
	pb_istream_t stream_in = pb_istream_from_buffer(pBuffer, pBufferLen);
	status = pb_decode(&stream_in, SimpleMessage_fields,message_in);
	return status;
}


/** @brief 	Encode message
 * @param[out]	pBuffer: pointer to encoded buffer
 * @param[in]	pBufferLen: length of buffer (max length of stream)
 * @param[in]	message_out: pointer to message to encode
 * @return	status: true, if encoding was successful
 */
bool encode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_out, uint8_t* bytesWritten)
{
	bool status;
	pb_ostream_t stream_out = pb_ostream_from_buffer(pBuffer, pBufferLen);
	status = pb_encode(&stream_out,SimpleMessage_fields,message_out);
	*bytesWritten = (uint8_t)stream_out.bytes_written;
	return status;
}



/** @brief	USART init
 *  @param	message_in: pointer to received message
 *  @param	husart: pointer to USART handler	**/
bool usart_init(Command* message_in, USART_HandleTypeDef* husart)
{
	switch(message_in->usart.bus){
	case usartBus_USART1:
#ifdef HAS_USART1
		husart->Instance = USART1;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART2:
#ifdef HAS_USART2
		husart->Instance = USART2;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART3:
#ifdef HAS_USART3
		husart->Instance = USART3;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART4:
#ifdef HAS_USART4
		husart->Instance = USART4;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART5:
#ifdef HAS_USART5
		husart->Instance = USART5;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART6:
#ifdef HAS_USART6
		husart->Instance = USART6;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	default:
		return false;
		break;
	}

	husart->Init.BaudRate = message_in->usart.baudRate;


	switch(message_in->usart.wordLength){
	case usartWordLength_USART_8_BITS:
		husart->Init.WordLength = USART_WORDLENGTH_8B;
		break;
	case usartWordLength_USART_9_BITS:
		husart->Init.WordLength = USART_WORDLENGTH_9B;
		break;
	default:
		break;
	}

	switch(message_in->usart.stopBits){
	case usartStopBits_USART_STOP_BITS_1:
		husart->Init.StopBits = USART_STOPBITS_1;
		break;
	case usartStopBits_USART_STOP_BITS_2:
		husart->Init.StopBits = USART_STOPBITS_2;
	default:
		break;
	}

	switch(message_in->usart.parity){
	case usartParity_USART_PARITY_NONE:
		husart->Init.Parity = USART_PARITY_NONE;
		break;
	case usartParity_USART_PARITY_EVEN:
		husart->Init.Parity = USART_PARITY_EVEN;
		break;
	case usartParity_USART_PARITY_ODD:
		husart->Init.Parity = USART_PARITY_ODD;
		break;
	default:
		break;
	}


	switch(message_in->usart.direction){
	case usartDirection_USART_TX:
		husart->Init.Mode = USART_MODE_TX;
		break;
	case usartDirection_USART_RX:
		husart->Init.Mode = USART_MODE_RX;
		break;
	case usartDirection_USART_TX_AND_RX:
		husart->Init.Mode = USART_MODE_TX_RX;
		break;
	default:
		break;
	}

	switch(message_in->usart.clockPolarity){
	case usartClockPolarity_USART_CLOCK_POLARITY_LOW:
		husart->Init.CLKPolarity = USART_POLARITY_LOW;
		break;
	case usartClockPolarity_USART_CLOCK_POLARITY_HIGH:
		husart->Init.CLKPolarity = USART_POLARITY_HIGH;
		break;
	default:
		break;
	}

	switch(message_in->usart.clockPhase){
	case usartClockPhase_USART_CLOCK_PHASE_ONE_EDGE:
		husart->Init.CLKPhase = USART_PHASE_1EDGE;
		break;
	case usartClockPhase_USART_CLOCK_PHASE_TWO_EDGE:
		husart->Init.CLKPhase = USART_PHASE_2EDGE;
		break;
	default:
		break;
	}

	switch(message_in->usart.clockLastBit){
	case usartClockLastBit_USART_CLOCK_LAST_BIT_DISABLE:
		husart->Init.CLKLastBit = USART_LASTBIT_DISABLE;
		break;
	case usartClockLastBit_USART_CLOCK_LAST_BIT_ENABLE:
		husart->Init.CLKLastBit = USART_LASTBIT_ENABLE;
		break;
	default:
		break;
	}


	HAL_USART_MspInit(husart);
	if (HAL_USART_Init(husart) != HAL_OK){
		return false;
	}

	return true;
}


/** @brief	UART init
 *  @param	message_in: pointer to received message
 *  @param	huart: pointer to UART handler	**/
bool uart_init(Command* message_in, UART_HandleTypeDef* huart)
{
	switch(message_in->usart.bus){
	case usartBus_USART1:
#ifdef HAS_USART1
		huart->Instance = USART1;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART2:
#ifdef HAS_USART2
		huart->Instance = USART2;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART3:
#ifdef HAS_USART3
		huart->Instance = USART3;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART4:
#ifdef HAS_USART4
		huart->Instance = USART4;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART5:
#ifdef HAS_USART5
		huart->Instance = USART5;
#else
		invalidPeripheral = true;
		return false;
#endif
		break;
	case usartBus_USART6:
#ifdef HAS_USART6
		huart->Instance = USART6;
		break;
#else
		invalidPeripheral = true;
		return false;
#endif
	default:
		return false;
		break;
	}

	huart->Init.BaudRate = message_in->usart.baudRate;



	switch(message_in->usart.wordLength){
	case usartWordLength_USART_8_BITS:
		huart->Init.WordLength = UART_WORDLENGTH_8B;
		break;
	case usartWordLength_USART_9_BITS:
		huart->Init.WordLength = UART_WORDLENGTH_9B;
		break;
	default:
		break;
	}

	switch(message_in->usart.stopBits){
	case usartStopBits_USART_STOP_BITS_1:
		huart->Init.StopBits = UART_STOPBITS_1;
		break;
	case usartStopBits_USART_STOP_BITS_2:
		huart->Init.StopBits = UART_STOPBITS_2;
	default:
		break;
	}

	switch(message_in->usart.parity){
	case usartParity_USART_PARITY_NONE:
		huart->Init.Parity = UART_PARITY_NONE;
		break;
	case usartParity_USART_PARITY_EVEN:
		huart->Init.Parity = UART_PARITY_EVEN;
		break;
	case usartParity_USART_PARITY_ODD:
		huart->Init.Parity = UART_PARITY_ODD;
		break;
	default:
		break;
	}


	switch(message_in->usart.direction){
	case usartDirection_USART_TX:
		huart->Init.Mode = UART_MODE_TX;
		break;
	case usartDirection_USART_RX:
		huart->Init.Mode = UART_MODE_RX;
		break;
	case usartDirection_USART_TX_AND_RX:
		huart->Init.Mode = UART_MODE_TX_RX;
		break;
	default:
		break;
	}

	switch(message_in->usart.hwFlowControl){
	case usartHardwareFlowControl_USART_HW_FLOW_DISABLE:
		huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
		break;
	case usartHardwareFlowControl_USART_HW_FLOW_CTS_ONLY:
		huart->Init.HwFlowCtl = UART_HWCONTROL_CTS;
		break;
	case usartHardwareFlowControl_USART_HW_FLOW_RTS_ONLY:
		huart->Init.HwFlowCtl = UART_HWCONTROL_RTS;
		break;
	case usartHardwareFlowControl_USART_HW_FLOW_CTS_AND_RTS:
		huart->Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
		break;
	}

	huart->Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_MspInit(huart);
	if (HAL_UART_Init(huart) != HAL_OK){
		return false;
	}

	return true;
}


/** @brief	USART/UART error handler - set response
 *  @param	message_in: pointer to received message
 *  @param  message_out: pointer to output message **/
void usart_error_handler(Command* message_in, Command* message_out)
{
	message_out->commandType = CommandTypeEnum_USART_test;
	message_out->has_response = true;
	message_out->response.has_responseEnum = true;
	if(invalidPeripheral == true){
		invalidPeripheral = false;
		message_out->response.responseEnum = responseEnum_t_INVALID_PERIPHERAL;
		return;
	}

	switch(message_in->usart.direction){
	case usartDirection_USART_RX:
		message_out->response.responseEnum = responseEnum_t_USART_RX_FAIL;
		break;
	case usartDirection_USART_TX:
		message_out->response.responseEnum = responseEnum_t_USART_TX_FAIL;
		break;
	case usartDirection_USART_TX_AND_RX:
		message_out->response.responseEnum = responseEnum_t_USART_TX_RX_FAIL;
		break;
	}

}
