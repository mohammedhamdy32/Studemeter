/*
 * USART_private.h
 *
 *  Created on: Nov 28, 2023
 *      Author: mohammedhamdy32
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

typedef struct{
	volatile u32 USART_SR  ;
	volatile u32 USART_DR  ;
	volatile u32 USART_BRR ;
	volatile u32 USART_CR1 ;
	volatile u32 USART_CR2 ;
	volatile u32 USART_CR3 ;
	volatile u32 USART_GTPR;

}USART_t;

#define USART1 			((volatile USART_t*)(0x40011000))
#define USART6 			((volatile USART_t*)(0x40011400))
#define USART2 			((volatile USART_t*)(0x40004400))

#endif /* USART_PRIVATE_H_ */
