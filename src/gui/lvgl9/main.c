#include <stdio.h>
#include "sys.h"
#include "lvgl.h"
#include "lv_demos.h"

#define TS_GT911          0
#define TS_NS2009         1
#define TS_ALLWINNER_ADC  2 

#define TS_DEVICE         (TS_ALLWINNER_ADC)

/** enable touch scren calibration
 * 0: disable
 * 1: enable
 */
#define TS_CALIBRATE_EN   (0)

#include "lv_tc.h"
#include "lv_tc_screen.h"

#if (TS_CALIBRATE_EN)
void lv_tc_coeff_cb(lv_tc_coeff_t coeff)
{
  lv_tc_coeff_t *result_coeff = lv_tc_get_coeff();
  printf("Coeff: a:%f b:%f c:%f d:%f e:%f f:%f\n", result_coeff->a,
                                              result_coeff->b,
                                              result_coeff->c,
                                              result_coeff->d,
                                              result_coeff->e,
                                              result_coeff->f);
}
#endif

#if (TS_DEVICE==TS_GT911)
struct TS_GT911 ts = GT911_TS_INIT;
struct TWI_DEV ts_dev = { .bus = SYS_TWI_NUM, .addr = GT911_ADDR, .data = &ts };
#elif (TS_DEVICE==TS_NS2009)
struct TS_NS2009 ts = NS2009_TS_INIT;
struct TWI_DEV ts_dev = { .bus = SYS_TWI_NUM, .addr = NS2009_ADDR, .data = &ts };
#elif (TS_DEVICE==TS_ALLWINNER_ADC)
struct point ts;
void __attribute__((interrupt("IRQ"))) irq_handler(void)
{
  tp_irq_handler();
}
#endif

struct TWI_CFG twi = { .type = TWI_MASTER, .port = SYS_TWI_PORT, .clkmn = TWI_400kHz };

u16 *fb;


static void ts_read (lv_indev_t *indev, lv_indev_data_t *data)
{
#if (TS_DEVICE==TS_GT911)
  if(gt911_read(&ts_dev) == 1)
  {
    data->point.x = ts.pt[0].x;
    data->point.y = ts.pt[0].y;
#elif (TS_DEVICE==TS_NS2009)
  if(ns2009_read(&ts_dev) == 1)
  {
    data->point.x = ts.x;
    data->point.y = ts.y;
#elif (TS_DEVICE==TS_ALLWINNER_ADC)
  if(tp_read(&ts) == 1) 
  {
    data->point.x = ts.x;
    data->point.y = ts.y;
    //printf("Data x: %d y: %d \n", data->point.x, data->point.y);
#endif
    data->state = LV_INDEV_STATE_PRESSED;
  }
  else data->state = LV_INDEV_STATE_RELEASED;
}

static void display_flush (lv_display_t *disp, const lv_area_t *area, u8 *buf)
{
  u32 w = lv_area_get_width(area), h = lv_area_get_height(area);
  u16 *dst = &fb[area->x1 + area->y1 * display->width], *src = (u16*)buf;
  while(h--)
  {
    for(int i = 0; i < w; i++) *dst++ = *src++;
    dst += display->width - w;
  }
  lv_disp_flush_ready(disp);
}

static u32 get_ms (void)
{
  return ctr_ms;
}

void lv_tc_finished_cb(lv_event_t * e)
{
  lv_demo_widgets();
}


int main (void)
{
  u8 *lv_buf[2];
  u32 lv_buf_size;
  lv_display_t  *disp_drv;
  lv_indev_t    *indev_drv;

  printf(FG_CYAN "F1C100S - LVGL_%d.%d.%d ("__DATE__" "__TIME__")" ATTR_RESET,
         LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);

  //disp_init(&TV_NTSC, 0);
  disp_init(&TFT_800x480, 0);

  ctr_ms = 0;
  fb = fb_alloc(display->width, display->height, 16);
  lay_config(0, display->width, display->height, 0, 0, 16, fb, 0, 5 << 8);
  lay_update(0);

  delay(100);

#if (TS_DEVICE==TS_ALLWINNER_ADC)
  tp_init();
#else
  twi_init(SYS_TWI_NUM, twi);
#endif

  disp_backlight(100);

  lv_init();
  lv_tick_set_cb(get_ms);
  disp_drv = lv_display_create(display->width, display->height);
  lv_display_set_flush_cb(disp_drv, display_flush);
  lv_buf_size = display->width * display->height * lv_color_format_get_size(LV_COLOR_FORMAT_NATIVE);
  lv_buf[0] = malloc(lv_buf_size);
  lv_display_set_buffers(disp_drv, lv_buf[0], NULL, lv_buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

  indev_drv = lv_indev_create();
  lv_indev_set_type(indev_drv, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev_drv, ts_read);

  lv_tc_indev_init(indev_drv);

#if defined CONFIG_USE_CUSTOM_LV_TC_COEFFICIENTS
  lv_tc_load_coeff_from_config();
#endif

#if (TS_CALIBRATE_EN)
  lv_obj_t *tCScreen = lv_tc_screen_create();

  lv_tc_register_coeff_save_cb(lv_tc_coeff_cb);
  lv_obj_add_event_cb(tCScreen, lv_tc_finished_cb, LV_EVENT_READY, NULL);

  lv_disp_load_scr(tCScreen);
  lv_tc_screen_start(tCScreen);
#else
  lv_demo_widgets();
  //lv_demo_music();
  //lv_demo_stress();
  //lv_demo_benchmark();
#endif

  __asm__ __volatile__ ("msr cpsr_c,#0x53\n"); 

  while(1)
  {
    lv_task_handler();
    dev_enable(state_switch() && state_vsys() > 3000 ? 1 : 0);
  }
}
