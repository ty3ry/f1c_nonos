#ifndef UART_H
#define UART_H

enum UART0_PORT { UART0_PE, UART0_PF };
enum UART1_PORT { UART1_PA, UART1_PD };
enum UART2_PORT { UART2_PD, UART2_PE };
enum UART_PAR   { UART_PAR_NO, UART_PAR_ODD, UART_PAR_EVEN };
enum UART_STP   { UART_STP_1, UART_STP_1_5 };
enum UART_LEN   { UART_5b, UART_6b, UART_7b, UART_8b };
#define UART_BR(x) (u16)(6000000L / x)

struct UART_CFG {
  u32 port    : 2;
  u32 parity  : 2;
  u32 stop    : 2;
  u32 lenght  : 2;
  u32 bitrate : 16;
};

/** new uart register mapping */
/** uart receiver buffer register */
typedef union {
  struct {
    uint32_t RBR : 8;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_RECV_BUFF_t;

/** uart transmit holding register */
typedef union {
  struct {
    uint32_t THR : 8;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_THR_t;

/*** uart Divisor lath low register */
typedef union {
  struct {
    uint32_t DLL : 8;       // Divisor Latch Low
                            // Lower 8 bits of a 16-bit, read/write, Divisor Latch register that contains the
                            // baud rate divisor for the UART. This register may only be accessed when
                            // the DLAB bit (LCR[7]) is set and the UART is not busy (USR[0] is zero).
                            // The output baud rate is equal to the serial clock (sclk) frequency divided by
                            // sixteen times the value of the baud rate divisor, as follows: baud rate =
                            // (serial clock freq) / (16 * divisor).
                            // Note that with the Divisor Latch Registers (DLL and DLH) set to zero, the
                            // baud clock is disabled and no serial communications occur. Also, once the
                            // DLL is set, at least 8 clock cycles of the slowest UART clock should be
                            // allowed to pass before transmitting or receiving data
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_DLL_t;

/** uart divisor latch high register */
typedef union {
  struct {
    uint32_t DLH : 8;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_DLH_t;

/** uart interrupt enable */
typedef union {
  struct {
    uint32_t ERBFI : 1;
    uint32_t ETBEI : 1;
    uint32_t ELSI : 1;
    uint32_t EDSSI : 1;
    uint32_t RESV1 : 3;
    uint32_t PTIME : 1;
    uint32_t RESV2 : 24;
  } bit;
  uint32_t word;
} UART_IE_t;

/** uart interrupt identity register */
typedef union {
  struct {
    uint32_t IID : 4;
    uint32_t RESV1 : 2;
    uint32_t FEFLAG : 2;
    uint32_t RESV2 : 24;
  } bit;
  uint32_t word;
} UART_IID_t;

/** uart fifo control register */
typedef union {
  struct {
    uint32_t FIFOE : 1;
    uint32_t RFIFOR : 1;
    uint32_t XFIFOR : 1;
    uint32_t DMAM : 1;
    uint32_t TFT : 2;
    uint32_t RT : 2;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_FIFO_CTRL_t;

/** uart line control register */
typedef union {
  struct {
    uint32_t DLS : 2;
    uint32_t STOP : 1;
    uint32_t PEN : 1;
    uint32_t EPS : 2;
    uint32_t BC : 1;
    uint32_t DLAB : 1;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_LINE_CTRL_t;

/** uart modem control register */
typedef union {
  struct {
    uint32_t DTR : 1;
    uint32_t RTS : 1;
    uint32_t RESV1 : 2;
    uint32_t LOOP : 1;
    uint32_t AFCE : 1;
    uint32_t SIRE : 1;
    uint32_t RESV : 25;
  } bit;
  uint32_t word;
} UART_MODEM_CTRL_t;

/** uart line status register */
typedef union {
  struct {
    uint32_t DR : 1;
    uint32_t OE : 1;
    uint32_t PARE : 1;
    uint32_t FRAE : 1;
    uint32_t BI : 1;
    uint32_t THRE : 1;
    uint32_t TEMT : 1;
    uint32_t FIFOERR : 1;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_LINE_STAT_t;

/** uart modem status register */
typedef union {
  struct {
    uint32_t DCTS : 1;
    uint32_t DDSR : 1;
    uint32_t TERI : 1;
    uint32_t DDCD : 1;
    uint32_t CTS : 1;
    uint32_t DSR : 1;
    uint32_t RI : 1;
    uint32_t DCD : 1;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_MODEM_STAT_t;

/** uart scratch register */
typedef union {
  struct {
    uint32_t SCRATCH : 8;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_SCRT_t;

/** uart status register */
typedef union {
  struct {
    uint32_t BUSY : 1;
    uint32_t TFNF : 1;
    uint32_t TFE : 1;
    uint32_t RFNE : 1;
    uint32_t RFF : 1;
    uint32_t RESV : 27;
  } bit;
  uint32_t word;
} UART_STAT_t;


/** uart transmit fifo level register */
typedef union {
  struct {
    uint32_t TFL : 7;
    uint32_t RESV : 25;
  } bit;
  uint32_t word;
} UART_TXFIFO_LEVEL_t;

/** uart fifo receive fifo level register */
typedef union {
  struct {
    uint32_t RFL : 7;
    uint32_t RESV : 25;
  } bit;
  uint32_t word;
} UART_RXFIFO_LEVEL_t;

/** uart halt tx register */
typedef union {
  struct {
    uint32_t HALT_TX : 1;
    uint32_t CHCFG_AT_BUSY : 1;
    uint32_t CHANGE_UPD : 1;
    uint32_t RESV1 : 1;
    uint32_t SIR_TX_INVERT : 1;
    uint32_t SIR_RX_INVERT : 1;
    uint32_t RESV2 : 26;
  } bit;
  uint32_t word;
} UART_HALT_TX_t;

/** uart dbg DLL register */
typedef union {
  struct {
    uint32_t DBG_DLL : 8;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_DBGDLL_t;


/** uart debug DLH register */
typedef union {
  struct {
    uint32_t DBG_DLH : 8;
    uint32_t RESV : 24;
  } bit;
  uint32_t word;
} UART_DBGDLH_t;


/** uart register handler */
typedef struct
{
  union {
    __I  UART_RECV_BUFF_t    rx_buff;
    __O  UART_THR_t          thr;
    __IO UART_DLL_t          dll;
  };
  union {
    __IO UART_IE_t           ie;
    __IO UART_DLH_t          dlh;
  };
  union {
    __I UART_IID_t          iid;
    __O UART_FIFO_CTRL_t    fifo_ctrl;
  };
  __IO UART_LINE_CTRL_t      line_ctrl;
  __IO UART_MODEM_CTRL_t     modem_ctrl;
  __I  UART_LINE_STAT_t      line_stat;
  __I  UART_MODEM_STAT_t     modem_stat;
  __I  UART_SCRT_t           scratch;
  __I  uint32_t              RESV1[23];
  __I  UART_STAT_t           stat;
  __I  UART_TXFIFO_LEVEL_t   tx_fifo_level;
  __I  UART_RXFIFO_LEVEL_t   rx_fifo_level;
  __I  uint32_t              RESV2[7];
  __I  UART_HALT_TX_t        halt_tx;
} UART_t;

/** end of uart register mapping */

int uart_init (UART_T *UART, struct UART_CFG cfg);
int uart_put (UART_T *UART, u8 c);
int uart_rx_check (UART_T *UART);
int uart_get (UART_T *UART);

#endif