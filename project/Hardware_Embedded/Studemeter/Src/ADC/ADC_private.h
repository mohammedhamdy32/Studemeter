/******************************************************************************	 
*	 
* Module: ADC	 
*	 
* File Name: ADC_private.h	 
*	 
* Description: Header file for the ADC driver private information	 
*	 
* Author: Mohamed Hossam	 
*	 
*******************************************************************************/	 
#ifndef ADC_PRIVATE_H_	 
#define ADC_PRIVATE_H_

#define ADC_BASE_ADDRESS		0x40012000
#define ADC  					((ADC_t *) ADC_BASE_ADDRESS)

#define ADC_CCR					*((volatile u32*) (0x304 + ADC_BASE_ADDRESS))

typedef struct{
	volatile u32 SR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 JOFR[4];
	volatile u32 HTR;
	volatile u32 LTR;
	volatile u32 SQR[3];
	volatile u32 JSQR;
	volatile u32 JDR[4];
	volatile u32 DR;
}ADC_t;

/* ADC_SR register bits */
#define EOC			1

/* ADC_CR1 register bits */
#define EOCIE		5
#define SCAN		8
#define RES 		24

#define RES_MASK	0x03000000

/* ADC_CR2 register bits */
#define ADON		0
#define CONT		1
#define ECOS		10

/* ADC_CCR register bits */
#define ADCPRE 		16
#define SWSTART		30

#define ADCPRE_MASK	0x00030000

/* ADC_SQR1 register bits */
#define L 			20

/* ADC_SQR3 register bits */
#define SQ1		0

#endif
