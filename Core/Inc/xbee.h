/*
 * xbee.h
 *
 *  Created on: Jun 28, 2025
 *      Author: dovlatib
 */

#ifndef INC_XBEE_H_
#define INC_XBEE_H_

#include "main.h"
#include <stdbool.h>



//AT commands to send to the Xbee Module
extern uint8_t AT_ENTER[]; //Command to enter AT mode
extern uint8_t AT_EXIT[];
extern uint8_t AT_OK[]; //AT OK response
extern uint8_t ATSD_R[]; //AT soft reset command
extern uint8_t ATSD_S[]; //AT shutdown command
extern uint8_t ATFR[]; //Force reset command
extern uint8_t ATAI[]; //Association indication command, tells state of connection
extern uint8_t ATAN[];
extern uint8_t ATI[];
extern uint8_t ATVR[];
extern uint8_t ATAN_SETUP[];


extern uint8_t AT_CONNECTED[]; //Connected to internet
extern uint8_t AT_REG[]; //Registering to cellular network
extern uint8_t AT_CON[]; //Connecting to internet
extern uint8_t AT_COR[]; //Firmware corrupt or missing
extern uint8_t AT_DEN[]; //Connection denied; may be power consumption related
extern uint8_t AT_AIR[]; //In airplane mode
extern uint8_t AT_USB[]; //USB Direct Active
extern uint8_t AT_PSM[]; //Cellular component in PSM
extern uint8_t AT_SD[]; //Modem shut down
extern uint8_t AT_VOL[]; // Low voltage shut down
extern uint8_t AT_BYP[]; //Bypass mode active
extern uint8_t AT_UPD[]; //Update in progress
extern uint8_t AT_TST[]; //Regulatory testing enabled
extern uint8_t AT_INI[]; //Initializing

extern uint8_t uart_rx[16]; //UART receive Buffer
extern UART_HandleTypeDef huart5;

void Enter_AT();
void CheckInternet();

#endif /* INC_XBEE_H_ */
