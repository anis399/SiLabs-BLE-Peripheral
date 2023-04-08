/******************************************************************************
 * File Name.c
 *
 *  Created on: April 08, 2023
 *  Author: Anis Shakkour
 *  Email:  anis.shakkour399@gmail.com
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
//Components

//Custom
#include "BLE_Peripheral.h"

/*******************************************************************************
 * Data types
 ******************************************************************************/
uint8_t BLE_Advertising_Set_Handle = 0xFF;
uint8_t BLE_Connection_Handle;

volatile bool BLE_Device_Connected = false;

/*******************************************************************************
 * Extern
 ******************************************************************************/

/*******************************************************************************
 * Interface Functions
 ******************************************************************************/

 /******************************************************************************
 * Function name:
 *
 * Description  :
 * Parameters   :
 * Returns      :
 *
 * Known issues :
 * Note         :
 *
 * ****************************************************************************/
RetVal_t Start_Advertising(uint8_t name[], uint8_t nameLen)
{
  RetVal_t ret = FuncFailed;
  sl_status_t sc;

#ifdef DEBUG_BLE_FUNCTIONS
  printf("BLE: Start Advertising\n");
#endif

  sc = sl_bt_system_start_bluetooth();
  BLE_sl_status_display(sc);

  if(sc == SL_STATUS_OK)
    {
      sc = sl_bt_gatt_server_write_attribute_value(gattdb_device_name,
                                                   0,
                                                   nameLen,
                                                   name);
      BLE_sl_status_display(sc);


      if(sc == SL_STATUS_OK){
          ret = FuncSuccess;
      }

      else{
          sc = sl_bt_system_stop_bluetooth();
          BLE_sl_status_display(sc);
      }
    }

  return ret;
}

/******************************************************************************
* Function name:
*
* Description  :
* Parameters   :
* Returns      :
*
* Known issues :
* Note         :
*
* @TODO : when stopping advertising , check if connection is open first,
*         close connection, stop advertising and then stop BLE
* ****************************************************************************/
RetVal_t Stop_Advertising(void)
{
  RetVal_t ret = FuncFailed;
  sl_status_t sc;

#ifdef DEBUG_BLE_FUNCTIONS
  printf("BLE: Stop Advertising\n");
#endif
  sc = sl_bt_advertiser_stop(BLE_Advertising_Set_Handle);
  BLE_sl_status_display(sc);

  if(sc == SL_STATUS_OK)
    {
      sc = sl_bt_system_stop_bluetooth();
      BLE_sl_status_display(sc);

      if(sc == SL_STATUS_OK)
        {
          ret = FuncSuccess;
        }
    }

 return ret;
}



/*******************************************************************************
 * Private Functions
 ******************************************************************************/
/******************************************************************************
 * Function name:
 *
 * Description :
* Parameters   : [in] sl_status_t.
* Returns      :
*
* Known issues :
* Note         :
*
* ****************************************************************************/
void BLE_sl_status_display(sl_status_t sc)
{
#ifdef DEBUG_BLE_SL_STATUS

  switch(sc){

    case SL_STATUS_OK:
      printf("sl status: success\n");
      break;

    case SL_STATUS_NOT_SUPPORTED:
      printf("sl status: feature not supported\n");
      break;

    case SL_STATUS_FAIL:
      printf("sl status: fail\n");
      break;

    case SL_STATUS_WOULD_OVERFLOW:
      printf("sl status: would overflow\n");
      break;

    default:
      printf("sl status: unknown %ld\n",sc);
      break;
  }
#endif
}
