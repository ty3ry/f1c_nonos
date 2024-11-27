#include <stddef.h>
#include "sys.h"

static int uart_idx (UART_T *UART)
{
  if(UART == UART0) return 1 << 20;
  else if(UART == UART1) return 1 << 21;
  else if(UART == UART2) return 1 << 22;
  else return KO;
}

int uart_init (UART_T *UART, struct UART_CFG cfg)
{
  int mask;
  UART_t *uart_config = {0};

  uart_config = UART;
  
  if(UART == UART0)
  {
    if(cfg.port == UART0_PE)      // PE0=UART0_RX, PE1=UART0_TX
      PE->CFG0 = (PE->CFG0 & 0xFFFFFF00) | 0x00000055;
    else if(cfg.port == UART0_PF) // PF2=UART0_RX, PF4=UART0_TX
      PF->CFG0 = (PF->CFG0 & 0xFFF0F0FF) | 0x00030300;
    else return KO;
  }
  else if(UART == UART1)
  {
    if(cfg.port == UART1_PA)      // PA2=UART1_RX, PA3=UART1_TX
      PA->CFG0 = (PA->CFG0 & 0xFFFF00FF) | 0x00005500;
    else if(cfg.port == UART1_PD) // PD3=UART1_RX, PD4=UART1_TX
      PD->CFG0 = (PD->CFG0 & 0xFFF00FFF) | 0x00033000;
    else return KO;
  }
  else if(UART == UART2)
  {
    if(cfg.port == UART2_PD)      // PD14=UART2_RX, PE13=UART2_TX
      PD->CFG1 = (PD->CFG1 & 0xF00FFFFF) | 0x03300000;
    else if(cfg.port == UART2_PE) // PE8=UART2_RX, PE7=UART2_TX
    {
      PE->CFG0 = (PE->CFG0 & 0x0FFFFFFF) | 0x30000000;
      PE->CFG1 = (PE->CFG1 & 0xFFFFFFF0) | 0x00000003;
    }
    else return KO;
  }
  else return KO;
  mask = uart_idx(UART);
  CCU->BUS_CLK_GATING2 |= mask;
  CCU->BUS_SOFT_RST2 &= ~mask;
  CCU->BUS_SOFT_RST2 |= mask;

  /*UART->THR = 0;
  UART->FCR = 0xF7;
  UART->MCR = 0;
  UART->LCR = 0x80;
  UART->DLL = cfg.bitrate;
  UART->DLH = cfg.bitrate >> 8;
  UART->LCR = (cfg.parity << 3) | (cfg.stop << 2) | cfg.lenght;*/

  uart_config->thr.word = 0;
  uart_config->fifo_ctrl.bit.FIFOE = 1;
  uart_config->fifo_ctrl.bit.RFIFOR = 1;
  uart_config->fifo_ctrl.bit.XFIFOR = 1;
  uart_config->fifo_ctrl.bit.TFT = 3;  // FIFO 1/2 Full
  uart_config->fifo_ctrl.bit.RT = 3;    // FIFO 2 less than full
  
  uart_config->modem_ctrl.word = 0;
  uart_config->line_ctrl.bit.DLAB = 1;

  uart_config->dll.bit.DLL = cfg.bitrate;
  uart_config->dlh.bit.DLH = cfg.bitrate >> 8;
  uart_config->line_ctrl.bit.DLAB = 0;

  uart_config->line_ctrl.bit.DLS = cfg.lenght;
  uart_config->line_ctrl.bit.STOP = cfg.stop;
  uart_config->line_ctrl.bit.PEN = cfg.parity;

  return OK;
}

void uart_enable_irq(UART_T *UART)
{
  UART_t *puart = UART;

  /** generate irq on 1 byte FIFO */
  puart->fifo_ctrl.bit.RT = 0;
  /** enable IRQ */
  puart->ie.bit.ERBFI = 1;
}

int uart_put (UART_T *UART, u8 c)
{
  UART_t *puart = UART;

  while(!(puart->line_stat.bit.TEMT));
  puart->thr.bit.THR = c;
  return OK;
}

int uart_rx_check (UART_T *UART)
{
  UART_t *puart = UART;
  return puart->line_stat.bit.DR ? OK : KO;
}

int uart_get (UART_T *UART)
{
  UART_t *puart = UART;
  return uart_rx_check(UART) == KO ? KO : puart->rx_buff.bit.RBR;
}

