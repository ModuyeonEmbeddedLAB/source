/**
  ******************************************************************************
  * File Name          : uart_debug.h
  * Description        : 
  ******************************************************************************
  *
**/

#ifndef __UART_DEBUG__
#define __UART_DEBUG__

#define UART_DEBUG_PORT_BAUDRATE_9600                    9600
#define UART_DEBUG_PORT_BAUDRATE_19200                   19200
#define UART_DEBUG_PORT_BAUDRATE_38400                   38400
#define UART_DEBUG_PORT_BAUDRATE_57600                   57600
#define UART_DEBUG_PORT_BAUDRATE_115200                  115200

typedef enum
{
   UART_DEBUG_USART1_PA9_PA10                            = 0,
   UART_DEBUG_USART1_PB6_PB7,
   UART_DEBUG_USART2_PA2_PA3,
   UART_DEBUG_USART2_PD5_PD6,
   UART_DEBUG_USART3_PB10_PB11,
   UART_DEBUG_USART3_PC10_PC11,
   UART_DEBUG_USART3_PD8_PD9,
   UART_DEBUG_UART4_PA0_PA1,
   UART_DEBUG_UART4_PC10_PC11,
   UART_DEBUG_UART5_PC12_PD2,
   UART_DEBUG_USART6_PC6_PC7,
} ENUM_UART_DEBUG_PORT;

typedef enum
{
   UART_DEBUG_NOT_INITIALIZE                             = -1,
   UART_DEBUG_INITIALIZE                                 = 0,
   UART_DEBUG_READY                                      = 1,
} ENUM_UART_STATUS;

typedef enum
{
   UART_DEBUG_NONE_ERROR                                 = 0,
   UART_DEBUG_WRONG_PARAMETER                            = -1,
   UART_DEBUG_NOT_SUPPORTED_BAUDRATE                     = -2,
   UART_DEBUG_UART_INIT_FAILED                           = -3,
} ENUM_UART_DEBUG_ERROR_CODE;


ENUM_UART_DEBUG_ERROR_CODE Uart_Debug_Init(ENUM_UART_DEBUG_PORT port_index, unsigned int baudrate);

#endif      // __UART_DEBUG__

