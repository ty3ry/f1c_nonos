#ifndef SYS_APP_H
#define SYS_APP_H

#include "sys_app.h"

typedef struct
{
	uint16_t		eventId;
    uint8_t         data;
}EventContext;

enum
{
    SYS_MODE_STANDBY = 0x00,
    SYS_MODE_BOOTING,
	//SYS_MODE_MAIN,
    SYS_MODE_LINEIN,
    SYS_MODE_BLUETOOTH,
    SYS_MODE_OPTICAL,
    SYS_MODE_USB_DISK,
    SYS_MODE_USB_AUDIO,
	SYS_MODE_NUM,
};

enum
{
    TASK_STATE_IDLE = 0x00,
    TASK_STATE_INIT,
    TASK_STATE_RUN,
    TASK_STATE_PAUSE,
    TASK_STATE_STOP,
};


typedef struct action
{
    uint8_t function;
    uint8_t last_function;
    uint8_t volume;
    uint8_t device_link;
    uint8_t pre_device_link;

    uint8_t handshake_valid :1;
    uint8_t player_state : 3;
}Action_t;

typedef struct tone
{
    uint8_t bass;
    uint8_t treble;
}Tone_t;

typedef struct fsc
{
    /**
     * mode(0-3,default:)
     *  0: BT Mode
     *  1: LineIn Mode
     *  2: Spdif Mode
     *  3: I2S Mode
     */
    uint8_t auxcfg; /** fsc mode */
    uint8_t pre_auxcfg;

    uint8_t a2dp_state;
    uint8_t pre_a2dp_state;

}FSC_t;

typedef struct sys_app
{
	uint8_t volume;
	uint8_t current_function;
    uint8_t pre_function;

    FSC_t fsc;

    Action_t action;
    Tone_t tone;

}SystemConfig_t;

/**
 * player status
 */
enum
{
    PLAY_STATE_STOP = 0,
    PLAY_STATE_PLAYING,
    PLAY_STATE_PAUSED,
    PLAY_STATE_FF,
    PLAY_STATE_FR,
};


typedef union
{
    struct
    {
        uint32_t bit0 : 1;
        uint32_t bit1 : 1;
        uint32_t bit2 : 1;
        uint32_t bit3 : 1;
        uint32_t bit4 : 1;
        uint32_t bit5 : 1;
        uint32_t bit6 : 1;
        uint32_t bit7 : 1;
        uint32_t bit8 : 1;
        uint32_t bit9 : 1;
        uint32_t bit10 : 1;
        uint32_t bit11 : 1;
        uint32_t bit12 : 1;
        uint32_t bit13 : 1;
        uint32_t bit14 : 1;
        uint32_t bit15 : 1;
        uint32_t bit16 : 1;
        uint32_t bit17 : 1;
        uint32_t bit18 : 1;
        uint32_t bit19 : 1;
        uint32_t bit20 : 1;
        uint32_t bit21 : 1;
        uint32_t bit22 : 1;
        uint32_t bit23 : 1;
        uint32_t bit24 : 1;
        uint32_t bit25 : 1;
        uint32_t bit26 : 1;
        uint32_t bit27 : 1;
        uint32_t bit28 : 1;
        uint32_t bit29 : 1;
        uint32_t bit30 : 1;
        uint32_t bit31 : 1;
    };
    uint32_t mask;
} gFlag_t;


/** protype function */

/** end of prototype function */

#endif /*SYS_APP_H*/
