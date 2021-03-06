/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */


void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  if(i2cHandle->Instance==I2C1)
	  {
	  /* USER CODE BEGIN I2C1_MspInit 0 */

	  /* USER CODE END I2C1_MspInit 0 */

	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    /**I2C1 GPIO Configuration
	    PB8     ------> I2C1_SCL
	    PB9     ------> I2C1_SDA
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    /* I2C1 clock enable */
	    __HAL_RCC_I2C1_CLK_ENABLE();
	  /* USER CODE BEGIN I2C1_MspInit 1 */

	  /* USER CODE END I2C1_MspInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C2)
	  {
	  /* USER CODE BEGIN I2C2_MspInit 0 */

	  /* USER CODE END I2C2_MspInit 0 */

	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    /**I2C2 GPIO Configuration
	    PB10     ------> I2C2_SCL
	    PB3     ------> I2C2_SDA
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_10;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF9_I2C2;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    /* I2C2 clock enable */
	    __HAL_RCC_I2C2_CLK_ENABLE();
	  /* USER CODE BEGIN I2C2_MspInit 1 */

	  /* USER CODE END I2C2_MspInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C3)
	  {
	  /* USER CODE BEGIN I2C3_MspInit 0 */

	  /* USER CODE END I2C3_MspInit 0 */

	    __HAL_RCC_GPIOC_CLK_ENABLE();
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    /**I2C3 GPIO Configuration
	    PC9     ------> I2C3_SDA
	    PA8     ------> I2C3_SCL
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_9;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_8;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    /* I2C3 clock enable */
	    __HAL_RCC_I2C3_CLK_ENABLE();
	  /* USER CODE BEGIN I2C3_MspInit 1 */

	  /* USER CODE END I2C3_MspInit 1 */
	  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

	  if(i2cHandle->Instance==I2C1)
	  {
	  /* USER CODE BEGIN I2C1_MspDeInit 0 */

	  /* USER CODE END I2C1_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_I2C1_CLK_DISABLE();

	    /**I2C1 GPIO Configuration
	    PB8     ------> I2C1_SCL
	    PB9     ------> I2C1_SDA
	    */
	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

	  /* USER CODE BEGIN I2C1_MspDeInit 1 */

	  /* USER CODE END I2C1_MspDeInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C2)
	  {
	  /* USER CODE BEGIN I2C2_MspDeInit 0 */

	  /* USER CODE END I2C2_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_I2C2_CLK_DISABLE();

	    /**I2C2 GPIO Configuration
	    PB10     ------> I2C2_SCL
	    PB3     ------> I2C2_SDA
	    */
	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_3);

	  /* USER CODE BEGIN I2C2_MspDeInit 1 */

	  /* USER CODE END I2C2_MspDeInit 1 */
	  }
	  else if(i2cHandle->Instance==I2C3)
	  {
	  /* USER CODE BEGIN I2C3_MspDeInit 0 */

	  /* USER CODE END I2C3_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_I2C3_CLK_DISABLE();

	    /**I2C3 GPIO Configuration
	    PC9     ------> I2C3_SDA
	    PA8     ------> I2C3_SCL
	    */
	    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);

	    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);

	  /* USER CODE BEGIN I2C3_MspDeInit 1 */

	  /* USER CODE END I2C3_MspDeInit 1 */
	  }
} 

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
