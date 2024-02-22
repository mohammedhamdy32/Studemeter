/*
 * @GPIO_Program.c
 * @Author: mohammedhamdy32
 * @GPIO functions implementation
 *
 *  Created on: Aug 10, 2023
 */


#include "std_types.h"
#include "common_macros.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"

/* An array to collect all my GPIOs */
static GPIO_MemMap_t* GPIO_PORT [MAX_PORTS_NUMBER] = {GPIOA , GPIOB , GPIOC };

void GPIO_voidSetPin( PORT_ID Port_ID , PIN_ID PinNum , u8 value )
{

	if( Port_ID > MAX_PORTS_NUMBER  || PinNum > MAX_PINS_NUMBER )
	{
		/* Do nothing */
	}else
	{
		if( value == SET )
		{

			SET_BIT( (GPIO_PORT[Port_ID]->ODR) , PinNum );

		}else if( value == RESET )
		{

			CLEAR_BIT( GPIO_PORT[Port_ID]->ODR , PinNum );

		}else
		{
			/* Do nothing */
		}
	}



}


void GPIO_voidPinMode( PORT_ID Port_ID , PIN_ID PinNum , MODE mode )
{
	if( Port_ID > MAX_PORTS_NUMBER  || PinNum > MAX_PINS_NUMBER )
	{
		/* Do nothing */
	}else
	{
		(GPIO_PORT[Port_ID]->MODER) = ( (GPIO_PORT[Port_ID]->MODER) & (~(0b11 << 2*PinNum)) ) | ( mode << 2*PinNum );
	}

}


void GPIO_voidWritePort( PORT_ID Port_ID , u16 value )
{
	if( Port_ID > MAX_PORTS_NUMBER )
	{

	}else
	{
		GPIO_PORT[Port_ID]->ODR = value;
	}

}

u16 GPIO_u16ReadPort( PORT_ID Port_id )
{
	u16 value = -1 ;

	if( Port_id > MAX_PORTS_NUMBER )
	{

	}else
	{
		value = (GPIO_PORT[Port_id]->IDR)   ;
	}

	return value;
}

void GPIO_voidPinOutputMode(  PORT_ID Port_ID , PIN_ID PinNum , OUTPUT_MODE mode )
{
	if( Port_ID > MAX_PORTS_NUMBER  || PinNum > MAX_PINS_NUMBER )
	{
		/* Do nothing */
	}else
	{
		(GPIO_PORT[Port_ID]->OTYPER) = (GPIO_PORT[Port_ID]->OTYPER) | (mode << PinNum) ;
	}

}

void GPIO_voidOutputSpeed( PORT_ID Port_ID , PIN_ID PinNum , OUTPUT_SPEED speed )
{
	if( Port_ID > MAX_PORTS_NUMBER  || PinNum > MAX_PINS_NUMBER )
	{
		/* Do nothing */
	}else
	{
		(GPIO_PORT[Port_ID]->OSPEEDR) = ( (GPIO_PORT[Port_ID]->OSPEEDR) & (~(0b11 << 2*PinNum)) ) | ( speed << 2*PinNum );
	}

}

void GPIO_void_PullType( PORT_ID Port_ID , PIN_ID PinNum , PULL_TYPE Pull_type )
{
	if( Port_ID > MAX_PORTS_NUMBER  || PinNum > MAX_PINS_NUMBER )
	{
		/* Do nothing */
	}else
	{
		(GPIO_PORT[Port_ID]->PUPDR) = ( (GPIO_PORT[Port_ID]->PUPDR) & (~(0b11 << 2*PinNum)) ) | ( Pull_type << 2*PinNum );
	}

}


u16   GPIO_u8ReadPin(  PORT_ID Port_ID , PIN_ID PinNum  )
{
	u16 value = -1 ;
	if( Port_ID > MAX_PORTS_NUMBER  || PinNum > MAX_PINS_NUMBER )
	{
		/* Do nothing */
	}else
	{
		value = (GPIO_PORT[Port_ID]->IDR)  & (1<<PinNum) ;
	}

	return value;

}

void GPIO_setAlternativeFunction( PORT_ID port_id , PIN_ID pin_id , ALTERNATIVE_FUNCTION altternative_fun )
{
	if( port_id > MAX_PORTS_NUMBER  || pin_id > MAX_PINS_NUMBER )
	{
		/* Do nothing */
	}else
	{
		u8 bit_num = (pin_id % 8U)*4U ;
		(GPIO_PORT[port_id]->AFR[pin_id/8U]) = ( (GPIO_PORT[port_id]->AFR[pin_id/8U]) & ( ~( (0b1111) << (bit_num) ) ) ) | ( (altternative_fun) <<  (bit_num) ) ;
	}

}

/*********************************************************************************
 * @fun GPIO_voidInti
 * @brief This function initialize GPIO pin according
 * @param[in] pin_config : A struct contains the initialization values
 * @retval void
 *********************************************************************************/
void GPIO_voidInti( const GPIO_PIN_CONFIG_T *pin_config )
{
	PORT_ID port_id  = pin_config->port_id;
	PIN_ID pin_id    = pin_config->pin_id;

	/* Pin Mode */
	GPIO_voidPinMode( port_id , pin_id ,pin_config->mode );

	/* Pull type */
	GPIO_void_PullType( port_id , pin_id , pin_config->pull_type );

	if( (pin_config->mode) == GPIO_INPUT || (pin_config->mode) == GPIO_ANALOG_MODE ) /* Input or Analog */
	{

		/* DO NOTHING */

	}else if( (pin_config->mode) == GPIO_OUTPUT ) /* Output */
	{
		/* Output mode */
		GPIO_voidPinOutputMode(  port_id , pin_id , pin_config->out_mode );

		/* Output speed */
		GPIO_voidOutputSpeed(  port_id , pin_id , pin_config->out_speed );

	}else if( (pin_config->mode) == GPIO_ALTERNATIVE_FUNCTION )  /* Alternative function */
	{

		/* Output mode */
		GPIO_voidPinOutputMode(  port_id , pin_id , pin_config->out_mode );

		/* Output speed */
		GPIO_voidOutputSpeed(  port_id , pin_id , pin_config->out_speed );

		/* ALlternative fun */
		GPIO_setAlternativeFunction(port_id , pin_id , pin_config->alternative_fun );
	}

}

