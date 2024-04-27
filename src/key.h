#ifndef _KEY_H__
#define _KEY_H__


#include "lvgl.h"
#include <Arduino.h>



void lv_port_indev_init(void);
lv_indev_t * get_indev(void);
lv_group_t *get_group_default(void);

#endif 
