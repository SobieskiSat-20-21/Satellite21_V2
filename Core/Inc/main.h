/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

I2C_HandleTypeDef* I2C2_Handler(void);
SPI_HandleTypeDef* Get_SPI1_Instance(void);
TIM_HandleTypeDef* Get_TIM10_Instance(void);
RTC_HandleTypeDef* Get_RTC_Instance(void);
UART_HandleTypeDef* Get_UART1_Instance(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEDA_Pin GPIO_PIN_0
#define LEDA_GPIO_Port GPIOC
#define LEDB_Pin GPIO_PIN_1
#define LEDB_GPIO_Port GPIOC
#define LEDC_Pin GPIO_PIN_2
#define LEDC_GPIO_Port GPIOC
#define LEDD_Pin GPIO_PIN_3
#define LEDD_GPIO_Port GPIOC
#define LR_D1_Pin GPIO_PIN_1
#define LR_D1_GPIO_Port GPIOA
#define LR_D0_Pin GPIO_PIN_2
#define LR_D0_GPIO_Port GPIOA
#define LR_RST_Pin GPIO_PIN_3
#define LR_RST_GPIO_Port GPIOA
#define MOT_STBY2_Pin GPIO_PIN_4
#define MOT_STBY2_GPIO_Port GPIOA
#define LR_SCK_Pin GPIO_PIN_5
#define LR_SCK_GPIO_Port GPIOA
#define LR_MISO_Pin GPIO_PIN_6
#define LR_MISO_GPIO_Port GPIOA
#define LR_MOSI_Pin GPIO_PIN_7
#define LR_MOSI_GPIO_Port GPIOA
#define LR_NSS_Pin GPIO_PIN_4
#define LR_NSS_GPIO_Port GPIOC
#define PHA_A2_Pin GPIO_PIN_5
#define PHA_A2_GPIO_Port GPIOC
#define ENB_A2_Pin GPIO_PIN_0
#define ENB_A2_GPIO_Port GPIOB
#define ENB_A1_Pin GPIO_PIN_1
#define ENB_A1_GPIO_Port GPIOB
#define PHA_A1_Pin GPIO_PIN_2
#define PHA_A1_GPIO_Port GPIOB
#define SCL_2_Pin GPIO_PIN_10
#define SCL_2_GPIO_Port GPIOB
#define SDA_2_Pin GPIO_PIN_11
#define SDA_2_GPIO_Port GPIOB
#define MOT_STBY1_Pin GPIO_PIN_12
#define MOT_STBY1_GPIO_Port GPIOB
#define USR_2_Pin GPIO_PIN_7
#define USR_2_GPIO_Port GPIOC
#define GPS_RX_Pin GPIO_PIN_9
#define GPS_RX_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_10
#define GPS_TX_GPIO_Port GPIOA
#define LIMIT_1_Pin GPIO_PIN_13
#define LIMIT_1_GPIO_Port GPIOA
#define SD_SW_Pin GPIO_PIN_15
#define SD_SW_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOB
#define USR_1_Pin GPIO_PIN_9
#define USR_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
