/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "uart_debug.h"
#include "debug_string.h"

static unsigned int MODULE_DEBUG_LEVEL                   = DEBUG_STRING_LEVEL_ERROR    |
                                                           DEBUG_STRING_LEVEL_WARN     |
                                                           DEBUG_STRING_LEVEL_DEBUG    |
                                                           DEBUG_STRING_LEVEL_INFO1    |
                                                           DEBUG_STRING_LEVEL_INFO2    |
                                                           DEBUG_STRING_LEVEL_INFO3    |
                                                           DEBUG_STRING_LEVEL_INFO4;

void SystemClock_Config(void);
void Error_Handler(void);

int main(void)
{
   /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
   HAL_Init();

   /* Configure the system clock */
   SystemClock_Config();

   /* Initialize all configured peripherals */
   if (Uart_Debug_Init(UART_DEBUG_USART2_PA2_PA3, UART_DEBUG_PORT_BAUDRATE_115200) != UART_DEBUG_NONE_ERROR)
   {
   }

   debug_output_str_info1(" \r\n");
   debug_output_str_info1("******************************************************************************** \r\n");
   debug_output_str_info1(" UART Debug Test Program ver 1.0 \r\n");
   debug_output_str_info1("******************************************************************************** \r\n");
   debug_output_str_info1(" \r\n");
   debug_output_str_info1(" System(Core) Clock    : %d MHz \r\n", HAL_RCC_GetSysClockFreq() / 1000000);
   debug_output_str_info1(" HCLK                  : %d MHz \r\n", HAL_RCC_GetHCLKFreq() / 1000000);
   debug_output_str_info1(" PCLK1                 : %d MHz \r\n", HAL_RCC_GetPCLK1Freq() / 1000000);
   debug_output_str_info1(" PCLK2                 : %d MHz \r\n", HAL_RCC_GetPCLK2Freq() / 1000000);
   debug_output_str_info1(" \r\n");
   debug_output_str_info1("******************************************************************************** \r\n");

   while (1)
   {

   }
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
   __HAL_RCC_PWR_CLK_ENABLE();

   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
   RCC_OscInitStruct.OscillatorType                      = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSIState                            = RCC_HSI_ON;
   RCC_OscInitStruct.HSICalibrationValue                 = 16;
   RCC_OscInitStruct.PLL.PLLState                        = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource                       = RCC_PLLSOURCE_HSI;
   RCC_OscInitStruct.PLL.PLLM                            = 8;
   RCC_OscInitStruct.PLL.PLLN                            = 168;
   RCC_OscInitStruct.PLL.PLLP                            = RCC_PLLP_DIV2;
   RCC_OscInitStruct.PLL.PLLQ                            = 4;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      Error_Handler();
   }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
   RCC_ClkInitStruct.ClockType                           = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK    |
                                                           RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource                        = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider                       = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider                      = RCC_HCLK_DIV4;
   RCC_ClkInitStruct.APB2CLKDivider                      = RCC_HCLK_DIV2;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
   {
      Error_Handler();
   }

    /**Configure the Systick interrupt time 
    */
   HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
   HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

   /* SysTick_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
   /* USER CODE BEGIN Error_Handler */
   /* User can add his own implementation to report the HAL error return state */
   while(1) 
   {
   }
   /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
   /* USER CODE BEGIN 6 */
   /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
   /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/