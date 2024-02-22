/*
 * queue.c
 *
 *  Created on: Jan 25, 2024
 *      Author: mohammedhamdy32
 */

#include "queue.h"

/* Global variables */
static u16 queue_rear;
static u16 queue_front;
static s16 queue_counter;
static QUEUE_DATATYPE queue_array[QUEUE_SIZE];

void Queue_init()
{
	queue_front = 0;
	queue_rear = 0;
}

void enqueue(QUEUE_DATATYPE *a_data)
{
	if( queue_counter == QUEUE_SIZE ) /* queue is full */
	{

	}else
		queue_counter++;

	queue_array[queue_rear] = *a_data;
	queue_rear = (queue_rear+1)%QUEUE_SIZE; /*To make queue cycler*/
}

u8 dequeue( QUEUE_DATATYPE *a_data )
{
	if( queue_counter == 0 ) /* queue is empty */
	{
        return -1;
	}else
		queue_counter--;

	u16 x =queue_front;
	queue_front = (queue_front+1)%QUEUE_SIZE ;  /*To make queue cycler*/
	*a_data = queue_array[x];
	return 1;

}

u16 queue_size()
{
	return queue_counter;
}

u8 is_queue_Full()
{
	return queue_counter == QUEUE_SIZE;
}

