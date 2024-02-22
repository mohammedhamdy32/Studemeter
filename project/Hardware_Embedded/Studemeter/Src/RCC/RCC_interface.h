/*
 * RCC_interface.h
 *
 *  Created on: Aug 9, 2023
 *      Author: mohammedhamdy32
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

#include "std_types.h"


/* Prototypes */
void RCC_voidInitSysCls(void);
void RCC_voidEnablePerpheralClk(u8 Copy_u8BusId , u8 Copy_u8PerpheralId);
void RCC_voidDisablePerpheralClk(u8 Copy_u8BusId , u8 Copy_u8PerpheralId);


/*define*/
#define  AHB1   0
#define  AHB2   1
#define  APB1   2
#define  APB2   3

#define MAX_BUSE_NUMBER          3
#define MAX_PERIPHERAL_PER_BUS   31

/* Periphrals IDs */
#define GPIOA_ID   0
#define GPIOB_ID   1
#define GPIOC_ID   2
#define ADC_ID     8
#define CRC_ID     12
#define DMA1_ID    21
#define DMA2_ID    22
#define OTGFS_ID   7
#define TIM2_ID    0
#define TIM3_ID    1
#define TIM4_ID    2
#define TIM5_ID    3
#define WWDG_ID    11
#define USART1_ID  4
#define USART2_ID  17
#define USART6_ID  5

#define HSI                 0
#define HSE_CRYSTAL         1
#define HSE_EXTERNAL_CLK    2
#define PLL_HSI             3
#define PLL_HSE             4

#define PLL_MULTIPLICATION_FACTOR_FOR_VCO   432

#define HSION     0
#define HSEON     16
#define HSEBYP    18
#define PLLON     24

#define PLLN      14
#define PLLSRC    22

#define SW0   0
#define SW1   1








#endif /* RCC_PRIVATE_H_ */
