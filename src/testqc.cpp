#include "testqc.h"

lv_obj_t * qr ;
const char * data = "hello";


void bt1_event_handler(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        data = "world";
        lv_qrcode_update(qr, data, strlen(data));
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}
void bt2_event_handler(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        data = "hi";
        lv_qrcode_update(qr, data, strlen(data));
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}
void bt3_event_handler(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        data = "how are you";
        lv_qrcode_update(qr, data, strlen(data));
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

void testqc(lv_indev_t *lv_button_device_obj){
    Serial.println("测试二维码");
    //测试例子
    lv_group_t *lvgl_btn_group = lv_group_create();
    lv_indev_set_group(lv_button_device_obj, lvgl_btn_group);

    lv_obj_t *lvgl_btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(lvgl_btn1, bt1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(lvgl_btn1, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_t *label1 = lv_label_create(lvgl_btn1);
    lv_label_set_text(label1, "Button1");

    lv_obj_t *lvgl_btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(lvgl_btn2, bt2_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(lvgl_btn2, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_t *label2 = lv_label_create(lvgl_btn2);
    lv_label_set_text(label2, "Button2");

    lv_obj_t *lvgl_btn3 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(lvgl_btn3, bt3_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(lvgl_btn3, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_t *label3 = lv_label_create(lvgl_btn3);
    lv_label_set_text(label3, "Button3");

    lv_group_add_obj(lvgl_btn_group, lvgl_btn1); // 将创建的按键加入组
    lv_group_add_obj(lvgl_btn_group, lvgl_btn2); // 将创建的按键加入组
    lv_group_add_obj(lvgl_btn_group, lvgl_btn3); // 将创建的按键加入组


    

    lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 5);
    lv_color_t fg_color = lv_palette_darken(LV_PALETTE_BLUE, 4);
    qr = lv_qrcode_create(lv_scr_act(), 150, fg_color, bg_color);
    
    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_align(qr, LV_ALIGN_TOP_MID, 0, 20);

    /*Add a border with bg_color*/
    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);

}