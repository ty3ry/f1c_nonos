#ifndef SD_H
#define SD_H

/* SD card config */
#define DATA_WIDTH_1BIT 0
#define DATA_WIDTH_4BIT 1

#define SD_CARD_DATA_WIDTH  (DATA_WIDTH_1BIT)

/** reserved for another config */

/** end of SDCARD configuration */

void sd_init (void);
void sd_deinit (void);
int sd_card_detect (void);
int sd_card_init (void);
int sd_read (void *ptr, u32 addr, u32 cnt);
int sd_write (void *ptr, u32 addr, u32 cnt);

#endif