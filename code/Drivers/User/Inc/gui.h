#ifndef __GUI_H
#define __GUI_H


#include "gps.h"
#include "usart.h"
#include "sdmmc_sd.h"
#include "stdio.h"
#include "string.h"
#include "ff.h"
#include "sd_diskio.h"
#include "sdcard.h"

#include "sdram.h"  
#include "lcd_rgb.h"
#include "lcd_pwm.h"
#include "touch_800x480.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "lv_demo_widgets.h"


void my_gui(void);
#endif // !__SDCARD_H
