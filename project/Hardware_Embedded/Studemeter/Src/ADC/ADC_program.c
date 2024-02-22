/******************************************************************************	 
*	 
* Module: ADC	 
*	 
* File Name: ADC_program.c	 
*	 
* Description: Source file for the ADC driver	 
*	 
* Author: Mohamed Hossam	 
*	 
*******************************************************************************/	 
#include"std_types.h"
#include"ADC_private.h"
#include"ADC_config.h"
#include"ADC_interface.h"	 



#ifdef ENABLE_INTERRUPT
static void (*g_callBack) (void);

void ADC_IRQHandler()
{
	(*g_callBack)();
}
#endif

void ADC_vSetSequence(u8* Ptr_u8Arr, u8 Copy_u8Size)
{
	if(Copy_u8Size < 17 && NULL != Ptr_u8Arr)
	{
		u8 i;
		ADC->SQR[0] = ((Copy_u8Size - 1u) << L);
		ADC->SQR[1] = 0;
		ADC->SQR[2] = 0;
		for(i=0; i<6 && i<Copy_u8Size; i++)
		{
			ADC->SQR[2] |= (Ptr_u8Arr[i] << (i * 5));
		}
		for(; i<12 && i<Copy_u8Size; i++)
		{
			ADC->SQR[1] |= (Ptr_u8Arr[i] << ((i % 6) * 5));
		}
		for(; i<16 && i<Copy_u8Size; i++)
		{
			ADC->SQR[0] |= (Ptr_u8Arr[i] << ((i % 6) * 5));
		}
	}
}

void ADC_vInit(const ADC_ConfigType* Ptr_config)
{
	if(NULL != Ptr_config)
	{
		/* Choose resolution and set scan mode */
		ADC->CR1 = (Ptr_config->res << RES) | (Ptr_config->scanMode << SCAN);
		/* Set clock Prescaler for ADC */
		ADC_CCR = (ADC_CCR & ~ADCPRE_MASK) | ((Ptr_config->prescaler << ADCPRE) & ADCPRE_MASK);
		/* configure End of conversion selection and continuous mode and Enable ADC  */
		ADC->CR2 = (Ptr_config->eachConvFlag << ECOS) | (Ptr_config->contConv << CONT) | (1 << ADON);
#ifdef ENABLE_INTERRUPT
		ADC->CR1 |= (1 << EOCIE);
#endif
	}
}


void ADC_vStartConversion()
{
	ADC->CR2 |= (1 << SWSTART);
}


#ifdef ENABLE_INTERRUPT
void ADC_vSetCallBack(void (*Ptr_func) (void))
{
	g_callBack = Ptr_func;
}

u16 ADC_u16Read()
{
	return ADC->DR;
}

#else

u16 ADC_u16Read()
{
	while(!(ADC->SR & (1 << EOC)));
	return ADC->DR;
}

u16 ADC_u16ReadChannel(u8 Copy_u8Channel)
{
	/* Select Channel */
	ADC->SQR[2] = (ADC->SQR[2] & 0xFFFFFFE0) | Copy_u8Channel;
	/* Start Conversion */
	ADC->CR2 |= (1 << SWSTART);
	/* Wait till conversion is done */
	while(!(ADC->SR & (1 << EOC)));
	/* Return ADC reading which also clears EOC flag */
	return ADC->DR;
}
#endif
