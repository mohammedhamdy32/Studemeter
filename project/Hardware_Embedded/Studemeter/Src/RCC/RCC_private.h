/*
 * RCC_private.h
 *
 *  Created on: Aug 9, 2023
 *      Author: mohammedhamdy32
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#include "std_types.h"


/* Bass address of RCC 0x40023800 */
#define RCC_CR                   (*( (volatile u32*) (0x40023800) ) )
#define RCC_PLLCFGR              (*( (volatile u32*) (0x40023804) ) )
#define RCC_CFGR                 (*( (volatile u32*) (0x40023808) ) )
#define RCC_CIR                  (*( (volatile u32*) (0x4002380C) ) )
#define RCC_AHB1RSTR             (*( (volatile u32*) (0x40023810) ) )
#define RCC_AHB2RSTR             (*( (volatile u32*) (0x40023814) ) )
#define RCC_APB2RSTR             (*( (volatile u32*) (0x40023824) ) )

#define RCC_AHB1ENR              (*( (volatile u32*) (0x40023830) ) )
#define RCC_AHB2ENR              (*( (volatile u32*) (0x40023834) ) )
#define RCC_APB1ENR              (*( (volatile u32*) (0x40023840) ) )
#define RCC_APB2ENR              (*( (volatile u32*) (0x40023844) ) )
#define RCC_AHB1LPENR            (*( (volatile u32*) (0x40023850) ) )
#define RCC_APB1LPENR            (*( (volatile u32*) (0x40023860) ) )




#endif /* RCC_PRIVATE_H_ */
