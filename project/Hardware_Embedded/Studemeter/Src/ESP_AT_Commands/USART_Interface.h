/*
  * File:  USART_Interface.h 
 *	SWC:    USART
 *	Version: 1.0 
 *  Created on: 19-06-2023 
 *  Author: Abdallah Ragab 
 */
#ifndef USART_INTERFACE
#define USART_INTERFACE
#include "std_types.h"

void USART_voidInit(void);

void USART_voidSend(u8* Datau8TransData,u16 Copy_u8Length);

void USART_voidReceive(u8* Datau8ReceData);
void UART_recieveString(u8 *str);
u8 USART_voidReceiveWithouStackPolling(u8* Datau8ReceData);


#endif // USART_INTERFACE
