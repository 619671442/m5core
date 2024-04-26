#include "key.h"

/*------------------
 * Keypad
 * -----------------*/
uint8_t keypin1 = 39;
uint8_t keypin2 = 38;
uint8_t keypin3 = 37;


void keypad_init(void)
{
    pinMode(keypin1, INPUT_PULLUP);
	pinMode(keypin2, INPUT_PULLUP);
	pinMode(keypin3, INPUT_PULLUP);
}

/*Will be called by the library to read the mouse*/
void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    
    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
        case 1:
            act_key = LV_KEY_LEFT;
            break;
        case 2:
            act_key = LV_KEY_ENTER;
            break;
        case 3:
            act_key = LV_KEY_RIGHT;
            break;
        }

        last_key = act_key;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}

uint32_t keypad_get_key(void)
{

    if ((digitalRead(keypin1) == LOW)) {
        return LV_KEY_PREV ;  
    } else if ((digitalRead(keypin2) == LOW)) {
        return LV_KEY_ENTER;  
    } else if ((digitalRead(keypin3) == LOW)) {
        return LV_KEY_NEXT ;  
    } 
	
    return 0;
}
