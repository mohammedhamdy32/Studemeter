/*
 * USART_program.c
 *
 *  Created on: Nov 28, 2023
 *      Author: mohammedhamdy32
 */

#include "std_types.h"
#include "common_macros.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"

void USART_voidInit( USART_config *a_config )
{

	u16 mantisa , div;
	switch( a_config->usart_numb )
	{
	case USART1_NUM:

		RCC_voidEnablePerpheralClk( APB2 ,  USART1_ID );
		RCC_voidEnablePerpheralClk(AHB1 , GPIOA_ID);

		/* Configare GPIO pins */
		GPIO_PIN_CONFIG_T gpio_cofig = { PORTA_ID , PIN9_ID , GPIO_ALTERNATIVE_FUNCTION , NO_PULL , NONE , NONE , AF7 };
		GPIO_voidInti( &gpio_cofig ); /* For TX pin (PIN 9) */
		gpio_cofig.pin_id = PIN10_ID;
		GPIO_voidInti( &gpio_cofig ); /* For RX pin (PIN 10) */


		/* For oversampling */
		PUT_VALUE_IN_BIT( USART1->USART_CR1 , 15 , a_config->over_sampling );
		PUT_VALUE_IN_BIT( USART1->USART_CR1 , 12 , a_config->word_size );
		PUT_VALUE_IN_BIT( USART1->USART_CR1 , 10 , a_config->parity_bit ); /* Enable or Disable parity bit */
		PUT_VALUE_IN_BIT( USART1->USART_CR1 , 9  , a_config->parity_bit ); /* EVEN OR ODD */
		USART1->USART_CR2 = ( (USART1->USART_CR2)&(0xFFFFCFFF) ) | ( (a_config->stop_bit)<<12 ); /* Stop bit */

		mantisa = ( (F_CK / (a_config->baudrate * 16)) );
		div = ( ( (F_CK / (a_config->baudrate * 16.0)) )*1.0 - mantisa*1.0 ) * 16;

		USART1->USART_BRR = div ;
		USART1->USART_BRR = ( (USART1->USART_BRR)&0x000F ) | ( mantisa << 4 ) ;


		SET_BIT( USART1->USART_CR1 , 3 ); /* EANBLE Transmitter */
		SET_BIT( USART1->USART_CR1 , 2 ); /* EANBLE Receiver */
		SET_BIT( USART1->USART_CR1 , 13 ); /* EANBLE USART */

		break;

	case USART2_NUM:

		RCC_voidEnablePerpheralClk( APB1 ,  USART2_ID );
		RCC_voidEnablePerpheralClk( AHB1 , GPIOA_ID);

		/* Configare GPIO pins */
		GPIO_PIN_CONFIG_T gpio_cofig2 = { PORTA_ID , PIN2_ID , GPIO_ALTERNATIVE_FUNCTION , NO_PULL , NONE , NONE , AF7 };
		GPIO_voidInti( &gpio_cofig2 ); /* For TX pin (PIN 9) */
		gpio_cofig2.pin_id = PIN3_ID;
		GPIO_voidInti( &gpio_cofig2 ); /* For RX pin (PIN 10) */


		/* For oversampling */
		PUT_VALUE_IN_BIT( USART2->USART_CR1 , 15 , a_config->over_sampling );
		PUT_VALUE_IN_BIT( USART2->USART_CR1 , 12 , a_config->word_size );
		PUT_VALUE_IN_BIT( USART2->USART_CR1 , 10 , a_config->parity_bit ); /* Enable or Disable parity bit */
		PUT_VALUE_IN_BIT( USART2->USART_CR1 , 9  , a_config->parity_bit ); /* EVEN OR ODD */
		USART2->USART_CR2 = ( (USART2->USART_CR2)&(0xFFFFCFFF) ) | ( (a_config->stop_bit)<<12 ); /* Stop bit */

		mantisa = ( (F_CK / (a_config->baudrate * 16)) );
		div = ( ( (F_CK / (a_config->baudrate * 16.0)) )*1.0 - mantisa*1.0 ) * 16;

		USART2->USART_BRR = div ;
		USART2->USART_BRR = ( (USART2->USART_BRR)&0x000F ) | ( mantisa << 4 ) ;


		SET_BIT( USART2->USART_CR1 , 3 ); /* EANBLE Transmitter */
		SET_BIT( USART2->USART_CR1 , 2 ); /* EANBLE Receiver */
		SET_BIT( USART2->USART_CR1 , 13 ); /* EANBLE USART */

		break;


	case USART6_NUM:

		RCC_voidEnablePerpheralClk( APB2 ,  USART6_ID );
		RCC_voidEnablePerpheralClk( AHB1 , GPIOA_ID);

		/* Configare GPIO pins */
		GPIO_PIN_CONFIG_T gpio_cofig3 = { PORTA_ID , PIN11_ID , GPIO_ALTERNATIVE_FUNCTION , NO_PULL , NONE , NONE , AF8 };
		GPIO_voidInti( &gpio_cofig3 ); /* For TX pin (PIN 9) */
		gpio_cofig3.pin_id = PIN12_ID;
		GPIO_voidInti( &gpio_cofig3 ); /* For RX pin (PIN 10) */


		/* For oversampling */
		PUT_VALUE_IN_BIT( USART6->USART_CR1 , 15 , a_config->over_sampling );
		PUT_VALUE_IN_BIT( USART6->USART_CR1 , 12 , a_config->word_size );
		PUT_VALUE_IN_BIT( USART6->USART_CR1 , 10 , a_config->parity_bit ); /* Enable or Disable parity bit */
		PUT_VALUE_IN_BIT( USART6->USART_CR1 , 9  , a_config->parity_bit ); /* EVEN OR ODD */
		USART6->USART_CR2 = ( (USART6->USART_CR2)&(0xFFFFCFFF) ) | ( (a_config->stop_bit)<<12 ); /* Stop bit */

		mantisa = ( (F_CK / (a_config->baudrate * 16)) );
		div = ( ( (F_CK / (a_config->baudrate * 16.0)) )*1.0 - mantisa*1.0 ) * 16;

		USART6->USART_BRR = div ;
		USART6->USART_BRR = ( (USART6->USART_BRR)&0x000F ) | ( mantisa << 4 ) ;


		SET_BIT( USART6->USART_CR1 , 3 ); /* EANBLE Transmitter */
		SET_BIT( USART6->USART_CR1 , 2 ); /* EANBLE Receiver */
		SET_BIT( USART6->USART_CR1 , 13 ); /* EANBLE USART */

		break;

	}

}


void USART_sendWord( USART_NUMBER usart_num, u16 a_data )
{
	switch( usart_num )
	{
	case USART1_NUM:
		USART1->USART_DR = ( (USART1->USART_DR)&0xFFFFFE00 ) | ( a_data & 0x000001FF ) ;
		while( ! GET_BIT( USART1->USART_SR , 6 ) );
		break;

	case USART2_NUM:
		USART2->USART_DR = ( (USART2->USART_DR)&0xFFFFFE00 ) | ( a_data & 0x000001FF ) ;
		while( ! GET_BIT( USART2->USART_SR , 6 ) );
		break;
	case USART6_NUM:
		USART6->USART_DR = ( (USART6->USART_DR)&0xFFFFFE00 ) | ( a_data & 0x000001FF ) ;
		while( ! GET_BIT( USART6->USART_SR , 6 ) );
		break;
	}


}


void USART_receiveWord( USART_NUMBER usart_num , u16 *a_data )
{
	switch( usart_num )
	{
	case USART1_NUM:
		while( ! GET_BIT( USART1->USART_SR , 5 ) );
		*a_data = (u16)(USART1->USART_DR) ;
		break;

	case USART2_NUM:
		while( ! GET_BIT( USART2->USART_SR , 5 ) );
		*a_data = (u16)(USART2->USART_DR) ;
		break;
	case USART6_NUM:
		while( ! GET_BIT( USART6->USART_SR , 5 ) );
		*a_data = (u16)(USART6->USART_DR) ;
		break;
	}

}

void USART_sendString( USART_NUMBER usart_num , const u8 *a_data )
{
	u16 i=0;
	while( a_data[i] != '\0' )
	{
		USART_sendWord( usart_num , a_data[i] );
		i++;
	}
}









