/*
 * File:  USART_Program.c
 *	SWC:    USART
 *	Version: 1.0 
 *  Created on: 19-06-2023 
 *  Author: Abdallah Ragab 
 */
#include "std_types.h"
#include "common_macros.h"
#include "USART_Interface.h"
#include "USART_Private.h"
#include "USART_Config.h"

#define SystemCoreClock  25000000

void USART_voidInit(void){
	/*1- Enable Rx*/
	SET_BIT(USART1->USART_CR1,3);
	SET_BIT(USART1->USART_CR1,2); /* Enable TX */
	/*USART1 is connected to APB2,8MHZ*/
	USART1->USART_BRR=139;
	/*USART1 is connected to APB2,8MHZ*/
	SET_BIT(USART1->USART_CR1,13);




}

void USART_voidSend(u8* Datau8TransData,u16 Copy_u8Length){
	u16 local_u8Counter=0;
	while(local_u8Counter<Copy_u8Length){
		for(u16 i=0 ; i<5000 ; i++ ){}
		USART1->USART_DR = Datau8TransData[local_u8Counter];
		local_u8Counter++;
		while( GET_BIT(USART1->USART_SR,6) == 0 );

	}

}

void USART_voidReceive(u8* Datau8ReceData)
{
	while(GET_BIT(USART1->USART_SR,5)==0);
	*Datau8ReceData=USART1->USART_DR;
}

u8 USART_voidReceiveWithouStackPolling(u8* Datau8ReceData)
{
	if( GET_BIT(USART1->USART_SR,5) == 1 )
	{
  	   *Datau8ReceData=USART1->USART_DR;
		return 1;
	}else
	{
		return 0;
	}
}



