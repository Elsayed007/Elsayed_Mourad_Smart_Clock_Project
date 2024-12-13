/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "time.h"

#include "string.h"
#include "stdlib.h"
#include "smartclock.h"
#include "wifi.h"

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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

// htim6 Timer for Modes: Time, Timer and Stopwatch
// htim7 Timer for Modes: Interlude, Date, Temp & Hum and Weather

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM1_Init(void);
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
	
	DS3231_TIME Time = {0};
	DS3231_DATE Date = {0};
//	DS3231_ALARM Alarm1 = {0};
//	DS3231_ALARM Alarm2 = {0};
	
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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	
	HT1632_BW_Init();
	HT1632_ClearMemory(HT1632_MEM_BW,0,23);
	HT1632_SetOutput(HT1632_CS_BW,HT1632_MEM_BW,Tilt1,Tilt2,0,23);
	
	HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN3_GPIO_Port,IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port,IN4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN5_GPIO_Port,IN5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN6_GPIO_Port,IN6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN7_GPIO_Port,IN7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN8_GPIO_Port,IN8_Pin,GPIO_PIN_RESET);
	
	
	receive_mode=1;
	HAL_Delay(1000);
	SetTimeServerURL(time_server_URL4);
	Wifi_Uart_Weather("+++",3);			//Switch to AT+ Command part1
	
	Wifi_Uart_Weather("a",1);				//Switch to AT+ Command part2
	Wifi_Uart_Weather("AT+Z\r", 5);	//Restart the wifi module
	Wifi_Uart_Weather("AT+ENTM\r", 8);	//end AT+command mode & switch back to Trans-Mode
	HAL_Delay(5000);
	GetTime();
//	
//receive_mode=2;
//HAL_Delay(3000);
//SetWeatherServerURL(weather_server_URL);
//Wifi_Uart_Weather("+++",3);			//Switch to AT+ Command part1

//Wifi_Uart_Weather("a",1);				//Switch to AT+ Command part2
//Wifi_Uart_Weather("AT+Z\r", 5);	//Restart the wifi module
//Wifi_Uart_Weather("AT+ENTM\r", 8);	//end AT+command mode & switch back to Trans-Mode
//HAL_Delay(5000);
//GetWeather();
	
	
	Time.Seconds = gmt_time.tm_sec;
	Time.Minutes = gmt_time.tm_min;
	Time.Hours = gmt_time.tm_hour;
	
	Date.Day = gmt_time.tm_wday-1;
	Date.Date = gmt_time.tm_mday;
	Date.Month = gmt_time.tm_mon;
	Date.Year = gmt_time.tm_year;
	
	DS3231_SetTime(Time,&hi2c1);
	DS3231_SetDate(Date,&hi2c1);

	
	
	HAL_TIM_Base_Start_IT(&htim7);	// Start with Interlude Mode = Time
	

//static uint8_t GoTo, Next, Space, CharPos, Mask, StringPos, Count, Dir, Step, StepRst, FrontPos;
//GoTo = Next = Space = CharPos = StringPos = 0;
//uint8_t LeftEdge = 0, RightEdge = 23;

//char Array[6][4]={"10.5","6.7","15.3","2.0","56.2","-7.4"};
//int8_t Min = GetMin(Array,6,0);
//int8_t Max = GetMax(Array,6,0);
//char Val[7] ={0};
//sprintf(Val,"%i %i",Min,Max);
//HT1632_BW_String(HT1632_MEM_BW,Val,&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
//HT1632_SetOutput(HT1632_CS_BW,HT1632_MEM_BW,Tilt1,Tilt2,LeftEdge,RightEdge);
	

	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 50;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 25;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 5;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 7999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 500;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 7999;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 200;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DM163_LAT_B_Pin|DM163_RST_B_Pin|DM163_EN_B_Pin|DM163_SELBK_Pin 
                          |HT1632_WR_Pin|HT1632_DATA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, HT1632_CS_Pin|HT1632_RD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DM163_DCK_Pin|DM163_SIN_Pin|RTC_Reset_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, IN2_Pin|IN3_Pin|IN4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(IN5_GPIO_Port, IN5_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, IN6_Pin|IN7_Pin|IN8_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : DM163_LAT_B_Pin DM163_SELBK_Pin */
  GPIO_InitStruct.Pin = DM163_LAT_B_Pin|DM163_SELBK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DM163_RST_B_Pin DM163_EN_B_Pin IN2_Pin IN3_Pin 
                           IN4_Pin */
  GPIO_InitStruct.Pin = DM163_RST_B_Pin|DM163_EN_B_Pin|IN2_Pin|IN3_Pin 
                          |IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BallTilt2_Pin BallTilt1_Pin */
  GPIO_InitStruct.Pin = BallTilt2_Pin|BallTilt1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : HT1632_CS_Pin HT1632_RD_Pin */
  GPIO_InitStruct.Pin = HT1632_CS_Pin|HT1632_RD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : HT1632_WR_Pin HT1632_DATA_Pin */
  GPIO_InitStruct.Pin = HT1632_WR_Pin|HT1632_DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DM163_DCK_Pin DM163_SIN_Pin IN6_Pin IN7_Pin 
                           IN8_Pin */
  GPIO_InitStruct.Pin = DM163_DCK_Pin|DM163_SIN_Pin|IN6_Pin|IN7_Pin 
                          |IN8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_Plus_Pin BUTTON_Set_Pin BUTTON_Mode_Pin */
  GPIO_InitStruct.Pin = BUTTON_Plus_Pin|BUTTON_Set_Pin|BUTTON_Mode_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : RTC_Alarm_Pin */
  GPIO_InitStruct.Pin = RTC_Alarm_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(RTC_Alarm_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IN1_Pin */
  GPIO_InitStruct.Pin = IN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IN1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IN5_Pin */
  GPIO_InitStruct.Pin = IN5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IN5_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RTC_Reset_Pin */
  GPIO_InitStruct.Pin = RTC_Reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RTC_Reset_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

/*UART Callback -> WIFI*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	if(receive_mode==1)
	{
		for(int i=0;i<max2;i++)
		{
		
			rx_timestamp[i]=(uint8_t)rx_string2[i];
		}
		Transmit_Timestamp+=(rx_timestamp[40]<<24);
		Transmit_Timestamp+=(rx_timestamp[41]<<16);
		Transmit_Timestamp+=(rx_timestamp[42]<<8);
		Transmit_Timestamp+=(rx_timestamp[43]<<0);
	
		Transmit_Timestamp-=2208988800; 				//Time from 1900 to 1970 in seconds 
		Transmit_Timestamp+=(3600*Timezone);
		gmt_time = *localtime(&Transmit_Timestamp);
		
		receive_mode=2;
	}
	if(receive_mode==2)
	{
		ConvertWeather((char*)rx_string2);
	}
	
}


/*GPIO Callback -> Buttons & Ball Tilts*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	if(GPIO_Pin == BUTTON_Mode_Pin && SWITCH == 2)		//BUTTON_MODE												
	{
		SWITCH= 0;

		if(MODE == MODE_TIME)											//TIME
		{
			if(INTERLUDE == TRUE)
			{
				HAL_TIM_Base_Stop_IT(&htim7);
			}
			else
			{
				HAL_TIM_Base_Stop_IT(&htim6);
			}
			
			MODE = MODE_DATE;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if(MODE == MODE_DATE)								//DATE
		{
			HAL_TIM_Base_Stop_IT(&htim7);
			MODE = MODE_TEMPHUM;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if(MODE == MODE_TEMPHUM)							//TEMPERATURE&HUMIDITY
		{
			HAL_TIM_Base_Stop_IT(&htim7);
			MODE = MODE_WEATHER;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if(MODE == MODE_WEATHER)							//WEATHER
		{
			HAL_TIM_Base_Stop_IT(&htim7);
			MODE = MODE_TIMER;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if(MODE == MODE_TIMER)								//TIMER
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
			if(INTERLUDE == TRUE)
			{
				HAL_TIM_Base_Stop_IT(&htim7);
			}
			else
			{
				HAL_TIM_Base_Stop_IT(&htim6);
			}
			
			MODE = MODE_STOPWATCH;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if(MODE == MODE_STOPWATCH)						//STOPWATCH
		{
			if(INTERLUDE == TRUE)
			{
				HAL_TIM_Base_Stop_IT(&htim7);
			}
			else
			{
				HAL_TIM_Base_Stop_IT(&htim6);
			}
			
			MODE = MODE_ALARM;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if(MODE == MODE_ALARM)								//ALARM
		{
			if(INTERLUDE == TRUE)
			{
				HAL_TIM_Base_Stop_IT(&htim7);
			}
			else
			{
				HAL_TIM_Base_Stop_IT(&htim6);
			}
			
			MODE = MODE_TIME;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if(MODE == MODE_ALARM_IT)
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
			HAL_TIM_Base_Stop_IT(&htim6);
			MODE = MODE_TIME;
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else
		{
			// No further action
		}
		
		INTERLUDE = TRUE;
		RST = TRUE;
	
	}
	else if(GPIO_Pin == BUTTON_Mode_Pin)
	{
		SWITCH = 1;
	}
	else if(GPIO_Pin == BallTilt1_Pin || GPIO_Pin == BallTilt2_Pin)	//Ball Tilts
	{
		Tilt1 = HAL_GPIO_ReadPin(BallTilt1_GPIO_Port,BallTilt1_Pin);
		Tilt2 = HAL_GPIO_ReadPin(BallTilt2_GPIO_Port,BallTilt2_Pin);
	}
	else if(GPIO_Pin == BUTTON_Plus_Pin)
	{
		if(MODE == MODE_TIMER)
		{
			if(B_PLUS == 2)
			{
				if(TIMER_POS == 0){if(++(TIMER.mx) == 6){TIMER.mx = 0;}}
				else if(TIMER_POS == 1){if(++(TIMER.xm) == 10){TIMER.xm = 0;}}
				else if(TIMER_POS == 2){if(++(TIMER.sx) == 6){TIMER.sx = 0;}}
				else if(TIMER_POS == 3){if(++(TIMER.xs) == 10){TIMER.xs = 0;}}
				B_PLUS = 0;
			}
			else
			{
				B_PLUS = 1;
			}
		}
		else if(MODE == MODE_STOPWATCH)
		{
			if(B_PLUS == 2)
			{
				if(STOPWATCH.Status == 0)
				{
					STOPWATCH.Status = 1;
				}
				else
				{
					STOPWATCH.Status = 0;
				}
				B_PLUS = 0;
			}
			else
			{
				B_PLUS = 1;
			}
		}
		else if(MODE == MODE_ALARM)
		{
			if(B_PLUS == 2)
			{
				if(ALARM_POS == 0)
				{
					if((ALARM1.Hours += 10) / 10 == 3)
					{
						ALARM1.Hours -= 30;
					}
				}
				else if(ALARM_POS == 1)
				{
					if((ALARM1.Hours += 1) % 10 == 0)
					{
						ALARM1.Hours -= 10;
					}
				}
				else if(ALARM_POS == 2)
				{
					if((ALARM1.Minutes += 10) >= 60)
					{
						ALARM1.Minutes -= 60;
					}
				}
				else if(ALARM_POS == 3)
				{
					if((ALARM1.Minutes += 1) % 10 == 0)
					{
						ALARM1.Minutes -= 10;
					}
				}
				else if(ALARM_POS == 10)
				{
					if(ALARM_ST == 0)
					{
						ALARM_ST = 1;
					}
					else
					{
						ALARM_ST = 0;
					}
				}
				if(ALARM1.Hours >= 25)
				{
					ALARM1.Hours = 20;
				}
				B_PLUS = 0;
			}
			else
			{
				B_PLUS = 1;
			}
		}
	}
	else if(GPIO_Pin == BUTTON_Set_Pin)
	{
		if(MODE == MODE_TIMER)
		{
			if(B_SET == 2)
			{
				if(++TIMER_POS == 4)
				{
					// No further action
				}
				else if(TIMER_POS-1 == 0 && TIMER.Status == 1)
				{
					TIMER.Status = 0;
				}
				B_SET = 0;
			}
			else
			{
				B_SET = 1;
			}
		}
		else if(MODE == MODE_STOPWATCH)
		{
			if(B_SET == 2)
			{
				STOPWATCH.mx = 0;STOPWATCH.xm = 0; STOPWATCH.sx = 0; STOPWATCH.xs = 0; STOPWATCH.Status = 0;
				B_SET = 0;
			}
			else
			{
				B_SET = 1;
			}
		}
		else if(MODE == MODE_ALARM)
		{
			if(B_SET == 2)
			{
				if(ALARM_POS == 10)
				{
					if(ALARM_ST == 0)
					{
						ALARM_ST = 2;
					}
					else if(ALARM_ST == 1)
					{
						ALARM_ST = 3;
					}
				}
				else if(++ALARM_POS == 4)
				{
					// No further action
				}
				B_SET = 0;
			}
			else
			{
				B_SET = 1;
			}
		}
	}
	else if(GPIO_Pin == RTC_Alarm_Pin)
	{
		HAL_TIM_Base_Stop_IT(&htim6);
		HAL_TIM_Base_Stop_IT(&htim7);
		uint8_t Data = 142;
			HAL_I2C_Mem_Write(&hi2c1,DS3231,0x0F,1,&Data,1,HAL_MAX_DELAY);
		HAL_TIM_Base_Start_IT(&htim6);
		MODE = MODE_ALARM_IT;
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	}
	else
	{
		// No further action
	}
}


/*TIMER Callback -> Refresh Data and Display*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/*Variables*/
	//Time
	static uint8_t TimePointsToggle = TRUE;
	
	//Date
	
	//Temp & Hum
	
	//General
	static uint8_t GoTo, Next, Space, CharPos, Mask, StringPos, Count, Dir, Step, StepRst, FrontPos;
	uint8_t LeftEdge = 0, RightEdge = 23;
	uint8_t Status = 0;
	uint8_t CpltRst = 0;
	uint8_t DataIn = 0xFF, DataOut = 0x00;
	
	if(SWITCH == 1){SWITCH = 2;}
	
	if(RST == TRUE)
	{
		GoTo = SET;
		Next = Space = CharPos = StringPos = Count = Dir = Step = 0;
		CpltRst = StepRst = TRUE;
		HT1632_ClearMemory(HT1632_MEM_BW,0,23);
		TimePointsToggle = TRUE;
		RST = FALSE;
		B_PLUS = B_SET = 1;
		TIMER_POS = ALARM_POS = ALARM_ST = 0;
		STOPWATCH.mx=0;STOPWATCH.xm=0;STOPWATCH.sx=0;STOPWATCH.xs=0;
	}
	
	
	if(htim == &htim6)	// Timer for Modes: Time, Timer and Stopwatch
	{
		/*Refresh Data*/
		DS3231_TIME Time = {0};
		if(DS3231_GetTime(&Time,&hi2c1) == HAL_OK && TimePointsToggle == TRUE)
		{
			if (SECONDS != Time.Seconds){TICK = TRUE;}
			SECONDS = Time.Seconds;
			MINUTES = Time.Minutes;
			HOURS = Time.Hours;
		}
		
		/*Refresh Output*/
		if(MODE == MODE_TIME)
		{
			HT1632_BW_Time(HT1632_MEM_BW,HOURS,MINUTES,10);
			(TimePointsToggle == TRUE) ? (HT1632_BW_TimePoints(HT1632_MEM_BW,TRUE), TimePointsToggle = FALSE):(HT1632_BW_TimePoints(HT1632_MEM_BW,FALSE), TimePointsToggle = TRUE);
		}
		else if(MODE == MODE_TIMER)		// Code with Alarm Time Set is Ready
		{
			switch(GoTo)
			{
				case SET:
					if(B_PLUS == 1){B_PLUS = 2;}
					if(B_SET == 1){B_SET = 2;}
					HT1632_ClearMemory(HT1632_MEM_BW,LeftEdge,RightEdge);
					if(TimePointsToggle == TRUE)
					{
						HT1632_BW_Time(HT1632_MEM_BW,TIMER.mx*10 + TIMER.xm, TIMER.sx*10+TIMER.xs,TIMER_POS);
						TimePointsToggle = FALSE;
					}
					else
					{
						HT1632_BW_Time(HT1632_MEM_BW,TIMER.mx*10 + TIMER.xm, TIMER.sx*10+TIMER.xs,10);
						TimePointsToggle = TRUE;
					}
					HT1632_BW_TimePoints(HT1632_MEM_BW,TRUE);
					if(TIMER_POS == 4)
					{
						GoTo = CNT;
						TIMER.Status = 1;
						TimePointsToggle = TRUE;
					}
					break;
				case CNT:
					if(TIMER.Status == 1)
					{
						if(TICK == TRUE)
						{
							TICK = FALSE;
							if(TIMER.mx == 0 && TIMER.xm == 0 && TIMER.sx == 0 && TIMER.xs - 1 == 0){TIMER.mx = 0; TIMER.xm = 0; TIMER.sx = 0; TIMER.xs = 0; TIMER.Status = 1; TIMER_POS = 0;GoTo = WAIT;HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);}
							if(--(TIMER.xs) < 0){TIMER.xs = 9; TIMER.sx -= 1;}
							if((TIMER.sx) < 0){TIMER.sx = 5; TIMER.xm -= 1;}
							if((TIMER.xm) < 0){TIMER.xm = 9; TIMER.mx -= 1;}
							if((TIMER.mx) < 0){TIMER.mx = 0; TIMER.xm = 0; TIMER.sx = 0; TIMER.xs = 0; TIMER.Status = 1; TIMER_POS = 0;GoTo = WAIT;}
						}
						(TimePointsToggle == TRUE) ? (HT1632_BW_Time(HT1632_MEM_BW, TIMER.mx * 10 + TIMER.xm, TIMER.sx*10+TIMER.xs,10),HT1632_BW_TimePoints(HT1632_MEM_BW,TRUE), TimePointsToggle = FALSE):(HT1632_BW_TimePoints(HT1632_MEM_BW,FALSE), TimePointsToggle = TRUE);
					}
					break;
				default:
					(TimePointsToggle == FALSE) ? (HT1632_BW_Time(HT1632_MEM_BW,0,0,5),HT1632_BW_TimePoints(HT1632_MEM_BW,TRUE),TimePointsToggle = TRUE) : (HT1632_ClearMemory(HT1632_MEM_BW,LeftEdge,RightEdge),TimePointsToggle = FALSE);
					if(B_SET == 1){B_SET = 2;}
					TIMER_POS = 0;
					if(TIMER.Status == 0)
					{
						GoTo = SET;
						HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
					}
					break;
			}
		}
		else if(MODE == MODE_STOPWATCH)
		{
			if(B_SET == 1){B_SET = 2;}
			if(B_PLUS == 1){B_PLUS = 2;}
			if(STOPWATCH.Status == 1)
			{
				if(TICK == TRUE)
				{
					TICK = FALSE;
					if(++(STOPWATCH.xs) == 10){STOPWATCH.xs = 0; STOPWATCH.sx += 1;}
					if(STOPWATCH.sx == 6){STOPWATCH.sx = 0; STOPWATCH.xm += 1;}
					if(STOPWATCH.xm == 10){STOPWATCH.xm = 0; STOPWATCH.mx += 1;}
					if(STOPWATCH.mx == 6){STOPWATCH.mx = 0;}
				}
					(TimePointsToggle == TRUE) ? (HT1632_BW_Time(HT1632_MEM_BW, STOPWATCH.mx * 10 + STOPWATCH.xm, STOPWATCH.sx*10+STOPWATCH.xs,10),HT1632_BW_TimePoints(HT1632_MEM_BW,TRUE), TimePointsToggle = FALSE):(HT1632_BW_TimePoints(HT1632_MEM_BW,FALSE), TimePointsToggle = TRUE);
			}
			else
			{
				HT1632_BW_Time(HT1632_MEM_BW, STOPWATCH.mx * 10 + STOPWATCH.xm, STOPWATCH.sx*10+STOPWATCH.xs,10);
				HT1632_BW_TimePoints(HT1632_MEM_BW,TRUE);
				TimePointsToggle = TRUE;
				// No further action
			}
		}
		else if(MODE == MODE_ALARM)
		{
			switch(GoTo)
			{
				case SET:
					if(B_PLUS == 1){B_PLUS = 2;}
					if(B_SET == 1){B_SET = 2;}
					HT1632_ClearMemory(HT1632_MEM_BW,LeftEdge,RightEdge);
					if(TimePointsToggle == TRUE)
					{
						HT1632_BW_Time(HT1632_MEM_BW,ALARM1.Hours, ALARM1.Minutes,ALARM_POS);
						TimePointsToggle = FALSE;
					}
					else
					{
						HT1632_BW_Time(HT1632_MEM_BW,ALARM1.Hours, ALARM1.Minutes,10);
						TimePointsToggle = TRUE;
					}
					HT1632_BW_TimePoints(HT1632_MEM_BW,TRUE);
					if(ALARM_POS == 4)
					{
						ALARM_ST = 0;
						GoTo = SFT;
						B_PLUS = 0;
						B_SET = 0;
					}
					break;
				case SFT:
					if(B_PLUS == 1){B_PLUS = 2;}
					if(B_SET == 1){B_SET = 2;}
					HT1632_ClearMemory(HT1632_MEM_BW,LeftEdge,RightEdge);
					StringPos = CharPos = Space = 0;
					ALARM_POS = 10;
					if(ALARM_ST == 0)
					{
						HT1632_BW_String(HT1632_MEM_BW,"OFF",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_RIGHT);
					}
					else if(ALARM_ST == 1)
					{
						HT1632_BW_String(HT1632_MEM_BW,"ON",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_LEFT);
					}
					else if(ALARM_ST == 2)//OFF
					{
						uint8_t Data = 28;
						HT1632_BW_String(HT1632_MEM_BW,"OFF",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
						GoTo = WAIT;
						ALARM1.AlarmMask = 0;
						ALARM1.AlarmMask |= (1<<3);
						ALARM1.Seconds = 0;
						HAL_I2C_Mem_Write(&hi2c1,DS3231,0x0E,1,&Data,1,HAL_MAX_DELAY);
						DS3231_SetAlarm1(ALARM1,&hi2c1);
					}
					else if(ALARM_ST == 3)//ON
					{
						uint8_t Data = 29;
						HT1632_BW_String(HT1632_MEM_BW,"ON",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
						ALARM1.AlarmMask = 0;
						ALARM1.AlarmMask |= (1<<3);
						ALARM1.Seconds = 0;
						HAL_I2C_Mem_Write(&hi2c1,DS3231,0x0E,1,&Data,1,HAL_MAX_DELAY);
						DS3231_SetAlarm1(ALARM1,&hi2c1);
						GoTo = WAIT;
					}
					break;
				default:
					HAL_GPIO_EXTI_Callback(BUTTON_Mode_Pin);
					break;
			}
		}
		else if(MODE == MODE_ALARM_IT)
		{
			StringPos = CharPos = Space = 0;
			HT1632_ClearMemory(HT1632_MEM_BW,LeftEdge,RightEdge);
			if(TimePointsToggle == TRUE)
			{
				HT1632_BW_String(HT1632_MEM_BW,"ALARM",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
				TimePointsToggle = FALSE;
			}
			else
			{
				TimePointsToggle = TRUE;
			}
		}
		else
		{
			// No further action
		}
		
	}
	else if(htim == &htim7)	// Timer for Modes: Date, Temperature & Humidity and Weather
	{
//		HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
		if(INTERLUDE == TRUE)
		{
			if(MODE == MODE_TIME)
			{
				switch(GoTo)
				{
					case SET:
						HT1632_BW_String(HT1632_MEM_BW,"TIME",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
						GoTo = WAIT;
						Count = WAIT_INTERLUDE;
						break;
					default:
						if(--Count == 0)
						{
							INTERLUDE = FALSE;
							RST = TRUE;
							HAL_TIM_Base_Stop_IT(&htim7);
							HAL_TIM_Base_Start_IT(&htim6);
						}
						break;
				}
					HT1632_MEM_BW[2] &= ~(1 << 7);
					HT1632_MEM_BW[3] &= ~(1 << 7);
			}
			else if(MODE == MODE_DATE)
			{
				switch(GoTo)
				{
					case SET:
						HT1632_BW_String(HT1632_MEM_BW,"DATE",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
						GoTo = WAIT;
						Count = WAIT_INTERLUDE;
						break;
					default:
						if(--Count == 0)
						{
							INTERLUDE = FALSE;
							RST = TRUE;
							HAL_TIM_Base_Stop_IT(&htim7);
							HAL_TIM_Base_Start_IT(&htim7);
						}
						break;
				}
				HT1632_MEM_BW[5] &= ~(1 << 7);
				HT1632_MEM_BW[6] &= ~(1 << 7);
			}
			else if(MODE == MODE_TEMPHUM)
			{
				HT1632_MEM_BW[8] |= (1 << 7);
				HT1632_MEM_BW[9] |= (1 << 7);
				switch(GoTo)
				{
					case SET:
						Status = HT1632_BW_String(HT1632_MEM_BW,"TEMP AND HUM",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_LEFT);
						if(Status == 2)
						{
							GoTo = WAIT;
							Next = 0;
							Count = WAIT_INTERLUDE;
						}
						else if(Space != 0)
						{
							GoTo = WAIT;
							Next = SPC;
							Count = WAIT_INTERLUDE / 2;
						}
						else
						{
							GoTo = WAIT;
							Next = SFT;
							Count = WAIT_INTERLUDE / 2;
						}
						break;
					case SPC:
						if(--Space == 0)
						{
							GoTo = Next;
						}
						HT1632_BW_Shift(HT1632_MEM_BW,&DataIn,&DataOut,LeftEdge,RightEdge,LEFT);
						break;
					case SFT:
						Status = STRING_GetData(&DataIn,"TEMP AND HUM",&StringPos,&CharPos,&Mask,LeftEdge,RightEdge,ALIGN_LEFT,LEFT);
						HT1632_BW_Shift(HT1632_MEM_BW,&DataIn,&DataOut,LeftEdge,RightEdge,LEFT);
						if(Status == FIN_CHAR)
						{
							Space = SPACE_BETWEEN_CHARACTERS;
							GoTo = SPC;
							Next = SFT;
						}
						else if(Status == FIN_STRING)
						{
							GoTo = WAIT;
							Next = 0;
							Count = WAIT_INTERLUDE / 2;
						}
						break;
					default:
						if(--Count == 0)
						{
							GoTo = Next;
							if(GoTo != SPC && GoTo != SFT)
							{
								HAL_TIM_Base_Stop_IT(&htim7);
								HAL_TIM_Base_Start_IT(&htim7);
								INTERLUDE = FALSE;
								RST = TRUE;
							}
						}
						break;
				}
				HT1632_MEM_BW[8] &= ~(1 << 7);
				HT1632_MEM_BW[9] &= ~(1 << 7);
			}
			else if(MODE == MODE_WEATHER)
			{
				HT1632_MEM_BW[11] |= (1 << 7);
				HT1632_MEM_BW[12] |= (1 << 7);
				switch(GoTo)
				{
					case SET:
						Status = HT1632_BW_String(HT1632_MEM_BW,"WEATHER",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_LEFT);
						if(Status == 2)
						{
							GoTo = WAIT;
							Next = 0;
							Count = WAIT_INTERLUDE;
						}
						else if(Space != 0)
						{
							GoTo = WAIT;
							Next = SPC;
							Count = WAIT_INTERLUDE / 2;
						}
						else
						{
							GoTo = WAIT;
							Next = SFT;
							Count = WAIT_INTERLUDE / 2;
						}
						break;
					case SPC:
						if(--Space == 0)
						{
							GoTo = Next;
						}
						HT1632_BW_Shift(HT1632_MEM_BW,&DataIn,&DataOut,LeftEdge,RightEdge,LEFT);
						break;
					case SFT:
						Status = STRING_GetData(&DataIn,"WEATHER",&StringPos,&CharPos,&Mask,LeftEdge,RightEdge,ALIGN_LEFT,LEFT);
						HT1632_BW_Shift(HT1632_MEM_BW,&DataIn,&DataOut,LeftEdge,RightEdge,LEFT);
						if(Status == FIN_CHAR)
						{
							Space = SPACE_BETWEEN_CHARACTERS;
							GoTo = SPC;
							Next = SFT;
						}
						else if(Status == FIN_STRING)
						{
							GoTo = WAIT;
							Next = 0;
							Count = WAIT_INTERLUDE / 2;
						}
						break;
					default:
						if(--Count == 0)
						{
							GoTo = Next;
							if(GoTo != SPC && GoTo != SFT)
							{
								HAL_TIM_Base_Stop_IT(&htim7);
								HAL_TIM_Base_Start_IT(&htim7);
								INTERLUDE = FALSE;
								RST = TRUE;
							}
						}
						break;
				}
				HT1632_MEM_BW[11] &= ~(1 << 7);
				HT1632_MEM_BW[12] &= ~(1 << 7);
			}
			else if(MODE == MODE_TIMER)
			{

				switch(GoTo)
				{
					case SET:
						HT1632_BW_String(HT1632_MEM_BW,"TIMER",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
						GoTo = WAIT;
						Count = WAIT_INTERLUDE;
						break;
					default:
						if(--Count == 0)
						{
							INTERLUDE = FALSE;
							RST = TRUE;
							HAL_TIM_Base_Stop_IT(&htim7);
							HAL_TIM_Base_Start_IT(&htim6);
						}
						break;
				}
				HT1632_MEM_BW[14] &= ~(1 << 7);
				HT1632_MEM_BW[15] &= ~(1 << 7);
			}
			else if(MODE == MODE_STOPWATCH)
			{
				HT1632_MEM_BW[17] |= (1 << 7);
				HT1632_MEM_BW[18] |= (1 << 7);
				switch(GoTo)
				{
					case SET:
						Status = HT1632_BW_String(HT1632_MEM_BW,"STOPWATCH",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_LEFT);
						if(Status == 2)
						{
							GoTo = WAIT;
							Next = 0;
							Count = WAIT_INTERLUDE;
						}
						else if(Space != 0)
						{
							GoTo = WAIT;
							Next = SPC;
							Count = WAIT_INTERLUDE / 2;
						}
						else
						{
							GoTo = WAIT;
							Next = SFT;
							Count = WAIT_INTERLUDE / 2;
						}
						break;
					case SPC:
						if(--Space == 0)
						{
							GoTo = Next;
						}
						HT1632_BW_Shift(HT1632_MEM_BW,&DataIn,&DataOut,LeftEdge,RightEdge,LEFT);
						break;
					case SFT:
						Status = STRING_GetData(&DataIn,"STOPWATCH",&StringPos,&CharPos,&Mask,LeftEdge,RightEdge,ALIGN_LEFT,LEFT);
						HT1632_BW_Shift(HT1632_MEM_BW,&DataIn,&DataOut,LeftEdge,RightEdge,LEFT);
						if(Status == FIN_CHAR)
						{
							Space = SPACE_BETWEEN_CHARACTERS;
							GoTo = SPC;
							Next = SFT;
						}
						else if(Status == FIN_STRING)
						{
							GoTo = WAIT;
							Next = 0;
							Count = WAIT_INTERLUDE / 2;
						}
						break;
					default:
						if(--Count == 0)
						{
							GoTo = Next;
							if(GoTo != SPC && GoTo != SFT)
							{
								HAL_TIM_Base_Stop_IT(&htim7);
								HAL_TIM_Base_Start_IT(&htim6);
								INTERLUDE = FALSE;
								RST = TRUE;
							}
						}
						break;
				}
				HT1632_MEM_BW[17] &= ~(1 << 7);
				HT1632_MEM_BW[18] &= ~(1 << 7);
			}
			else if(MODE == MODE_ALARM)
			{
				switch(GoTo)
				{
					case SET:
						HT1632_BW_String(HT1632_MEM_BW,"ALARM",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
						GoTo = WAIT;
						Count = WAIT_INTERLUDE;
						break;
					default:
						if(--Count == 0)
						{
							INTERLUDE = FALSE;
							RST = TRUE;
							HAL_TIM_Base_Stop_IT(&htim7);
							HAL_TIM_Base_Start_IT(&htim6);
						}
						break;
				}
					HT1632_MEM_BW[20] &= ~(1 << 7);
					HT1632_MEM_BW[21] &= ~(1 << 7);
			}
		}
		else
		{
			if(MODE == MODE_DATE)
			{
				DS3231_DATE Date = {0};
				if(DS3231_GetDate(&Date,&hi2c1) == HAL_OK)
				{
					DAY = Date.Day;
					DATE = Date.Date;
					MONTH = Date.Month;
				}
				Status = HT1632_BW_Date(HT1632_MEM_BW,&GoTo,&Next,&Dir,&Count,&CharPos,&StringPos,&Mask,&Step,StepRst,CpltRst);
				StepRst = CpltRst = 0;
				if(Status == 1){StepRst = TRUE;}
			}
			else if(MODE == MODE_TEMPHUM)
			{
				AM2320 TempHumSensor = AM2320_Init(&hi2c1,0xB8);
				if(AM2320_GetValue(&TempHumSensor,&TEMPERATURE,&HUMIDITY) == HAL_OK)
				{
					// No further action
				}
				else
				{
					// No further action
				}
				Status = HT1632_BW_TempHum(HT1632_MEM_BW,&GoTo,&Next,&Dir,&Count,&Space,&FrontPos,&CharPos,&StringPos,&Mask,&Step,StepRst,CpltRst);
				StepRst = CpltRst = 0;
				if(Status == 1){StepRst = TRUE;}
			}
			else if(MODE == MODE_WEATHER)
			{
				char max[4] ="";
				char min[4]="";
				sprintf(max,"12%c",64);
				sprintf(min,"8%c",64);
				switch(GoTo)
				{
					case SET:
							HT1632_ClearMemory(HT1632_MEM_BW,LeftEdge,RightEdge);
						Space = StringPos = CharPos = 0;
						if(Next == 0)	//MAX
						{
							Status = HT1632_BW_String(HT1632_MEM_BW,"MAX",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
							GoTo = 0;
							Next = 1;
							Count = WAIT_INTERLUDE;
						}
						else if(Next == 1)	//MAX Value
						{
							Status = HT1632_BW_String(HT1632_MEM_BW,max,&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
							GoTo = 0;
							Next = 2;
							Count = WAIT_INTERLUDE;
						}
						else if(Next == 2)	//MIN
						{
							Status = HT1632_BW_String(HT1632_MEM_BW,"MIN",&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
							GoTo = 0;
							Next = 3;
							Count = WAIT_TEMPHUM;
						}
						else if(Next == 3)	//MIN Value
						{
							Status = HT1632_BW_String(HT1632_MEM_BW,min,&Space,&CharPos,&StringPos,LeftEdge,RightEdge,ALIGN_MID);
							GoTo = 0;
							Next = 0;
							Count = WAIT_TEMPHUM;
						}
						else if(Next == 4)
						{
						
						}
						break;
					default:
						if(--Count == 0)
						{
							GoTo = SET;
						}
						break;
					
				}
			}
			else
			{
				// No further action
			}
		}
	}
	HT1632_SetOutput(HT1632_CS_BW,HT1632_MEM_BW,Tilt1,Tilt2,LeftEdge,RightEdge);
}

/* USER CODE END 4 */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
