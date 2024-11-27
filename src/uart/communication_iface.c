/**
 * @brief   application layer for uart communication
 * 
 * @date    27/11/2024
 * @author  c_e (cosmas.es08@gmail.com)
 */

#include "communication_iface.h"


/** extern variable */

/** end of extern variable */

/** extern function */
/** end of extern function */

/***
 * @brief   communication interface init
 * @param   none
*/
void communication_iface_init(void)
{
    /** init action communication uart */
    uart_comm_init();
}


static void tone_communication_handler(uint16_t cmd, uint8_t *data, EventContext *ev)
{
    uint8_t temp = 0;

    switch ( cmd ) {
        /** command from slave handler */
        case CMD_AUDIO_SET_VOLUME|COMMAND_SLAVE_MASK:
            break;
        case CMD_AUDIO_GET_VOLUME|COMMAND_SLAVE_MASK:

            break;
        case CMD_AUDIO_SET_BASS|COMMAND_SLAVE_MASK:
            break;
        case CMD_AUDIO_SET_MIDD|COMMAND_SLAVE_MASK:
            break;

        case CMD_AUDIO_SET_TREB|COMMAND_SLAVE_MASK:
            break;

        case CMD_AUDIO_MUTE|COMMAND_SLAVE_MASK: /** set to toggle */
            break;
        case CMD_AUDIO_UNMUTE|COMMAND_SLAVE_MASK:
            break;
        /** end of command from slave handler */

        /** command from master handler */
        case CMD_AUDIO_SET_VOLUME:
            printf("Set volume: %d \n", data[0]);
            temp = data[0];
            communication_iface_send_data(CMD_AUDIO_SET_VOLUME, &temp, 1);
            break;
        case CMD_AUDIO_GET_VOLUME:

            break;
        case CMD_AUDIO_SET_BASS:
            break;
        case CMD_AUDIO_SET_MIDD:
            break;

        case CMD_AUDIO_SET_TREB:
            break;

        case CMD_AUDIO_MUTE: /** set to toggle */
            break;
        case CMD_AUDIO_UNMUTE:
            break;

        default: break;
    }
}

static void mode_communication_handler(uint16_t cmd, uint8_t *data, EventContext *ev)
{
    switch ( cmd ) {
        /** command receive from slave */
        case CMD_SET_MODE|COMMAND_SLAVE_MASK:

            break;

        /** end of command receive from slave */

        /** command receive from master */
        case CMD_SET_MODE:

            break;
        /** end of command receive from master */
        default: break;
    }
}


static void system_communication_handler(uint16_t cmd, uint8_t *data, EventContext *ev)
{
    switch ( cmd ) {
        case CMD_SYSTEM_TOGGLE_SOMETHING:
            ev->eventId = MSG_TOGGLE_SOMETHING;
            break;
        case CMD_SYSTEM_CHECK_SOFT_VERSION:

            break;
        default: break;
    }
}


static void player_communication_handler(uint16_t cmd, uint8_t *data, EventContext *ev)
{
    switch ( cmd ) {
        /** command receive from slave */
        case CMD_PLAYER_PLAY|COMMAND_SLAVE_MASK:
            /** data ack */
            break;

        case CMD_PLAYER_PAUSE|COMMAND_SLAVE_MASK:
            /** data ack */
            break;
        case CMD_PLAYER_NEXT|COMMAND_SLAVE_MASK:
            /** data ack */
            break;

        case CMD_PLAYER_PREV|COMMAND_SLAVE_MASK:
            /** data ack */
            break;
        
        /** end of command receive from slave */

        /** command receive from master */
        case CMD_PLAYER_PLAY:

            break;

        case CMD_PLAYER_PAUSE:

            break;
        case CMD_PLAYER_NEXT:

            break;

        case CMD_PLAYER_PREV:

            break;
        
        /** end of command receive from master */
        default: break;
    }
}


inline void communication_iface_send_data(uint16_t cmd, uint8_t *buff, uint8_t len)
{
    uart_comm_send_command(cmd, buff, len);
}


/**
 * @brief   communication handler
 * @note    placed on main loop
*/
int communication_handler(EventContext *ev)
{
    uint16_t CmdCode = 0;
    uint8_t CmdClass = 0;

    if ( !uart_comm_scan_data())
    {
        /** some protocol error */
        return;
    }

    CmdCode = ( (uart_comm.rx_buffer[1] << 8) + uart_comm.rx_buffer[2]);
    /** remove high bit (MSB) --> reply from slave */
    //CmdCode &= 0x7FFF;

    if (CmdCode != 0xF800)
    	CmdClass = ((CmdCode & 0x7fff) >> 8) & 0xff;
    else
    	CmdClass = (CmdCode >> 8) & 0xff;


    switch( CmdClass )
    {
        case CMD_SYSTEM_CLASS:
            system_communication_handler(CmdCode, &uart_comm.rx_buffer[3], ev);
            break;

        case CMD_PLAYER_CLASS:
            player_communication_handler(CmdCode, &uart_comm.rx_buffer[3], ev);
            break;
            
        case CMD_AUDIO_CLASS:
            tone_communication_handler(CmdCode, &uart_comm.rx_buffer[3], ev);
            break;

        case CMD_MODE_CLASS:
            mode_communication_handler(CmdCode, &uart_comm.rx_buffer[3], ev);
            break;

        default: break;
    }

    return 0;
}

