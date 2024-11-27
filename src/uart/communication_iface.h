/**
 * @file: communication_iface.h
 * 
*/
#ifndef COMMUNICATION_IFACE_H
#define COMMUNICATION_IFACE_H

#include "comm/uart_comm.h"
#include "sys_app.h"
#include"app_event_message.h"

#define COMMAND_SLAVE_MASK  (0x8000)

/** function prototype */
void communication_iface_init(void);
void communication_iface_send_data(uint16_t cmd, uint8_t *buff, uint8_t len);
int communication_handler(EventContext *ev);
/** end of prototype function */

#endif /** COMMUNICATION_IFACE_H */
