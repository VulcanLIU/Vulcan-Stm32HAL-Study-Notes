/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Adafruit_SSD1306.h"
#include "Joystick.h"
#include "Blink.h"
#include "GY25.h"
#include "Stepper.h"
#include "HC08.h"
#include "untitled2.h" // Model's header file
#include "rtwtypes.h"
#include "timer4.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NUMFLAKES 10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char logo_bmp[] =
    {
        0B00000000, 0B11000000,
        0B00000001, 0B11000000,
        0B00000001, 0B11000000,
        0B00000011, 0B11100000,
        0B11110011, 0B11100000,
        0B11111110, 0B11111000,
        0B01111110, 0B11111111,
        0B00110011, 0B10011111,
        0B00011111, 0B11111100,
        0B00001101, 0B01110000,
        0B00011011, 0B10100000,
        0B00111111, 0B11100000,
        0B00111111, 0B11110000,
        0B01111100, 0B11110000,
        0B01110000, 0B01110000,
        0B00000000, 0B00110000};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Adafruit_SSD1306 display(I2C1);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
long random(long howbig);
long random(long howsmall, long howbig);
void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h);
int map(int x, int in_min, int in_max, int out_min, int out_max);
float fmap(float x, float in_min, float in_max, float out_min, float out_max);
void rt_OneStep(void);
void OneStep(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static untitled2ModelClass untitled2_Obj;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  //MX_TIM1_Init();
  MX_USART2_UART_Init();
  //MX_TIM2_Init();
  //MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  joystick.init();
  joystick.begin();

  blink.init();
  blink.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x78); // Address 0x3D for 128x64
  display.display();

  gy25.begin();

  Stepper_left.init();
  Stepper_left.begin();
  Stepper_right.init();
  Stepper_right.begin();

  hc08.begin();

  untitled2_Obj.initialize();
  timer4.init();
  timer4.attachInterrupt(OneStep);
  timer4.begin();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    //float _speed = fmap(joystick.ADC_VALUE_buffer[0] & 0xff, 0, 255, -1800, 1800);

    hc08.send(gy25.getPitch(), Stepper_left.getSpeed());

    // display.clearDisplay();
    // display.setCursor(0, 0);
    // display.setTextColor(WHITE);
    // display.print("H:");
    // display.print(joystick.ADC_VALUE_buffer[0] >> 8);
    // display.setCursor(64, 0);
    // display.setTextColor(WHITE);
    // display.print("V:");
    // display.print(joystick.ADC_VALUE_buffer[0] & 0xff);
    // if (joystick.Clicked == true)
    // {
    //   display.setCursor(110, 0);
    //   display.setTextColor(WHITE);
    //   display.print("B");
    //   joystick.Clicked = false;
    // }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.print("Kp:");
    display.print(hc08.getKp());
    display.setCursor(50, 0);
    display.setTextColor(WHITE);
    display.print("Ki:");
    display.print(hc08.getKi());
    display.setCursor(0, 10);
    display.setTextColor(WHITE);
    display.print("Kd:");
    display.print(hc08.getKd());

    // display.setCursor(0, 10);
    // display.setTextColor(WHITE);
    // display.print("Y:");
    // display.print(gy25.YPR[0]);
    // display.setCursor(64, 10);
    // display.setTextColor(WHITE);
    // display.print("P:");
    // display.print(gy25.YPR[1]);
    // display.setCursor(0, 20);
    // display.setTextColor(WHITE);sjsjsjsjsjj
    // display.print("R:");
    // display.print(gy25.YPR[2]);
    // display.setCursor(64, 20);
    // display.setTextColor(WHITE);
    // display.print("S:");
    // display.print(Stepper_left.getSpeed());

    display.display();

    HAL_Delay(5);
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
long random(long howbig)
{
  if (howbig == 0)
  {
    return 0;
  }

  return random() % howbig;
}

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig)
  {
    return howsmall;
  }

  long diff = howbig - howsmall;

  return random(diff) + howsmall;
}

#define XPOS 0 // Indexes into the 'icons' array in function below
#define YPOS 1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h)
{
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for (f = 0; f < NUMFLAKES; f++)
  {
    icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS] = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
  }

  for (;;)
  {                         // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for (f = 0; f < NUMFLAKES; f++)
    {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, 1);
    }

    display.display(); // Show the display buffer on the screen
    HAL_Delay(200);    // Pause for 1/10 second

    // Then update coordinates of each flake...
    for (f = 0; f < NUMFLAKES; f++)
    {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height())
      {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS] = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  // Disable interrupts here

  // Check for overrun
  if (OverrunFlag)
  {
    rtmSetErrorStatus(untitled2_Obj.getRTM(), "Overrun");
    return;
  }

  OverrunFlag = true;

  // Save FPU context here (if necessary)
  // Re-enable timer or interrupt here
  // Set model inputs here

  // Step the model for base rate
  untitled2_Obj.step();

  // Get model outputs here

  // Indicate task complete
  OverrunFlag = false;

  // Disable interrupts here
  // Restore FPU context here (if necessary)
  // Enable interrupts here
}

void OneStep()
{
  untitled2ModelClass::ExtU_untitled2_T INPUT = {hc08.getTarget_Angle(),
                                                 gy25.getPitch(),
                                                 hc08.getKp(),
                                                 hc08.getKi(),
                                                 hc08.getKd()};

  untitled2_Obj.setExternalInputs(&INPUT);

  rt_OneStep();

  untitled2ModelClass::ExtY_untitled2_T OUTPUT = untitled2_Obj.getExternalOutputs();

  Stepper_right.setSpeed(OUTPUT.Stepper_Speed);
  Stepper_left.setSpeed(OUTPUT.Stepper_Speed);
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

#ifdef USE_FULL_ASSERT
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
