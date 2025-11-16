#include "MQTTNetwork.h"
#include "main.h"

extern UART_HandleTypeDef huart5;

int xbee_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    if (HAL_UART_Receive(&huart5, buffer, len, timeout_ms) == HAL_OK)
        return len;
    return 0;
}

int xbee_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    if (HAL_UART_Transmit(&huart5, buffer, len, timeout_ms) == HAL_OK)
        return len;
    return -1;
}

void NetworkInit(Network *n)
{
    n->mqttread = xbee_read;
    n->mqttwrite = xbee_write;
}
