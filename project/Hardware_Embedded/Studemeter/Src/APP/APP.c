/*
 * APP.c
 *
 *  Created on: Jan 26, 2024
 *      Author: mohammedhamdy32
 */


#include "std_types.h"
#include "common_macros.h"
#include "delay.h"

#include "queue.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "ADC_interface.h"
#include "USART_interface.h"
#include "APP.h"
#include "ESP01.h"

/* Static function deceleration */
static void APP_voidReverseString(u8* str , u8 a_length);
static void APP_voidChangeQueueDataToString( QUEUE_DATATYPE *a_queue_data , u16 a_queue_size , u8 *a_string_data , u16 *string_size );
static void APP_voidSendDataBy_WiFi( QUEUE_DATATYPE *a_data , u16 a_size );
static void APP_voidSystickCallBackFun(void);



/* Functions Implementation */
static void APP_voidSystickCallBackFun(void)
{
	u16 gsr_reading = ADC_u16ReadChannel(GSR_PIN_NUM);

	if( gsr_reading < GSR_MAX_FLOATING_VALUE ) /* Sensor is not connected right */
	{
		/* Open Error LED */
		GPIO_voidSetPin( GSR_ERROR_LED_PORT , GSR_ERROR_LED_PIN , HIGH );
	}else
	{
		/* Close Error LED */
		GPIO_voidSetPin( GSR_ERROR_LED_PORT , GSR_ERROR_LED_PIN , LOW );
	}

	Queue_data_t q_data = { gsr_reading , 0 };
	enqueue( &q_data );

}

void APP_voidOpenWifiErrorLed(void)
{
	/* Open Error LED */
	GPIO_voidSetPin( WIFI_ERROR_LED_PORT , WIFI_ERROR_LED_PIN , HIGH );
}

void APP_voidCloseWifiErrorLed(void)
{
	/* Open Error LED */
	GPIO_voidSetPin( WIFI_ERROR_LED_PORT , WIFI_ERROR_LED_PIN , LOW );
}

void APP_Init()
{
	/***** Initializations *****/
	Queue_init();

	/* RCC */
	RCC_voidInitSysCls();
	RCC_voidEnablePerpheralClk( AHB1 , GPIOA_ID );
	RCC_voidEnablePerpheralClk( AHB1 , GPIOB_ID );
	RCC_voidEnablePerpheralClk(APB2  , ADC_ID ); /* ADC */


	/* ADC configuration and initialization */
	GPIO_PIN_CONFIG_T gpio_config = { GSR_PORT_NUM , GSR_PIN_NUM , GPIO_ANALOG_MODE , NO_PULL , 0 , 0 , 0 };
	GPIO_voidInti( &gpio_config );
	ADC_ConfigType adcConfig = {TWELVE_BIT, 0 , 0 , 0 , PCLK2_8};
	ADC_vInit(&adcConfig);

	//	/* USART1 */
	//	USART_config uart_config = { USART1_NUM , ONE_BIT , DISABLE_PARITY , BIT8_WORD , OVERSAMPLING_16 , 9600 };
	//	USART_voidInit( &uart_config );
	//	USART_sendWord( USART1_NUM , ' ');

	/* Initialize Gsr error led */
	GPIO_PIN_CONFIG_T gpio_config_2 = { GSR_ERROR_LED_PORT , GSR_ERROR_LED_PIN , GPIO_OUTPUT , NO_PULL , PUSH_PULL_MODE , LOW_SPEED , 0 };
	GPIO_voidInti( &gpio_config_2 );

	/*WIFI error Led*/
	GPIO_PIN_CONFIG_T gpio_config_3 = { WIFI_ERROR_LED_PORT , WIFI_ERROR_LED_PIN , GPIO_OUTPUT , NO_PULL , PUSH_PULL_MODE , LOW_SPEED , 0 };
	GPIO_voidInti( &gpio_config_3 );

	/* Systick */
	SYSTICK_voidInit();

	/* Pass call back function to systick */
	SYSTICK_voidSetIntervalNumber( (2000000.0)/GSR_SAMPLING_RATE_HZ , INFINITY_TIMES , APP_voidSystickCallBackFun );

}


/***** ESP32 Application functions *****/

STATUS_OF_CONNECTION_WITH_WIFI APP_u8InitWifiConnection(void)
{

	u8 status = WELL_DONE , check = 0;

	ESP01_voidInit();


	for( u8 i=0 ; i<3 ;i++ )
	{
		check = ESP01_u8CheckModuleConnection(); /* Check the module connection */
		if( check == TRUE )
			break;
		//		for(u32 j=0 ; j<10000000 ; j++);  /* Some delay */
	}

	if( check != TRUE )
	{
		/* The WiFI module is not working */
		status = ESP_NOT_WORKING;
		return status;
	}

	check = ESP01_u8SendDisableEchoCommand(); /* Disable the echo */
	if( check != TRUE )
	{
		status = ERROR_IN_DISABLE_ECHO;
	}


	check = ESP01_u8SetStationMode(); /* Put the ESP in station mode */
	if(check != TRUE )
	{
		status = ERROR_IN_STATION_MODE;
	}

	check = ESP01_u8ConnectToWIFI( WIFI_USER_NAME , WIFI_USER_NAME_SIZE , WIFI_PASSWORD , WIFI_PASSWORD_SIZE );
	if( check != TRUE )
	{
		status =ERROR_WITH_USERNAME_OR_PASSWORD;
	}

	return status;

}

/* This function takes a string and concatenate it with the server link, and send this link to server */
u8 APP_sendString( u8 * data , u16 size )
{
	u8 check ;
	check = ESP01_u8ConnectToServer( SERVER_IP , SERVER_IP_SIZE , "80", 2 , TCP );

	if( check != TRUE )
	{
		return ERROR_WITH_CONNECTION_TO_SERVER;
	}

	u16 link_size=54;
	u8 link[MAX_LINK_SIZE] = "http://localhost/Studemeter/action.php?type=data&data=";

	/* Concatenate the string with link */
	for( u16 i=0 ; i<size ; i++ , link_size++ )
		link[link_size] = data[i];

	u8 value[MAX_RECEIVED_DATA_SIZE] ;
	u16 data_size ;
	check = ESP01_u8SendDataOverConnection( link , link_size , GET , value , &data_size , WRITE );

	return check;


}

/* This function reverse a string */
static void APP_voidReverseString(u8* str , u8 a_length)
{

	u8 i;
	u8 temp;

	for (i = 0; i < a_length / 2; i++)
	{
		temp = str[i];
		str[i] = str[a_length - 1 - i];
		str[a_length - 1 - i] = temp;
	}

}

/* This function changes the queue data to a string reading is separated by ; */
static void APP_voidChangeQueueDataToString( QUEUE_DATATYPE *a_queue_data , u16 a_queue_size , u8 *a_string_data , u16 *string_size )
{

	u8 temp_data[10];
	u8 single_number ;
	u16 counter = 0 , local_counter ;
	u16 data;

	for(u8 i=0 ; i<a_queue_size ; i++)
	{
		data = a_queue_data[i].GSR_reading ;
		local_counter = 0;
		while( data != 0 )
		{
			single_number = data % 10;
			data = (u8) (data /10);
			temp_data[local_counter] = single_number + 48 ; /* change number into char */
			counter++;
			local_counter++;
		}

		/* Reverse the string */
		APP_voidReverseString(temp_data , local_counter );

		/* Save string to main string */
		for( s8 j=local_counter ; j>0 ; j-- )
			a_string_data[counter-j] = temp_data[local_counter-j] ;

		a_string_data[counter] = ';';
		counter++;
	}

	/* Pass the string size */
	*string_size = counter-1; /* Ignore last \n  */


}

/* This function send data through TTL  */
//static void APP_voidSendDataBy_TTL(  QUEUE_DATATYPE *a_data , u16 a_size )
//{
//	u8 numInAsci[16];
//
//	for(u16 i=0; i <a_size ; i++)
//	{
//		itoa( a_data[i].GSR_reading , numInAsci , 10);
//		USART_sendString( USART1_NUM , numInAsci );
//		USART_sendWord( USART1_NUM , '\n' );
//		delay_ms(5);
//	}
//
//}

/* This function send data through WiFi  */
static void APP_voidSendDataBy_WiFi( QUEUE_DATATYPE *a_data , u16 a_size )
{

	u8 string_data[ MAX_STRING_DATA_SIZE ];
	u16 string_size;

	/* Change the data in the queue to a string */
	APP_voidChangeQueueDataToString( a_data , a_size , string_data ,  &string_size  );

	/* Send String to WiFi module */
	APP_sendString( string_data , string_size );

}

/* This function in app layer that choose how to sent data */
void APP_voidSendData( QUEUE_DATATYPE *a_data , u16 a_size )
{
	APP_voidSendDataBy_WiFi(a_data,a_size);
}
