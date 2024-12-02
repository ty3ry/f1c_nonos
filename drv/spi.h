#ifndef SPI_H
#define SPI_H

#include "f1c100s.h"


/** SPI Global Control Register */
typedef union {
    struct {
        uint32_t EN : 1;
        uint32_t MODE : 1;
        uint32_t RESV1 : 5;
        uint32_t TP_EN : 1;
        uint32_t RESV2 : 23;
        uint32_t SRST : 1;
    } bit;
    uint32_t word;
} GC_t;


/** SPI Transfer Control Register */
typedef union {
    struct {
        uint32_t CPHA : 1;
        uint32_t CPOL : 1;
        uint32_t SPOL : 1;
        uint32_t SSCTL : 1;
        uint32_t SS_SEL : 2;
        uint32_t SS_OWNER : 1;
        uint32_t SS_LEVEL : 1;
        uint32_t DHB : 1;
        uint32_t DDB : 1;
        uint32_t RPSM : 1;
        uint32_t SDC : 1;
        uint32_t FBS : 1;
        uint32_t SDM : 1;
        uint32_t RESV1 : 17;
        uint32_t XCH : 1;
    } bit;
    uint32_t word;
} TC_t;

/** SPI Interrupt Control Register */
typedef union {
    struct {
        uint32_t RF_RDY_INT_EN : 1;
        uint32_t RX_EMP_INT_EN : 1;
        uint32_t RF_FUL_INT_EN : 1;
        uint32_t RESV1 : 1;
        uint32_t TX_ERQ_INT_EN : 1;
        uint32_t TX_EMP_INT_EN : 1;
        uint32_t TX_FUL_INT_EN : 1;
        uint32_t RESV2 : 1;
        uint32_t RF_OVF_INT_EN : 1;
        uint32_t RF_UDR_INT_EN : 1;
        uint32_t TF_OVF_INT_EN : 1;
        uint32_t TF_UDR_INT_EN : 1;
        uint32_t TC_INT_EN : 1;
        uint32_t SS_INT_EN : 1;
        uint32_t RESV3 : 18;
    } bit;
    uint32_t word;
} IE_t;


/** SPI Interrupt Status Register */
typedef union {
    struct {
        uint32_t RX_RDY : 1;
        uint32_t RX_EMP : 1;
        uint32_t RX_FULL : 1;
        uint32_t RESV1 : 1;
        uint32_t TX_READY : 1;
        uint32_t TX_EMP : 1;
        uint32_t TX_FULL : 1;
        uint32_t RESV2 : 1;
        uint32_t RX_OVF : 1;
        uint32_t RX_UDF : 1;
        uint32_t TF_OVF : 1;
        uint32_t TF_UDF : 1;
        uint32_t TC : 1;
        uint32_t SSI : 1;
        uint32_t RESV3 : 18;
    } bit;
    uint32_t word;
} IS_t;

/** SPI FIFO Control Register */
typedef union {
    struct {
        uint32_t RX_TRIG_LEVEL : 8;
        uint32_t RF_DRQ_EN : 1;
        uint32_t RX_DMA_MODE : 1;
        uint32_t RX_FIFO_ACCESS_SIZE : 2;
        uint32_t RESV1 : 2;
        uint32_t RF_TEST : 1;
        uint32_t RF_RST : 1;
        uint32_t TX_TRIG_LEVEL : 8;
        uint32_t TF_DRQ_EN : 1;
        uint32_t RESV2 : 1;
        uint32_t TX_FIFO_ACCESS_SIZE : 2;
        uint32_t RESV3 : 2;
        uint32_t TF_TEST_EN : 1;
        uint32_t TX_FIFO_RST : 1;
    } bit;
    uint32_t word;
} FC_t;


/** SPI FIFO Status Register */
typedef union {
    struct {
        uint32_t RF_CNT : 8;
        uint32_t RESV1 : 4;
        uint32_t RB_CNT : 3;
        uint32_t RB_WR : 1;
        uint32_t TF_CNT : 8;
        uint32_t RESV2 : 4;
        uint32_t TB_CNT : 3;
        uint32_t TB_WR : 1;
    } bit;
    uint32_t word;
} FS_t;

/** SPI Wait Clock Register */
typedef union {
    struct {
        uint32_t WCC : 16;
        uint32_t SWC : 4;
        uint32_t RESV1 : 12;
    } bit;
    uint32_t word;
} WC_t;

/** SPI Clock Control Register */
typedef union {
    struct {
        uint32_t CDR2 : 8;
        uint32_t CDR1 : 4;
        uint32_t DRS : 1;
        uint32_t RESV1 : 19;
    } bit;
    uint32_t word;
} CC_t;


/** SPI Master Burst Counter Register */
typedef union {
    struct {
        uint32_t MBC : 24;
        uint32_t RESV : 18;
    } bit;
    uint32_t word;
} MBC_t;

/** SPI Master Transmit Counter Register */
typedef union {
    struct {
        uint32_t MWTC : 24;
        uint32_t RESV : 18;
    } bit;
    uint32_t word;
} MTC_t;

/** SPI Master Burst Control Counter Register */
typedef union {
    struct {
        uint32_t STC : 24;
        uint32_t DBC : 4;
        uint32_t DRM : 1;
        uint32_t RESV : 3;
    } bit;
    uint32_t word;
} BCC_t;

/** SPI TX Data Register */
typedef union {
    struct {
        uint32_t TDATA : 32;
    } bit;
    uint32_t word;
} TX_t;


/** SPI RX Data Register */
typedef union {
    struct {
        uint32_t RDATA : 32;
    } bit;
    uint32_t word;
} RX_t;


/** SPI Register */
typedef struct {
  __I  uint32_t   RESV1;
  __IO GC_t       GC;
  __IO TC_t       TC;
  __I  uint32_t   RESV2;
  __IO IE_t       IE;
  __IO IS_t       IS;
  __IO FC_t       FC;
  __IO FS_t       FS;
  __IO WC_t       WC;
  __IO CC_t       CC;
  __I  uint32_t   RESV3[2];
  __IO MBC_t      MBC;
  __IO MTC_t      MTC;
  __IO BCC_t      BCC;
  __I  uint32_t   RESV4[113];
  __O TX_t        TX;
  __I uint32_t    RESV5[63];
  __I RX_t        RX;
} SPI_t;

/** prototype function */
void spi_init (void);
void spi_deinit (void);
int spi_flash_read (u32 addr, void *buf, u32 len);
int spi_transmit (uint8_t *buf, u32 len);
void spi_init_periph (void);
/** end of prototype function  */

#endif