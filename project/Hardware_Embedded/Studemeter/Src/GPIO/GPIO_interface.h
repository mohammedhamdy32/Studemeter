/*
 * GPIO_interface.h
 *
 *  Created on: Aug 10, 2023
 *  Author: mohammedhamdy32
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


#define SET    1U
#define RESET  0U

#define  MAX_PORTS_NUMBER   3U
#define  MAX_PINS_NUMBER    16U

#define  HIGH         1U
#define  LOW          0U

#define NONE   0U

/*** ENUM ***/
typedef enum
{ GPIO_INPUT , GPIO_OUTPUT ,  GPIO_ALTERNATIVE_FUNCTION , GPIO_ANALOG_MODE }
MODE;

typedef enum
{ NO_PULL = 0 , PULL_UP ,  PULL_DOWN }
PULL_TYPE;

typedef enum
{ PUSH_PULL_MODE = 0 , OPEN_DRAIN_MODE }OUTPUT_MODE;

typedef enum
{ LOW_SPEED = 0 , MEDIUM_SPEED , HIGH_SPEED , VERY_HIGH_SPEED }OUTPUT_SPEED;

typedef enum
{ PORTA_ID = 0 , PORTB_ID , PORTC_ID  }PORT_ID;

typedef enum
{ PIN0_ID = 0 ,PIN1_ID , PIN2_ID ,PIN3_ID ,PIN4_ID , PIN5_ID , PIN6_ID , PIN7_ID , PIN8_ID , PIN9_ID , PIN10_ID , PIN11_ID , PIN12_ID , PIN13_ID , PIN14_ID , PIN15_ID}PIN_ID;

typedef enum
{ AF0 = 0 , AF1 , AF2 , AF3 , AF4 , AF5 , AF6 , AF7 , AF8 , AF9 , AF10 , AF11 , AF12 , AF13 , AF14 , AF15 }ALTERNATIVE_FUNCTION;


/*** STRUCT ***/
typedef struct {

	PORT_ID port_id;
	PIN_ID pin_id;
	MODE mode;
	PULL_TYPE pull_type;
	OUTPUT_MODE out_mode;
	OUTPUT_SPEED out_speed;
	ALTERNATIVE_FUNCTION alternative_fun;

}GPIO_PIN_CONFIG_T;

/* Prototypes */
void GPIO_voidSetPin( PORT_ID Port_ID , PIN_ID PinNum , u8 value );
void GPIO_voidPinMode( PORT_ID Port_ID , PIN_ID PinNum , MODE mode );
u16  GPIO_u8ReadPin(  PORT_ID Port_ID , PIN_ID PinNum  );
void GPIO_void_PullType( PORT_ID Port_ID , PIN_ID PinNum , u8 Pull_type );
void GPIO_voidPinOutputMode(  PORT_ID Port_ID , PIN_ID PinNum , OUTPUT_MODE mode );
void GPIO_voidOutputSpeed( PORT_ID Port_ID , PIN_ID PinNum , OUTPUT_SPEED speed );
void GPIO_voidWritePort( PORT_ID Port_ID , u16 value );
u16 GPIO_u16ReadPort( PORT_ID Port_id );
void GPIO_setAlternativeFunction( PORT_ID port_id , PIN_ID pin_id , ALTERNATIVE_FUNCTION altternative_fun );
void GPIO_voidInti( const GPIO_PIN_CONFIG_T *pin_config );


#endif
