#include <lvgl.h>
#include <TFT_eSPI.h>
#include "key.h"

static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];




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



/* TFT instance */
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

/* ui刷新 */
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

void setup()
{
    Serial.begin(115200);

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println(LVGL_Arduino);
    Serial.println("I am LVGL_Arduino");

    lv_init();
    /* TFT init */
    tft.begin();
    /* 旋转90° */
    tft.setRotation(1);
    tft.invertDisplay(1);

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    // static lv_indev_drv_t indev_drv;
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_BUTTON; // 指定输入类型是按键
    // indev_drv.read_cb = mykey_read;
    // lv_indev_drv_register(&indev_drv);

    // 初始化keypad,不用button模式,因为button需要指定按钮坐标
    keypad_init();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD; // 指定输入类型是按键
    indev_drv.read_cb = keypad_read;
    lv_indev_t *lv_button_device_obj = lv_indev_drv_register(&indev_drv);

    /* Create simple label */
    // lv_obj_t *label = lv_label_create(lv_scr_act());
    // lv_label_set_text(label, "Hello Ardino and LVGL!");
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    Serial.println("Setup done");
    

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

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}
