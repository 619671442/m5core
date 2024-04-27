#include "testkeyboard.h"

static lv_obj_t *kb;

static void textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e); // 创建输入事件对象
    lv_obj_t *ta = lv_event_get_target(e);       // 获取事件对象
    switch (code)
    {
    case LV_EVENT_PRESSED: // 按压事件
        Serial.println("按压事件");
        break;
    case LV_EVENT_CLICKED: // 点击事件
        Serial.println("点击事件");
        lv_group_set_editing(lv_group_get_default(), true);
        lv_keyboard_set_textarea(kb, ta);
        break;
    case LV_EVENT_LONG_PRESSED: // 长按压事件
        Serial.println("长按压事件");
        break;
    case LV_EVENT_LONG_PRESSED_REPEAT: // 重复按压事件
        Serial.println(" 重复按压事件");
        break;
    case LV_EVENT_KEY: // KEY事件
        Serial.println("KEY事件");
        break;
    default:
        break;
    }
}

void testkeyboard()
{
    // 声明字体
    LV_FONT_DECLARE(font_songti);

    lv_obj_t *pwd_ta = lv_textarea_create(lv_scr_act()); // 创建输入对话框
    lv_textarea_set_text(pwd_ta, "");
    lv_textarea_set_placeholder_text(pwd_ta, "密码");                   // 设置文本区域的文本
    lv_textarea_set_password_mode(pwd_ta, true);                        // 密码输入模式
    lv_textarea_set_one_line(pwd_ta, true);                             // 一行输入模式
    lv_obj_set_width(pwd_ta, lv_pct(40));                               // 设置宽度
    lv_obj_set_pos(pwd_ta, 5, 20);                                      // 设置位置
    lv_obj_add_event_cb(pwd_ta, textarea_event_cb, LV_EVENT_ALL, NULL); // 创建回调函数
    lv_obj_set_style_text_font(pwd_ta, &font_songti, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *pwd_label = lv_label_create(lv_scr_act());             // 创建label对象
    lv_label_set_text(pwd_label, "密码");                            // 密码输入模式
    lv_obj_align_to(pwd_label, pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0); // 设置位置
    lv_obj_set_style_text_font(pwd_label, &font_songti, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *text_ta = lv_textarea_create(lv_scr_act());                // 创建输入对话框
    lv_textarea_set_one_line(text_ta, true);                             // 创建输入对话框
    lv_textarea_set_password_mode(text_ta, false);                       // 非密码输入模式
    lv_obj_set_width(text_ta, lv_pct(40));                               // 设置尺寸
    lv_obj_add_event_cb(text_ta, textarea_event_cb, LV_EVENT_ALL, NULL); // 创建回调
    lv_obj_align(text_ta, LV_ALIGN_TOP_RIGHT, -5, 20);                   // 设置位置

    lv_obj_t *text_label = lv_label_create(lv_scr_act());              // 创建label
    lv_label_set_text(text_label, "text");                             // 设置label内容
    lv_obj_align_to(text_label, text_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0); // 设置位置

    kb = lv_keyboard_create(lv_scr_act());           // 创建键盘输入
    lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2); // 设置键盘尺寸
}