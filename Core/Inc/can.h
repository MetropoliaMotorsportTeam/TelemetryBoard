#ifndef INC_CAN_H
#define INC_CAN_H



typedef struct{
	uint16_t Id;
	uint8_t DLC;
	uint8_t Bytes[8];
    uint8_t CanNbr;
}CAN_Message;

void CanSend(uint8_t *TxData, uint32_t identifier, uint8_t CanBusNbr );

#endif /* INC_CAN_H */