#include <lvgl.h>
#include <TFT_eSPI.h>
#include "key.h"
#include "testqc.h"
#include "testkeyboard.h"

static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

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

    // 初始化keypad,不用button模式,因为button需要指定按钮坐标
    keypad_init();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD; // 指定输入类型是按键
    indev_drv.read_cb = keypad_read;
    lv_indev_t *lv_button_device_obj = lv_indev_drv_register(&indev_drv);

    Serial.println("Setup done");
    // 二维码
    // testqc(lv_button_device_obj);
    // 虚拟键盘
    testkeyboard(lv_button_device_obj);
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}
