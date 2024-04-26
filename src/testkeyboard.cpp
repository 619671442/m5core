#include "testkeyboard.h"

static lv_obj_t* kb;
static lv_obj_t* ta;
static lv_group_t *lvgl_btn_group;
static void ta_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e); // 获取对象产生的事件码
    lv_obj_t* ta = lv_event_get_target(e);   // 获取产生事件的对象
    //lv_obj_t* kb = lv_event_get_user_data(e); // 获取对象关联的用户数据
    if (code == LV_EVENT_FOCUSED) {  // 焦点事件处理
        lv_keyboard_set_textarea(kb, ta); // 文本区与键盘关联
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN); // 清除对象隐藏标志
        LV_LOG_USER("%s","LV_EVENT_FOCUSED");
    }
    if (code == LV_EVENT_DEFOCUSED) { // 失去焦点事件处理
        lv_keyboard_set_textarea(kb, NULL);    // 取消文本区与键盘关联
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN); // 添加对象隐藏标志
         LV_LOG_USER("%s","LV_EVENT_DEFOCUSED");
    }
}

void testkeyboard(lv_indev_t *lv_button_device_obj)
{
    lvgl_btn_group = lv_group_create();
    lv_indev_set_group(lv_button_device_obj, lvgl_btn_group);

 
    kb = lv_keyboard_create(lv_scr_act());   //创建键盘对象
 

    ta = lv_textarea_create(lv_scr_act());   // 创建文本输入框对象
    lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, 10);  // LV_ALIGN_TOP_LEFT方式对齐
    //lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb); // 文本输入框对象添加所有事件
    lv_textarea_set_placeholder_text(ta, "Hello"); // 设置占位字符Hello
    lv_obj_set_size(ta, 140, 80);  // 设置大小
    

    lv_group_add_obj(lvgl_btn_group, ta);
    lv_group_add_obj(lvgl_btn_group, kb);
}