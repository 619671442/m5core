#ifndef _KEY_H__
#define _KEY_H__


#include "lvgl.h"
#include <Arduino.h>



void keypad_init(void);
void keypad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);
uint32_t keypad_get_key(void);



#endif 
