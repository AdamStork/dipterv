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



bool encode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_out, uint8_t* bytesWritten);
bool decode_message(uint8_t* pBuffer, uint8_t pBufferLen, Command* message_in);

void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);
void command_reset(Command* message);
void buffer_send(uint8_t* pBuffer, uint8_t pSize);

void enter_processing_state(void);

void i2c_init(void);
void i2c_test(void);
void i2c_deinit(void);



void spi_init(void);
void spi_test(void);
void spi_deinit(void);

void gpio_init(Command* message_in, GPIO_TypeDef* gpioPort, uint32_t gpioPin);
void gpio_test(Command* message_in, Command* message_out);
void gpio_deinit(GPIO_TypeDef* gpioPort, uint32_t gpioPin);
GPIO_TypeDef* gpio_port_pin(gpioPins pinEnum, uint16_t* gpioPin);


void analog_read_init(Command* message_in, ADC_HandleTypeDef* adcHandle, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void analog_read_test(Command* message_in, Command* message_out);
void analog_read_deinit(ADC_HandleTypeDef* adcHandler, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
uint32_t analog_read_choose_channel(Command* message_in);


void pwm_init(Command* message_in, GPIO_TypeDef* gpioPort, uint32_t gpioPin);
void pwm_test(Command* message_in, Command* message_out);
void pwm_deinit(GPIO_TypeDef* gpioPort, uint32_t gpioPin);
void timer_init(TIM_HandleTypeDef* htim, TIM_TypeDef* Instance, uint32_t period);

#endif /* INC_TEST_H_ */
