#include "testkeyboard.h"

static void textarea_event_cb(lv_event_t *e);
static void keyboard_event_cb(lv_event_t *e);

void testkeyboard()
{
    // 声明字体
    LV_FONT_DECLARE(font_songti);

    lv_obj_t *kb = lv_keyboard_create(lv_scr_act()); // 创建键盘输入
    lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2); // 设置键盘尺寸
    //lv_keyboard_set_textarea(kb, NULL);
    lv_keyboard_set_popovers(kb, true);      // 键盘弹窗提示
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN); // 隐藏键盘


    lv_obj_t *pwd_ta = lv_textarea_create(lv_scr_act()); // 创建输入对话框
    lv_textarea_set_text(pwd_ta, "");
    lv_textarea_set_placeholder_text(pwd_ta, "密码"); // 设置文本区域的文本
    lv_textarea_set_password_mode(pwd_ta, true);      // 密码输入模式
    lv_textarea_set_one_line(pwd_ta, true);           // 一行输入模式
    lv_obj_set_width(pwd_ta, lv_pct(40));             // 设置宽度
    lv_obj_set_pos(pwd_ta, 10, 30);
    lv_obj_add_state(pwd_ta, LV_STATE_DEFAULT);                       // 设置位置
    lv_obj_add_event_cb(pwd_ta, textarea_event_cb, LV_EVENT_ALL, kb); // 创建回调函数
    lv_obj_set_style_text_font(pwd_ta, &font_songti, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *pwd_label = lv_label_create(lv_scr_act());             // 创建label对象
    lv_label_set_text(pwd_label, "密码");                            // 密码输入模式
    lv_obj_align_to(pwd_label, pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0); // 设置位置
    lv_obj_set_style_text_font(pwd_label, &font_songti, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *text_ta = lv_textarea_create(lv_scr_act()); // 创建输入对话框
    lv_textarea_set_one_line(text_ta, true);              // 创建输入对话框
    lv_textarea_set_password_mode(text_ta, false);        // 非密码输入模式
    lv_obj_set_width(text_ta, lv_pct(40));                // 设置尺寸
    lv_obj_align(text_ta, LV_ALIGN_TOP_RIGHT, -10, 30);    // 设置位置
    lv_obj_add_event_cb(text_ta, textarea_event_cb, LV_EVENT_ALL, kb); // 创建回调函数

    lv_obj_t *text_label = lv_label_create(lv_scr_act());              // 创建label
    lv_label_set_text(text_label, "text");                             // 设置label内容
    lv_obj_align_to(text_label, text_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0); // 设置位置
}

static void textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e); // 创建输入事件对象
    lv_obj_t *ta = lv_event_get_target(e);       // 获取事件对象
    lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);

    switch (code)
    {
    case LV_EVENT_CLICKED: // 点击事件
        Serial.println("textarea点击事件");
        if (kb != NULL)
        {
            Serial.println("textarea和keyboard绑定");
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN); // 清除键盘的隐身标志，显示键盘
            
            lv_keyboard_set_textarea(kb, ta);
            lv_group_focus_obj(kb);
            lv_group_set_editing(lv_group_get_default(), true);            
            lv_obj_add_event_cb(kb, keyboard_event_cb, LV_EVENT_ALL, ta); // 创建回调函数

        }
        break;
    case LV_EVENT_FOCUSED: // 获取焦点事件
        Serial.println("textarea获取焦点");
        // if (kb != NULL)
        // {
        //     Serial.println("textarea和keyboard绑定");
        //     lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN); // 清除键盘的隐身标志，显示键盘
        //     lv_keyboard_set_textarea(kb, ta);
        //     // lv_group_focus_obj(kb);
        //     // lv_group_set_editing(lv_group_get_default(),true);
        // }
        break;
    case LV_EVENT_DEFOCUSED: // 获取焦点事件
        Serial.println("textarea失去焦点");
        //lv_keyboard_set_textarea(kb, NULL);      // 取消键盘的关联
        //lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN); // 添加键盘隐藏标志，隐藏键盘

        break;

    default:
        break;
    }
}

static void keyboard_event_cb(lv_event_t *e)
{
    lv_obj_t *kb = lv_event_get_target(e);       // 获取当前事件对象，也就是键盘对象
    lv_event_code_t code = lv_event_get_code(e); // 创建输入事件对象
    lv_obj_t *ta = lv_keyboard_get_textarea(kb); // 获取与键盘绑定的输入缓冲区的对象

    switch(code) {
    case LV_EVENT_READY :
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN); // 清除键盘的隐身标志，显示键盘          
        lv_keyboard_set_textarea(kb, NULL);
        lv_group_focus_obj(ta);
        lv_group_set_editing(lv_group_get_default(), false);            
        lv_obj_remove_event_cb(kb, keyboard_event_cb); // 删除回调函数
        break;
    case LV_EVENT_CANCEL :
        break;
    default:
        break;
    }
}