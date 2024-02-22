/*
 * queue.h
 *
 *  Created on: Jan 25, 2024
 *      Author: mohammedhamdy32
 */

#ifndef QUEUE_QUEUE_H_
#define QUEUE_QUEUE_H_

#include "std_types.h"

/* Queue data type struct */
typedef struct
{
    u16 GSR_reading;
    u8 heartrate_reading;
}Queue_data_t;

/***  Define  ***/
#define QUEUE_SIZE      100
#define QUEUE_DATATYPE  Queue_data_t



/*** Functions prototypes  ***/
void Queue_init();
void enqueue(QUEUE_DATATYPE *a_data);
u8 dequeue( QUEUE_DATATYPE *a_data );
u16 queue_size();
u8 is_queue_Full();

#endif /* QUEUE_QUEUE_H_ */
