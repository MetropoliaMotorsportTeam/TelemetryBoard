/*
 * xbee.h
 *
 *  Created on: Jun 28, 2025
 *      Author: dovlatib
 */

#ifndef INC_XBEE_H_
#define INC_XBEE_H_

#include "main.h"
#include "MQTTNetwork.h"
#include "Timer.h"
#include "MQTTClient.h"
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

typedef struct sFlags {
    bool connected_net;
    bool connected_mqtt;
    bool waiting_ping_resp;
    bool transmit_ready;
    bool at_enabled;
    bool xbee_fr;
    bool at_ok;
}sFlags;

typedef struct CanFrame {
    uint32_t id;   // 11- or 29-bit CAN ID
    uint8_t  dlc;  // number of valid data bytes (0–8)
    uint8_t  data[8];
}CanFrame;


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

//MQTT Responses
extern uint8_t MQTT_CONACK[]; //Connection acknowlegement response
extern uint8_t MQTT_PUBACK[]; //Message published acknowlegement response
extern uint8_t MQTT_PINGRESP[];		   // ping response

extern uint8_t XBEE_ATVR[];
extern uint8_t XBEE_ATDE[];
extern uint8_t XBEE_ATDL[];
extern uint8_t MQTT_CONNECT_XBEE[];
extern uint8_t MQTT_PUBLISH_XBEE[];

extern uint8_t uart_rx[16]; //UART receive Buffer
extern UART_HandleTypeDef huart5;

void Enter_AT();
void CheckInternet();
void Send_MQTT();
void Send_ATVR_API();

void MQTT_Init(void);
void MQTT_Connect(void);
int MQTT_Connect_Paho(void);
void MQTT_Publish();
int MQTT_Publish_Paho(const char* topic, const char* payload);
int build_mqtt_publish_from_can_raw(const CanFrame *frame,
                                    const char *topic,
                                    uint8_t *out_buf,
                                    size_t out_buf_len);
int mqtt_encode_remaining_length(uint32_t len,
                                        uint8_t *out,
                                        size_t out_size);
void UART_Send(uint8_t *packet, uint16_t length);



#endif /* INC_XBEE_H_ */
