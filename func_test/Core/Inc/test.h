/*
 * test.h
 *
 *  Created on: 2019. okt. 19.
 *      Author: Golyszi
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_
//#include <stdbool.h>
#include "functional_test.pb.h"

typedef enum{
	STATE_WAIT,
	STATE_PROCESS,
	STATE_DECODE,
	STATE_TEST
} StateType;

#define PWM_DUTY_MAX 100
#define TEST_TIMEOUT_DURATION	100

bool encode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_out, uint8_t* bytesWritten);
bool decode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_in);

void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);
void command_reset(Command* message);
void buffer_send(uint8_t* pBuffer, uint8_t pSize);

void enter_processing_state(void);

bool i2c_init(Command* message_in, I2C_HandleTypeDef* hi2c);
void i2c_test(Command* message_in, Command* message_out);
void i2c_error_handler(Command* message_in, Command* message_out);

bool spi_init(Command* message_in, SPI_HandleTypeDef* hspi);
void spi_test(Command* message_in, Command* message_out);
void spi_error_handler(Command* message_out);

bool uart_init(Command* message_in, UART_HandleTypeDef* huart);
bool usart_init(Command* message_in, USART_HandleTypeDef* husart);
void usart_test(Command* message_in, Command* message_out);
void usart_deinit(USART_TypeDef* husart);
void usart_error_handler(Command* message_in, Command* message_out);

void gpio_init(Command* message_in, GPIO_TypeDef* gpioPort, uint32_t gpioPin);
void gpio_test(Command* message_in, Command* message_out);
void gpio_deinit(GPIO_TypeDef* gpioPort, uint32_t gpioPin);
bool gpio_port_pin(gpioPins pinEnum, uint16_t* gpioPin, GPIO_TypeDef** gpioPort);
void gpio_error(Command* message_in, Command* message_out);

bool analog_read_init(Command* message_in, ADC_HandleTypeDef* adcHandle, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void analog_read_test(Command* message_in, Command* message_out);
void analog_read_deinit(ADC_HandleTypeDef* adcHandler, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
uint32_t analog_read_choose_channel(Command* message_in);
void analog_read_error_handler(Command* message_out);


bool pwm_init(Command* message_in);
void pwm_test(Command* message_in, Command* message_out);
void pwm_error_handler(Command* message_out);


#endif /* INC_TEST_H_ */
