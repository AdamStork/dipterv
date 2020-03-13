/**
 * @file 	wrapper_spi.h
 * @author 	Adam Golya
 * @date   	13 03 2020
 * @brief 	Wrapper for SPI testing 			**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __wrapper_spi_H
#define __wrapper_spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "functional_test.pb.h"

bool spi_init(Command* message_in, SPI_HandleTypeDef* hspi);
void spi_test(Command* message_in, Command* message_out);
void spi_error_handler(Command* message_out);

#ifdef __cplusplus
}
#endif
#endif /*__ wrapper_pwm_H */


