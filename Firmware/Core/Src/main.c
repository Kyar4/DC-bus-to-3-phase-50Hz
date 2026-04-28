/* USER CODE BEGIN Header */

/**

******************************************************************************

* @file : main.c

* @brief : Main program body - SPWM 3 Phase (Chuẩn 20kHz Carrier / 50Hz Sine)

******************************************************************************

*/

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "main.h"



/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN Includes */

#include <math.h>

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

TIM_HandleTypeDef htim1;



/* USER CODE BEGIN PV */

#define SINE_POINTS 400 // Số điểm băm (20kHz / 50Hz = 400)

#define ARR_VALUE 1800 // Period chuẩn để tạo ra 20kHz ở chế độ Center-Aligned (72MHz)



uint16_t sine_lookUp[SINE_POINTS];



uint16_t index_U = 0; // 0 độ

uint16_t index_V = 133; // 120 độ (~ 1/3 của 400)

uint16_t index_W = 266; // 240 độ (~ 2/3 của 400)



float modulation_index = 0.9; // Chỉ số điều chế (biên độ đỉnh, max = 1.0)

/* USER CODE END PV */



/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);

static void MX_GPIO_Init(void);

static void MX_TIM1_Init(void);



/* USER CODE BEGIN PFP */



/* USER CODE END PFP */



/* Private user code ---------------------------------------------------------*/

/* USER CODE BEGIN 0 */



/* USER CODE END 0 */



/**

* @brief The application entry point.

* @retval int

*/

int main(void)

{

/* MCU Configuration--------------------------------------------------------*/

HAL_Init();

SystemClock_Config();

MX_GPIO_Init();

MX_TIM1_Init();



/* USER CODE BEGIN 2 */




__HAL_TIM_SET_AUTORELOAD(&htim1, ARR_VALUE);



// tính mảng SPWM

for(int i = 0; i < SINE_POINTS; i++) {

float sin_val = (sin(2.0 * M_PI * i / SINE_POINTS) + 1.0) / 2.0;

sine_lookUp[i] = (uint16_t)(sin_val * ARR_VALUE * modulation_index); //a(0,1)*%pwm a

}



//Mở khóa Driver IR2110

HAL_GPIO_WritePin(SD_Signal_GPIO_Port, SD_Signal_Pin, GPIO_PIN_RESET);



// Kích hoạt xuất PWM cho cả 6 chân (Pha U, Pha V, Pha W)

HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);


HAL_TIM_Base_Start_IT(&htim1);



/* USER CODE END 2 */



/* Infinite loop */

/* USER CODE BEGIN WHILE */

while (1)

{

//
HAL_GPIO_TogglePin(LED_BUILDIN_GPIO_Port, LED_BUILDIN_Pin);

HAL_Delay(2000);



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



RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;

RCC_OscInitStruct.HSEState = RCC_HSE_ON;

RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;

RCC_OscInitStruct.HSIState = RCC_HSI_ON;

RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)

{

Error_Handler();

}



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

* @brief TIM1 Initialization Function

*/

static void MX_TIM1_Init(void)

{

TIM_ClockConfigTypeDef sClockSourceConfig = {0};

TIM_MasterConfigTypeDef sMasterConfig = {0};

TIM_OC_InitTypeDef sConfigOC = {0};

TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};



htim1.Instance = TIM1;

htim1.Init.Prescaler = 0;

htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;

htim1.Init.Period = 36000;

htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

htim1.Init.RepetitionCounter = 0;

htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

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

sConfigOC.Pulse = 18000;

sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;

sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;

sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;

sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)

{

Error_Handler();

}

if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)

{

Error_Handler();

}

if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)

{

Error_Handler();

}

sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;

sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;

sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;

sBreakDeadTimeConfig.DeadTime = 72;

sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;

sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;

sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;

if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)

{

Error_Handler();

}

HAL_TIM_MspPostInit(&htim1);

}



/**

* @brief GPIO Initialization Function

*/

static void MX_GPIO_Init(void)

{

GPIO_InitTypeDef GPIO_InitStruct = {0};



/* GPIO Ports Clock Enable */

__HAL_RCC_GPIOC_CLK_ENABLE();

__HAL_RCC_GPIOD_CLK_ENABLE();

__HAL_RCC_GPIOB_CLK_ENABLE();

__HAL_RCC_GPIOA_CLK_ENABLE();



/*Configure GPIO pin Output Level */

HAL_GPIO_WritePin(LED_BUILDIN_GPIO_Port, LED_BUILDIN_Pin, GPIO_PIN_RESET);

HAL_GPIO_WritePin(SD_Signal_GPIO_Port, SD_Signal_Pin, GPIO_PIN_RESET);



/*Configure GPIO pin : LED_BUILDIN_Pin */

GPIO_InitStruct.Pin = LED_BUILDIN_Pin;

GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

GPIO_InitStruct.Pull = GPIO_NOPULL;

GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

HAL_GPIO_Init(LED_BUILDIN_GPIO_Port, &GPIO_InitStruct);



/*Configure GPIO pin : SD_Signal_Pin */

GPIO_InitStruct.Pin = SD_Signal_Pin;

GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

GPIO_InitStruct.Pull = GPIO_NOPULL;

GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

HAL_GPIO_Init(SD_Signal_GPIO_Port, &GPIO_InitStruct);

}



/* USER CODE BEGIN 4 */



/**



*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)

{

if (htim->Instance == TIM1)

{

//

__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, sine_lookUp[index_U]);

__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, sine_lookUp[index_V]);

__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, sine_lookUp[index_W]);


//reset điểm hehehe

index_U++; if(index_U >= SINE_POINTS) index_U = 0;

index_V++; if(index_V >= SINE_POINTS) index_V = 0;

index_W++; if(index_W >= SINE_POINTS) index_W = 0;

}

}



/* USER CODE END 4 */



/**

* @brief This function is executed in case of error occurrence.

*/

void Error_Handler(void)

	{

		/* USER CODE BEGIN Error_Handler_Debug */

		__disable_irq();

		while (1)

		{

		}

		/* USER CODE END Error_Handler_Debug */

	}



#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)

{

}

#endif /* USE_FULL_ASSERT */
