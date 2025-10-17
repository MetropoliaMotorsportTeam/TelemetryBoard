/*
 * xbee.c
 *
 *  Created on: Jun 28, 2025
 *      Author: dovlatib
 */



#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "xbee.h"


//AT commands to send to the Xbee Module
uint8_t AT_ENTER[] = {'+','+','+'}; //Command to enter AT mode
uint8_t AT_EXIT[] = { 'A', 'T', 'C', 'N', 0x0D };
uint8_t AT_OK[] = {'O', 'K', 0x0D}; //AT OK response
uint8_t ATSD_R[] = {'A', 'T', 'S', 'D','1', 0x0D}; //AT soft reset command
uint8_t ATSD_S[] = {'A', 'T', 'S', 'D','0', 0x0D}; //AT shutdown command
uint8_t ATFR[] = {'A', 'T', 'F', 'R', 0x0D}; //Force reset command
uint8_t ATAI[] = {'A', 'T', 'A', 'I', 0x0D}; //Association indication command, tells state of connection


uint8_t AT_CONNECTED[] = {'0', 0x0D}; //Connected to internet
uint8_t AT_REG[] = {'2', '2', 0x0D}; //Registerring to cellular network
uint8_t AT_CON[] = {'2', '3', 0x0D}; //Connecting to internet
uint8_t AT_COR[] = {'2', '4', 0x0D}; //Firmware corrupt or missing
uint8_t AT_DEN[] = {'2', '5', 0x0D}; //Connection denied; may be power consumption related
uint8_t AT_AIR[] = {'2', 'A', 0x0D}; //In airplane mode
uint8_t AT_USB[] = {'2', 'B', 0x0D}; //USB Direct Active
uint8_t AT_PSM[] = {'2', 'C', 0x0D}; //Cellular component in PSM
uint8_t AT_SD[] = {'2', 'D', 0x0D}; //Modem shut down
uint8_t AT_VOL[] = {'2', 'E', 0x0D}; // Low voltage shut down
uint8_t AT_BYP[] = {'2', 'F', 0x0D}; //Bypass mode active
uint8_t AT_UPD[] = {'3', '0', 0x0D}; //Update in progress
uint8_t AT_TST[] = {'3', '1', 0x0D}; //Regulatory testing enabled
uint8_t AT_INI[] = {'F', 'F', 0x0D}; //Initializing

uint8_t uart_rx[4]; //UART receive Buffer
uint16_t last_element = 14;	 //Last array element location of rx_transmit
uint8_t *id_array[128];  // Array of pointers indicating location of any given ID in rx_transmit
uint8_t timeout_count = 0; //Timeout counter

//Enters AT Mode on XBee
bool Enter_AT(){
	HAL_UART_Transmit_IT(&huart5, AT_ENTER, sizeof(AT_ENTER));
	while (!FLAG.at_ok){
		__WFI();
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	HAL_UARTEx_ReceiveToIdle_IT(&huart5, uart_rx, sizeof(uart_rx));
		switch(Size)
		{
//		case 4:
//			if(!memcmp(uart_rx, MQTT_PUBACK, sizeof(MQTT_PUBACK))){
//				FLAG.transmit_ready = true;
//				timeout_count = 0;
//			}
//			else if(!memcmp(uart_rx, MQTT_CONACK, sizeof(MQTT_CONACK))){
//				FLAG.connected_mqtt = true;
//				FLAG.transmit_ready = true;
//			}
//			FLAG.at_ok = false;
//			memset(uart_rx, 0x00, sizeof(uart_rx));
//			break;
		case 3:
			if(!memcmp(uart_rx, AT_OK, sizeof(AT_OK)))
				FLAG.at_ok = true;
			else
				FLAG.at_ok = false;
			memset(uart_rx, 0x00, sizeof(uart_rx));
			break;
		case 2:
			if(!memcmp(uart_rx, AT_CONNECTED, sizeof(AT_CONNECTED)))
				FLAG.connected_net = true;
			FLAG.at_ok = false;
			memset(uart_rx, 0x00, sizeof(uart_rx));
			break;
		case 1:
			FLAG.at_ok = false;
			memset(uart_rx, 0x00, sizeof(uart_rx));
			break;
		default:
			break;
		}
}

void CheckInternet() {
	int count = 0;
	if (FLAG.xbee_fr == true)
		return; //Returns function if reset flag is true, or else it will be stuck in here for a while
	while (!FLAG.connected_net) {
		HAL_UART_Transmit_IT(&huart4, AT_ENTER, sizeof(AT_ENTER));
		while (!FLAG.at_ok) {
			__WFI();
		}

		HAL_Delay(2000);

		while (FLAG.at_ok && !FLAG.connected_net) {
			HAL_UART_Transmit_IT(&huart4, ATAI, sizeof(ATAI));
			HAL_GPIO_WritePin(Yellow_GPIO_Port, Yellow_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(Yellow_GPIO_Port, Yellow_Pin, GPIO_PIN_RESET);
			count++;

			if (count > 4) { //If over five AT AI messages has been sent without returning a connected value, there will be a 10 second delay until the next transmit
				HAL_Delay(10000);
				FLAG.at_ok = false;
			}
			if (count > 10) {
				FLAG.xbee_fr = true; //If over 10 AT AI messages have been sent without a connected value,  he xbee will be reset
				count = 0;
				return;
			}
		}
	}
	HAL_UART_Transmit_IT(&huart4, AT_EXIT, sizeof(AT_EXIT));
	if(FLAG.connected_net) {
		HAL_GPIO_WritePin(Yellow_GPIO_Port, Yellow_Pin, GPIO_PIN_SET);
	}
}
