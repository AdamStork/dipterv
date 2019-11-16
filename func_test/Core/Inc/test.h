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

bool encode_message(uint8_t* pBuffer);
bool decode_message(uint8_t* pBuffer, Command* msg);

void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);

void i2c_init(void);
void i2c_test(void);
void i2c_deinit(void);

void adc_init(void);
void adc_test(void);
void adc_deinit(void);

void spi_init(void);
void spi_test(void);
void spi_deinit(void);

void gpio_init(void);
void gpio_test(void);
void gpio_deinit(void);

void led_init(void);
void led_test(void);
void led_deinit(void);

void pwm_init(void);
void pwm_test(void);
void pwm_deinit(void);

#endif /* INC_TEST_H_ */
