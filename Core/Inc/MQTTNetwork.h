#ifndef MQTTNETWORK_H
#define MQTTNETWORK_H

typedef struct Network
{
    int (*mqttread)(struct Network*, unsigned char*, int, int);
    int (*mqttwrite)(struct Network*, unsigned char*, int, int);
} Network;

void NetworkInit(Network *n);

#endif
