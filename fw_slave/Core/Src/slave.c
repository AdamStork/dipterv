/**
 * @file 	slave.c
 * @author 	Adam Golya
 * @date   	19 10 2019
 * @brief 	Slave FW for I2C, SPI, USART tests 			**/

#include "slave.h"
#include "usart.h"
#include "spi.h"
#include "i2c.h"

#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "simple_message.pb.h"
#include "link_layer.h"

TestType testType =  TEST_USART_SLAVE_RX_ONLY;
uint32_t expectedWord = 0xDEADBEEF;
uint32_t responseWord = 0xB00B1122;

#define USART_UART_RX_SIZE	4
#define USART_UART_TX_SIZE 	10
#define I2C_RECEIVE_SIZE	2
#define I2C_TRANSMIT_SIZE	4
#define SPI_RECEIVE_SIZE	2
#define SPI_TRANSMIT_SIZE	2

uint8_t receiveBuffer[50];
uint8_t transmitBuffer[50];
uint8_t receiveBufferLen;
link_layer_t linkLayer;
uint8_t receiveByte;



bool encode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_out, uint8_t* bytesWritten);
bool decode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_in);

void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);




/** @brief	Enter slave test mode. Tests can be executed by giving TestType	**/
void enter_slave_test_mode(void)
{
	while(1){
		switch(testType){
		case TEST_I2C_SLAVE_READ:
			test_i2c_slave_read();
			break;
		case TEST_I2C_SLAVE_READ_AND_WRITE:
			test_i2c_slave_read_and_write();
			break;
		case TEST_SPI_SLAVE_FULL_DUPLEX:
			test_spi_slave_full_duplex();
			break;
		case TEST_SPI_SLAVE_HALF_DUPLEX:
			test_spi_slave_half_duplex();
			break;
		case TEST_SPI_SLAVE_RECEIVE_ONLY:
			test_spi_slave_receive_only();
			break;
		case TEST_USART_SLAVE_RX_ONLY:
			test_usart_slave_rx_only();
			break;
		case TEST_USART_SLAVE_TX_ONLY:
			test_usart_slave_tx_only();
			break;
		case TEST_USART_SLAVE_RX_AND_TX:
			test_usart_slave_rx_and_tx();
			break;
		case TEST_UART_SLAVE_RX_ONLY:
			test_uart_slave_rx_only();
			break;
		case TEST_UART_SLAVE_TX_ONLY:
			test_uart_slave_tx_only();
			break;
		case TEST_UART_SLAVE_RX_AND_TX:
			test_uart_slave_rx_and_tx();
			break;
		}


	}
}



/**********************			I2C test				******************************/
void test_i2c_slave_read(void)
{
//	uint8_t* rxBuffer;
//	uint8_t rxSize = I2C_RECEIVE_SIZE;
//
//
//	HAL_I2C_Slave_Receive(&hi2c1, rxBuffer, rxSize,TEST_TIMEOUT_DURATION);
//
//	uint32_t resp = 0;
//	// decode rxBuffer
//	for(uint8_t i = 0; i<rxSize; i++){
//		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
//	}
//
//	if(resp == expectedWord){
//		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
//	}

}


void test_i2c_slave_read_and_write(void)
{
//	uint8_t* rxBuffer;
//	uint8_t rxSize = I2C_RECEIVE_SIZE;
//	uint8_t* txBuffer;
//	uint8_t txSize = I2C_TRANSMIT_SIZE;
//
//	HAL_I2C_Slave_Receive(&hi2c1, rxBuffer, rxSize,TEST_TIMEOUT_DURATION);
//
//	// Read message
//	uint32_t resp = 0;
//	for(uint8_t i = 0; i<rxSize; i++){
//		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
//	}
//
//	// Send message
//	if(resp == expectedWord){
//		for(uint8_t i = 0; i<txSize; i++){
//			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
//		}
//
//		HAL_I2C_Slave_Transmit(&hi2c1,txBuffer, txSize, TEST_TIMEOUT_DURATION);
//	}
}



/**********************			SPI test				******************************/
void test_spi_slave_full_duplex(void)
{
//	uint8_t* rxBuffer;
//	uint8_t rxSize = I2C_RECEIVE_SIZE;
//	uint8_t* txBuffer;
//	uint8_t txSize = I2C_TRANSMIT_SIZE;
//
//	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);
//
//	// Read message
//	uint32_t resp = 0;
//	for(uint8_t i = 0; i<rxSize; i++){
//		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
//	}
//
//	// Send message
//	if(resp == expectedWord){
//		for(uint8_t i = 0; i<txSize; i++){
//			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
//		}
//
//		HAL_SPI_Transmit(&hspi2,txBuffer, txSize, TEST_TIMEOUT_DURATION);
//	}
}


void test_spi_slave_half_duplex(void)
{
//	uint8_t* rxBuffer;
//	uint8_t rxSize = I2C_RECEIVE_SIZE;
//	uint8_t* txBuffer;
//	uint8_t txSize = I2C_TRANSMIT_SIZE;
//
//	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);
//
//	// Read message
//	uint32_t resp = 0;
//	for(uint8_t i = 0; i<rxSize; i++){
//		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
//	}
//
//	// Send message
//	if(resp == expectedWord){
//		for(uint8_t i = 0; i<txSize; i++){
//			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
//		}
//
//		HAL_SPI_Transmit(&hspi2,txBuffer, txSize, TEST_TIMEOUT_DURATION);
//	}
}


void test_spi_slave_receive_only(void)
{
//	uint8_t* rxBuffer;
//	uint8_t rxSize = I2C_RECEIVE_SIZE;
//
//	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);
//
//	// Read message
//	uint32_t resp = 0;
//	for(uint8_t i = 0; i<rxSize; i++){
//		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
//	}
//
//	// Send message
//	if(resp == expectedWord){
//		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
//	}
}



/**********************			USART test				******************************/
/** @brief Receive message **/
void test_usart_slave_rx_only(void)
{
	MX_USART6_Init();

	bool messageDecodeSuccessful = false;
	SimpleMessage simplMsgIn = SimpleMessage_init_zero;
	uint8_t invalidFrameCounter = 0;
	buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_USART_Receive(&husart6,&receiveByte, 1,HAL_MAX_DELAY);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,receiveBuffer, &receiveBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(receiveBuffer, sizeof(receiveBuffer), &simplMsgIn);
			buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
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

	if(messageDecodeSuccessful == true){
		if(simplMsgIn.msg == expectedWord){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		}
	}
}

/** @brief Send message **/
void test_usart_slave_tx_only(void)
{
	SimpleMessage message_out = SimpleMessage_init_zero;
	uint8_t bytesWritten = 0;

	buffer_init_zero(transmitBuffer, sizeof(transmitBuffer));
	message_out.msg = responseWord;

	encode_simplemessage(transmitBuffer,sizeof(transmitBuffer), &message_out, &bytesWritten);
	link_write(&linkLayer,transmitBuffer,bytesWritten);
	HAL_USART_Transmit(&husart6,linkLayer.tx_buffer, linkLayer.tx_buffer_size, TEST_TIMEOUT_DURATION);
}


/** @brief Receive and send message **/
void test_usart_slave_rx_and_tx(void)
{
	bool messageDecodeSuccessful = false;
	SimpleMessage simplMsgIn = SimpleMessage_init_zero;
	uint8_t invalidFrameCounter = 0;
	buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_USART_Receive(&husart6,(uint8_t*)&receiveByte, 1,TEST_TIMEOUT_DURATION);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,receiveBuffer, &receiveBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(receiveBuffer, sizeof(receiveBuffer), &simplMsgIn);
			buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
		}
		else{
			invalidFrameCounter++;
			if(invalidFrameCounter == INVALID_FRAME_CNTR_MAX){
				return;
			}
		}

		// If status NOT OK: send fail response
		if(status != HAL_OK){
			return;
		}
	}

	if(messageDecodeSuccessful == true){
		if(simplMsgIn.msg == expectedWord){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			SimpleMessage message_out = SimpleMessage_init_zero;
			uint8_t bytesWritten = 0;

			buffer_init_zero(transmitBuffer, sizeof(transmitBuffer));
			message_out.msg = responseWord;

			encode_simplemessage(transmitBuffer,sizeof(transmitBuffer), &message_out, &bytesWritten);
			link_write(&linkLayer,transmitBuffer,bytesWritten);
			HAL_USART_Transmit(&husart6,linkLayer.tx_buffer, linkLayer.tx_buffer_size, TEST_TIMEOUT_DURATION);
		}
	}
}



/**********************			UART test				******************************/
/** @brief Receive message **/
void test_uart_slave_rx_only(void)
{
	bool messageDecodeSuccessful = false;
	SimpleMessage simplMsgIn = SimpleMessage_init_zero;
	uint8_t invalidFrameCounter = 0;
	buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_UART_Receive(&huart1,(uint8_t*)&receiveByte, 1,HAL_MAX_DELAY);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,receiveBuffer, &receiveBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(receiveBuffer, sizeof(receiveBuffer), &simplMsgIn);
			buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
		}
		else{
			invalidFrameCounter++;
//			if(invalidFrameCounter == INVALID_FRAME_CNTR_MAX){
//				break;
//			}
		}

		// If status NOT OK: send fail response
		if(status != HAL_OK){
			break;
		}
	}

	if(messageDecodeSuccessful == true){
		if(simplMsgIn.msg == expectedWord){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		}
	}
}


/** @brief Send message continuously **/
void test_uart_slave_tx_only(void)
{
	SimpleMessage message_out = SimpleMessage_init_zero;
	uint8_t bytesWritten = 0;

	buffer_init_zero(transmitBuffer, sizeof(transmitBuffer));
	message_out.msg = responseWord;

	encode_simplemessage(transmitBuffer,sizeof(transmitBuffer), &message_out, &bytesWritten);
	link_write(&linkLayer,transmitBuffer,bytesWritten);
	HAL_UART_Transmit(&huart1,linkLayer.tx_buffer, linkLayer.tx_buffer_size, TEST_TIMEOUT_DURATION);
}


/** @brief Receive and send message **/
void test_uart_slave_rx_and_tx(void)
{
	bool messageDecodeSuccessful = false;
	SimpleMessage simplMsgIn = SimpleMessage_init_zero;
	uint8_t invalidFrameCounter = 0;
	buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_UART_Receive(&huart1,(uint8_t*)&receiveByte, 1,TEST_TIMEOUT_DURATION);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,receiveBuffer, &receiveBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(receiveBuffer, sizeof(receiveBuffer), &simplMsgIn);
			buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
		}
		else{
			invalidFrameCounter++;
			if(invalidFrameCounter == INVALID_FRAME_CNTR_MAX){
				return;
			}
		}

		// If status NOT OK: send fail response
		if(status != HAL_OK){
			return;
		}
	}

	if(messageDecodeSuccessful == true){
		if(simplMsgIn.msg == expectedWord){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			SimpleMessage message_out = SimpleMessage_init_zero;
			uint8_t bytesWritten = 0;

			buffer_init_zero(transmitBuffer, sizeof(transmitBuffer));
			message_out.msg = responseWord;

			encode_simplemessage(transmitBuffer,sizeof(transmitBuffer), &message_out, &bytesWritten);
			link_write(&linkLayer,transmitBuffer,bytesWritten);
			HAL_UART_Transmit(&huart1,linkLayer.tx_buffer, linkLayer.tx_buffer_size, TEST_TIMEOUT_DURATION);
		}
	}
}




/********************************************************************************************/

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
