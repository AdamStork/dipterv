/*	@author	Adam Golya
 * 	@date	2019.11.12
 * 	@brief	main.c
 */
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include <stdbool.h>
#include "test.h"
#include "functional_test.pb.h"
#include "link_layer.h"

bool frameReady = false;
uint8_t receiveByte;
uint8_t transmitByte;
uint8_t receiveBuffer[128];
uint8_t transmitBuffer[128];
uint8_t receiveBufferLen;

link_layer_t linkLayer;


void SystemClock_Config(void);

int main(void)
{
  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  Command message_in = Command_init_zero;
  Command message_out = Command_init_zero;
  buffer_init_zero(receiveBuffer, sizeof(receiveBuffer));
  bool messageDecodeSuccessful = false;
  bool testToggle = false;

  while (1){
	  HAL_UART_Receive_DMA(&huart2,(uint8_t*)&receiveByte, 1);
	  if(frameReady){
		  frameReady = false;
		  messageDecodeSuccessful = decode_message(receiveBuffer, &message_in);
		  if(messageDecodeSuccessful){
			  switch(message_in.commandType){
			  case CommandTypeEnum_STOP_CURRENT_TEST:
				  break;
			  case CommandTypeEnum_ADC_test:
				  break;
			  case CommandTypeEnum_I2C_test:
				  // perif_init()
				  // perif_test()
				  // perif_uninit()
				  break;
			  case CommandTypeEnum_SPI_test:
				  break;
			  case CommandTypeEnum_LED_test:
				  HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
				  if(testToggle){
					  message_out.commandType = CommandTypeEnum_LED_test;
					  testToggle = false;
				  }
				  else{
					  message_out.commandType = CommandTypeEnum_GPIO_test;
					  testToggle = true;
				  }
				  encode_message(transmitBuffer,&message_out);
				  link_set_phy_write_fn(&linkLayer,&buffer_send);
				  link_write(&linkLayer,transmitBuffer,strlen((char*)transmitBuffer));
				  // transmitByte --> protobuf --> framing --> protobuf
//				  HAL_UART_Transmit_DMA(&huart2,,1);
				  break;
			  case CommandTypeEnum_GPIO_test:
				  break;
			  case CommandTypeEnum_TIMER_SINGLE_SHOT:
				  break;
			  case CommandTypeEnum_RTC_test:
				  break;
			  case CommandTypeEnum_PWM:
				  break;
			  default:
				  break;
			  }
		  }
	  }

  }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
