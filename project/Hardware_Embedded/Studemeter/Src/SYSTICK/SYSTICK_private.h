/*
 * SYSTICK_private.h
 *
 *  Created on: Oct 1, 2023
 *      Author: mohammedhamdy32
 */

#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_

/* Registers */
#define STK_CTRL		*((volatile u32*)0xE000E010)
#define STK_LOAD		*((volatile u32*)0xE000E014)
#define STK_VAL		    *((volatile u32*)0xE000E018)
#define STK_CALIB 		*((volatile u32*)0xE000E01C)


/* Bits */
#define  COUNTFLAG     16   /* Return 1 if the timer counted to 0 */
#define  CLKSOURCE     2    /* To choose between AHB/8 or AHB(processor clock) */
#define  TICKINT       1    /* Enable systick exception request */
#define  ENABLE        0    /* Enable timer */


#endif /* SYSTICK_PRIVATE_H_ */
