/**
  ******************************************************************************
  * File Name          : uart_debug.c
  * Description        : 
  ******************************************************************************
  *
  *
  * STM32F407VGTx : UART4, UART5, USART1, USART2, USART3, USART6
  *
  * UART4
  *   UART4_TX  : PA0
  *   UART4_RX  : PA1
  *
  * USART2
  *   USART2_TX : PA2
  *   USART2_RX : PA3
  *
  * USART1
  *   USART1_TX : PA9
  *   USART2_RX : PA10
  *
  * USART1
  *   USART1_TX : PB6
  *   USART1_RX : PB7
  *
  * USART3
  *   USART3_TX : PB10
  *   USART3_RX : PB11
  *
  * USART6
  *   USART6_TX : PC6
  *   USART6_RX : PC7
  *
  * USART3
  *   USART3_TX : PC10
  *   USART3_RX : PC11
  *
  * UART4
  *   UART4_TX  : PC10
  *   UART4_RX  : PC11
  *
  * UART5
  *   UART5_TX  : PC12
  *   UART5_RX  : PD2
  *
  * USART2
  *   USART2_TX : PD5
  *   USART2_RX : PD6
  *
  * USART3
  *   USART3_TX : PD8
  *   USART3_RX : PD9
  *
  ******************************************************************************
  */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "uart_debug.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
  set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

typedef struct
{
   __IO ENUM_UART_STATUS Status;

   GPIO_TypeDef *pGPIO_Type_Uart_tx;
   GPIO_TypeDef *pGPIO_Type_Uart_rx;
   GPIO_InitTypeDef GPIO_InitStruct_Uart_Tx_Pin;
   GPIO_InitTypeDef GPIO_InitStruct_Uart_Rx_Pin;

   UART_HandleTypeDef UartHandle;
   IRQn_Type uart_irq_type;

} UART_DEBUG_STRUCT;
UART_DEBUG_STRUCT g_Uart_Debug_Struct               = {UART_DEBUG_NOT_INITIALIZE, };


ENUM_UART_DEBUG_ERROR_CODE Uart_Debug_Init(ENUM_UART_DEBUG_PORT port_index, unsigned int baudrate)
{
   g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Mode  = GPIO_MODE_AF_PP;
   g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pull  = GPIO_NOPULL;
   g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

   g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Mode  = GPIO_MODE_AF_PP;
   g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pull  = GPIO_NOPULL;
   g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

   if ((baudrate == UART_DEBUG_PORT_BAUDRATE_9600      ||
        baudrate == UART_DEBUG_PORT_BAUDRATE_19200     ||
        baudrate == UART_DEBUG_PORT_BAUDRATE_38400     ||
        baudrate == UART_DEBUG_PORT_BAUDRATE_57600     ||
        baudrate ==  UART_DEBUG_PORT_BAUDRATE_115200) == 0)
   {
      return UART_DEBUG_NOT_SUPPORTED_BAUDRATE;
   }

   switch(port_index)
   {
      case UART_DEBUG_USART1_PA9_PA10 :
         __HAL_RCC_GPIOA_CLK_ENABLE();
         __HAL_RCC_USART1_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                               = GPIOA;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                  = GPIO_PIN_9;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate            = GPIO_AF7_USART1;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                               = GPIOA; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                  = GPIO_PIN_10;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate            = GPIO_AF7_USART1;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART1;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART1_IRQn;
         break;

      case UART_DEBUG_USART1_PB6_PB7 :
         __HAL_RCC_GPIOB_CLK_ENABLE();
         __HAL_RCC_USART1_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOB;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_6;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF7_USART1;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOB; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_7;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF7_USART1;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART1;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART1_IRQn;
         break;

      case UART_DEBUG_USART2_PA2_PA3 :
         __HAL_RCC_GPIOA_CLK_ENABLE();
         __HAL_RCC_USART2_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOA;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_2;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF7_USART2;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOA; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_3;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF7_USART2;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART2;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART2_IRQn;
         break;

      case UART_DEBUG_USART2_PD5_PD6 :
         __HAL_RCC_GPIOD_CLK_ENABLE();
         __HAL_RCC_USART2_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOD;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_5;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF7_USART2;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOD; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_6;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF7_USART2;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART2;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART2_IRQn;
         break;

      case UART_DEBUG_USART3_PB10_PB11 :
         __HAL_RCC_GPIOB_CLK_ENABLE();
         __HAL_RCC_USART3_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOB;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_10;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF7_USART3;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOB; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_11;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF7_USART3;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART3;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART3_IRQn;
         break;

      case UART_DEBUG_USART3_PC10_PC11 :
         __HAL_RCC_GPIOC_CLK_ENABLE();
         __HAL_RCC_USART3_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOC;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_10;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF7_USART3;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOC; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_11;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF7_USART3;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART3;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART3_IRQn;
         break;

      case UART_DEBUG_USART3_PD8_PD9 :
         __HAL_RCC_GPIOD_CLK_ENABLE();
         __HAL_RCC_USART3_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOD;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_8;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF7_USART3;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOD; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_9;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF7_USART3;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART3;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART3_IRQn;
         break;

      case UART_DEBUG_UART4_PA0_PA1 :
         __HAL_RCC_GPIOA_CLK_ENABLE();
         __HAL_RCC_UART4_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOA;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_0;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF8_UART4;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOA; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_1;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF8_UART4;

         g_Uart_Debug_Struct.UartHandle.Instance                              = UART4;
         g_Uart_Debug_Struct.uart_irq_type                                    = UART4_IRQn;
         break;

      case UART_DEBUG_UART4_PC10_PC11 :
         __HAL_RCC_GPIOC_CLK_ENABLE();
         __HAL_RCC_UART4_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOC;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_10;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF8_UART4;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOC; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_11;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF8_UART4;

         g_Uart_Debug_Struct.UartHandle.Instance                              = UART4;
         g_Uart_Debug_Struct.uart_irq_type                                    = UART4_IRQn;
         break;

      case UART_DEBUG_UART5_PC12_PD2 :
         __HAL_RCC_GPIOC_CLK_ENABLE();
         __HAL_RCC_GPIOD_CLK_ENABLE();
         __HAL_RCC_UART5_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOC;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_12;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF8_UART5;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOD; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_2;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF8_UART5;

         g_Uart_Debug_Struct.UartHandle.Instance                              = UART5;
         g_Uart_Debug_Struct.uart_irq_type                                    = UART5_IRQn;
         break;

      case UART_DEBUG_USART6_PC6_PC7 :
         __HAL_RCC_GPIOC_CLK_ENABLE();
         __HAL_RCC_USART6_CLK_ENABLE();

         g_Uart_Debug_Struct.pGPIO_Type_Uart_tx                              = GPIOC;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Pin                 = GPIO_PIN_6;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin.Alternate           = GPIO_AF8_USART6;

         g_Uart_Debug_Struct.pGPIO_Type_Uart_rx                              = GPIOC; 
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Pin                 = GPIO_PIN_7;
         g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin.Alternate           = GPIO_AF8_USART6;

         g_Uart_Debug_Struct.UartHandle.Instance                              = USART6;
         g_Uart_Debug_Struct.uart_irq_type                                    = USART6_IRQn;
         break;

      default :
         return UART_DEBUG_WRONG_PARAMETER;
   }

   g_Uart_Debug_Struct.UartHandle.Init.BaudRate          = baudrate;
   g_Uart_Debug_Struct.UartHandle.Init.WordLength        = UART_WORDLENGTH_8B;
   g_Uart_Debug_Struct.UartHandle.Init.StopBits          = UART_STOPBITS_1;
   g_Uart_Debug_Struct.UartHandle.Init.Parity            = UART_PARITY_NONE;
   g_Uart_Debug_Struct.UartHandle.Init.Mode              = UART_MODE_TX_RX;
   g_Uart_Debug_Struct.UartHandle.Init.HwFlowCtl         = UART_HWCONTROL_NONE;
   g_Uart_Debug_Struct.UartHandle.Init.OverSampling      = UART_OVERSAMPLING_16;
   if (HAL_UART_Init(&g_Uart_Debug_Struct.UartHandle) != HAL_OK)
   {
      return UART_DEBUG_UART_INIT_FAILED;
   }

   return UART_DEBUG_NONE_ERROR;
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
   HAL_GPIO_Init(g_Uart_Debug_Struct.pGPIO_Type_Uart_tx, &g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Tx_Pin);
   HAL_GPIO_Init(g_Uart_Debug_Struct.pGPIO_Type_Uart_rx, &g_Uart_Debug_Struct.GPIO_InitStruct_Uart_Rx_Pin);

   /*##-3- Configure the NVIC for UART ########################################*/
   /* NVIC for USART1 */
   HAL_NVIC_SetPriority(g_Uart_Debug_Struct.uart_irq_type, 0, 1);
   HAL_NVIC_EnableIRQ(g_Uart_Debug_Struct.uart_irq_type);
}


void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  }
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */

}

#if 0
void USART1_IRQHandler(void)
{
   HAL_UART_IRQHandler(&g_Uart_Debug_Struct.UartHandle);
}

void USART2_IRQHandler(void)
{
   HAL_UART_IRQHandler(&g_Uart_Debug_Struct.UartHandle);
}

void USART3_IRQHandler(void)
{
   HAL_UART_IRQHandler(&g_Uart_Debug_Struct.UartHandle);
}

void UART4_IRQHandler(void)
{
   HAL_UART_IRQHandler(&g_Uart_Debug_Struct.UartHandle);
}

void UART5_IRQHandler(void)
{
   HAL_UART_IRQHandler(&g_Uart_Debug_Struct.UartHandle);
}

void USART6_IRQHandler(void)
{
   HAL_UART_IRQHandler(&g_Uart_Debug_Struct.UartHandle);
}
#endif

#define UARTS_R_TXE                                      0x00000080
#define UART_SR_TC                                       0x00000040
PUTCHAR_PROTOTYPE
{
   int i                                                 = 0;

   while ((g_Uart_Debug_Struct.UartHandle.Instance->SR & UARTS_R_TXE) == 0)
   {
      i++;
      if (i > 0xFFFF)
      {
         break;
      }
   }
   g_Uart_Debug_Struct.UartHandle.Instance->DR           = ch;

   while ((g_Uart_Debug_Struct.UartHandle.Instance->SR & UART_SR_TC) == 0)
   {
      i++;
      if (i > 0xFFFF)
      {
         break;
      }
   }
   return ch;
}


