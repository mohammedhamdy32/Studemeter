/*
 * GPIO_private.h
 *
 *  Created on: Aug 10, 2023
 *  Author: mohammedhamdy32
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_


#define GPIOA_BASE_ADDRESS    0x40020000
#define GPIOB_BASE_ADDRESS    0x40020400
#define GPIOC_BASE_ADDRESS    0x40020800


typedef struct {
    
u32 MODER  ;
u32 OTYPER ;
u32 OSPEEDR;
u32 PUPDR  ;
u32 IDR    ;
u32 ODR    ;
u32 BSRR   ;
u32 LCKR   ;
u32 AFR[2] ;
	
}GPIO_MemMap_t;


#define GPIOA ( ( volatile GPIO_MemMap_t *)  (GPIOA_BASE_ADDRESS) )
#define GPIOB ( ( volatile GPIO_MemMap_t *)  (GPIOB_BASE_ADDRESS) )
#define GPIOC ( ( volatile GPIO_MemMap_t *)  (GPIOC_BASE_ADDRESS) )


#endif /* RCC_CONFIG_H_ */

