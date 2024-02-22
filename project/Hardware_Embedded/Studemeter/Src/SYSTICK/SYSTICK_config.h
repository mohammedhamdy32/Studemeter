/*
 * SYSTICK_config.h
 *
 *  Created on: Oct 8, 2023
 *      Author: mohammedhamdy32
 */

#ifndef SYSTICK_CONFIG_H_
#define SYSTICK_CONFIG_H_


#define AHB_DIV_8      0
#define AHB            1

/*
 * if MC_clk = 16MHZ  ==> if AHB then 16M ticks equal 1 sec
 *                        if AHB/8 then 2M thicks equal 1 sec
 *                                                                  */
#define  SYSTICK_CLOCK    AHB_DIV_8


#endif /* SYSTICK_CONFIG_H_ */
