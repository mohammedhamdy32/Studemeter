/*
 * APP.h
 *
 *  Created on: Jan 26, 2024
 *      Author: mohammedhamdy32
 */

#ifndef APP_APP_H_
#define APP_APP_H_


/*** Defines ***/
#define  TRUE                               1U
#define  FALSE                              0U

#define  MAX_LINK_SIZE                      500   /* The max size of link that will be send to the server by GET */
#define  MAX_STRING_DATA_SIZE               (MAX_LINK_SIZE-40)

#define  GSR_SAMPLING_RATE_HZ               10.0f
#define  GSR_PORT_NUM                       PORTA_ID
#define  GSR_PIN_NUM                        PIN0_ID

#define  NUMBER_OF_SAMPLES_TO_SEND_DATA     100

#define  GSR_MAX_FLOATING_VALUE             20
#define  GSR_ERROR_LED_PORT                 PORTB_ID
#define  GSR_ERROR_LED_PIN                  12
#define  WIFI_ERROR_LED_PORT                PORTB_ID
#define  WIFI_ERROR_LED_PIN                 13


/************** WIFI  **************/
#define  WIFI_USER_NAME                 "ieee"
#define  WIFI_USER_NAME_SIZE            4
#define  WIFI_PASSWORD                  "123456789"
#define  WIFI_PASSWORD_SIZE             9

#define  SERVER_IP                     "192.168.137.1"
#define  SERVER_IP_SIZE                13

#define  ERROR_LED                     PORTB_ID,PIN0_ID

#define  DEVICE_ID                      1
#define  THRE_SHOLD_VALUE               100



/*******************************************************************************************
 * 									Types Declaration
 *******************************************************************************************/
typedef enum{
	WELL_DONE = 1 , ESP_NOT_WORKING , ERROR_IN_STATION_MODE , ERROR_WITH_USERNAME_OR_PASSWORD , ERROR_IN_DISABLE_ECHO
}STATUS_OF_CONNECTION_WITH_WIFI;


typedef enum{
	LED_OFF , LED_ON , ERROR_WITH_CONNECTION_TO_SERVER , ERROR_IN_LINK
}STATUS_OF_RECEIVING_LED_VALUE;



/*** Functions prototypes ***/
void APP_Init();
void APP_voidSendData( QUEUE_DATATYPE *a_data , u16 a_size );
STATUS_OF_CONNECTION_WITH_WIFI APP_u8InitWifiConnection(void);
void APP_voidCloseWifiErrorLed(void);
void APP_voidOpenWifiErrorLed(void);



#endif /* APP_APP_H_ */
