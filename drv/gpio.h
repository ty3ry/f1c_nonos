/******************************************************************************
 * @brief   driver for f1c100/200 gpio 
 *          The chip has 6 ports for multi-functional input/out pins. They are 
 *          shown below:
 *          - Port A(PA): 4 input/output port
 *          - Port B(PB): 4 input/output port
 *          - Port C(PC): 4 input/output port
 *          - Port D(PD): 22 input/output port
 *          - Port E(PE) : 13 input/output port
 *          - Port F(PF) : 6 input/output port
 *          
 *          For various system configurations, these ports can be easily 
 *          configured by software. 
 *          All these ports can be configured as
 *          GPIO if multiplexed functions are not used. The total 4 group 
 *          external PIO interrupt sources are supported and interrupt mode 
 *          can be configured by software
 * 
 * @author  c_e (cosmas.es08@gmail.com)
 * 
 * @date    2024/11/23
 * 
 *****************************************************************************/
#ifndef GPIO_H
#define GPIO_H

enum {
    ALT0 = 0x00,
    ALT1,
    ALT2,
    ALT3,
    ALT4,
    ALT5,
    ALT6,
    ALT7,
};

/** pullup/pulldown register 0  */
enum {
    PU_PD_DISABLED = 0x00,
    PU_EN,
    PD_EN,
    PU_PD_RESERVED,
};

/** multi drive select level */
enum {
    DRIVE_LEVEL0 = 0x00,
    DRIVE_LEVEL1,
    DRIVE_LEVEL2,
    DRIVE_LEVEL3,
};

/**
 * external interrupt mode
 */
enum {
    EXTI_MODE_POSEDGE = 0,
    EXTI_MODE_NEGEDGE,
    EXTI_MODE_HIGH_LEVEL,
    EXTI_MODE_LOW_LEVEL,
    EXTI_MODE_DOUBLE_EDGE,
};

/** 
 * external interrupt configure register 0 
 * used for pin 0 ~ 7
 * */
typedef union
{
    struct {
        uint32_t P0_INT_MODE : 4;
        uint32_t P1_INT_MODE : 4;
        uint32_t P2_INT_MODE : 4;
        uint32_t P3_INT_MODE : 4;
        uint32_t P4_INT_MODE : 4;
        uint32_t P5_INT_MODE : 4;
        uint32_t P6_INT_MODE : 4;
        uint32_t P7_INT_MODE : 4;
    } bit;
    uint32_t word;
} EXTIConfig0_t;

/** 
 * external interrupt configure register 1
 * used for pin 8 ~ 15
 * */
typedef union
{
    struct {
        uint32_t P8_INT_MODE : 4;
        uint32_t P9_INT_MODE : 4;
        uint32_t P10_INT_MODE : 4;
        uint32_t P11_INT_MODE : 4;
        uint32_t P12_INT_MODE : 4;
        uint32_t P13_INT_MODE : 4;
        uint32_t P14_INT_MODE : 4;
        uint32_t P15_INT_MODE : 4;
    } bit;
    uint32_t word;
} EXTIConfig1_t;

/** 
 * external interrupt configure register 2 
 * used for pin 16 ~ 21
 * */
typedef union
{
    struct {
        uint32_t P16_INT_MODE : 4;
        uint32_t P17_INT_MODE : 4;
        uint32_t P18_INT_MODE : 4;
        uint32_t P19_INT_MODE : 4;
        uint32_t P20_INT_MODE : 4;
        uint32_t P21_INT_MODE : 4;
        uint32_t RESV : 8;
    } bit;
    uint32_t word;
} EXTIConfig2_t;

/** 
 * external interrupt control register
 * used for pin 0 ~ 21
 * */
typedef union
{
    struct {
        uint32_t P0_INT_EN : 1;
        uint32_t P1_INT_EN : 1;
        uint32_t P2_INT_EN : 1;
        uint32_t P3_INT_EN : 1;
        uint32_t P4_INT_EN : 1;
        uint32_t P5_INT_EN : 1;
        uint32_t P6_INT_EN : 1;
        uint32_t P7_INT_EN : 1;
        uint32_t P8_INT_EN : 1;
        uint32_t P9_INT_EN : 1;
        uint32_t P10_INT_EN : 1;
        uint32_t P11_INT_EN : 1;
        uint32_t P12_INT_EN : 1;
        uint32_t P13_INT_EN : 1;
        uint32_t P14_INT_EN : 1;
        uint32_t P15_INT_EN : 1;
        uint32_t P16_INT_EN : 1;
        uint32_t P17_INT_EN : 1;
        uint32_t P18_INT_EN : 1;
        uint32_t P19_INT_EN : 1;
        uint32_t P20_INT_EN : 1;
        uint32_t P21_INT_EN : 1;
        uint32_t RESV : 11;
    } bit;
    uint32_t word;
} EXTICtrl_t;

/** 
 * external interrupt status register
 * used for pin 0 ~ 21
 * */
typedef union
{
    struct {
        uint32_t P0_INT_STAT : 1;
        uint32_t P1_INT_STAT : 1;
        uint32_t P2_INT_STAT : 1;
        uint32_t P3_INT_STAT : 1;
        uint32_t P4_INT_STAT : 1;
        uint32_t P5_INT_STAT : 1;
        uint32_t P6_INT_STAT : 1;
        uint32_t P7_INT_STAT : 1;
        uint32_t P8_INT_STAT : 1;
        uint32_t P9_INT_STAT : 1;
        uint32_t P10_INT_STAT : 1;
        uint32_t P11_INT_STAT : 1;
        uint32_t P12_INT_STAT : 1;
        uint32_t P13_INT_STAT : 1;
        uint32_t P14_INT_STAT : 1;
        uint32_t P15_INT_STAT : 1;
        uint32_t P16_INT_STAT : 1;
        uint32_t P17_INT_STAT : 1;
        uint32_t P18_INT_STAT : 1;
        uint32_t P19_INT_STAT : 1;
        uint32_t P20_INT_STAT : 1;
        uint32_t P21_INT_STAT : 1;
        uint32_t RESV : 11;
    } bit;
    uint32_t word;
} EXTIStatus_t;

/** 
 * external interrupt debounce register
 * used for pin 0 ~ 21
 * */
typedef union
{
    struct {
        uint32_t PIO_INT_CLK_SELECT : 1;        // PIO_INT_CLK_SELECT
                                                // PIO Interrupt Clock Select
                                                // 0: LOSC 32Khz
                                                // 1: HOSC 24Mhz

        uint32_t RESV1 : 3;                     
        uint32_t DEB_CLK_PRE_SCALE : 3;         // DEB_CLK_PRE_SCALE
                                                // Debounce Clock Pre-scale n
                                                // The selected clock source is prescaled by 2^n
        uint32_t RESV2 : 25;
    } bit;
    uint32_t word;
} EXTIDebounce_t;



/** 
 * external interrupt configure register 3 
 * reserved
 * */
typedef union
{
    struct {
        uint32_t RESV : 32;
    } bit;
    uint32_t word;
} EXTIConfig3_t;


typedef struct {
    uint32_t pin;
    uint32_t mode;
    uint32_t drive;
    uint32_t pu_pd;
} GPIO_Init_t;

typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
}GPIO_PinState;

/** PORTA 0 CFG0 alternate function */
#define CFG0_PA0_INPUT      ((ALT0) << 0)
#define CFG0_PA0_OUTPUT     ((ALT1) << 0)
#define CFG0_PA0_TP_X1      ((ALT2) << 0)
#define CFG0_PA0_Reserved   ((ALT3) << 0)
#define CFG0_PA0_DA_BCLK    ((ALT4) << 0)
#define CFG0_PA0_UART1_RTS  ((ALT5) << 0)
#define CFG0_PA0_SPI1_CS    ((ALT6) << 0)
#define CFG0_PA0_DISABLED   ((ALT7) << 0)

/** PORTA-1 CFG0 alternate function */
#define CFG0_PA1_INPUT      ((ALT0) << 4)
#define CFG0_PA1_OUTPUT     ((ALT1) << 4)
#define CFG0_PA1_TP_X2      ((ALT2) << 4)
#define CFG0_PA1_Reserved   ((ALT3) << 4)
#define CFG0_PA1_DA_LRCK    ((ALT4) << 4)
#define CFG0_PA1_UART1_CTS  ((ALT5) << 4)
#define CFG0_PA1_SPI1_MOSI  ((ALT6) << 4)
#define CFG0_PA1_DISABLED   ((ALT7) << 4)

/** PORTA-2 CFG0 alternate function */
#define CFG0_PA2_INPUT      ((ALT0) << 8)
#define CFG0_PA2_OUTPUT     ((ALT1) << 8)
#define CFG0_PA2_TP_Y1      ((ALT2) << 8)
#define CFG0_PA2_PWM0       ((ALT3) << 8)
#define CFG0_PA2_DA_IN      ((ALT4) << 8)
#define CFG0_PA2_UART1_RX   ((ALT5) << 8)
#define CFG0_PA2_SPI1_CLK   ((ALT6) << 8)
#define CFG0_PA2_DISABLED   ((ALT7) << 8)

/** PORTA-3 CFG0 alternate function */
#define CFG0_PA3_INPUT      ((ALT0) << 12)
#define CFG0_PA3_OUTPUT     ((ALT1) << 12)
#define CFG0_PA3_TP_Y2      ((ALT2) << 12)
#define CFG0_PA3_IR_RX      ((ALT3) << 12)
#define CFG0_PA3_DA_OUT     ((ALT4) << 12)
#define CFG0_PA3_UART1_TX   ((ALT5) << 12)
#define CFG0_PA3_SPI1_MISO  ((ALT6) << 12)
#define CFG0_PA3_DISABLED   ((ALT7) << 12)

/** PORTB-3 CFG0 alternate function */
#define CFG0_PB3_INPUT      ((ALT0) << 4)
#define CFG0_PB3_OUTPUT     ((ALT1) << 4)
#define CFG0_PB3_DDR_REF_D      ((ALT2) << 4)
#define CFG0_PB3_IR_RX          ((ALT3) << 4)
#define CFG0_PB3_Reserved1    ((ALT4) << 4)
#define CFG0_PB3_Reserved2  ((ALT5) << 4)
#define CFG0_PB3_Reserved3  ((ALT6) << 4)
#define CFG0_PB3_DISABLED   ((ALT7) << 4)

/** PORTC-0 CFG0 alternate function */
#define CFG0_PC0_Reserved1      ((ALT0) << 0)
#define CFG0_PC0_OUTPUT         ((ALT1) << 0)
#define CFG0_PC0_SPI0_CLK       ((ALT2) << 0)
#define CFG0_PC0_SDC1_CLK       ((ALT3) << 0)
#define CFG0_PC0_Reserved2      ((ALT4) << 0)
#define CFG0_PC0_Reserved3      ((ALT5) << 0)
#define CFG0_PC0_Reserved4      ((ALT6) << 0)
#define CFG0_PC0_DISABLED       ((ALT7) << 0)

/** PORTC-1 CFG0 alternate function */
#define CFG0_PC1_INPUT      ((ALT0) << 4)
#define CFG0_PC1_OUTPUT         ((ALT1) << 4)
#define CFG0_PC1_SPI0_CS       ((ALT2) << 4)
#define CFG0_PC1_SDC1_CMD      ((ALT3) << 4)
#define CFG0_PC1_Reserved1      ((ALT4) << 4)
#define CFG0_PC1_Reserved2      ((ALT5) << 4)
#define CFG0_PC1_Reserved3      ((ALT6) << 4)
#define CFG0_PC1_DISABLED       ((ALT7) << 4)

/** PORTC-2 CFG0 alternate function */
#define CFG0_PC2_INPUT      ((ALT0) << 8)
#define CFG0_PC2_OUTPUT         ((ALT1) << 8)
#define CFG0_PC2_SPI0_MISO       ((ALT2) << 8)
#define CFG0_PC2_SDC1_DO       ((ALT3) << 8)
#define CFG0_PC2_Reserved2      ((ALT4) << 8)
#define CFG0_PC2_Reserved3      ((ALT5) << 8)
#define CFG0_PC2_Reserved4      ((ALT6) << 8)
#define CFG0_PC2_DISABLED       ((ALT7) << 8)

/** PORTC-3 CFG0 alternate function */
#define CFG0_PC3_INPUT      ((ALT0) << 12)
#define CFG0_PC3_OUTPUT         ((ALT1) << 12)
#define CFG0_PC3_SPI0_MOSI       ((ALT2) << 12)
#define CFG0_PC3_UART0_TX       ((ALT3) << 12)
#define CFG0_PC3_Reserved1      ((ALT4) << 12)
#define CFG0_PC3_Reserved2      ((ALT5) << 12)
#define CFG0_PC3_Reserved3      ((ALT6) << 12)
#define CFG0_PC3_DISABLED       ((ALT7) << 12)

/** PORTD-0 CFG0 alternate function */
#define CFG0_PD0_INPUT          ((ALT0) << 0)
#define CFG0_PD0_OUTPUT         ((ALT1) << 0)
#define CFG0_PD0_LCD_D2         ((ALT2) << 0)
#define CFG0_PD0_TWI0_SDA       ((ALT3) << 0)
#define CFG0_PD0_RSB_SDA        ((ALT4) << 0)
#define CFG0_PD0_Reserved1      ((ALT5) << 0)
#define CFG0_PD0_EINTD0         ((ALT6) << 0)
#define CFG0_PD0_DISABLED       ((ALT7) << 0)

/** PORTD-1 CFG0 alternate function */
#define CFG0_PD1_INPUT          ((ALT0) << 4)
#define CFG0_PD1_OUTPUT         ((ALT1) << 4)
#define CFG0_PD1_LCD_D3         ((ALT2) << 4)
#define CFG0_PD1_UART1_RTS       ((ALT3) << 4)
#define CFG0_PD1_Reserved1        ((ALT4) << 4)
#define CFG0_PD1_Reserved2      ((ALT5) << 4)
#define CFG0_PD1_EINTD1         ((ALT6) << 4)
#define CFG0_PD1_DISABLED       ((ALT7) << 4)

/** PORTD-2 CFG0 alternate function */
#define CFG0_PD2_INPUT          ((ALT0) << 8)
#define CFG0_PD2_OUTPUT         ((ALT1) << 8)
#define CFG0_PD2_LCD_D4         ((ALT2) << 8)
#define CFG0_PD2_UART1_CTS       ((ALT3) << 8)
#define CFG0_PD2_Reserved1        ((ALT4) << 8)
#define CFG0_PD2_Reserved2      ((ALT5) << 8)
#define CFG0_PD2_EINTD2         ((ALT6) << 8)
#define CFG0_PD2_DISABLED       ((ALT7) << 8)

/** PORTD-3 CFG0 alternate function */
#define CFG0_PD3_INPUT          ((ALT0) << 12)
#define CFG0_PD3_OUTPUT         ((ALT1) << 12)
#define CFG0_PD3_LCD_D5         ((ALT2) << 12)
#define CFG0_PD3_UART1_RX       ((ALT3) << 12)
#define CFG0_PD3_Reserved1        ((ALT4) << 12)
#define CFG0_PD3_Reserved2      ((ALT5) << 12)
#define CFG0_PD3_EINTD3         ((ALT6) << 12)
#define CFG0_PD3_DISABLED       ((ALT7) << 12)

/** PORTD-4 CFG0 alternate function */
#define CFG0_PD4_INPUT          ((ALT0) << 16)
#define CFG0_PD4_OUTPUT         ((ALT1) << 16)
#define CFG0_PD4_LCD_D6         ((ALT2) << 16)
#define CFG0_PD4_UART1_TX       ((ALT3) << 16)
#define CFG0_PD4_Reserved1        ((ALT4) << 16)
#define CFG0_PD4_Reserved2      ((ALT5) << 16)
#define CFG0_PD4_EINTD4         ((ALT6) << 16)
#define CFG0_PD4_DISABLED       ((ALT7) << 16)

/** PORTD-5 CFG0 alternate function */
#define CFG0_PD5_INPUT          ((ALT0) << 20)
#define CFG0_PD5_OUTPUT         ((ALT1) << 20)
#define CFG0_PD5_LCD_D7         ((ALT2) << 20)
#define CFG0_PD5_TWI1_SCK       ((ALT3) << 20)
#define CFG0_PD5_Reserved1        ((ALT4) << 20)
#define CFG0_PD5_Reserved2      ((ALT5) << 20)
#define CFG0_PD5_EINTD5         ((ALT6) << 20)
#define CFG0_PD5_DISABLED       ((ALT7) << 20)

/** PORTD-6 CFG0 alternate function */
#define CFG0_PD6_INPUT          ((ALT0) << 24)
#define CFG0_PD6_OUTPUT         ((ALT1) << 24)
#define CFG0_PD6_LCD_D10         ((ALT2) << 24)
#define CFG0_PD6_TWI1_SDA       ((ALT3) << 24)
#define CFG0_PD6_Reserved1        ((ALT4) << 24)
#define CFG0_PD6_Reserved2      ((ALT5) << 24)
#define CFG0_PD6_EINTD6         ((ALT6) << 24)
#define CFG0_PD6_DISABLED       ((ALT7) << 24)

/** PORTD-7 CFG0 alternate function */
#define CFG0_PD7_INPUT          ((ALT0) << 28)
#define CFG0_PD7_OUTPUT         ((ALT1) << 28)
#define CFG0_PD7_LCD_D11         ((ALT2) << 28)
#define CFG0_PD7_DA_MCLK       ((ALT3) << 28)
#define CFG0_PD7_Reserved1        ((ALT4) << 28)
#define CFG0_PD7_Reserved2      ((ALT5) << 28)
#define CFG0_PD7_EINTD7         ((ALT6) << 28)
#define CFG0_PD7_DISABLED       ((ALT7) << 28)

// CONFIG1 Register =========================
/** PORTD-8 CFG1 alternate function */
#define CFG1_PD8_INPUT          ((ALT0) << 0)
#define CFG1_PD8_OUTPUT         ((ALT1) << 0)
#define CFG1_PD8_LCD_D12        ((ALT2) << 0)
#define CFG1_PD8_DA_BCLK        ((ALT3) << 0)
#define CFG1_PD8_Reserved1      ((ALT4) << 0)
#define CFG1_PD8_Reserved2      ((ALT5) << 0)
#define CFG1_PD8_EINTD8         ((ALT6) << 0)
#define CFG1_PD8_DISABLED       ((ALT7) << 0)

/** PORTD-9 CFG1 alternate function */
#define CFG1_PD9_INPUT          ((ALT0) << 4)
#define CFG1_PD9_OUTPUT         ((ALT1) << 4)
#define CFG1_PD9_LCD_D13        ((ALT2) << 4)
#define CFG1_PD9_DA_LRCK        ((ALT3) << 4)
#define CFG1_PD9_Reserved1      ((ALT4) << 4)
#define CFG1_PD9_Reserved2      ((ALT5) << 4)
#define CFG1_PD9_EINTD9         ((ALT6) << 4)
#define CFG1_PD9_DISABLED       ((ALT7) << 4)

/** PORTD-10 CFG1 alternate function */
#define CFG1_PD10_INPUT          ((ALT0) << 8)
#define CFG1_PD10_OUTPUT         ((ALT1) << 8)
#define CFG1_PD10_LCD_D14        ((ALT2) << 8)
#define CFG1_PD10_DA_IN        ((ALT3) << 8)
#define CFG1_PD10_Reserved1      ((ALT4) << 8)
#define CFG1_PD10_Reserved2      ((ALT5) << 8)
#define CFG1_PD10_EINTD10         ((ALT6) << 8)
#define CFG1_PD10_DISABLED       ((ALT7) << 8)

/** PORTD-11 CFG1 alternate function */
#define CFG1_PD11_INPUT          ((ALT0) << 12)
#define CFG1_PD11_OUTPUT         ((ALT1) << 12)
#define CFG1_PD11_LCD_D15        ((ALT2) << 12)
#define CFG1_PD11_DA_OUT        ((ALT3) << 12)
#define CFG1_PD11_Reserved1      ((ALT4) << 12)
#define CFG1_PD11_Reserved2      ((ALT5) << 12)
#define CFG1_PD11_EINTD11         ((ALT6) << 12)
#define CFG1_PD11_DISABLED       ((ALT7) << 12)

/** PORTD-12 CFG1 alternate function */
#define CFG1_PD12_INPUT          ((ALT0) << 16)
#define CFG1_PD12_OUTPUT         ((ALT1) << 16)
#define CFG1_PD12_LCD_D18        ((ALT2) << 16)
#define CFG1_PD12_TWI0_SCK        ((ALT3) << 16)
#define CFG1_PD12_RSB_SCK      ((ALT4) << 16)
#define CFG1_PD12_Reserved1      ((ALT5) << 16)
#define CFG1_PD12_EINTD11         ((ALT6) << 16)
#define CFG1_PD12_DISABLED       ((ALT7) << 16)

/** PORTD-13 CFG1 alternate function */
#define CFG1_PD13_INPUT          ((ALT0) << 20)
#define CFG1_PD13_OUTPUT         ((ALT1) << 20)
#define CFG1_PD13_LCD_D19        ((ALT2) << 20)
#define CFG1_PD13_UART2_TX        ((ALT3) << 20)
#define CFG1_PD13_Reserved1      ((ALT4) << 20)
#define CFG1_PD13_Reserved2      ((ALT5) << 20)
#define CFG1_PD13_EINTD13         ((ALT6) << 20)
#define CFG1_PD13_DISABLED       ((ALT7) << 20)

/** PORTD-14 CFG1 alternate function */
#define CFG1_PD14_INPUT          ((ALT0) << 24)
#define CFG1_PD14_OUTPUT         ((ALT1) << 24)
#define CFG1_PD14_LCD_D20        ((ALT2) << 24)
#define CFG1_PD14_UART2_RX        ((ALT3) << 24)
#define CFG1_PD14_Reserved1      ((ALT4) << 24)
#define CFG1_PD14_Reserved2      ((ALT5) << 24)
#define CFG1_PD14_EINTD14         ((ALT6) << 24)
#define CFG1_PD14_DISABLED       ((ALT7) << 24)

/** PORTD-15 CFG1 alternate function */
#define CFG1_PD15_INPUT          ((ALT0) << 28)
#define CFG1_PD15_OUTPUT         ((ALT1) << 28)
#define CFG1_PD15_LCD_D21        ((ALT2) << 28)
#define CFG1_PD15_UART2_RTS       ((ALT3) << 28)
#define CFG1_PD15_TWI2_SCK      ((ALT4) << 28)
#define CFG1_PD15_Reserved1      ((ALT5) << 28)
#define CFG1_PD15_EINTD15         ((ALT6) << 28)
#define CFG1_PD15_DISABLED       ((ALT7) << 28)

// CONFIG2 Register =========================
/** PORTD-16 CFG2 alternate function */
#define CFG2_PD16_INPUT          ((ALT0) << 0)
#define CFG2_PD16_OUTPUT         ((ALT1) << 0)
#define CFG2_PD16_LCD_D22        ((ALT2) << 0)
#define CFG2_PD16_UART2_CTS      ((ALT3) << 0)
#define CFG2_PD16_TWI2_SDA       ((ALT4) << 0)
#define CFG2_PD16_Reserved1      ((ALT5) << 0)
#define CFG2_PD16_EINTD16        ((ALT6) << 0)
#define CFG2_PD16_DISABLED       ((ALT7) << 0)

/** PORTD-17 CFG2 alternate function */
#define CFG2_PD17_INPUT          ((ALT0) << 4)
#define CFG2_PD17_OUTPUT         ((ALT1) << 4)
#define CFG2_PD17_LCD_D23        ((ALT2) << 4)
#define CFG2_PD17_OWA_OUT        ((ALT3) << 4)
#define CFG2_PD17_Reserved1      ((ALT4) << 4)
#define CFG2_PD17_Reserved2      ((ALT5) << 4)
#define CFG2_PD17_EINTD17        ((ALT6) << 4)
#define CFG2_PD17_DISABLED       ((ALT7) << 4)

/** PORTD-18 CFG2 alternate function */
#define CFG2_PD18_INPUT          ((ALT0) << 8)
#define CFG2_PD18_OUTPUT         ((ALT1) << 8)
#define CFG2_PD18_LCD_CLK        ((ALT2) << 8)
#define CFG2_PD18_SPI0_CS        ((ALT3) << 8)
#define CFG2_PD18_Reserved1      ((ALT4) << 8)
#define CFG2_PD18_Reserved2      ((ALT5) << 8)
#define CFG2_PD18_EINTD18        ((ALT6) << 8)
#define CFG2_PD18_DISABLED       ((ALT7) << 8)

/** PORTD-19 CFG2 alternate function */
#define CFG2_PD19_INPUT          ((ALT0) << 12)
#define CFG2_PD19_OUTPUT         ((ALT1) << 12)
#define CFG2_PD19_LCD_DE        ((ALT2) << 12)
#define CFG2_PD19_SPI0_MOSI        ((ALT3) << 12)
#define CFG2_PD19_Reserved1      ((ALT4) << 12)
#define CFG2_PD19_Reserved2      ((ALT5) << 12)
#define CFG2_PD19_EINTD19        ((ALT6) << 12)
#define CFG2_PD19_DISABLED       ((ALT7) << 12)

/** PORTD-20 CFG2 alternate function */
#define CFG2_PD20_INPUT          ((ALT0) << 16)
#define CFG2_PD20_OUTPUT         ((ALT1) << 16)
#define CFG2_PD20_LCD_HSYNC        ((ALT2) << 16)
#define CFG2_PD20_SPI0_CLK        ((ALT3) << 16)
#define CFG2_PD20_Reserved1      ((ALT4) << 16)
#define CFG2_PD20_Reserved2      ((ALT5) << 16)
#define CFG2_PD20_EINTD20        ((ALT6) << 16)
#define CFG2_PD20_DISABLED       ((ALT7) << 16)

/** PORTD-21 CFG2 alternate function */
#define CFG2_PD21_INPUT          ((ALT0) << 20)
#define CFG2_PD21_OUTPUT         ((ALT1) << 20)
#define CFG2_PD21_LCD_VSYNC        ((ALT2) << 20)
#define CFG2_PD21_SPI0_MISO        ((ALT3) << 20)
#define CFG2_PD21_Reserved1      ((ALT4) << 20)
#define CFG2_PD21_Reserved2      ((ALT5) << 20)
#define CFG2_PD21_EINTD21        ((ALT6) << 20)
#define CFG2_PD21_DISABLED       ((ALT7) << 20)

// CONFIG0 Register =========================
/** PORTE-0 CFG0 alternate function */
#define CFG0_PE0_INPUT          ((ALT0) << 0)
#define CFG0_PE0_OUTPUT         ((ALT1) << 0)
#define CFG0_PE0_CSI_HSYNC      ((ALT2) << 0)
#define CFG0_PE0_LCD_D0      ((ALT3) << 0)
#define CFG0_PE0_TWI2_SCK      ((ALT4) << 0)
#define CFG0_PE0_UART0_RX      ((ALT5) << 0)
#define CFG0_PE0_EINTE0        ((ALT6) << 0)
#define CFG0_PE0_DISABLED       ((ALT7) << 0)

/** PORTE-1 CFG0 alternate function */
#define CFG0_PE1_INPUT          ((ALT0) << 4)
#define CFG0_PE1_OUTPUT         ((ALT1) << 4)
#define CFG0_PE1_CSI_VSYNC      ((ALT2) << 4)
#define CFG0_PE1_LCD_D1         ((ALT3) << 4)
#define CFG0_PE1_TWI2_SDA       ((ALT4) << 4)
#define CFG0_PE1_UART0_TX       ((ALT5) << 4)
#define CFG0_PE1_EINTE1         ((ALT6) << 4)
#define CFG0_PE1_DISABLED       ((ALT7) << 4)

/** PORTE-2 CFG0 alternate function */
#define CFG0_PE2_INPUT          ((ALT0) << 8)
#define CFG0_PE2_OUTPUT         ((ALT1) << 8)
#define CFG0_PE2_CSI_PCLK      ((ALT2) << 8)
#define CFG0_PE2_LCD_D8         ((ALT3) << 8)
#define CFG0_PE2_CLK_OUT       ((ALT4) << 8)
#define CFG0_PE2_Reserved1      ((ALT5) << 8)
#define CFG0_PE2_EINTE2         ((ALT6) << 8)
#define CFG0_PE2_DISABLED       ((ALT7) << 8)

/** PORTE-3 CFG0 alternate function */
#define CFG0_PE3_INPUT          ((ALT0) << 12)
#define CFG0_PE3_OUTPUT         ((ALT1) << 12)
#define CFG0_PE3_CSI_D0      ((ALT2) << 12)
#define CFG0_PE3_LCD_D9         ((ALT3) << 12)
#define CFG0_PE3_DA_BCLK      ((ALT4) << 12)
#define CFG0_PE3_RSB_SCK       ((ALT5) << 12)
#define CFG0_PE3_EINTE3         ((ALT6) << 12)
#define CFG0_PE3_DISABLED       ((ALT7) << 12)

/** PORTE-4 CFG0 alternate function */
#define CFG0_PE4_INPUT          ((ALT0) << 16)
#define CFG0_PE4_OUTPUT         ((ALT1) << 16)
#define CFG0_PE4_CSI_D1     ((ALT2) << 16)
#define CFG0_PE4_LCD_D16         ((ALT3) << 16)
#define CFG0_PE4_DA_LRCK       ((ALT4) << 16)
#define CFG0_PE4_RSB_SDA       ((ALT5) << 16)
#define CFG0_PE4_EINTE4         ((ALT6) << 16)
#define CFG0_PE4_DISABLED       ((ALT7) << 16)

/** PORTE-5 CFG0 alternate function */
#define CFG0_PE5_INPUT          ((ALT0) << 20)
#define CFG0_PE5_OUTPUT         ((ALT1) << 20)
#define CFG0_PE5_CSI_D2      ((ALT2) << 20)
#define CFG0_PE5_LCD_D17         ((ALT3) << 20)
#define CFG0_PE5_DA_IN      ((ALT4) << 20)
#define CFG0_PE5_Reserved1       ((ALT5) << 20)
#define CFG0_PE5_EINTE5         ((ALT6) << 20)
#define CFG0_PE5_DISABLED       ((ALT7) << 20)

/** PORTE-6 CFG0 alternate function */
#define CFG0_PE6_INPUT          ((ALT0) << 24)
#define CFG0_PE6_OUTPUT         ((ALT1) << 24)
#define CFG0_PE6_CSI_D3     ((ALT2) << 24)
#define CFG0_PE6_PWM1         ((ALT3) << 24)
#define CFG0_PE6_DA_OUT      ((ALT4) << 24)
#define CFG0_PE6_OWA_OUT       ((ALT5) << 24)
#define CFG0_PE6_EINTE6         ((ALT6) << 24)
#define CFG0_PE6_DISABLED       ((ALT7) << 24)

/** PORTE-7 CFG0 alternate function */
#define CFG0_PE7_INPUT          ((ALT0) << 28)
#define CFG0_PE7_OUTPUT         ((ALT1) << 28)
#define CFG0_PE7_CSI_D4      ((ALT2) << 28)
#define CFG0_PE7_UART2_TX         ((ALT3) << 28)
#define CFG0_PE7_SPI1_CS       ((ALT4) << 28)
#define CFG0_PE7_Reserved       ((ALT5) << 28)
#define CFG0_PE7_EINTE7        ((ALT6) << 28)
#define CFG0_PE7_DISABLED       ((ALT7) << 28)

// CONFIG1 Register =========================
/** PORTE-8 CFG1 alternate function */
#define CFG1_PE8_INPUT          ((ALT0) << 0)
#define CFG1_PE8_OUTPUT         ((ALT1) << 0)
#define CFG1_PE8_CSI_D5         ((ALT2) << 0)
#define CFG1_PE8_UART2_RX       ((ALT3) << 0)
#define CFG1_PE8_SPI1_MOSI      ((ALT4) << 0)
#define CFG1_PE8_Reserved       ((ALT5) << 0)
#define CFG1_PE8_EINTE8         ((ALT6) << 0)
#define CFG1_PE8_DISABLED       ((ALT7) << 0)

/** PORTE-9 CFG1 alternate function */
#define CFG1_PE9_INPUT          ((ALT0) << 4)
#define CFG1_PE9_OUTPUT         ((ALT1) << 4)
#define CFG1_PE9_CSI_D6         ((ALT2) << 4)
#define CFG1_PE9_UART2_RTS       ((ALT3) << 4)
#define CFG1_PE9_SPI1_CLK      ((ALT4) << 4)
#define CFG1_PE9_Reserved       ((ALT5) << 4)
#define CFG1_PE9_EINTE9         ((ALT6) << 4)
#define CFG1_PE9_DISABLED       ((ALT7) << 4)

/** PORTE-10 CFG1 alternate function */
#define CFG1_PE10_INPUT          ((ALT0) << 8)
#define CFG1_PE10_OUTPUT         ((ALT1) << 8)
#define CFG1_PE10_CSI_D7         ((ALT2) << 8)
#define CFG1_PE10_UART2_CTS       ((ALT3) << 8)
#define CFG1_PE10_SPI1_MISO      ((ALT4) << 8)
#define CFG1_PE10_Reserved       ((ALT5) << 8)
#define CFG1_PE10_EINTE10         ((ALT6) << 8)
#define CFG1_PE10_DISABLED       ((ALT7) << 8)

/** PORTE-11 CFG1 alternate function */
#define CFG1_PE11_INPUT          ((ALT0) << 12)
#define CFG1_PE11_OUTPUT         ((ALT1) << 12)
#define CFG1_PE11_CLK_OUT        ((ALT2) << 12)
#define CFG1_PE11_TWI0_SCK       ((ALT3) << 12)
#define CFG1_PE11_IR_RX          ((ALT4) << 12)
#define CFG1_PE11_Reserved       ((ALT5) << 12)
#define CFG1_PE11_EINTE11        ((ALT6) << 12)
#define CFG1_PE11_DISABLED       ((ALT7) << 12)

/** PORTE-12 CFG1 alternate function */
#define CFG1_PE12_INPUT          ((ALT0) << 16)
#define CFG1_PE12_OUTPUT         ((ALT1) << 16)
#define CFG1_PE12_DA_MCLK        ((ALT2) << 16)
#define CFG1_PE12_TWI0_SDA       ((ALT3) << 16)
#define CFG1_PE12_PWM0           ((ALT4) << 16)
#define CFG1_PE12_Reserved       ((ALT5) << 16)
#define CFG1_PE12_EINTE12        ((ALT6) << 16)
#define CFG1_PE12_DISABLED       ((ALT7) << 16)

// CONFIG0 Register =========================
/** PORTF-0 CFG0 alternate function */
#define CFG0_PF0_INPUT          ((ALT0) << 0)
#define CFG0_PF0_OUTPUT         ((ALT1) << 0)
#define CFG0_PF0_SDC0_D1        ((ALT2) << 0)
#define CFG0_PF0_DBG_MS         ((ALT3) << 0)
#define CFG0_PF0_IR_RX          ((ALT4) << 0)
#define CFG0_PF0_Reserved       ((ALT5) << 0)
#define CFG0_PF0_EINTF0         ((ALT6) << 0)
#define CFG0_PF0_DISABLED       ((ALT7) << 0)

/** PORTF-1 CFG0 alternate function */
#define CFG0_PF1_INPUT          ((ALT0) << 4)
#define CFG0_PF1_OUTPUT         ((ALT1) << 4)
#define CFG0_PF1_SDC0_D0        ((ALT2) << 4)
#define CFG0_PF1_DBG_DI         ((ALT3) << 4)
#define CFG0_PF1_Reserved1      ((ALT4) << 4)
#define CFG0_PF1_Reserved2      ((ALT5) << 4)
#define CFG0_PF1_EINTF1         ((ALT6) << 4)
#define CFG0_PF1_DISABLED       ((ALT7) << 4)

/** PORTF-2 CFG0 alternate function */
#define CFG0_PF2_INPUT          ((ALT0) << 8)
#define CFG0_PF2_OUTPUT         ((ALT1) << 8)
#define CFG0_PF2_SDC0_CLK       ((ALT2) << 8)
#define CFG0_PF2_UART0_TX         ((ALT3) << 8)
#define CFG0_PF2_Reserved1      ((ALT4) << 8)
#define CFG0_PF2_Reserved2      ((ALT5) << 8)
#define CFG0_PF2_EINTF4         ((ALT6) << 8)
#define CFG0_PF2_DISABLED       ((ALT7) << 8)

/** PORTF-3 CFG0 alternate function */
#define CFG0_PF3_INPUT          ((ALT0) << 12)
#define CFG0_PF3_OUTPUT         ((ALT1) << 12)
#define CFG0_PF3_SDC0_CMD       ((ALT2) << 12)
#define CFG0_PF3_DBG_DO         ((ALT3) << 12)
#define CFG0_PF3_Reserved1      ((ALT4) << 12)
#define CFG0_PF3_Reserved2      ((ALT5) << 12)
#define CFG0_PF3_EINTF3         ((ALT6) << 12)
#define CFG0_PF3_DISABLED       ((ALT7) << 12)

/** PORTF-4 CFG0 alternate function */
#define CFG0_PF4_INPUT          ((ALT0) << 16)
#define CFG0_PF4_OUTPUT         ((ALT1) << 16)
#define CFG0_PF4_SDC0_D3        ((ALT2) << 16)
#define CFG0_PF4_UART0_TX         ((ALT3) << 16)
#define CFG0_PF4_Reserved1      ((ALT4) << 16)
#define CFG0_PF4_Reserved2      ((ALT5) << 16)
#define CFG0_PF4_EINTF4         ((ALT6) << 16)
#define CFG0_PF4_DISABLED       ((ALT7) << 16)

/** PORTF-5 CFG0 alternate function */
#define CFG0_PF5_INPUT          ((ALT0) << 20)
#define CFG0_PF5_OUTPUT         ((ALT1) << 20)
#define CFG0_PF5_SDC0_D2        ((ALT2) << 20)
#define CFG0_PF5_DBG_CK         ((ALT3) << 20)
#define CFG0_PF5_PWM1           ((ALT4) << 20)
#define CFG0_PF5_Reserved1      ((ALT5) << 20)
#define CFG0_PF5_EINTF5         ((ALT6) << 20)
#define CFG0_PF5_DISABLED       ((ALT7) << 20)

#define GPIO_PIN_0              (1 << 0)
#define GPIO_PIN_1              (1 << 1)
#define GPIO_PIN_2              (1 << 2)
#define GPIO_PIN_3              (1 << 3)
#define GPIO_PIN_4              (1 << 4)
#define GPIO_PIN_5              (1 << 5)
#define GPIO_PIN_6              (1 << 6)
#define GPIO_PIN_7              (1 << 7)
#define GPIO_PIN_8              (1 << 8)
#define GPIO_PIN_9              (1 << 9)
#define GPIO_PIN_10             (1 << 10)
#define GPIO_PIN_11             (1 << 11)
#define GPIO_PIN_12             (1 << 12)
#define GPIO_PIN_13             (1 << 13)
#define GPIO_PIN_14             (1 << 14)
#define GPIO_PIN_15             (1 << 15)
#define GPIO_PIN_16             (1 << 16)
#define GPIO_PIN_17             (1 << 17)
#define GPIO_PIN_18             (1 << 18)
#define GPIO_PIN_19             (1 << 19)
#define GPIO_PIN_20             (1 << 20)
#define GPIO_PIN_21             (1 << 21)
#define GPIO_PIN_22             (1 << 22)
#define GPIO_PIN_23             (1 << 23)

#define GPIO_PIN_All            (0xFFFFFF)

/**
 * multi driving register 0
 */
#define MULTI_DRIVE_SELECT(pio_num, val)    ((val) << (2*pio_num+1))

/**
 * pullup/pulldown ctrl register 0
 */
#define PU_PD_CTRL(pio_num, val)    ((val) << (2*pio_num+1))

/**
 * external interrupt set
 */
#define EXTI_CONFIG(pio_num, val)   ((val) << (4*pio_num+3))

/**
 * external interrupt enable
 * PD_EINT_CTRL
 * 0: disable
 * 1: enable
 */
#define EXTI_EN(x)          (1 << x)

/** external interrupt status  
 * EINT_STATUS
 * External INTn Pending Bit (n = 0~21)
 * 0: No IRQ pending
 * 1: IRQ pending
 * Write ‘1’ to clear
*/
#define EXTI_STATUS(x)      (1 << x)


#define PA0_SET_FUNC(x)  ((x) << 0)
#define PA1_SET_FUNC(x)  ((x) << 4)

#define CFG0_SET_FUNC(num, val)   ((val) << (4*num+2))
#define CFG1_SET_FUNC(num, val)   ((val) << (4*(num-8)+2))
#define CFG2_SET_FUNC(num, val)   ((val) << (4*(num-16)+2))
#define CFG3_SET_FUNC(num, val)   ((val) << (4*(num-24)+2))

/** prototype function */
int gpio_init(PIO_T *port, GPIO_Init_t *gpio_init);
void gpio_set_pin(PIO_T *port, uint32_t pin, uint8_t state);
bool gpio_get_pin(PIO_T *port, uint32_t pin);
void gpio_toggle_pin(PIO_T *port, uint32_t pin);
/** end of prototype function  */

#endif /** end of GPIO_H */
