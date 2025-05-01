/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8] =
{ 0, };
uint8_t RxData[8] =
{ 0, };
uint32_t TxMailbox = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	bool updateIf = 0;
	bool startBomberCANflag = 0;
	bool iniCANflag = 0;
	bool cursorShowFlag = 0;
	uint8_t modeInreface = 0;
	uint8_t modeInrefaceSet = 0;
	uint8_t cursorX = 0;
	uint8_t cursorY = 20;
	uint8_t startPointsCursor = 0;
	uint8_t numPointsCursor = 0;
	uint8_t stepPointsCursor = 0;
	uint8_t prescalerCAN = 0;
	uint16_t a = 0;
	uint64_t timeCAN = 0;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	ST7735_Init();
	ST7735_FillScreenFast(ST7735_BLACK);
	ST7735_WriteString(25, 50, "CAN", Font_16x26, ST7735_GREEN, ST7735_BLACK);
	ST7735_WriteString(73, 50, "hack", Font_16x26, textColour, ST7735_BLACK);
	TIM2->CCR4 = ST7735_BL;
	HAL_Delay(300);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{
		/*---------------Запуск меню---------------*/
		if (updateIf == 0)
		{
			interfaceInit(modeInreface, prescalerCAN);
			startPointsCursor = startPointsCurSet();
			numPointsCursor = numPointsCurSet();
			stepPointsCursor = stepPointsCurSet();
			cursorY = cursorYSet();
			cursorX = cursorXSet();
			updateIf = 1;
		}
		/*------------------------------*/
		modeInrefaceSet = modeInreface; //Запомнимает прошлое значение меню
		/*---------------Обновить данные в бомбер при наборе---------------*/
		if (showBomberDataFlagSet() == 1)
		{
			bomberDATAnumber();
		}
		/*------------------------------*/
		/*---------------Прятать курсор в режиме записи CAN---------------*/
		switch (modeInreface)
		{
		case modeStartCAN:
			cursorShowFlag = 1;
			break;
		case modeStartCANstop:
			cursorShowFlag = 1;
			break;
		default:
			cursorShowFlag = 0;
			break;
		}
		/*------------------------------*/
		/*---------------Задать позицию курсора если активен---------------*/
		if (cursorShowFlag == 0)
		{
			cursor(cursorX, cursorY);
		}
		/*------------------------------*/
		/*---------------Опрос клавиш---------------*/
		cursorY = buttonClickUpDown(startPointsCursor, numPointsCursor, stepPointsCursor, cursorX, cursorY);
		modeInreface = buttonClickOut(modeInreface);
		modeInreface = buttonClickOK(cursorY, modeInreface);
		modeInreface = buttonClickLeftRight(modeInreface);
		prescalerCAN = prescalerCANset();
		/*------------------------------*/
		/*---------------Перенос перемннх из одной библиотке в другую---------------*/
		bomberTIMEnumSet(bomberTIMEkeySet()); //Период отправления сообщения
		startIDnumSet(startIDkeySet()); //Начальный адрес
		finishIDnumSet(finishIDkeySet()); //Конечный адрес
		dataCANnumSet(dataCANkeySet()); //Данные сообщения
		iniCANflag = iniCANflagKeySet(); //Инициализация CAN
		/*------------------------------*/
		/*---------------Проверка изменилось ли меню---------------*/
		if (modeInrefaceSet != modeInreface)
		{
			updateIf = 0;
		}
		/*------------------------------*/
		/*---------------Запус бомбер CAN---------------*/
		if (iniCANflag == 0)
		{
			startBomberCANflag = startBomberCANflagSet();
			startBomberCANflag = testCANset(startBomberCANflag);
		}

		if (startBomberCANflag == 1)
		{
			if (iniCANflag == 0)
			{
				a = startIDkeySet();
				uint64_t data1 = dataCANkeySet();
				for (uint8_t i = 0; i < 8; i++)
				{
					uint8_t data2 = data1;
					TxData[i] = data2;
					data1 = data1 >> 8;
				}
				hcan.Init.Prescaler = prescalerCANset();
				TxHeader.StdId = 0;
				TxHeader.ExtId = 0;
				TxHeader.RTR = CAN_RTR_DATA; //CAN_RTR_REMOTE
				TxHeader.IDE = CAN_ID_STD;   // CAN_ID_EXT
				TxHeader.DLC = 8;
				TxHeader.TransmitGlobalTime = 0;
				HAL_CAN_Start(&hcan);
				iniCANflag = 1;
				iniCANflagSet(iniCANflag);
				ST7735_FillScreenFast(ST7735_BLACK);
			}

			if ((HAL_GetTick() - timeCAN) >= bomberTIMEkeySet())
			{
				TxHeader.StdId = a;
				HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_ERROR | CAN_IT_BUSOFF | CAN_IT_LAST_ERROR_CODE);
				while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
					;
				char dataText[64] =
				{ 0, };
				snprintf(dataText, 23, "ID: %x", a);
				ST7735_WriteString(10, 0, dataText, Font_7x10, textColour, ST7735_BLACK);

				if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
				{
				}
				if (a < finishIDkeySet())
				{
					a++;
				}
				else
				{
					startBomberCANflag = 0;
					ST7735_WriteString(10, 15, "CANstop", Font_7x10, textColour, ST7735_BLACK);
					modeInreface = modeStartCANstop;
				}
				timeCAN = HAL_GetTick();
			}
/*------------------------------*/
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
