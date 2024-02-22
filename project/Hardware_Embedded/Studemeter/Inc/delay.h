/*
 * delay.h
 *
 *  Created on: Jan 26, 2024
 *      Author: mohammedhamdy32
 */

#ifndef DELAY_H_
#define DELAY_H_

#define  MC_FREQ 16000000
#define  delay_ms(x)  	for( u32 _DELAY_MACRO_ = 0 ; _DELAY_MACRO_ < ( (MC_FREQ/12.0)*( (x) /1000.0) ) ; _DELAY_MACRO_ ++ )

#endif /* DELAY_H_ */
