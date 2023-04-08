/*******************************************************************************
*                     _           _           _    _                           *
*         /\         (_)         | |         | |  | |                          *
*        /  \   _ __  _ ___   ___| |__   __ _| | _| | _____  _   _ _ __        *
*       / /\ \ | '_ \| / __| / __| '_ \ / _` | |/ / |/ / _ \| | | | '__|       *
*      / ____ \| | | | \__ \ \__ \ | | | (_| |   <|   < (_) | |_| | |          *
*     /_/    \_\_| |_|_|___/ |___/_| |_|\__,_|_|\_\_|\_\___/ \__,_|_|          *
*                                                                              *
*******************************************************************************/
/*******************************************************************************
 * File Template.h
 *
 *  Created on: April 08, 2023
 *  Author: Anis Shakkour
 *  Email:  anis.shakkour399@gmail.com
 *
 *  @brief :
 *  @note  :
 *  @todo  :
 *
 * For more information on the development board,
 *    please refer to the "https://www.silabs.com/documents/public/user-guides/ug465-brd4314a.pdf".
 *
 * For more information on the BLE pairing process,
 *    please refer to the "https://docs.silabs.com/bluetooth/5.0/general/security/pairing-processes".
 *
 * For more information on the BLE security features,
 *    please refer to the "https://docs.silabs.com/bluetooth/5.0/general/security/using-bluetooth-security-features-in-silicon-labs-bluetooth-sdk".
 *
 * For more information on the BLE GATT Server & Client roles,
 *    please refer to the "https://docs.silabs.com/bluetooth/3.1/general/gatt-protocol/gatt-server-and-client-roles".
 *
 ******************************************************************************/
/*________________________________|   PIN-OUT  |________________________________
|
| GPIO:
|     PC00 -
|     PC01 -
|     PC02 -
|     PC03 -
|     PC06 -
|     PC07 -
|     PA07 -
|
| IADC:
|
| PWM leds:
|
| UARTerminal:
|     PD02 -
|     PD03 -
|
|     PA05 - UART1 Tx. Vcom. (printf)
|     PA06 - UART1 Rx. Vcom. (printf)
|_____________________________________________________________________________*/

/*____________________________|   Software Usage  |_____________________________
|
| USTIMER:
| VCOM:
|       UART1
|_____________________________________________________________________________*/


/******************************************************************************
 * Multiple include protection
 *****************************************************************************/
#ifndef BLE_PERIPHERAL_H_
#define BLE_PERIPHERAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Defines
 ******************************************************************************/
//BLE Configurations
#define BLE_PASWORD   ((uint32_t)123456)
#define BLE_NAME      "Anis1234"
#define BLE_NAME_LEN  ((uint8_t)8)

//Advertising timing
#define BLE_MIN_ADV_INTERVAL  ((uint16_t)160 ) ///< Minimum advertising interval.
#define BLE_MAX_ADV_INTERVAL  ((uint16_t)160 ) ///< Maximum advertising interval.
#define BLE_MAX_ADV_DURATION  ((uint16_t)0   ) ///< no limit for advertising duration.
#define BLE_MAX_ADV_MAXEVENT  ((uint8_t )0   ) ///< No limit to stop advertising.

//Connection timing
#define BLE_MIN_INTERVAL  ((uint16_t)40    ) ///< Minimum value for the connection event interval.
#define BLE_MAX_INTERVAL  ((uint16_t)40    ) ///< Maximum value for the connection event interval.
#define BLE_LATENCY       ((uint16_t)0     ) ///< how many connection intervals the peripheral can skip if it has no data to send
#define BLE_TIMEOUT       ((uint16_t)450   ) ///< time that the connection is maintained although the devices can't communicate at the currently
#define BLE_MIN_CE_LEN    ((uint16_t)0     ) ///< Minimum length of the connection event.
#define BLE_MAX_CE_LEN    ((uint16_t)0xffff) ///< Maximum length of the connection event.




//********************************** DEBUG ON **********************************
#define DEBUG_BLE_SL_STATUS
#define DEBUG_BLE_FUNCTIONS
#define DEBUG_BLE_EVTs

/*******************************************************************************
 * Typedef & Enums
 ******************************************************************************/
typedef enum{
  FuncSuccess   ,
  FuncFailed    ,
  FuncOnGoing   ,
  FuncTimeOut   ,

}RetVal_t ;

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

/*******************************************************************************
 * Interface Functions
 ******************************************************************************/

/*******************************************************************************
 * END
 ******************************************************************************/
#endif /* BLE_PERIPHERAL_H_ */

