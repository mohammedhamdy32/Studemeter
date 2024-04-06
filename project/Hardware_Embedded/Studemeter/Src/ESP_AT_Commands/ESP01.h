/*
 * ESP01.h
 *
 *  Created on: Sep 6, 2023
 *      Author: mohammedhamdy32
 */

#ifndef ESP01_H_
#define ESP01_H_

#define AT_TEST_COMMAND               "AT\r\n",4
#define AT_DISABLE_ECHO               "ATE0\r\n",6
#define AT_RESTART_MODULE             "AT+RST\r\n",8
#define AT_SATION_MODE                "AT+CWMODE=1\r\n",13
#define AT_ACCESS_POINT_MODE          "AT+CWMODE=2\r\n",13
#define AT_ACCESS_AND_STATION_MODE    "AT+CWMODE=3\r\n",13

#define MAX_RECEIVED_DATA_SIZE           10
#define NUM_OF_TICK_FOR_CHECK_MODULE     10000000
#define MAX_VALUE_OF_GOLBAL_COUNTER      1
#define TRUE                             1


typedef enum{
	TCP , UDP
}CONNECTION_TYPE;

typedef enum{
	GET , POST
}SENDING_METHOD;

typedef enum{
	READ , WRITE
}READ_OR_WRITE_FROM_SEVER;


void ESP01_voidInit(void);
u8 ESP01_u8SendDisableEchoCommand(void);
u8 ESP01_u8SendAT_TestCommand(void);
u8 ESP01_u8RestartModule(void);
u8 ESP01_u8SetAcessPointMode(void);
u8 ESP01_u8SetStationMode(void);
u8 ESP01_u8SetAcessAndStationModes(void);
u8 ESP01_u8ConnectToWIFI( u8* a_ptr_user_name , u8 a_size_user_name , u8* a_ptr_password , u8 a_size_password );
u8 ESP01_u8ConnectToServer( u8 *server_ip , u8 size_server_ip , u8 * port_num , u8 size_port_num , CONNECTION_TYPE connection_type );
u8 ESP01_u8SendDataOverConnection( u8 * link , u16 size_link , SENDING_METHOD method , u8 *a_data , u16 *a_size_data , READ_OR_WRITE_FROM_SEVER read_or_write  );
u8 ESP01_u8CheckModuleConnection(void);





#endif /* ESP01_H_ */
