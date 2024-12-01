/**
 * @file: uart_comm_comm.h
 * @brief   driver for uart communication
 * 
*/

#include "uart_comm.h"
#include <stdint.h>

UartComm_t uart_comm;

/**
 * @brief process uart data 
 * 
 * @note    handler circular buffer content
 *          call at loop
*/
uint8_t uart_comm_scan_data(void)
{
    uint8_t CheckSum = 0;
	int i, len;
    static int rx_index = -2;
    uint8_t data_out;

    TimeoutSet(&uart_comm.timeout, 100);

    while( (len = MCUCircular_GetDataLen(&uart_comm.cbCtx)) > 0 )
    {
        if (IsTimeout(&uart_comm.timeout))
        {
            return 0;
        }

        /** get uart data */
        if (MCUCircular_GetData(&uart_comm.cbCtx, &data_out, 1) == 0)
        {
            /* reserved */
        }

        if(rx_index == -2)
        {
            if (data_out == UART_COMM_HEADER1) rx_index = -1;
        }
        else if (rx_index == -1)
        {
            if (data_out == UART_COMM_HEADER2) rx_index = 0;
        }
        else
        {
            uart_comm.rx_buffer[rx_index++] = data_out;
            if(uart_comm.rx_buffer[0] > UART_COMM_BUFF_LEN+3 )
            {
                rx_index = -2;
                continue;
            }
            /** check len on buffer[0] */
            if(rx_index >= uart_comm.rx_buffer[0] + 4)
            {
                CheckSum = 0;
                for(i = 0; i < rx_index; i++)
                {
                    CheckSum += uart_comm.rx_buffer[i];
                }
                rx_index = -2;
                return (CheckSum == 0) ? 1 : 0;
            }
        }

    }

    return 0;
}


/**
 * @brief   uart1 irq handler
 * 
 * @note    
*/
void uart_comm_irq_handler(void)
{
    UART_t *puart = uart_comm.handler;
    uint8_t temp = 0;

    if (puart->iid.bit.IID == IRQ_ID_RX_DATA_AVAIL) {
        temp = puart->rx_buff.bit.RBR;
        MCUCircular_PutData(&uart_comm.cbCtx, &temp, 1);
    }
}


/**
 * @brief   uart comm init
*/
void uart_comm_init(void)
{
    struct UART_CFG cfg ;
    UART_t uart_reg = {0};

    uart_comm.handler = UART2;

    cfg.port = UART2_PE;
    cfg.bitrate = UART_BR(115200);
    cfg.parity = UART_PAR_NO;
    cfg.stop = UART_STP_1;
    cfg.lenght = UART_8b;

    /** init uart */
    uart_init(uart_comm.handler, cfg);
    uart_enable_irq(uart_comm.handler);

    /** enable uart IRQ */
    IRQ_Init(IRQ_UART2, IRQ_PRIO_1);
    
    /** init circular buffer */
    MCUCircular_Config(&uart_comm.cbCtx, uart_comm.circular_buffer, CIRCULAR_BUFFER_LEN);
}

/**
 * @brief   send data uart per byte
 * @note    
*/
static void uart_comm_uart_send_byte(uint8_t data)
{
    uart_put(uart_comm.handler, data); 
}


/**
 * @brief   send command with defined protocol
*/
void uart_comm_send_command(uint16_t cmd, uint8_t *buff, uint8_t len)
{
    uint8_t CheckSum;
    uint8_t temp[5];
    uint8_t len_temp;

#if (UART_COM_ROLE==DEV_ROLE_SLAVE)
    cmd |= 0x8000;
#endif

    CheckSum = len + (uint8_t)(cmd >> 8) + (uint8_t)cmd;
    len_temp = len;

    while(len_temp)
    {
        CheckSum += buff[len_temp - 1];
        len_temp--;
    }
    CheckSum = 0 - CheckSum;
    temp[0] = UART_COMM_HEADER1;
    temp[1] = UART_COMM_HEADER2;
    temp[2] = len;
    temp[3] = (uint8_t)(cmd >> 8);  /** command byte 1 */
    temp[4] = (uint8_t)(cmd);       /** command byte 0 */

    /* send header and command */
    len_temp = 5;
    for(len_temp = 0; len_temp < 5; len_temp += 1)
    {
        uart_comm_uart_send_byte(temp[len_temp]);
    }

    if(len)
    {
        for(len_temp = 0; len_temp < len; len_temp += 1)
        {
            uart_comm_uart_send_byte(buff[len_temp]);
        }
       
    }
    uart_comm_uart_send_byte(CheckSum);
}
