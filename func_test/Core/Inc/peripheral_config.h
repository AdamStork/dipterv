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

/*******	 UART handle for communication with PC ****/
 #define UART_HANDLE huart2


/*******		PWM Timer Peripherals			 ******/
#define FREQ_TIMER_INSTANCE	TIM2
#define ACTIVITY_TIMER_INSTANCE	TIM3


/*******		SPI Peripherals		  			 ******/
#define HAS_SPI1
#define HAS_SPI2
#define HAS_SPI3


/*******		I2C Peripherals		  			 ******/
#define HAS_I2C1
#define HAS_I2C2
#define HAS_I2C3


/*******		USART Peripherals	  			 ******/
#define HAS_USART1
#define HAS_USART2
//#define HAS_USART3
//#define HAS_USART4
//#define HAS_USART5
#define HAS_USART6


/*******		ADC Peripherals		  			 ******/
#define HAS_ADC1


/*******		GPIO Peripherals	  			******/
#define HAS_GPIO_PA0_PA7
#define HAS_GPIO_PA8_PA15
#define HAS_GPIO_PB0_PB7
#define HAS_GPIO_PB8_PB15
#define HAS_GPIO_PC0_PC7
#define HAS_GPIO_PC8_PC15




#ifdef __cplusplus
}
#endif
#endif /*__ peripheral_config_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
