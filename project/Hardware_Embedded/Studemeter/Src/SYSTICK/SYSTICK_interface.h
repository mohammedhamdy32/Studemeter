/*
 * SYSTICK_interface.h
 *
 *  Created on: Oct 1, 2023
 *      Author: mohammedhamdy32
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

#define INFINITY_TIMES   -1


void SYSTICK_voidInit(void);
void SYSTICK_voidDisable(void);
void SYSTICK_voidBussyWaitDelay(u32 a_number_of_delay_ticks);
void SYSTICK_voidSetIntervalSingle( u32 a_number_of_delay_ticks , void (*a_callBackFun)(void) );
void SYSTICK_voidSetIntervalNumber( u32 a_number_of_delay_ticks , s32 a_number_of_intervals , void (*a_callBackFun)(void) );
void STK_voidSetIntervalPeriodic( u32 a_number_of_delay_ticks , void (*a_callBackFun)(void) );
u32 SYSTICK_voidGetRemainingTicks(void);








#endif /* SYSTICK_INTERFACE_H_ */
