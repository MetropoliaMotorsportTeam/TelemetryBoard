#include "stm32g4xx.h"
#include "main.h"
#include "can.h"

extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;

extern FDCAN_TxHeaderTypeDef TxHeader;

extern FDCAN_RxHeaderTypeDef RxHeader;

uint8_t CAN_RxData[8];

CAN_Message MessageBuffer[256];
uint8_t MessageBufferIndex = 0;


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    /* Retreive Rx messages from RX FIFO0 */
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, CAN_RxData) != HAL_OK)
    {
    /* Reception Error */
    Error_Handler();
    }
    else{

            MessageBuffer[MessageBufferIndex].Id = RxHeader.Identifier;
            MessageBuffer[MessageBufferIndex].DLC = RxHeader.DataLength;
            for (int i = 0; i < RxHeader.DataLength; i++)
            {
                MessageBuffer[MessageBufferIndex].Bytes[i] = CAN_RxData[i];
            }
            MessageBuffer[MessageBufferIndex].CanNbr = (hfdcan->Instance == FDCAN2) ? 1 : 2;
            MessageBufferIndex++;
   
    }

    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
      /* Notification Error */
      Error_Handler();
    }
  }
}

void CanSend(uint8_t *TxData, uint32_t identifier, uint8_t CanBusNbr){

	TxHeader.Identifier = identifier;

    switch (CanBusNbr)
    {
        case 1:
            while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2) != 0 && HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader, TxData) != HAL_OK){
            Error_Handler();
            }
            break;
        case 2:
            while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2) != 0 && HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader, TxData) != HAL_OK){
            Error_Handler();
            }
            break;
        default:
            break;
    }
}

