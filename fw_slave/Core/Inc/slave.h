/**
 * @file 	slave.h
 * @author 	Adam Golya
 * @date   	19 10 2019
 * @brief 	Slave FW for I2C, SPI, USART tests 			**/

#ifndef __slave_H
#define __slave_H

#include <stdint.h>

#define TEST_TIMEOUT_DURATION 3000
/**
 * Read only: turn on LED
 * Read & Write: send back value
 **/

typedef enum{
	TEST_I2C_SLAVE_READ,
	TEST_I2C_SLAVE_READ_AND_WRITE,
	TEST_SPI_SLAVE_FULL_DUPLEX,
	TEST_SPI_SLAVE_HALF_DUPLEX,
	TEST_SPI_SLAVE_RECEIVE_ONLY,
	TEST_USART_SLAVE_RX_ONLY,
	TEST_USART_SLAVE_TX_ONLY,
	TEST_USART_SLAVE_RX_AND_TX,
	TEST_UART_SLAVE_RX_ONLY,
	TEST_UART_SLAVE_TX_ONLY,
	TEST_UART_SLAVE_RX_AND_TX,
}TestType;


void enter_slave_test_mode(void);


void test_i2c_slave_read(void);
void test_i2c_slave_read_and_write(void);

void test_spi_slave_full_duplex(void);
void test_spi_slave_half_duplex(void);
void test_spi_slave_receive_only(void);

void test_usart_slave_rx_only(void);
void test_usart_slave_tx_only(void);
void test_usart_slave_rx_and_tx(void);

void test_uart_slave_rx_only(void);
void test_uart_slave_tx_only(void);
void test_uart_slave_rx_and_tx(void);


void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);

#endif /*__ slave_H */
