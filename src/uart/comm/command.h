#ifndef COMMAND_H
#define COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

/**
 * Command define
 */

/** command system class */
#define CMD_SYSTEM_CLASS    0x01
#define CMD_SYSTEM_POWER    0x0101
#define CMD_SYSTEM_INIT     0x0102
#define CMD_SYSTEM_RESET    0x0103
#define CMD_SYSTEM_CHECK_SOFT_VERSION   0x0104
#define CMD_SYSTEM_TOGGLE_SOMETHING     0x0105

/** function/mode class */
#define CMD_MODE_CLASS  0x02
#define CMD_CHANGE_MODE 0x0201
#define CMD_GET_MODE    0x0202
#define CMD_SET_MODE    0x0203

/** command audio class  */
#define CMD_AUDIO_CLASS 0x03
#define CMD_AUDIO_SET_VOLUME    0x0301
#define CMD_AUDIO_GET_VOLUME    0x0302
#define CMD_AUDIO_SET_BASS      0x0303
#define CMD_AUDIO_GET_BASS      0x0304
#define CMD_AUDIO_SET_TREB      0x0305
#define CMD_AUDIO_GET_TREB      0x0306
#define CMD_AUDIO_SET_MIDD      0x0307
#define CMD_AUDIO_GET_MIDD      0x0308
#define CMD_AUDIO_MUTE          0x0309
#define CMD_AUDIO_UNMUTE        0x030A

/** command player class */
#define CMD_PLAYER_CLASS        0x04
#define CMD_PLAYER_PLAYPAUSE    0x0401
#define CMD_PLAYER_PLAY         0x0402
#define CMD_PLAYER_PAUSE        0x0403
#define CMD_PLAYER_STOP         0x0404
#define CMD_PLAYER_NEXT         0x0405
#define CMD_PLAYER_PREV         0x0406
#define CMD_PLAYER_FF           0x0407
#define CMD_PLAYER_FB           0x0408
#define CMD_PLAYER_STOP_FFFB    0x0409


#ifdef __cplusplus
}
#endif//__cplusplus

#endif /** end of COMMAND_H */

/**
 * @}
 * @}
 */
