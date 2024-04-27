#include "key.h"

/*------------------
 * Keypad
 * -----------------*/
#define PinA 39 // 左键引脚
#define PinB 37 // 右键引脚
#define PinC 38 // 确定键引脚

static lv_indev_drv_t indev_drv;

static lv_indev_t *indev_keypad;
// 组的指针
static lv_group_t *group_default;

static void keypad_init(void)
{
    pinMode(PinC, INPUT_PULLUP);
    pinMode(PinA, INPUT_PULLUP);
    pinMode(PinB, INPUT_PULLUP);
}

static uint32_t keypad_get_key(void)
{

    if (digitalRead(PinC) == LOW) // 确认键
    {
        Serial.println("OK");
        return 1;
    }

    if (digitalRead(PinA) == LOW)
    {
        if (lv_group_get_editing(group_default) == 1)
        {
            Serial.println("A(E)");
            return 4;
        }
        Serial.println("A");
        return 2;
    }
    if (digitalRead(PinB) == LOW)
    {
        // 编辑模式状态按键返回值
        if (lv_group_get_editing(group_default) == 1)
        {
            Serial.println("B(E)");
            return 5;
        }
        Serial.println("B");
        return 3;
    }

    return 0; // 没按下返回0
}
/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    static uint32_t last_key = 0;
    uint8_t act_enc = keypad_get_key();

    if (act_enc != 0)
    {
        switch (act_enc)
        {
        case 1:
            act_enc = LV_KEY_ENTER; // 确认键
            data->state = LV_INDEV_STATE_PRESSED;
            break;
        case 2:
            act_enc = LV_KEY_PREV; // 聚焦到上一个
            data->state = LV_INDEV_STATE_PRESSED;
            break;
        case 3:
            act_enc = LV_KEY_NEXT; // 聚焦到下一个
            data->state = LV_INDEV_STATE_PRESSED;
            break;
        case 4:
            act_enc = LV_KEY_LEFT; // 减少或向左
            data->state = LV_INDEV_STATE_PRESSED;
            break;
        case 5:
            act_enc = LV_KEY_RIGHT; // 增加或向右
            data->state = LV_INDEV_STATE_PRESSED;
            break;
        }
        last_key = (uint32_t)act_enc;
    }
    data->key = last_key;
}
void lv_port_indev_init(void)
{
    keypad_init();

    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD; // 指定输入类型是按键
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);

    group_default = lv_group_create();               // 创建组
    lv_group_set_default(group_default); 
    lv_indev_set_group(indev_keypad, group_default); // 将组绑定到输入设备
}

/**
** 为了方便获得组和输入设备可以在这个编写返回函数
**/
lv_indev_t *get_indev(void)
{
    return indev_keypad;
}
lv_group_t *get_group_default(void)
{
    return group_default;
}