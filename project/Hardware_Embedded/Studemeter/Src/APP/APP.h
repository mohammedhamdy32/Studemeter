/*
 * APP.h
 *
 *  Created on: Jan 26, 2024
 *      Author: mohammedhamdy32
 */

#ifndef APP_APP_H_
#define APP_APP_H_


/*** Defines ***/
#define  GSR_SAMPLING_RATE_HZ               10.0f
#define  GSR_PORT_NUM                       PORTA_ID
#define  GSR_PIN_NUM                        PIN0_ID

#define  NUMBER_OF_SAMPLES_TO_SEND_DATA     1

/*** Functions prototypes ***/
void APP_Init();
void APP_send_data( QUEUE_DATATYPE *a_data , u16 a_size );


#endif /* APP_APP_H_ */
