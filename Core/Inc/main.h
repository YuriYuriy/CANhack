/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "stdio.h"
#include "stdbool.h"
#include "st7735.h"
#include "interfaceCANhack_a.h"
#include "buttonClickFun.h"
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BL_Pin GPIO_PIN_3
#define BL_GPIO_Port GPIOA
#define RES_Pin GPIO_PIN_0
#define RES_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_1
#define DC_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_10
#define CS_GPIO_Port GPIOB
#define OUT_Pin GPIO_PIN_4
#define OUT_GPIO_Port GPIOB
#define DOWN_Pin GPIO_PIN_5
#define DOWN_GPIO_Port GPIOB
#define LEFT_Pin GPIO_PIN_6
#define LEFT_GPIO_Port GPIOB
#define RIGHT_Pin GPIO_PIN_7
#define RIGHT_GPIO_Port GPIOB
#define OK_Pin GPIO_PIN_8
#define OK_GPIO_Port GPIOB
#define UP_Pin GPIO_PIN_9
#define UP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define ST7735_BL 30
/*---------------MENU---------------*/
#define menu 0
#define modeReadSpeedCANPoint 20
#define modeWriteSpeedCANPoint 35
#define modeSettingPoint 50
/*------------------------------*/
/*---------------SpeedCAN---------------*/
#define modeSpeedCAN 1
#define setPrescalerCAN200Point 20
#define setPrescalerCAN200  200
#define setPrescalerCAN80Point 35
#define setPrescalerCAN80  80
#define setPrescalerCAN40Point 50
#define setPrescalerCAN40 40
#define setPrescalerCAN32Point 65
#define setPrescalerCAN32 32
#define setPrescalerCAN16Point 80
#define setPrescalerCAN16 16
#define setPrescalerCAN8Point 95
#define setPrescalerCAN8 8
#define setPrescalerCAN4Point 110
#define setPrescalerCAN4  4
/*------------------------------*/
/*---------------READ---------------*/
#define modeReadCAN 2
/*------------------------------*/
/*---------------SETTING---------------*/
#define modeSetting 4
/*------------------------------*/
/*---------------BOMBER---------------*/
#define modeBomber 5
#define modeStartCANPoint 20
#define modeStartIdPoint 35
#define modeFinishIdPoint 50
#define modeTimePoint 65
#define modeDataPoint 80
/*------------------------------*/
/*---------------NUMBERKEY---------------*/
#define modeNumHEXone 7
#define modeNumHEXtwo 8
#define modeNumTime 9
/*------------------------------*/
/*---------------StartCAN---------------*/
#define modeStartCAN 10
#define modeStartCANstop 11
/*------------------------------*/
/*---------------WRITTING---------------*/
#define modeWritting 6
/*------------------------------*/
/*---------------COLOUR---------------*/
#define textColour 0xFFFF
#define cursorColour 0x07E0
#define titleColour 0xFFFF
/*------------------------------*/
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
