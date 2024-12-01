/**
 * @file uart_comm.h.h
 * @author c_e (cosmas.eric.polytron.co.id)
 * @brief communcation driver for bt broadcaster (Actions MCU)
 * @version 0.1
 * @date 2023-05-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef UART_COMM_H
#define UART_COMM_H

#include "sys.h"
#include "circular_buffer.h"
#include "timeout.h"
#include "command.h"

/**
 * option for bluetooth broadcast to use ACK
 * so reply from bt broadcaster used to control 
 * current system state
 * 0: dont used ACK`ed
 * 1: used ACK`ed
*/
#define BT_BROADCASTER_REPLY_CONTROL_ACKED      (1)

#define CIRCULAR_BUFFER_LEN     32
#define UART_COMM_BUFF_LEN      16

/** header communication definition */
#define UART_COMM_HEADER1    (0xBE)
#define UART_COMM_HEADER2    (0xEF)

#define DEV_ROLE_MASTER 0
#define DEV_ROLE_SLAVE  1
#define UART_COM_ROLE   (DEV_ROLE_SLAVE)


/** handler for bt broadcaster */
typedef struct
{
    uint32_t *handler;
    uint8_t circular_buffer[CIRCULAR_BUFFER_LEN];
    MCU_CIRCULAR_CONTEXT cbCtx;
    uint8_t rx_buffer[UART_COMM_BUFF_LEN];
    TIMER timeout;

}UartComm_t;

/** define command */
#define BT_CMD_RESERVED     0x0000  /** reserved for future use */

/** bluetooth broadcaster ready status */
#define BT_CMD_DEVICE_CLASS         0x00
#define BT_CMD_DEVICE_READY_STATUS  0x0001


/** function prototype */
void uart_comm_irq_handler(void);
void uart_comm_init(void);
uint8_t uart_comm_scan_data(void);
void uart_comm_send_command(uint16_t cmd, uint8_t *buff, uint8_t len);
/** end of function prototype */

/** extern variable */
extern UartComm_t uart_comm;
/* end of extern variable */

#endif /*UART_COMM_H*/
