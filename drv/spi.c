#include "sys.h"

/******************************************************************************/
/*                                SPI0 (FLASH)                                */
/******************************************************************************/
#define spi_flash_select() SPI0->TC = 0x44
#define spi_flash_deselect() SPI0->TC = 0xC4

#define spi_periph_select() SPI1->TC = 0x44
#define spi_periph_deselect() SPI1->TC = 0xC4

void spi_init (void)
{
  CCU->BUS_CLK_GATING0 |= (1 << 20);  // SPI0
  CCU->BUS_SOFT_RST0 &= ~(1 << 20);
  CCU->BUS_SOFT_RST0 |= (1 << 20);
  PC->CFG0 = 0x2222;                  // PC0-CLK, PC1-CS, PC2-MISO, PC3-MOSI
  SPI0->CC = 0x1001;                  // AHB / 4 = 48MHz
  for(SPI0->GC = 0x80000083; SPI0->GC & 0x80000000;) {};
  spi_flash_deselect();
  for(SPI0->FC = 0x80408001; SPI0->FC & 0x80008000;) {};
}

void spi_init_periph (void)
{
  SPI_t *spi_cfg = SPI1; 

  CCU->BUS_CLK_GATING0 |= (1 << 21);  // SPI1
  CCU->BUS_SOFT_RST0 &= ~(1 << 21);
  CCU->BUS_SOFT_RST0 |= (1 << 21);

  PA->CFG0 = 0x6666;                  // PA0-CS, PA1-MOSI, PA2-CLK, PA3-MISO

  /*SPI1->CC = 0x100F;                  // AHB / 4 = 48MHz
  SPI1->GC = 0x80000083; 
  spi_periph_deselect();
  SPI1->FC = 0x80408001;*/
  //spi_periph_deselect();
  //SPI1->TC = 0xC4;
  

  spi_cfg->CC.bit.CDR2 = 15;
  spi_cfg->CC.bit.DRS = 1;

  spi_cfg->GC.bit.EN = 1;
  spi_cfg->GC.bit.MODE = 1; // master mode
  spi_cfg->GC.bit.TP_EN = 1;
  spi_cfg->GC.bit.SRST = 1;

  spi_cfg->FC.bit.RX_TRIG_LEVEL = 0x01;
  spi_cfg->FC.bit.RF_RST = 1;
  spi_cfg->FC.bit.TX_TRIG_LEVEL = 0x40;
  spi_cfg->FC.bit.TX_FIFO_RST = 1;

  spi_cfg->TC.bit.SPOL = 1;
  spi_cfg->TC.bit.SS_OWNER = 1;
  spi_cfg->TC.bit.SS_LEVEL = 1;
  spi_cfg->TC.bit.CPOL = 0;
  //SPI1->TC = 0xC4;

}

void spi_deinit (void)
{
  CCU->BUS_CLK_GATING0 &= ~(1 << 20);
  PC->CFG0 = 0x7777;
}

int spi_transmit (uint8_t *buf, u32 len)
{
  u8 i, *rx = (u8*)buf;
  SPI_t *spi_cfg = SPI1; 


  if(!buf || !len) return 1;
  //spi_periph_select();
  spi_cfg->MBC.bit.MBC = 1;
  spi_cfg->MTC.bit.MWTC = 1;
  spi_cfg->BCC.bit.STC = 1;
  /*SPI1->MBC = 1;
  SPI1->MTC = 1;
  SPI1->BCC = 1;*/

  for(i = len; i > 0; i--) {
    /*SPI0->MBC = i;
    SPI1->TX.byte = buf[len - i]; //buf[i] & 0x55AA55AA;
    SPI1->TC |= (1U << 31);*/
    spi_cfg->TX.bit.TDATA = buf[len-1];
    spi_cfg->TC.bit.XCH = 1;
    //for(SPI1->TC |= (1U << 31); SPI1->TC & (1U << 31); ) {};
  }

  //spi_periph_deselect();
  return 0;
}

int spi_flash_read (u32 addr, void *buf, u32 len)
{
  u8 i, *rx = (u8*)buf;
  if(!buf || !len) return 1;
  spi_flash_select();
  SPI0->MBC = 4;
  SPI0->MTC = 4;
  SPI0->BCC = 4;
  SPI0->TX.word = __builtin_bswap32((addr & 0x00FFFFFF) | 0x03000000);
  for(SPI0->TC |= (1U << 31); SPI0->TC & (1U << 31); ) {};
  SPI0->RX.word;
  do
  {
    i = len > 64 ? 64 : len;
    SPI0->MBC = i;
    SPI0->TC |= (1U << 31);
    len -= i;
    do
    {
      if(SPI0->FS & 0xFF)
      {
        *rx++ = SPI0->RX.byte;
        i--;
      }
    } while(i);
  } while(len);
  spi_flash_deselect();
  return 0;
}
