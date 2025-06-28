/*
 * xbee.h
 *
 *  Created on: Jun 28, 2025
 *      Author: dovlatib
 */

#ifndef INC_XBEE_H_
#define INC_XBEE_H_

struct sFlags
{
	bool connected_net;
	bool connected_mqtt;
	bool waiting_ping_resp;
	bool transmit_ready;
	bool at_enabled;
	bool xbee_fr;
	bool at_ok;
};
struct sFlags FLAG;

#endif /* INC_XBEE_H_ */
