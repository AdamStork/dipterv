/**
 * @file 	slave.c
 * @author 	Adam Golya
 * @date   	19 10 2019
 * @brief 	Slave FW for I2C, SPI, USART tests 			**/

#include "slave.h"
#include "usart.h"
#include "spi.h"
#include "i2c.h"

TestType testType =  TEST_I2C_SLAVE_READ;
uint32_t expectedWord = 0xDEADBEEF;
uint32_t responseWord = 0x11AA22BB;

#define USART_UART_RX_SIZE	4
#define USART_UART_TX_SIZE 	4
#define I2C_RECEIVE_SIZE	2
#define I2C_TRANSMIT_SIZE	4
#define SPI_RECEIVE_SIZE	2
#define SPI_TRANSMIT_SIZE	2


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

		HAL_Delay(1000);
	}
}



/**********************			I2C test				******************************/
void test_i2c_slave_read(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = I2C_RECEIVE_SIZE;


	HAL_I2C_Slave_Receive(&hi2c1, rxBuffer, rxSize,TEST_TIMEOUT_DURATION);

	uint32_t resp = 0;
	// decode rxBuffer
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	if(resp == expectedWord){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}

}


void test_i2c_slave_read_and_write(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = I2C_RECEIVE_SIZE;
	uint8_t* txBuffer;
	uint8_t txSize = I2C_TRANSMIT_SIZE;

	HAL_I2C_Slave_Receive(&hi2c1, rxBuffer, rxSize,TEST_TIMEOUT_DURATION);

	// Read message
	uint32_t resp = 0;
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	// Send message
	if(resp == expectedWord){
		for(uint8_t i = 0; i<txSize; i++){
			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
		}

		HAL_I2C_Slave_Transmit(&hi2c1,txBuffer, txSize, TEST_TIMEOUT_DURATION);
	}
}



/**********************			SPI test				******************************/
void test_spi_slave_full_duplex(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = I2C_RECEIVE_SIZE;
	uint8_t* txBuffer;
	uint8_t txSize = I2C_TRANSMIT_SIZE;

	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);

	// Read message
	uint32_t resp = 0;
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	// Send message
	if(resp == expectedWord){
		for(uint8_t i = 0; i<txSize; i++){
			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
		}

		HAL_SPI_Transmit(&hspi2,txBuffer, txSize, TEST_TIMEOUT_DURATION);
	}
}


void test_spi_slave_half_duplex(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = I2C_RECEIVE_SIZE;
	uint8_t* txBuffer;
	uint8_t txSize = I2C_TRANSMIT_SIZE;

	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);

	// Read message
	uint32_t resp = 0;
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	// Send message
	if(resp == expectedWord){
		for(uint8_t i = 0; i<txSize; i++){
			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
		}

		HAL_SPI_Transmit(&hspi2,txBuffer, txSize, TEST_TIMEOUT_DURATION);
	}
}


void test_spi_slave_receive_only(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = I2C_RECEIVE_SIZE;

	HAL_SPI_Receive(&hspi2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);

	// Read message
	uint32_t resp = 0;
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	// Send message
	if(resp == expectedWord){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
}



/**********************			USART test				******************************/
/** @brief Receive message **/
void test_usart_slave_rx_only(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = USART_UART_RX_SIZE;
	HAL_USART_Receive(&husart1,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);

	uint32_t resp = 0;
	// decode rxBuffer
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	if(resp == expectedWord){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}

}

/** @brief Send message **/
void test_usart_slave_tx_only(void)
{
	uint8_t* txBuffer;
	uint8_t txSize = USART_UART_TX_SIZE;

	// Send message
	for(uint8_t i = 0; i<txSize; i++){
		txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
	}

	HAL_USART_Transmit(&husart1,txBuffer,txSize, TEST_TIMEOUT_DURATION);
}


/** @brief Receive and send message **/
void test_usart_slave_rx_and_tx(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = USART_UART_RX_SIZE;
	uint8_t* txBuffer;
	uint8_t txSize = USART_UART_TX_SIZE;

	HAL_USART_Receive(&husart1,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);

	// Read message
	uint32_t resp = 0;
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	// Send message
	if(resp == expectedWord){
		for(uint8_t i = 0; i<txSize; i++){
			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
		}

		HAL_USART_Transmit(&husart1,txBuffer,txSize, TEST_TIMEOUT_DURATION);
	}
}



/**********************			UART test				******************************/
/** @brief Receive message **/
void test_uart_slave_rx_only(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = 1;
	HAL_UART_Receive(&huart2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);

	uint32_t resp = 0;
	// decode rxBuffer
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	if(resp == expectedWord){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}

}


/** @brief Send message **/
void test_uart_slave_tx_only(void)
{
	uint8_t* txBuffer;
	uint8_t txSize = USART_UART_TX_SIZE;

	// Send message
	for(uint8_t i = 0; i<txSize; i++){
		txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
	}

	HAL_UART_Transmit(&huart2,txBuffer,txSize, TEST_TIMEOUT_DURATION);

}


/** @brief Receive and send message **/
void test_uart_slave_rx_and_tx(void)
{
	uint8_t* rxBuffer;
	uint8_t rxSize = USART_UART_RX_SIZE;
	uint8_t* txBuffer;
	uint8_t txSize = USART_UART_TX_SIZE;

	HAL_UART_Receive(&huart2,rxBuffer, rxSize, TEST_TIMEOUT_DURATION);

	// Read message
	uint32_t resp = 0;
	for(uint8_t i = 0; i<rxSize; i++){
		resp |= (rxBuffer[i] << (i*8)); // Byte: LSB first
	}

	// Send message
	if(resp == expectedWord){
		for(uint8_t i = 0; i<txSize; i++){
			txBuffer[i] = (uint8_t)(responseWord >> (i*8)); // Byte: LSB first
		}

		HAL_UART_Transmit(&huart2,txBuffer,txSize, TEST_TIMEOUT_DURATION);
	}
}


