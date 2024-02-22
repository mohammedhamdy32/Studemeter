/*
 * SYSTICK_program.c
 *
 *  Created on: Oct 1, 2023
 *      Author: mohammedhamdy32
 */

#include "std_types.h"
#include "common_macros.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_config.h"
#include "SYSTICK_private.h"

static volatile void (*g_callBackFun) (void) = NULL;
s32 g_state;

void SYSTICK_voidInit(void)
{

#if ( SYSTICK_CLOCK == AHB_DIV_8 )
	CLEAR_BIT( STK_CTRL , CLKSOURCE );
#else
	SET_BIT( STK_CTRL , CLKSOURCE );
#endif


}

void SYSTICK_voidDisable(void)
{
	CLEAR_BIT( STK_CTRL , ENABLE );  /* Disable timer */
	CLEAR_BIT( STK_CTRL , TICKINT ); /* Disable exception  */
	STK_VAL  = 0; /* Make it count from zero */
	STK_LOAD = 0;
}

void SYSTICK_voidBussyWaitDelay(u32 a_number_of_delay_ticks)
{
	STK_LOAD = a_number_of_delay_ticks; /* Put the number of ticks in reload value */
	SET_BIT( STK_CTRL , ENABLE ); /* Enable timer */

	while( GET_BIT( STK_CTRL , COUNTFLAG ) != 1 ); /* Make polling till it finish counting */

	CLEAR_BIT( STK_CTRL , ENABLE ); /* Disable timer */

}

void SYSTICK_voidSetIntervalSingle( u32 a_number_of_delay_ticks , void (*a_callBackFun)(void) )
{
	STK_LOAD = a_number_of_delay_ticks; /* Put the number of ticks in reload value */
	g_callBackFun = a_callBackFun;  /* Put call back function */
	g_state = 1;
	SET_BIT( STK_CTRL , TICKINT );  /* Open exception */
	SET_BIT( STK_CTRL , ENABLE ); /* Enable timer */
}

void SYSTICK_voidSetIntervalNumber( u32 a_number_of_delay_ticks , s32 a_number_of_intervals , void (*a_callBackFun)(void) )
{
	STK_LOAD = a_number_of_delay_ticks; /* Put the number of ticks in reload value */
	g_callBackFun = a_callBackFun;  /* Put call back function */
	g_state = a_number_of_intervals ;
	SET_BIT( STK_CTRL , TICKINT );  /* Open exception */
	SET_BIT( STK_CTRL , ENABLE );   /* Enable timer */
}


void STK_voidSetIntervalPeriodic( u32 a_number_of_delay_ticks , void (*a_callBackFun)(void) )
{
	STK_LOAD = a_number_of_delay_ticks; /* Put the number of ticks in reload value */
	g_callBackFun = a_callBackFun;  /* Put call back function */
	g_state = -1;
	SET_BIT( STK_CTRL , TICKINT );  /* Open exception */
	SET_BIT( STK_CTRL , ENABLE ); /* Enable timer */
}

u32 SYSTICK_voidGetRemainingTicks(void)
{
	return STK_VAL;
}


/* ISR of SYSTICK */
void SysTick_Handler(void)
{
	if( g_callBackFun != NULL )
	{
		if( g_state == 1 )
		{
			SYSTICK_voidDisable(); /* Disable timer */
			g_callBackFun();
		}else if( g_state > 1 )
		{
			g_callBackFun();
			g_state--;
		}else
		{
			g_callBackFun();
		}
	}

}


