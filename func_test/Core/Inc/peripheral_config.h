/**
  ******************************************************************************
  * File Name			peripheral_config.h
  * Author				Adam Golya
  * Brief				This file contains the macro defines, whether a peripheral
  * 					should be used or not.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __peripheral_config_H
#define __peripheral_config_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/



/*******	SPI Peripherals		********/
#define HAS_SPI1
#define HAS_SPI2
#define HAS_SPI3

#define HAS_I2C1
#define HAS_I2C2
#define HAS_I2C3

#define HAS_USART1
#define HAS_USART2
//#define HAS_USART3
//#define HAS_USART4
//#define HAS_USART5
#define HAS_USART6

#define HAS_ADC1



#ifdef __cplusplus
}
#endif
#endif /*__ peripheral_config_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
