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
#include "printf.h"

//Custom
#include "BLE_Peripheral.h"

/*******************************************************************************
 * Data types
 ******************************************************************************/

/*******************************************************************************
 * Extern
 ******************************************************************************/
//extern const int32_t BLE_Password;
//extern const uint8_t BLE_deviceName[];
//extern const uint8_t BLE_deviceName_len;

extern uint8_t BLE_Advertising_Set_Handle;
extern uint8_t BLE_Connection_Handle;

extern volatile bool BLE_Device_Connected;

/*******************************************************************************
 * Interface Functions
 ******************************************************************************/

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

/******************************************************************************
 * Function name:
 *
 * Description  : Bluetooth stack event handler.
 *                This overrides the dummy weak implementation.
 * Parameters   : [in] evt Event coming from the Bluetooth stack.
 * Returns      :
 *
 * Known issues :
 * Note         :
 *
 * ****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{

  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];
  uint8_t buf[100] = {0};
  size_t bufSize = 0;

  switch (SL_BT_MSG_ID(evt->header))
  {
    //************************************* sl_bt_evt_system_boot_id *************************************
    case sl_bt_evt_system_boot_id:

#ifdef DEBUG_BLE_EVTs
      printf("BLE evt: boot\n");
#endif

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      BLE_sl_status_display(sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      BLE_sl_status_display(sc);

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&BLE_Advertising_Set_Handle);
      BLE_sl_status_display(sc);

      // Set advertising interval
      sc = sl_bt_advertiser_set_timing(BLE_Advertising_Set_Handle,
                                       BLE_MIN_ADV_INTERVAL,   // min. adv. interval (milliseconds * 1.6)
                                       BLE_MAX_ADV_INTERVAL,   // max. adv. interval (milliseconds * 1.6)
                                       BLE_MAX_ADV_DURATION,   // adv. duration
                                       BLE_MAX_ADV_MAXEVENT);  // max. num. adv. events
      BLE_sl_status_display(sc);

      // Set security
      //    sl_bt_sm_delete_bondings();
      sc = sl_bt_sm_configure(0x03,
                              sl_bt_sm_io_capability_displayonly);//00000011- all can connect
      BLE_sl_status_display(sc);

      // Set password
      sc = sl_bt_sm_set_passkey(BLE_PASWORD);
      BLE_sl_status_display(sc);

      // Start general advertising and enable connections.
      sc = sl_bt_advertiser_start(BLE_Advertising_Set_Handle,
                                  sl_bt_advertiser_general_discoverable,
                                  sl_bt_advertiser_connectable_scannable);
      BLE_sl_status_display(sc);

      break;

      //********************************** sl_bt_evt_connection_opened_id **********************************
    case sl_bt_evt_connection_opened_id:

#ifdef DEBUG_BLE_EVTs
      printf("BLE evt: connection open\n");
#endif

      sc = sl_bt_sm_increase_security(evt->data.evt_connection_opened.connection);
      BLE_sl_status_display(sc);

      if(evt->data.evt_connection_opened.bonding != 0xff)
        {
          BLE_Connection_Handle = evt->data.evt_connection_opened.connection;
          //BLE_Device_Connected = true;
          //configure BLE connection parameters
          sc = sl_bt_connection_set_parameters(BLE_Connection_Handle,
                                               BLE_MIN_INTERVAL,
                                               BLE_MAX_INTERVAL,
                                               BLE_LATENCY,
                                               BLE_TIMEOUT,
                                               BLE_MIN_CE_LEN,
                                               BLE_MAX_CE_LEN);
          BLE_sl_status_display(sc);

        }
      else
        {
          //Requesting to connect
        }
      //
      //      if(evt->data.evt_connection_opened.bonding != 0xff)//already bounding
      //        {
      //          BLE_Device_Connected = true;
      //          //configure BLE connection parameters
      //          sc = sl_bt_connection_set_parameters(evt->data.evt_connection_opened.connection,
      //                                               40,
      //                                               40,
      //                                               0,
      //                                               450,
      //                                               0,
      //                                               0xffff);
      //          //already bonded
      //        }
      break;

      //********************************** sl_bt_evt_connection_closed_id **********************************
    case sl_bt_evt_connection_closed_id:

#ifdef DEBUG_BLE_EVTs
      printf("BLE evt: connection closed\n");
#endif

      BLE_Device_Connected = false;
      // Start general advertising and enable connections.
      sc = sl_bt_advertiser_start(BLE_Advertising_Set_Handle,
                                  sl_bt_advertiser_general_discoverable,
                                  sl_bt_advertiser_connectable_scannable);
      BLE_sl_status_display(sc);

      break;

      //********************************** sl_bt_evt_sm_passkey_display_id *********************************
    case sl_bt_evt_sm_passkey_display_id:

#ifdef DEBUG_BLE_EVTs
      printf("BLE evt: display password\n");
#endif

      break;

      //************************************* sl_bt_evt_sm_bonded_id ***************************************
    case sl_bt_evt_sm_bonded_id:

#ifdef DEBUG_BLE_EVTs
      printf("BLE evt: bonded\n");
#endif

      BLE_Connection_Handle = evt->data.evt_connection_opened.connection;
      BLE_Device_Connected = true;
      sc = sl_bt_connection_set_parameters(BLE_Connection_Handle,
                                           BLE_MIN_INTERVAL,
                                           BLE_MAX_INTERVAL,
                                           BLE_LATENCY,
                                           BLE_TIMEOUT,
                                           BLE_MIN_CE_LEN,
                                           BLE_MAX_CE_LEN);
      BLE_sl_status_display(sc);

      break;

      //********************************** sl_bt_evt_sm_bonding_failed_id **********************************
    case sl_bt_evt_sm_bonding_failed_id:

#ifdef DEBUG_BLE_EVTs
      printf("BLE evt: bonding failed\n");
#endif

      sc = sl_bt_connection_close(evt->data.evt_sm_bonding_failed.connection);
      BLE_sl_status_display(sc);

      BLE_Device_Connected = false;
      break;

      //************************* sl_bt_evt_gatt_server_characteristic_status_id ***************************
    case sl_bt_evt_gatt_server_characteristic_status_id:;

#ifdef DEBUG_BLE_EVTs
    printf("BLE evt: server char status\n");
#endif

    break;

    //************************* sl_bt_evt_gatt_server_attribute_value_id ***************************
    case sl_bt_evt_gatt_server_attribute_value_id:;

#ifdef DEBUG_BLE_EVTs
    printf("BLE evt: server attribute value\n");
#endif

    if(gattdb_systick_fromCenteral == evt->data.evt_gatt_server_characteristic_status.characteristic)
      {

        sc = sl_bt_gatt_server_read_attribute_value(gattdb_systick_fromCenteral,
                                                    0,
                                                    sizeof(buf),
                                                    &bufSize,
                                                    &buf);
        if(sc != SL_STATUS_OK)
          {
            BLE_sl_status_display(sc);
          }
      }
    break;

    //********************************************* Default **********************************************
    default:;

    uint32_t Step = SL_BT_MSG_ID(evt->header);

#ifdef DEBUG_BLE_EVTs
    printf("BLE evt: unknowen %ls\n", Step);
#endif

    break;
  }
}

