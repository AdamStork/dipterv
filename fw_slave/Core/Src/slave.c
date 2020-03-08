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

TestType testType;
uint32_t expectedWord = 0xDEADBEEF;
uint32_t expectedHalfWord = 0xAABB;
uint32_t expectedByte = 0xA5;
uint32_t responseWord = 0xB00B1122;

#define USART_UART_RX_SIZE	4
#define USART_UART_TX_SIZE 	10
#define I2C_RECEIVE_SIZE	2
#define I2C_TRANSMIT_SIZE	4
#define SPI_RECEIVE_SIZE	2
#define SPI_TRANSMIT_SIZE	2

uint8_t rxBuffer[50];
uint8_t txBuffer[50];
uint8_t rxBufferLen;
link_layer_t linkLayer;
uint8_t receiveByte;



bool encode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_out, uint8_t* bytesWritten);
bool decode_simplemessage(uint8_t* pBuffer, uint8_t pBufferLen, SimpleMessage* message_in);

void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);




/** @brief	Enter slave test mode. Tests can be executed by giving TestType	**/
void enter_slave_test_mode(void)
{
//	testType = TEST_I2C_SLAVE_READ;
//	testType = TEST_I2C_SLAVE_READ_AND_WRITE;
//	testType = TEST_SPI_SLAVE_FULL_DUPLEX;
	testType = TEST_SPI_SLAVE_HALF_DUPLEX;
//	testType = TEST_SPI_SLAVE_RECEIVE_ONLY;
//	testType = TEST_USART_SLAVE_RX_ONLY;
//	testType = TEST_USART_SLAVE_TX_ONLY;
//	testType = TEST_USART_SLAVE_RX_AND_TX;
//	testType = TEST_UART_SLAVE_RX_ONLY;
//	testType = TEST_UART_SLAVE_TX_ONLY;
//	testType = TEST_UART_SLAVE_RX_AND_TX;

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
/** @brief	I2C write simulation for configuring a register
 * @details	Master sends 2 bytes to slave: register and config (write) value.  Correct configuration is signaled with LED toggle.
 * 		>> expected Byte: 0xA5		**/
void test_i2c_slave_read(void)
{
	uint8_t rxSize = 2;	// receiving 2 bytes
	HAL_StatusTypeDef status;

	status = HAL_I2C_Slave_Receive(&hi2c1, rxBuffer, rxSize,HAL_MAX_DELAY);
	/* rxBuffer[0]: Register
	 * rxBuffer[1]: Write value
	 */

	if(status == HAL_OK){
		if(rxBuffer[1] == expectedByte){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		}
	}
}


/** @brief 		I2C Read simulation
 *	@details	Master sends 1 byte to slave to initiate read simulation. Master then receives back 2 bytes if the expected register was sent.
 *			>>>	expected Register: 0xA5			**/
void test_i2c_slave_read_and_write(void)
{
	uint8_t txSize = 2;
	uint8_t rxSize = 1;		// receiving 2 bytes
	HAL_StatusTypeDef status;

	status = HAL_BUSY;
	while(status != HAL_OK){
		status = HAL_I2C_Slave_Receive(&hi2c1, rxBuffer, rxSize, HAL_MAX_DELAY);
	}

	/* rxBuffer[0]: Register */


	if(rxBuffer[0] == expectedByte){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		txBuffer[0] = 0x11;
		txBuffer[1] = 0x22;
		status = HAL_BUSY;
		while(status != HAL_OK){
			status = HAL_I2C_Slave_Transmit(&hi2c1,txBuffer, txSize, HAL_MAX_DELAY);
		}
	}


}



/**********************			SPI test				******************************/
/** @brief SPI Full duplex test. Slave receives 4 bytes from Master: command (1), dummyclock (1), value (2). Then sends back 2 byte response: 0x1122
 * 	>>>	expected Command: 0xA5
 * 	>>> expected writeValue: 0xAABB		**/
void test_spi_slave_full_duplex(void)
{
	uint8_t totalsize = 6;

	HAL_StatusTypeDef status;
	buffer_init_zero(rxBuffer, sizeof(rxBuffer));
	buffer_init_zero(txBuffer, sizeof(txBuffer));

	MX_SPI2_Init();
	HAL_SPI_MspInit(&hspi2);

	txBuffer[0] = 0x00;
	txBuffer[1] = 0x00;
	txBuffer[2] = 0x00;
	txBuffer[3] = 0x00;
	txBuffer[4] = 0x11;
	txBuffer[5] = 0x22;

	status = HAL_SPI_TransmitReceive(&hspi2,txBuffer,rxBuffer, totalsize, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);

	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	HAL_SPI_DeInit(&hspi2);
}

/** @brief SPI Half duplex test. Slave receives 5 bytes from Master: command (1), dummyclock (1), value (2). Then sends back 2 byte response
 * 	>>>	expected Command: 0xA5
 * 	>>> expexted writeValue: 0xAABB		**/
void test_spi_slave_half_duplex(void)
{
	uint8_t rxSize = 4;
	uint8_t txSize = 2;
	buffer_init_zero(rxBuffer, sizeof(rxBuffer));
	buffer_init_zero(txBuffer, sizeof(txBuffer));
	uint16_t writeValue = 0;

	MX_SPI2_Init();
	HAL_SPI_MspInit(&hspi2);

//	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, HAL_MAX_DELAY);
//	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);



//	HAL_SPI_DeInit(&hspi2);
////	HAL_Delay(30);
//
//
	txBuffer[0] = 0x11;
	txBuffer[1] = 0x22;
//	txBuffer[2] = 0x33;
//	txBuffer[3] = 0x44;
//	txBuffer[4] = 0x55;
//	txBuffer[5] = 0x66;
//
//	MX_SPI2_Init();
//	HAL_SPI_MspInit(&hspi2);
	HAL_SPI_Transmit(&hspi2,txBuffer, txSize, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
//	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	HAL_SPI_DeInit(&hspi2);
}


/** @brief SPI Receive test. Slave receives 5 bytes from Master: command (1), dummyclock (1), value (2).
 * 	>>>	expected Command: 0xA5
 * 	>>> expected writeValue: 0xAABB		**/
void test_spi_slave_receive_only(void)
{
	uint8_t rxSize = 4;
	uint16_t writeValue = 0;
//	uint8_t rxByte;

	MX_SPI2_Init();
	HAL_SPI_MspInit(&hspi2);

	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);

	__HAL_SPI_DISABLE(&hspi2);

	writeValue |= rxBuffer[3];
	writeValue |= (rxBuffer[2] << 8);
	if((rxBuffer[0] == expectedByte) && (writeValue == expectedHalfWord)){
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}


	HAL_SPI_MspDeInit(&hspi2);
}



/**********************			USART test				******************************/
/** @brief Receive message **/
void test_usart_slave_rx_only(void)
{
	MX_USART6_Init();

	bool messageDecodeSuccessful = false;
	SimpleMessage simplMsgIn = SimpleMessage_init_zero;
	uint8_t invalidFrameCounter = 0;
	buffer_init_zero(rxBuffer, sizeof(rxBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_USART_Receive(&husart6,&receiveByte, 1,HAL_MAX_DELAY);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,rxBuffer, &rxBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(rxBuffer, sizeof(rxBuffer), &simplMsgIn);
			buffer_init_zero(rxBuffer, sizeof(rxBuffer));
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

	buffer_init_zero(txBuffer, sizeof(txBuffer));
	message_out.msg = responseWord;

	encode_simplemessage(txBuffer,sizeof(txBuffer), &message_out, &bytesWritten);
	link_write(&linkLayer,txBuffer,bytesWritten);
	HAL_USART_Transmit(&husart6,linkLayer.tx_buffer, linkLayer.tx_buffer_size, TEST_TIMEOUT_DURATION);
}


/** @brief Receive and send message **/
void test_usart_slave_rx_and_tx(void)
{
	bool messageDecodeSuccessful = false;
	SimpleMessage simplMsgIn = SimpleMessage_init_zero;
	uint8_t invalidFrameCounter = 0;
	buffer_init_zero(rxBuffer, sizeof(rxBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_USART_Receive(&husart6,(uint8_t*)&receiveByte, 1,TEST_TIMEOUT_DURATION);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,rxBuffer, &rxBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(rxBuffer, sizeof(rxBuffer), &simplMsgIn);
			buffer_init_zero(rxBuffer, sizeof(rxBuffer));
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

			buffer_init_zero(txBuffer, sizeof(txBuffer));
			message_out.msg = responseWord;

			encode_simplemessage(txBuffer,sizeof(txBuffer), &message_out, &bytesWritten);
			link_write(&linkLayer,txBuffer,bytesWritten);
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
	buffer_init_zero(rxBuffer, sizeof(rxBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_UART_Receive(&huart1,(uint8_t*)&receiveByte, 1,HAL_MAX_DELAY);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,rxBuffer, &rxBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(rxBuffer, sizeof(rxBuffer), &simplMsgIn);
			buffer_init_zero(rxBuffer, sizeof(rxBuffer));
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

	buffer_init_zero(txBuffer, sizeof(txBuffer));
	message_out.msg = responseWord;

	encode_simplemessage(txBuffer,sizeof(txBuffer), &message_out, &bytesWritten);
	link_write(&linkLayer,txBuffer,bytesWritten);
	HAL_UART_Transmit(&huart1,linkLayer.tx_buffer, linkLayer.tx_buffer_size, TEST_TIMEOUT_DURATION);
}


/** @brief Receive and send message **/
void test_uart_slave_rx_and_tx(void)
{
	bool messageDecodeSuccessful = false;
	SimpleMessage simplMsgIn = SimpleMessage_init_zero;
	uint8_t invalidFrameCounter = 0;
	buffer_init_zero(rxBuffer, sizeof(rxBuffer));
	HAL_StatusTypeDef status;

	while(messageDecodeSuccessful != true){
		// Receive frame byte-by-byte
		status = HAL_UART_Receive(&huart1,(uint8_t*)&receiveByte, 1,TEST_TIMEOUT_DURATION);

		// Get frame and decode message
		link_parse_byte(&linkLayer, receiveByte);
		if(link_get_valid_frame(&linkLayer,rxBuffer, &rxBufferLen)){
			messageDecodeSuccessful = decode_simplemessage(rxBuffer, sizeof(rxBuffer), &simplMsgIn);
			buffer_init_zero(rxBuffer, sizeof(rxBuffer));
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

			buffer_init_zero(txBuffer, sizeof(txBuffer));
			message_out.msg = responseWord;

			encode_simplemessage(txBuffer,sizeof(txBuffer), &message_out, &bytesWritten);
			link_write(&linkLayer,txBuffer,bytesWritten);
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
