/*
 * ESP01.c
 *
 *  Created on: Sep 6, 2023
 *      Author: mohammedhamdy32
 */

#include "std_types.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "USART_Interface.h"
#include "RCC_interface.h"
#include "ESP01.h"
#include "delay.h"

static u8 ESP01_u8RecieveOKString();
static u8 ESP01_recieveConnectedOrDisConnecteString();
static u8 ESP01_u8NumberToString( u16 number , u8 * str_num );
static u8 ESP01_u8ReceiveDataFromServer( u8 *data , u32 *size , READ_OR_WRITE_FROM_SEVER read_or_write );
static u8 ESP01_u8RecieveOKStringWithoutStack();
static u8 ESP01_u8RecieveOKStringWithoutStack();
static u8 ESP01_u8ReceiveClosed();

u8 g_counter;


static u8 ESP01_u8RecieveOKString()
{
	u8 first_char=1;
	u8 second_char=1;
	USART_voidReceive( &second_char );

	while(1)
	{
		first_char = second_char;  /* save the old received char in first_char */
		USART_voidReceive( &second_char) ;

		if( 'K' == second_char && 'O' == first_char )
			break;

	}

	u8 back_slash_r , back_slash_n;
	USART_voidReceive( &back_slash_r );   /* \r */
	USART_voidReceive( &back_slash_n ); /* \n */

	if( first_char == 'O' && second_char == 'K' && back_slash_r == '\r' && back_slash_n == '\n' )
		return 1;
	else
		return 0;

}

static u8 ESP01_u8RecieveOKStringWithoutStack()
{
	u8 first_char=1;
	u8 second_char=1;
	u8 check = 0 ;


	while( 1 )
	{
		if(check == 1) /* So the UART receive something */
			first_char = second_char;  /* save the old received char in first_char */

		check = USART_voidReceiveWithouStackPolling( &second_char) ;

		if( 'K' == second_char && 'O' == first_char )
			break;

	}


	u8 back_slash_r , back_slash_n;
	USART_voidReceive( &back_slash_r );   /* \r */
	USART_voidReceive( &back_slash_n );  /* \n */

	if( first_char == 'O' && second_char == 'K' && back_slash_r == '\r' && back_slash_n == '\n' )
		return 1;
	else
		return 0;

}

static u8 ESP01_recieveConnectedOrDisConnecteString()
{
	u8 second_char = 1;
	u8 first_char = 1;
	u8 status = -1 ;
	USART_voidReceive( &second_char );

	while(1) /* Loop till sent OK or FAIL */
	{
		first_char = second_char;  /* save the old received char in first_char */
		USART_voidReceive(&second_char); /* Save the current received element in second_char */
		if( ('L' == second_char && 'I' == first_char) || ('K' == second_char && 'O' == first_char) || ('R' == second_char && 'O' == first_char)  )  /* To check if it response OK or FAIL or ERROR  */
			break;
	}

	if( first_char == 'O' && second_char == 'K' ) /* OK */
	{
		status = 1;
	}else if( first_char == 'O' && second_char == 'R' ) /* ERROR */
	{
		status = 0;
	}
	else if( first_char == 'I' ) /* FAIL */
	{
		status = 0;
	}

	u8 back_slash_r , back_slash_n;
	USART_voidReceive( &back_slash_r );   /* \r */
	USART_voidReceive( &back_slash_n );  /* \n */

	return status;

}


static u8 ESP01_u8ReceiveClosed()
{
	u8 second_char = 1;
	u8 first_char = 1;
	u8 status = -1 ;
	USART_voidReceive( &second_char );

	while(1) /* Loop till sent OK or FAIL */
	{
		first_char = second_char;  /* save the old received char in first_char */
		USART_voidReceive(&second_char); /* Save the current received element in second_char */
		if( 'D' == second_char && 'E' == first_char  )  /* To check if it response CLOSED  */
			break;
	}

	if( first_char == 'E' && second_char == 'D' ) /* CLOSED */
	{
		status = 1;
	}else
	{
		status = 0;
	}


	u8 back_slash_r , back_slash_n;
	USART_voidReceive( &back_slash_r );   /* \r */
	USART_voidReceive( &back_slash_n );  /* \n */

	return status;

}

static u8 ESP01_u8NumberToString( u16 number , u8 * str_num )
{
	u8 counter = 0 , single_number;

	while( number != 0 )
	{
		single_number = number % 10;
		number = (u8) (number /10);
		str_num[counter] = single_number + 48 ; /* change number into char */
		counter++;
	}

	u8 temp;
	if( counter == 3 )
	{
		temp = str_num[0];
		str_num[0] = str_num[2];
		str_num[2] = temp;
	}else if( counter == 2 )
	{
		temp = str_num[0];
		str_num[0] = str_num[1];
		str_num[1] = temp;
	}

	return counter;
}


static u8 ESP01_u8ReceiveDataFromServer( u8 *data , u32 *size , READ_OR_WRITE_FROM_SEVER read_or_write )
{
	u8 status = 1;
	/* First you should receive OK  */
	u8 OK_check = ESP01_u8RecieveOKString();
	if( OK_check == 0 )
	{
		status = 3;
		return status;
	}

	if( read_or_write == WRITE )
	{
		u8 check = ESP01_u8ReceiveClosed();
		return check;
	}

	u8 second_char = 1;
	u8 first_char = 1;
	USART_voidReceive( &second_char );

	while(1) /* Loop till sent D, */
	{
		first_char = second_char;  /* save the old received char in first_char */
		USART_voidReceive(&second_char); /* Save the current received element in second_char */
		if( ',' == second_char && 'D' == first_char )  /* To check if it response OK or FAIL  */
			break;
	}

	u8 arr_data_size[4] , temp_data , counter = 0  ;
	u32 size_data = 0 ;	/* data_size should be the size of file */
	USART_voidReceive( &temp_data);

	while( temp_data != ':' )
	{
		arr_data_size[counter] = temp_data;
		counter++;
		USART_voidReceive( &temp_data);
	}

	u32 b=1;
	for( s8 j=counter-1 ; j>=0 ; j-- , b=b*10 )
	{
		size_data = size_data + (arr_data_size[j]-48)*b;
	}

	*size =  size_data; /* Send the data size to the user */

	if( size_data > MAX_RECEIVED_DATA_SIZE ) /* The size is bigger than the MAX size */
	{
		/* To receive all the data but didn't store, it to avoid any errors in other function because the UART will still receive */
		u8 first_char=1;
		u8 second_char=1;
		USART_voidReceive( &second_char );

		while(1)
		{
			first_char = second_char;  /* save the old received char in first_char */
			USART_voidReceive( &second_char) ;

			if( 'D' == second_char && 'E' == first_char )
				break;

		}

		u8 back_slash_r , back_slash_n;
		USART_voidReceive( &back_slash_r );   /* \r */
		USART_voidReceive( &back_slash_n ); /* \n */

		status = 0;
		return status;
	}

	for( u8 i=0 ; i< size_data ; i++ )
	{
		USART_voidReceive( data+i );
	}

	u8 closed[8];
	USART_voidReceive( closed  );    /* C  */
	USART_voidReceive( closed + 1 ); /* L  */
	USART_voidReceive( closed + 2 ); /* O  */
	USART_voidReceive( closed + 3 ); /* S  */
	USART_voidReceive( closed + 4 ); /* E  */
	USART_voidReceive( closed + 5 ); /* D  */
	USART_voidReceive( closed + 6 ); /* \r */
	USART_voidReceive( closed + 7 ); /* \n */

	return status;

}

static void ESP01_voidIncrmentGlobalCounter(void)
{
	g_counter++;
}


void ESP01_voidInit(void)
{

	RCC_voidEnablePerpheralClk( APB2 ,  USART1_ID );
	RCC_voidEnablePerpheralClk(AHB1 , GPIOA_ID);

	/* Configare GPIO pins */
	GPIO_PIN_CONFIG_T gpio_cofig = { PORTA_ID , PIN9_ID , GPIO_ALTERNATIVE_FUNCTION , NO_PULL , NONE , NONE , AF7 };
	GPIO_voidInti( &gpio_cofig ); /* For TX pin (PIN 9) */
	gpio_cofig.pin_id = PIN10_ID;
	GPIO_voidInti( &gpio_cofig ); /* For RX pin (PIN 10) */


	GPIO_voidPinMode( PORTA_ID , PIN9_ID , GPIO_ALTERNATIVE_FUNCTION );
	GPIO_voidPinMode( PORTA_ID , PIN10_ID , GPIO_ALTERNATIVE_FUNCTION );

	USART_voidInit();


}


u8 ESP01_u8CheckModuleConnection(void)
{
	u8 check;


	USART_voidSend( AT_TEST_COMMAND ); /* Send AT command */
	USART_voidSend( AT_TEST_COMMAND ); /* Send AT command */

	check = ESP01_u8RecieveOKStringWithoutStack();  /* check = 0 : The WiFi module is not connected, check = 1 : WiFi module is connected  */

	return check;

}



u8 ESP01_u8SendAT_TestCommand(void)
{
	USART_voidSend( AT_TEST_COMMAND ); /* Send command */
	u8 status = ESP01_u8RecieveOKString();   /* receive response */

	return status;

}

u8 ESP01_u8SendDisableEchoCommand(void)
{
	USART_voidSend( AT_DISABLE_ECHO ); /* Send command */
	u8 status = ESP01_u8RecieveOKString();  /* receive response */

	return status;
}

/* Restart didn't send OK only so don't use it NOW  */
u8 ESP01_u8RestartModule(void)
{
	USART_voidSend( AT_RESTART_MODULE ); /* Send command */
	u8 status = ESP01_u8RecieveOKString();  /* receive response */


	return status;
}


u8 ESP01_u8SetAcessPointMode(void)
{
	USART_voidSend( AT_ACCESS_POINT_MODE ); /* Send command */
	u8 status = ESP01_u8RecieveOKString();  /* receive response */


	return status;
}

u8 ESP01_u8SetStationMode(void)
{
	USART_voidSend( AT_SATION_MODE ); /* Send command */
	u8 status = ESP01_u8RecieveOKString();  /* receive response */


	return status;
}

u8 ESP01_u8SetAcessAndStationModes(void)
{
	USART_voidSend( AT_ACCESS_AND_STATION_MODE ); /* Send command */
	u8 status = ESP01_u8RecieveOKString();  /* receive response */


	return status;
}
/*****************************************************************************
 * This function takes the user name and password of your WIFI, then returns *
 * if it connected or not                                                    *
 *****************************************************************************/
u8 ESP01_u8ConnectToWIFI( u8* a_ptr_user_name , u8 a_size_user_name , u8* a_ptr_password , u8 a_size_password )
{
	u8 status;

	u8 start_command[9] = "AT+CWJAP=";  /* The first part of the command */
	u16 command_array_size = a_size_password + a_size_user_name + 16 ; /* 16 = 9(AT+CWJAP=) + 2(" ") + 2(" ") + 1(,) + 1(\n) + 1(\r) */
	u8 command[command_array_size]; /* Array contains all my command */

	u16 i; /* Counter to my command array */

	for( i=0 ; i<9 ; i++ ) /* First put the First part of command in command array */
		command[i] = start_command[i];

	command[i] = '"'; /* add " for user name */
	i++;

	for( u8 j=0 ; j<a_size_user_name ; j++ ,i++ ) /* Add user name */
	{
		command[i] = a_ptr_user_name[j];
	}

	command[i] = '"'; /* add " for end of user name */
	i++;
	command[i] = ','; /* add , */
	i++;
	command[i] = '"'; /* add " for password */
	i++;

	for(u8 j=0 ; j<a_size_password ; j++,i++) /* Add password */
	{
		command[i] = a_ptr_password[j];
	}

	command[i] = '"'; /* add " for end of password */
	i++;
	command[i] = '\r'; /* add \r */
	i++;
	command[i] = '\n'; /* add \n */

	USART_voidSend( command ,command_array_size ); /* Send the command array by UART */

	status = ESP01_recieveConnectedOrDisConnecteString(); /* This function receive the ESP01 response and return if WIFI is connected or not */

	return status;

}


u8 ESP01_u8ConnectToServer( u8 *server_ip , u8 size_server_ip , u8 * port_num , u8 size_port_num , CONNECTION_TYPE connection_type )
{
	u8 status = 2;

	u8 start_command[12] = "AT+CIPSTART=";  /* The first part of the command */
	u16 command_array_size = size_server_ip + size_port_num + 23 ; /* 23 = 12(AT+CIPSTART=) + 3(TCP or UDP) + 2(" ") + 2(" ")  + 1(,) + 1(,) + 1(\n) + 1(\r) */
	u8 command[command_array_size]; /* Array contains all my command */

	u8 type_connection[3];
	if( connection_type == TCP )
	{
		type_connection[0] = 'T' ;
		type_connection[1] = 'C' ;
		type_connection[2] = 'P' ;
	}else if( connection_type == UDP )
	{
		type_connection[0] = 'U' ;
		type_connection[1] = 'D' ;
		type_connection[2] = 'P' ;
	}else
	{
		status = 3;  /* wrong connection type argument */
		return status;
	}

	u16 i; /* Counter to my command array */

	for( i=0 ; i<12 ; i++ ) /* First put the First part of command in command array */
		command[i] = start_command[i];

	command[i] = '"'; /* add " for start of Connection type */
	i++;

	for( u8 j=0 ; j<3 ; j++ ,i++ )
		command[i] = type_connection[j];

	command[i] = '"'; /* add " for end of Connection type */
	i++;

	command[i] = ','; /* add , */
	i++;

	command[i] = '"'; /* add " for start of server ip */
	i++;

	for( u8 j=0 ; j<size_server_ip ; j++ ,i++ )
		command[i] = server_ip[j];

	command[i] = '"'; /* add " for end of server ip */
	i++;

	command[i] = ','; /* add , */
	i++;

	for( u8 j=0 ; j<size_port_num ; j++ , i++ )
		command[i] = port_num[j];

	command[i] = '\r'; /* add \r */
	i++;
	command[i] = '\n'; /* add \n */

	USART_voidSend( command ,command_array_size ); /* Send the command array by UART */

	status = ESP01_recieveConnectedOrDisConnecteString(); /* This function receive the ESP01 response and return if WIFI is connected or not */

	return status;

}


u8 ESP01_u8SendDataOverConnection( u8 * link , u16 size_link , SENDING_METHOD method , u8 *a_data , u16 *a_size_data , READ_OR_WRITE_FROM_SEVER read_or_write  )
{
	u8 status = 1;
	u8  sending_method[4];
	u8 sending_method_size;

	if( method == GET )
	{
		sending_method[0] = 'G' ;
		sending_method[1] = 'E' ;
		sending_method[2] = 'T' ;
		sending_method_size = 3;
	}else if( method == POST )
	{
		sending_method[0] = 'P' ;
		sending_method[1] = 'O' ;
		sending_method[2] = 'S' ;
		sending_method[3] = 'T' ;
		sending_method_size = 4;
	}else
	{
		status =3;
		return status;
	}

	u8 size ;
	u16 size_total_link = size_link + sending_method_size + 3 ; /* 3 = 1(' ') + 1(\r) + 1(\n) */
	u8 arr_size[3]; /* Max is 3 */
	size = ESP01_u8NumberToString( size_total_link , arr_size);

	u8 start_command[11] = "AT+CIPSEND=";  /* The first part of the command */
	u16 command_array_size = size + 13 ; /*  11(AT+CIPSEND=) + size + 1(\n) + 1(\r)  */
	u8 command[command_array_size]; /* Array contains all my command */


	u16 i; /* Counter to my command array */

	for( i=0 ; i<11 ; i++ ) /* First put the First part of command in command array */
		command[i] = start_command[i];


	for( u8 j=0 ; j<size ; j++ , i++ )
		command[i] = arr_size[j];

	command[i] = '\r'; /* add \r */
	i++;
	command[i] = '\n'; /* add \n */
	i++;

	u8 greater_than_symbol , backslash_r , backslash_n;
	USART_voidSend( command ,command_array_size ); /* Send the command array by UART */
	u8 check = ESP01_recieveConnectedOrDisConnecteString();
	USART_voidReceive(&backslash_r);
	USART_voidReceive(&backslash_n);
	USART_voidReceive(&greater_than_symbol);

	if( check == 1 && greater_than_symbol == '>' )
	{
		/* Do nothing */
	}else
	{
		status = 4;
		return status;
	}

	u8 total_link[ size_total_link ];
	u16 counter ;

	for( counter = 0 ;counter < sending_method_size ; counter++ ) /* write GET or POST */
		total_link[counter] = sending_method[counter];

	total_link[counter] = ' '; /* space */
	counter++;

	for( u16 j=0 ; j<size_link ; j++ , counter++ )  /* write link */
		total_link[counter] = link[j];

	total_link[counter] = '\r'; /* add \r */
	counter++;
	total_link[counter] = '\n'; /* add \n */
	counter++;

	USART_voidSend( total_link , size_total_link );

//	u8 data[MAX_RECEIVED_DATA_SIZE] , size_data;

//	status = ESP01_u8ReceiveDataFromServer( a_data , a_size_data , read_or_write  );

	return status;
}







