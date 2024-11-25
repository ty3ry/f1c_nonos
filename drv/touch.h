/******************************************************************************
 * @file     	touch.h
 * 
 * @brief		driver for allwinner touch panel
 * 				The controller is a 4-wire resistive touch screen controller, 
 * 				includes 12-bit resolution A/D converter. Especially, it
 * 				provides the ability of dual touch detection. 
 * 				The controller through the implementation of the two A/D 
 * 				conversion has been identified by the location of the screen 
 * 				of single touch, in addition to measurable increase in pressure 
 * 				on the touch screen 
 * 
 * @author		c_e (cosmas.es08@gmail.com) 
 * @note 		refer to linux device driver 
 * 				https://github.com/torvalds/linux/blob/master/drivers/input/touchscreen/sun4i-ts.c
 * 
 *****************************************************************************/
#ifndef TOUCH_H
#define TOUCH_H

#define TP_CTRL0		0x00
#define TP_CTRL1		0x04
#define TP_CTRL2		0x08
#define TP_CTRL3		0x0c
#define TP_INT_FIFOC		0x10
#define TP_INT_FIFOS		0x14
#define TP_TPR			0x18
#define TP_CDAT			0x1c
#define TEMP_DATA		0x20
#define TP_DATA			0x24

/* TP_CTRL0 bits */
#define ADC_FIRST_DLY(x)	((x) << 24) /* 8 bits */
#define ADC_FIRST_DLY_MODE(x)	((x) << 23)
#define ADC_CLK_SEL(x)		((x) << 22)
#define ADC_CLK_DIV(x)		((x) << 20) /* 3 bits */
#define FS_DIV(x)		((x) << 16) /* 4 bits */
#define T_ACQ(x)		((x) << 0) /* 16 bits */

/* TP_CTRL1 bits */
#define STYLUS_UP_DEBOUN(x)	((x) << 12) /* 8 bits */
#define STYLUS_UP_DEBOUN_EN(x)	((x) << 9)
#define TOUCH_PAN_CALI_EN(x)	((x) << 7)
#define TP_DUAL_EN(x)		((x) << 6)
#define TP_EN(x)		((x) << 5)
#define	TP_MODE_SELECT(x)	((x) << 4)
//#define TP_ADC_SELECT(x)	((x) << 3)
#define ADC_CHAN_SELECT(x)	((x) << 0)  /* 4 bits */

/* on sun6i, bits 3~6 are left shifted by 1 to 4~7 */
#define SUN6I_TP_MODE_EN(x)	((x) << 5)

/* TP_CTRL2 bits */
#define TP_SENSITIVE_ADJUST(x)	((x) << 28) /* 4 bits */
#define TP_FIFO_MODE_SELECT(x)	((x) << 26) /* 2 bits */
#define PRE_MEA_EN(x)		((x) << 24)
#define PRE_MEA_THRE_CNT(x)	((x) << 0) /* 24 bits */

/* TP_CTRL3 bits */
#define FILTER_EN(x)		((x) << 2)
#define FILTER_TYPE(x)		((x) << 0)  /* 2 bits */

/* TP_INT_FIFOC irq and fifo mask / control bits */
#define TEMP_IRQ_EN(x)		((x) << 18)
#define OVERRUN_IRQ_EN(x)	((x) << 17)
#define DATA_IRQ_EN(x)		((x) << 16)
#define TP_DATA_XY_CHANGE(x)	((x) << 13)
#define FIFO_TRIG(x)		((x) << 8)  /* 5 bits */
#define DATA_DRQ_EN(x)		((x) << 7)
#define FIFO_FLUSH(x)		((x) << 4)
#define TP_UP_IRQ_EN(x)		((x) << 1)
#define TP_DOWN_IRQ_EN(x)	((x) << 0)

/* TP_INT_FIFOS irq and fifo status bits */
#define TEMP_DATA_PENDING		(1<<18)
#define FIFO_OVERRUN_PENDING	(1<<17)
#define FIFO_DATA_PENDING		(1<<16)
#define TP_IDLE_FLG				(1<<2)
#define TP_UP_PENDING			(1<<1)
#define TP_DOWN_PENDING			(1<<0)

/* TP_TPR bits */
#define TEMP_ENABLE(x)		((x) << 16)
#define TEMP_PERIOD(x)		((x) << 0)  /* t = x * 256 * 16 / clkin */

/**
 *  TP control register 0
 */
typedef union {
	struct {
		uint32_t TACQ : 16;
		uint32_t FS_DIV : 4;
		uint32_t ADC_CLK_DIVIDER : 2;
		uint32_t ADC_CLK_SEL : 1;
		uint32_t ADC_FIRST_DLY_MODE : 1;
		uint32_t ADC_FIRST_DLY : 8;
	} bit;
	uint32_t word;
} TP_Ctrl0_t;

/**
 *  TP control register 1
 */
typedef union {
	struct {
		uint32_t ADC_CHAN0_SELECT : 1;
		uint32_t ADC_CHAN1_SELECT : 1;
		uint32_t ADC_CHAN2_SELECT : 1;
		uint32_t ADC_CHAN3_SELECT : 1;
		uint32_t TP_MODE_SEL : 1;
		uint32_t TP_EN : 1;
		uint32_t TP_DUAL_EN : 1;
		uint32_t TOUCH_PAN_CALI_EN : 1;
		uint32_t RESV1 : 1;
		uint32_t STYLUS_UP_DEBOUNCE_EN : 1;
		uint32_t RESV2 : 2;
		uint32_t STYLUS_UP_DEBOUNCE : 8;
		uint32_t RESV3 : 12;
	} bit;
	uint32_t word;
} TP_Ctrl1_t;


/**
 *  TP control register 2
 */
typedef union {
	struct {
		uint32_t PRE_MEA_THRE_CNT : 24;
		uint32_t PRE_MEA_EN : 1;
		uint32_t RESV : 1; 
		uint32_t TP_FIFO_MODE_SELECT : 2;
		uint32_t TP_SENS_ADJUST : 4;
	} bit;
	uint32_t word;
} TP_Ctrl2_t;


/**
 *  TP control register 3
 */
typedef union {
	struct {
		uint32_t FILTER_TYPE : 2;
		uint32_t FILTER_EN : 1;
		uint32_t RESV : 29;
	} bit;
	uint32_t word;
} TP_Ctrl3_t;

/**
 *  TP interrupt FIFO control register
 */
typedef union {
	struct {
		uint32_t TP_DOWN_IRQ_EN : 1;
		uint32_t TP_UP_IRQ_EN : 1;
		uint32_t RESV1 : 2;
		uint32_t TP_FIFO_FLUSH : 1;
		uint32_t RESV2 : 2;
		uint32_t TP_DATA_DRQ_EN : 1;
		uint32_t TP_FIFO_TRIG_LEVEL : 5;
		uint32_t TP_DATA_XY_CHANGE : 1;
		uint32_t RESV3 : 2;
		uint32_t TP_DATA_IRQ_EN : 1;
		uint32_t TP_OVERRUN_IRQ_EN : 1;
		uint32_t RESV4 : 14;
	} bit;
	uint32_t word;
} TP_Int_Ctrl_t;

/**
 *  TP interrupt FIFO status register
 */
typedef union {
	struct {
		uint32_t TP_DOWN_PENDING1 : 1;
		uint32_t TP_UP_PENDING1 : 1;
		uint32_t TP_IDLE_FLAG : 1;
		uint32_t RESV1 : 5;
		uint32_t RXA_CNT : 5;
		uint32_t RESV2 : 3;
		uint32_t FIFO_DATA_PENDING1 : 1;
		uint32_t FIFO_OVERRUN_PENDING1 : 1;
		uint32_t RESV3 : 14;
	} bit;
	uint32_t word;
} TP_Int_Status_t;

/**
 *  TP common data register
 */
typedef union {
	struct {
		uint32_t TP_CDAT1 : 12;
		uint32_t RESV : 20;
	} bit;
	uint32_t word;
} TP_ComData_t;

/**
 *  TP data register
 */
typedef union {
	struct {
		uint32_t TP_DATAX : 12;
		uint32_t RESV : 20;
	} bit;
	uint32_t word;
} TP_Data_t;


typedef struct {
	__IO TP_Ctrl0_t tpctrl0;
	__IO TP_Ctrl1_t tpctrl1;
	__IO TP_Ctrl2_t tpctrl2;
	__IO TP_Ctrl3_t tpctrl3;
	__IO TP_Int_Ctrl_t tp_int_ctrl;
	__IO TP_Int_Status_t tp_int_stat;
	__IO uint32_t tpr_data;
	__IO TP_ComData_t tp_com_dat;
	__IO uint32_t t_data;
	__IO TP_Data_t tp_data;
} TouchPanel_t;


struct point {
	u32 x;
	u32 y;
};

struct ts_data {
	bool ignore_fifo_data;
    struct point pt;
	bool ready;
	int temp_data; 
};

void tp_irq_handler(void);
int tp_init(void);
int tp_read(struct point *p);

void touch_panel_irq_handler(void);
int touch_panel_init(void);
int touch_panel_read(struct point *p);

#endif /** end of TOUCH_H */