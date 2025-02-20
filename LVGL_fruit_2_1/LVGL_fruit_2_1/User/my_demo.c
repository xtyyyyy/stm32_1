#include "my_demo.h"
#include "lvgl.h"
#include "./BSP/DENG/deng.h"
#include <stdio.h>
#include "./BSP/BH1750/bh1750.h"
#include "./BSP/JSON/cJSON.h"

/* 获取当前活动屏幕的宽高 */
#define scr_act_width()  lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

extern DHT11_Data_TypeDef DHT11_Data;
extern float light1;

/* 全局变量定义 */
static lv_obj_t *page1;                  // 页面1
static lv_obj_t *page2;                  // 页面2
static lv_obj_t *keyboard;                // 键盘
static lv_obj_t *label_name;              // 用户名正误提示标签
static lv_obj_t *label_pass;              // 密码正误提示标签
static const lv_font_t *font;             // 定义字体
                           // 缓冲区
						   
static lv_obj_t *switch_led;						   
static lv_obj_t *switch_bump;

uint8_t flag_code = 0;                    // 标志位

static void page1_gesture_event_handler(lv_event_t *event);
static void page2_gesture_event_handler(lv_event_t *event);
static void led_switch_event_handler(lv_event_t *event);

static void name_event_cb(lv_event_t *e);
static void pass_event_cb(lv_event_t *e);


static void name_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);            /* 获取事件类型 */
    lv_obj_t *target = lv_event_get_target(e);              /* 获取触发源 */

    if(code == LV_EVENT_FOCUSED)                            /* 事件类型：被聚焦 */
    {
        lv_keyboard_set_textarea(keyboard, target);         /* 关联用户名文本框和键盘 */
    }
    else if(code == LV_EVENT_VALUE_CHANGED)                 /* 事件类型：文本框的内容发生变化 */
    {
        const char *txt = lv_textarea_get_text(target);     /* 获取文本框的文本 */

        if(strcmp(txt,"admin") == 0)                        /* 判断用户名是否正确 */
        {
            lv_label_set_text(label_name, LV_SYMBOL_OK);    /* 用户名正确，显示√ */
        }
        else
        {
            lv_label_set_text(label_name, "");              /* 用户名错误，不提示 */
        }
    }
}

/**
 * @brief  密码文本框事件回调
 * @param  *e ：事件相关参数的集合，它包含了该事件的所有数据
 * @return 无
 */
static void pass_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);            /* 获取事件类型 */
    lv_obj_t *target = lv_event_get_target(e);              /* 获取触发源 */

    if(code == LV_EVENT_FOCUSED)                            /* 事件类型：被聚焦 */
    {
        lv_keyboard_set_textarea(keyboard, target);         /* 关联用户名文本框和键盘 */
    }
    else if(code == LV_EVENT_VALUE_CHANGED)                 /* 事件类型：文本框的内容发生变化 */
    {
        const char *txt = lv_textarea_get_text(target);     /* 获取文本框的文本 */

        if(strcmp(txt,"123456") == 0)                       /* 判断密码是否正确 */
        {
            lv_label_set_text(label_pass, LV_SYMBOL_OK);    /* 密码正确，显示√ */
			flag_code = 1;
        }
        else
        {
            lv_label_set_text(label_pass, "");              /* 密码错误，不提示 */
        }
    }
}


static void page1_gesture_event_handler(lv_event_t * event)
{
    if (event->code == LV_EVENT_CLICKED) {
		if(flag_code)
			lv_scr_load_anim(page2, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 0, false);
			printf("111\r\n");
    }
}


static void page2_gesture_event_handler(lv_event_t * event)
{
    if (event->code == LV_EVENT_CLICKED) {
       lv_scr_load_anim(page1, LV_SCR_LOAD_ANIM_OVER_RIGHT, 1000, 0, false);
    }
}

static void led_switch_event_handler(lv_event_t *event)
{
	if (event->code == LV_EVENT_VALUE_CHANGED)
	{
		if(lv_obj_has_state(switch_led, LV_STATE_CHECKED))
		{
			DENG(1);
		}
		else
		{
			DENG(0);
		}
	}
}


static void bump_switch_event_handler(lv_event_t *event)
{
	if (event->code == LV_EVENT_VALUE_CHANGED)
	{
		if(lv_obj_has_state(switch_bump, LV_STATE_CHECKED))
		{
			BUMP(1);
		}
		else
		{
			BUMP(0);
		}
	}
}
/* 其他代码保持不变 */

static void lv_example_textarea(lv_obj_t *page)
{
    /* 根据屏幕大小设置字体 */
    if (scr_act_width() <= 320)
    {
        font = &lv_font_montserrat_12;
    }
    else if (scr_act_width() <= 480)
    {
        font = &lv_font_montserrat_14;
    }
    else
    {
        font = &lv_font_montserrat_22;
    }

    /* 用户名文本框 */
    lv_obj_t *textarea_name = lv_textarea_create(page);                                     /* 创建文本框 */
    lv_obj_set_width(textarea_name, scr_act_width()/2);                                             /* 设置宽度 */
    lv_obj_set_style_text_font(textarea_name, font, LV_PART_MAIN);                                  /* 设置字体 */
    lv_obj_align(textarea_name, LV_ALIGN_CENTER, 0, -scr_act_height()/3 );                          /* 设置位置 */
    lv_textarea_set_one_line(textarea_name, true);                                                  /* 设置单行模式 */
    lv_textarea_set_max_length(textarea_name, 6);                                                   /* 设置输入字符的最大长度 */
    lv_textarea_set_placeholder_text(textarea_name, "user name");                                   /* 设置占位符 */
    lv_obj_add_event_cb(textarea_name, name_event_cb, LV_EVENT_ALL, NULL);                          /* 添加文本框事件回调 */

    /* 用户名正误提示标签 */
    label_name = lv_label_create(page);                                                     /* 创建标签 */
    lv_label_set_text(label_name, "");                                                              /* 默认不提示 */
    lv_obj_set_style_text_font(label_name, font, LV_PART_MAIN);                                     /* 设置字体 */
    lv_obj_align_to(label_name, textarea_name, LV_ALIGN_OUT_RIGHT_MID, 5, 0);                       /* 设置位置 */

    /* 密码文本框 */
    lv_obj_t *textarea_pass = lv_textarea_create(page);                                     /* 创建文本框 */
    lv_obj_set_width(textarea_pass, scr_act_width()/2);                                             /* 设置宽度 */
    lv_obj_set_style_text_font(textarea_pass, font, LV_PART_MAIN);                                  /* 设置字体 */
    lv_obj_align_to(textarea_pass, textarea_name, LV_ALIGN_OUT_BOTTOM_MID, 0, scr_act_height()/20); /* 设置位置 */
    lv_textarea_set_one_line(textarea_pass, true);                                                  /* 设置单行模式 */
    lv_textarea_set_password_mode(textarea_pass, true);                                             /* 设置密码模式 */
    lv_textarea_set_password_show_time(textarea_pass, 1000);                                        /* 设置密码显示时间 */
    lv_textarea_set_max_length(textarea_pass, 8);                                                   /* 设置输入字符的最大长度 */
    lv_textarea_set_placeholder_text(textarea_pass, "password");                                    /* 设置占位符 */
    lv_obj_add_event_cb(textarea_pass, pass_event_cb, LV_EVENT_ALL, NULL);                          /* 添加文本框事件回调 */

    /* 密码正误提示标签 */
    label_pass = lv_label_create(page);                                                     /* 创建标签 */
    lv_label_set_text(label_pass, "");                                                              /* 默认不提示 */
    lv_obj_set_style_text_font(label_pass, font, LV_PART_MAIN);                                     /* 设置字体 */
    lv_obj_align_to(label_pass, textarea_pass, LV_ALIGN_OUT_RIGHT_MID, 5, 0);                       /* 设置位置 */

    /* 键盘 */
    keyboard = lv_keyboard_create(page);                                                    /* 创建键盘 */
    lv_obj_set_size(keyboard, scr_act_width(), scr_act_height()/2);                                 /* 设置大小 */
}



static lv_obj_t *label_temp; 
static lv_obj_t *label_light; 
static const lv_font_t * my_font_large = &lv_font_montserrat_32;
lv_style_t custom_style;


void create_page_denglu(void)
{
    // Create page 1 content
    page1 = lv_obj_create(NULL);
    lv_obj_set_size(page1, LV_HOR_RES, LV_VER_RES);
    
    // Add a label "Smart Orchard Control System" at the top of the page with a larger font
    lv_obj_t *label = lv_label_create(page1);
    lv_label_set_text(label, "Smart Orchard Control System");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);  // Align the text to the center at the top with a 20-pixel offset
    
    // Increase font size for the label
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, 0);  // Set font size to 24

    // Create the text area (username/password input fields)
    lv_example_textarea(page1);

    // Create the first button (Login) with a larger font and adjusted position
    lv_obj_t *btn1 = lv_btn_create(page1);
    lv_obj_set_pos(btn1, (LV_HOR_RES - 320) / 2, (LV_VER_RES - 100) / 2);  // Adjust position to shift down
    lv_obj_set_size(btn1, 150, 50);

    lv_obj_t *label1_1 = lv_label_create(btn1);
    lv_label_set_text(label1_1, "Login");

    // Increase font size for Login button label
    lv_obj_set_style_text_font(label1_1, &lv_font_montserrat_20, 0);  // Set font size to 20

    // Create the second button (Sign) with a larger font and adjusted position
    lv_obj_t *btn2 = lv_btn_create(page1);
    lv_obj_set_pos(btn2, (LV_HOR_RES + 50) / 2, (LV_VER_RES - 100) / 2);  // Adjust position to shift down
    lv_obj_set_size(btn2, 150, 50);

    lv_obj_t *label1_2 = lv_label_create(btn2);
    lv_label_set_text(label1_2, "Sign");

    // Increase font size for Sign button label
    lv_obj_set_style_text_font(label1_2, &lv_font_montserrat_20, 0);  // Set font size to 20

    // Add event callback to the Login button
    lv_obj_add_event_cb(btn1, page1_gesture_event_handler, LV_EVENT_ALL, NULL);
}



void create_page_yonghu(void)
{
    // 创建页面2的内容
    page2 = lv_obj_create(NULL);
    lv_obj_set_size(page2, LV_HOR_RES, LV_VER_RES);

    lv_obj_t *tabview = lv_tabview_create(page2, LV_DIR_TOP, 50);
	
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Data");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Control");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Camera");
	
    label_temp = lv_label_create(tab1);
	label_light = lv_label_create(tab1);
	
	lv_obj_set_pos(label_temp, 30, 100);
	lv_obj_set_pos(label_light, 30, 200);
	
	lv_obj_set_style_text_font(label_temp,my_font_large,LV_PART_MAIN);
	
	switch_led = lv_switch_create(tab2);
	lv_obj_set_pos(switch_led, 30, 100);
	lv_obj_add_event_cb(switch_led, led_switch_event_handler, LV_EVENT_ALL, NULL);
	
	switch_bump = lv_switch_create(tab2);
	lv_obj_set_pos(switch_bump, 200, 100);
	lv_obj_add_event_cb(switch_bump, bump_switch_event_handler, LV_EVENT_ALL, NULL);
	
	
	lv_obj_t *led_label = lv_label_create(tab2);
	lv_label_set_text(led_label, "led");
	//lv_obj_set_style_text_font(led_label, font, LV_STATE_DEFAULT); // 确保font已经被定义和初始化
	lv_obj_set_pos(led_label, 30, 65); // 将标签的y坐标设置为80，使其在开关的上方
	
	lv_obj_t *bump_label = lv_label_create(tab2);
	lv_label_set_text(bump_label, "bump");
	//lv_obj_set_style_text_font(led_label, font, LV_STATE_DEFAULT); // 确保font已经被定义和初始化
	lv_obj_set_pos(bump_label, 200, 65); // 将标签的y坐标设置为80，使其在开关的上方
	
	lv_obj_set_style_text_font(label_temp,my_font_large,LV_PART_MAIN);
	lv_obj_set_style_text_font(label_light,my_font_large,LV_PART_MAIN);
	lv_obj_set_style_text_font(led_label,my_font_large,LV_PART_MAIN);
	lv_obj_set_style_text_font(bump_label,my_font_large,LV_PART_MAIN);
}

/**
 * @brief  LVGL演示
 * @param  无
 * @return 无
 */
 
int  flag = 1;

char temp_buf[30];  
char light_buf[30];   
extern cJSON* cjson_items_LEDSwitch_value ;

void my_demo(void)
{
    //create_page_denglu();
    
	if(flag)
	{
		create_page_denglu();
		create_page_yonghu();
		
		flag = 0;
	}
	lv_scr_load(page1); // 初始加载页面1
	//lv_scr_load(page1); // 初始加载页面1
	snprintf(temp_buf, sizeof(temp_buf), "humi: %d RH, temp: %d ℃", DHT11_Data.humi_int, DHT11_Data.temp_int);
    lv_label_set_text(label_temp, temp_buf); // 更新标签文本
	snprintf(light_buf, sizeof(light_buf), "light: %d", cjson_items_LEDSwitch_value->valueint);
	//snprintf(light_buf, sizeof(light_buf), "light_buf: %d", SOIL_Read());
	
    lv_label_set_text(label_light, light_buf); // 更新标签文本
}
