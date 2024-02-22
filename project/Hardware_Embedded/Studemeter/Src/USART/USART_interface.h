/*
 * USART_interface.h
 *
 *  Created on: Nov 28, 2023
 *      Author: mohammedhamdy32
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#define DIV_Mantissa 4


/*** enums ***/

typedef enum{
	USART1_NUM , USART2_NUM , USART6_NUM
}USART_NUMBER;

typedef enum{
	HALF_BIT , ONE_BIT, ONE_AND_HALF_BIT , TWO_BITS
}USART_stop_bit;

typedef enum{
	DISABLE_PARITY , EVEN_PARITY , ODD_PARITY
}USART_parity_bit;

typedef enum{
	BIT8_WORD , BIT9_WORD
}USART_word_size;

typedef enum{
	OVERSAMPLING_16 , OVERSAMPLING_8
}USART_OVER_SAMPLING_MODE;


/*** struct ***/
typedef struct{

	USART_NUMBER     usart_numb;
	USART_stop_bit   stop_bit;
	USART_parity_bit parity_bit;
	USART_word_size  word_size;
	USART_OVER_SAMPLING_MODE over_sampling;

	u32 baudrate;

}USART_config;

/*** Function Prototypes ***/

void   USART_voidInit( USART_config *a_config );
void USART_sendWord( USART_NUMBER usart_num, u16 a_data );
void USART_receiveWord( USART_NUMBER usart_num , u16 *a_data );
void USART_sendString( USART_NUMBER usart_num , const u8 *a_data );

#endif /* USART_INTERFACE_H_ */
