/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
/******************************************************************************
 * File Name.c
 *
 *  Created on: June 23, 2022
 *  Author: Anis Shakkour
 *  Email:  anis.shakkour399@gmail.com
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app.h"

/*******************************************************************************
 * Data types
 ******************************************************************************/

/*******************************************************************************
 * Extern
 ******************************************************************************/

/*******************************************************************************
 * Interface Functions
 ******************************************************************************/
/*******************************************************************************
 * Function name:
 *
 * Description  :
 * Parameters   :
 * Returns      :
 *
 * Known issues :
 * Note         :
 ******************************************************************************/
void app_init(void)
{
  printf("Peripheral\n");

  Start_Advertising(&BLE_NAME,  BLE_NAME_LEN);

}

/*******************************************************************************
 * Function name:
 *
 * Description  :
 * Parameters   :
 * Returns      :
 *
 * Known issues :
 * Note         :
 ******************************************************************************/
void app_process_action(void)
{

}



/*******************************************************************************
 * Private Functions
 ******************************************************************************/
/*******************************************************************************
 * Function name:
 *
 * Description  :
 * Parameters   :
 * Returns      :
 *
 * Known issues :
 * Note         :
 ******************************************************************************/
