/*
 * APP.c
 *
 *  Created on: Jan 26, 2024
 *      Author: mohammedhamdy32
 */


#include "std_types.h"
#include "common_macros.h"
#include "delay.h"

#include "queue.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "ADC_interface.h"
#include "USART_interface.h"
#include "APP.h"




static void APP_SystickCallBackFun(void)
{
	u16 gsr_reading = ADC_u16ReadChannel(GSR_PIN_NUM);
	Queue_data_t q_data = { gsr_reading , 0 };
	enqueue( &q_data );

}

void APP_Init()
{
	/***** Initializations *****/
	Queue_init();

	/* RCC */
	RCC_voidInitSysCls();
	RCC_voidEnablePerpheralClk( AHB1 , GPIOA_ID );
	RCC_voidEnablePerpheralClk( AHB1 , GPIOB_ID );
	RCC_voidEnablePerpheralClk(APB2  , ADC_ID ); /* ADC */


	/* ADC configuration and initialization */
	GPIO_PIN_CONFIG_T gpio_config = { GSR_PORT_NUM , GSR_PIN_NUM , GPIO_ANALOG_MODE , NO_PULL , 0 , 0 , 0 };
	GPIO_voidInti( &gpio_config );
	ADC_ConfigType adcConfig = {TWELVE_BIT, 0 , 0 , 0 , PCLK2_8};
	ADC_vInit(&adcConfig);

	/* USART */
	USART_config uart_config = { USART1_NUM , ONE_BIT , DISABLE_PARITY , BIT8_WORD , OVERSAMPLING_16 , 9600 };
	USART_voidInit( &uart_config );
	USART_sendWord( USART1_NUM , ' ');

	/* Systick */
	SYSTICK_voidInit();

	/* Pass call back function to systick */
	SYSTICK_voidSetIntervalNumber( (2000000.0)/GSR_SAMPLING_RATE_HZ , INFINITY_TIMES , APP_SystickCallBackFun );

}


void APP_send_data( QUEUE_DATATYPE *a_data , u16 a_size )
{
	u8 numInAsci[16];

	for(u16 i=0; i <a_size ; i++)
	{
	   itoa( a_data[i].GSR_reading , numInAsci , 10);
	   USART_sendString( USART1_NUM , numInAsci );
	   USART_sendWord( USART1_NUM , '\n' );
	   delay_ms(5);
	}


}

