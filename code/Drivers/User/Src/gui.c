#include "gui.h"

#include "FreeRTOS.h"
#include "freertos_os2.h"
#include "cmsis_os2.h"
#include "gps.h"
#include "imu.h"


//*****************************移植的lvgl，一旦调用自己生成的字体文件就会卡死，换而言之，无法显示中文***************** */



#if LV_MEM_CUSTOM == 0 && LV_MEM_SIZE < (38ul * 1024ul)
    #error Insufficient memory for lv_demo_widgets. Please set LV_MEM_SIZE to at least 38KB (38ul * 1024ul).  48KB is recommended.
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;


/**********************
 *  STATIC VARIABLES
 **********************/
static disp_size_t disp_size;

static lv_obj_t * tv;
static lv_obj_t * calendar;
static lv_style_t style_text_muted;
static lv_style_t style_title;
static lv_style_t style_icon;
static lv_style_t style_bullet;


static const lv_font_t * font_large;
static const lv_font_t * font_normal;

static uint32_t session_desktop = 1000;
static uint32_t session_tablet = 1000;
static uint32_t session_mobile = 1000;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/




lv_obj_t* title, * scr;
lv_obj_t* panel1; // 创建一个面板
lv_obj_t* panel2;
lv_obj_t* win1, * win2;
lv_obj_t* win3, * win4;


 // 按钮handler
static void btn1_event_handler(lv_event_t* event) {
    // button pressed
    
        lv_obj_clear_flag(win1, LV_OBJ_FLAG_HIDDEN);
}
// 按钮btn2的handler
static void btn2_event_handler(lv_event_t* event) {
    // button pressed
    lv_obj_clear_flag(win2, LV_OBJ_FLAG_HIDDEN);
}
// 按钮btn3的handler
static void btn3_event_handler(lv_event_t* event) {
    // button pressed
    lv_obj_clear_flag(win3, LV_OBJ_FLAG_HIDDEN);
}
// 按钮btn4的handler
static void btn4_event_handler(lv_event_t* event) {
    // button pressed
    lv_obj_clear_flag(win4, LV_OBJ_FLAG_HIDDEN);
}


static void win1_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win1, LV_OBJ_FLAG_HIDDEN);
}
// 窗口2的关闭handler
static void win2_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win2, LV_OBJ_FLAG_HIDDEN);
}
// 窗口3的关闭handler
static void win3_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win3, LV_OBJ_FLAG_HIDDEN);
}
// 窗口4的关闭handler
static void win4_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win4, LV_OBJ_FLAG_HIDDEN);
}


lv_style_t borderless;
// 透明样式
lv_style_t transparent;

int contorller1_num = 0;
// 加号按钮bp1的handler
static void btn_plus1_event_cb(lv_event_t* event) {
       // button pressed
    contorller1_num++;
    lv_obj_t* bp1_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp1_txt, "%d", contorller1_num);
}
// 减号按钮bm1的handler
static void btn_minus1_event_cb(lv_event_t* event) {
    // button pressed
    contorller1_num--;
    lv_obj_t* bp1_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp1_txt, "%d", contorller1_num);
}

int contorller2_num = 0;
// 加号按钮bp2的handler
static void btn_plus2_event_cb(lv_event_t* event) {
    // button pressed
    contorller2_num++;
    lv_obj_t* bp2_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp2_txt, "%d", contorller2_num);
}
// 减号按钮bm2的handler
static void btn_minus2_event_cb(lv_event_t* event) {
    // button pressed
    contorller2_num--;
    lv_obj_t* bp2_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp2_txt, "%d", contorller2_num);
}


int contorller3_num = 0;
// 加号按钮bp3的handler
static void btn_plus3_event_cb(lv_event_t* event) {
    // button pressed
    contorller3_num++;
    lv_obj_t* bp3_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp3_txt, "%d", contorller3_num);
}
// 减号按钮bm3的handler
static void btn_minus3_event_cb(lv_event_t* event) {
    // button pressed
    contorller3_num--;
    lv_obj_t* bp3_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp3_txt, "%d", contorller3_num);
}


// 下拉框的handler
static void ddlist_event_handler(lv_event_t* event) {
    // button pressed
    lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t * obj = lv_event_get_target(event);
    uint16_t c = lv_dropdown_get_selected(obj);
}

//保存按钮的handler
static void save_btn_event_handler(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(win2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(win3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(win4, LV_OBJ_FLAG_HIDDEN);
}

extern uint8_t delete_flag;
//
extern osMessageQueueId_t gpshuart_flagqHandle;
static void btn_savemsg_event_cb(lv_event_t* event) {
    delete_flag = 1;
    gps_save_flag = 0;

}
static void btn_startsavemsg_event_cb(lv_event_t* event) {
    gps_save_flag = 1;
}


static void btn_calculate_event_cb(lv_event_t* event) {
    static flag = 2;
    osMessageQueuePut(gpshuart_flagqHandle, &flag, 2U, 0U); //将接收到的数据发送到队列
}

static void btn_bstartsaveimu_event_cb(lv_event_t* event) {
    imu_save_flag = 1;
}
static void btn_bsaveimu_event_cb(lv_event_t* event) {
    imu_save_flag = 0;
    delete_flag = 1;
}


LV_FONT_DECLARE(lv_font_siyuan_small);
LV_FONT_DECLARE(lv_font_siyuan_micro);
// LV_FONT_DECLARE(lv_font_siyuan);

#define BTN_WIDTH 30
//定义容器的大小
#define CTN_WIDTH 220
#define CTN_HEIGHT 60

// 初始化隐藏的win1窗口
static void win1_init() {
    // 窗口1
    win1 = lv_win_create(lv_scr_act(),70);
    lv_win_add_title(win1, "   ");
    
    lv_obj_add_flag(win1, LV_OBJ_FLAG_HIDDEN); // 隐藏
    lv_obj_t* close_btn1 = lv_win_add_btn(win1, LV_SYMBOL_CLOSE, 70);
    lv_obj_add_event_cb(close_btn1, win1_close_event_cb, LV_EVENT_CLICKED, NULL);

    // 创建容器，大小与win1相同，使用flex布局，设置元素距离
    lv_obj_t* win1_cont = lv_win_get_content(win1);
    lv_obj_set_flex_flow(win1_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(win1_cont, 5, LV_PART_MAIN);
    //不显示滚动条
    // lv_obj_clear_flag(win1_cont, LV_OBJ_FLAG_SCROLLABLE);

    // 上方容器，透明
    lv_obj_t* up_cont = lv_obj_create(win1_cont);
    lv_obj_add_style(up_cont, &transparent, 0);
    lv_obj_set_flex_flow(up_cont, LV_FLEX_FLOW_COLUMN_WRAP);
    // lv_obj_set_flex_align(up_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(up_cont, 5, LV_PART_MAIN);
    lv_obj_clear_flag(up_cont, LV_OBJ_FLAG_SCROLLABLE);
    // 设定大小
    lv_obj_set_size(up_cont, 780, 360);


    // 图片容器
    lv_obj_t * img_cont = lv_obj_create(up_cont);
    // 设定大小 428x208
    lv_obj_set_size(img_cont, 460, 340);
    // 无边框
    lv_obj_add_style(img_cont, &transparent, 0);
    // 不显示滚动条
    lv_obj_clear_flag(img_cont, LV_OBJ_FLAG_SCROLLABLE);
    // flex竖向布局
    lv_obj_set_flex_flow(img_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(img_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    LV_IMG_DECLARE(img1);
    lv_obj_t* img1_obj = lv_img_create(img_cont);
    lv_img_set_src(img1_obj, &img1);
    // img位于中心
    // lv_obj_set_align(img1_obj, LV_ALIGN_CENTER);
    // img 下方文本
    lv_obj_t* img1_txt = lv_label_create(img_cont);
    lv_label_set_text(img1_txt, "Schema");
    // 字体
    // lv_obj_set_style_text_font(img1_txt, &lv_font_siyuan_micro, 0);

    // 文本
    //lv_obj_t* win1_txt = lv_label_create(win1_cont);
    //lv_label_set_text(win1_txt, "This is a hidden window. Click the button to show it.");

    // 大容器，里面四个小容器
    lv_obj_t* option_cont2 = lv_obj_create(up_cont);    
    lv_obj_set_flex_flow(option_cont2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(option_cont2, 5, LV_PART_MAIN);
    lv_obj_clear_flag(option_cont2, LV_OBJ_FLAG_SCROLLABLE);
    //透明
    lv_obj_add_style(option_cont2, &transparent, 0);
    // 大小
    lv_obj_set_size(option_cont2, 400, 400);


    // 容器1，包括一个加号按钮，一个文本，一个减号按钮，flex横向布局，指定大小，该容器透明
    lv_obj_t* contorller1 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller1, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller1, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller1, &transparent, 0); // 必须初始化transparent样式!!
    lv_obj_set_flex_align(contorller1, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //不显示滚动条
    lv_obj_clear_flag(contorller1, LV_OBJ_FLAG_SCROLLABLE);
    
    // 文本使用指定字体
    lv_obj_t* bp1_txt1 = lv_label_create(contorller1);
    lv_label_set_text(bp1_txt1, "L1");
    // lv_obj_set_style_text_font(bp1_txt1, &lv_font_siyuan_micro, 0);
    // 加号按钮，按下后改变后面的文本，按钮大小必须小于容器大小
    lv_obj_t* bp1 = lv_btn_create(contorller1);
    lv_obj_set_size(bp1, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bp1_label = lv_label_create(bp1);
    lv_label_set_text(bp1_label, "+");
    // 按钮图标位于中心
    lv_obj_set_align(bp1_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bp1, btn_plus1_event_cb, LV_EVENT_CLICKED, bp1);
    // 文本
    lv_obj_t* bp1_txt = lv_label_create(contorller1);
    lv_label_set_text(bp1_txt, "0");
    //文本位于中心
    lv_obj_set_align(bp1_txt, LV_ALIGN_CENTER);
    // 减号按钮，按下后改变前面的文本，按钮大小必须小于容器大小
    lv_obj_t* bm1 = lv_btn_create(contorller1);
    lv_obj_set_size(bm1, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bm1_label = lv_label_create(bm1);
    lv_label_set_text(bm1_label, "-");
    // 按钮图标位于中心
    lv_obj_set_align(bm1_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bm1, btn_minus1_event_cb, LV_EVENT_CLICKED, bm1);


    // 容器2，包括一个文本，加号按钮，一个文本，一个减号按钮，flex横向布局，指定大小，该容器透明
    lv_obj_t* contorller2 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller2, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller2, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller2, &transparent, 0); // 必须初始化transparent样式!!
    lv_obj_set_flex_align(contorller2, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //不显示滚动条
    lv_obj_clear_flag(contorller2, LV_OBJ_FLAG_SCROLLABLE);
    // 文本使用指定字体
    lv_obj_t* bp2_txt1 = lv_label_create(contorller2);
    lv_label_set_text(bp2_txt1, "L2");
    // lv_obj_set_style_text_font(bp2_txt1, &lv_font_siyuan_micro, 0);
    // 加号按钮，按下后改变后面的文本，按钮大小必须小于容器大小
    lv_obj_t* bp2 = lv_btn_create(contorller2);
    lv_obj_set_size(bp2, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bp2_label = lv_label_create(bp2);
    lv_label_set_text(bp2_label, "+");
    // 按钮图标位于中心
    lv_obj_set_align(bp2_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bp2, btn_plus2_event_cb, LV_EVENT_CLICKED, bp2);
    // 文本
    lv_obj_t* bp2_txt = lv_label_create(contorller2);
    lv_label_set_text(bp2_txt, "0");
    //文本位于中心
    lv_obj_set_align(bp2_txt, LV_ALIGN_CENTER);
    // 减号按钮，按下后改变前面的文本，按钮大小必须小于容器大小
    lv_obj_t* bm2 = lv_btn_create(contorller2);
    lv_obj_set_size(bm2, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t * bm2_label = lv_label_create(bm2);
    lv_label_set_text(bm2_label, "-");
    // 按钮图标位于中心 
    lv_obj_set_align(bm2_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bm2, btn_minus2_event_cb, LV_EVENT_CLICKED, bm2);


    // 容器3，包括一个文本，一个输入框，flex横向布局，指定大小，该容器透明
    lv_obj_t* contorller3 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller3, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller3, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller3, &transparent, 0); // 必须初始化transparent样式!!
    lv_obj_set_flex_align(contorller3, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //不显示滚动条
    lv_obj_clear_flag(contorller3, LV_OBJ_FLAG_SCROLLABLE);
    // 文本使用指定字体
    lv_obj_t* bp3_txt1 = lv_label_create(contorller3);
    lv_label_set_text(bp3_txt1, "L3");
    // lv_obj_set_style_text_font(bp3_txt1, &lv_font_siyuan_micro, 0);
    // 加号按钮，按下后改变后面的文本，按钮大小必须小于容器大小
    lv_obj_t* bp3 = lv_btn_create(contorller3);
    lv_obj_set_size(bp3, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bp3_label = lv_label_create(bp3);
    lv_label_set_text(bp3_label, "+");
    lv_obj_add_event_cb(bp3, btn_plus3_event_cb, LV_EVENT_CLICKED, bp3);

    // 按钮图标位于中心
    lv_obj_set_align(bp3_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bp3, btn_plus3_event_cb, LV_EVENT_VALUE_CHANGED, bp3);
    // 文本
    lv_obj_t* bp3_txt = lv_label_create(contorller3);
    lv_label_set_text(bp3_txt, "0");
    //文本位于中心
    lv_obj_set_align(bp3_txt, LV_ALIGN_CENTER);
    // 减号按钮，按下后改变前面的文本，按钮大小必须小于容器大小
    lv_obj_t* bm3 = lv_btn_create(contorller3);
    lv_obj_set_size(bm3, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t * bm3_label = lv_label_create(bm3);
    lv_label_set_text(bm3_label, "-");
    // 按钮图标位于中心
    lv_obj_set_align(bm3_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bm3, btn_minus3_event_cb, LV_EVENT_CLICKED, bm3);

    // 容器4，包括一个文本，一个下拉框，下拉框里有三个选项，flex横向布局，指定大小，该容器透明
    lv_obj_t* contorller4 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller4, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller4, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller4, &transparent, 0); // 必须初始化transparent样式!!
    lv_obj_set_flex_align(contorller4, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //不显示滚动条
    lv_obj_clear_flag(contorller4, LV_OBJ_FLAG_SCROLLABLE);
    //lv_obj_set_style_text_font(contorller4, &lv_font_siyuan_micro, 0);

    // 文本使用指定字体
    lv_obj_t* bp4_txt1 = lv_label_create(contorller4);
    lv_label_set_text(bp4_txt1, "Type");
    // lv_obj_set_style_text_font(bp4_txt1, &lv_font_siyuan_micro, 0);

    // 初始化中文风格
    lv_style_t chinese_style;
    lv_style_init(&chinese_style);
    lv_style_set_text_font(&chinese_style, &lv_font_siyuan_micro);

    // 下拉框
    lv_obj_t* ddlist = lv_dropdown_create(contorller4);
    //lv_dropdown_set_options(ddlist, "1");

    lv_dropdown_set_options(ddlist, "A\nB\nC");
    //设置字体
    lv_obj_t * dd_txt = lv_dropdown_get_list(ddlist);


    // lv_obj_add_style(dd_txt, &chinese_style, LV_PART_MAIN);
    // lv_obj_add_style(ddlist, &chinese_style, LV_PART_MAIN);
    // lv_obj_set_style_text_font(dd_txt, &lv_font_simsun_16_cjk, 0);
    // lv_obj_set_style_text_font(dd_txt, &lv_font_siyuan_micro, LV_PART_MAIN);
    // lv_obj_set_style_text_font(ddlist, &lv_font_siyuan_micro, 0);
    // lv_dropdown_set_text(ddlist, "  ");
    lv_obj_set_width(ddlist, 90);
    lv_obj_set_height(ddlist, 40);
    lv_obj_add_event_cb(ddlist, ddlist_event_handler, LV_EVENT_VALUE_CHANGED, ddlist);

    // 文字说明三个选项功能
    lv_obj_t* bp4_txt = lv_label_create(option_cont2);
    lv_label_set_text(bp4_txt, "A:Sow B: Fertilize C:Spray");
    // lv_obj_set_style_text_font(bp4_txt, &lv_font_siyuan_micro, 0);

    // 下方容器 透明
    lv_obj_t* down_cont = lv_obj_create(win1_cont);
    lv_obj_add_style(down_cont, &transparent, 0);
    // 大小
    lv_obj_set_size(down_cont, 780, 40);
    // 中心位置放置按钮，按钮文字为保存
    lv_obj_t* save_btn = lv_btn_create(down_cont);
    lv_obj_set_size(save_btn, 100, 30);
    lv_obj_t* save_btn_label = lv_label_create(save_btn);
    lv_label_set_text(save_btn_label, "Save");
    // 文字在中心
    lv_obj_set_align(save_btn_label, LV_ALIGN_CENTER);

    // lv_obj_set_style_text_font(save_btn_label, &lv_font_siyuan_micro, 0);
    lv_obj_add_event_cb(save_btn, save_btn_event_handler, LV_EVENT_CLICKED, NULL);
    //位置在中心
    lv_obj_set_align(save_btn, LV_ALIGN_CENTER);
    //不显示滚动条
    lv_obj_clear_flag(down_cont, LV_OBJ_FLAG_SCROLLABLE);

}


// 初始化隐藏的win2窗口
static void win2_init() {
    // 窗口2
    win2 = lv_win_create(lv_scr_act(), 60);
    lv_win_add_title(win2, "   ");
    lv_obj_add_flag(win2, LV_OBJ_FLAG_HIDDEN); // 隐藏
    lv_obj_t* close_btn2 = lv_win_add_btn(win2, LV_SYMBOL_CLOSE, 60);
    lv_obj_add_event_cb(close_btn2, win2_close_event_cb, LV_EVENT_CLICKED, NULL);

    //创建容器，大小与win2相同，使用flex布局
    lv_obj_t* win2_cont = lv_win_get_content(win2);
    lv_obj_set_flex_flow(win2_cont, LV_FLEX_FLOW_COLUMN_WRAP);

    // 初始化lv_style_plain_color
    lv_style_t lv_style_plain_color;
    lv_style_init(&lv_style_plain_color);
    lv_style_set_border_color(&lv_style_plain_color, lv_color_black());

    // 创建画板
    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(380,380)];
    int canvas_height = 380;
    int canvas_width = 380;
    lv_obj_t* canvas = lv_canvas_create(win2_cont);
    lv_obj_set_size(canvas, canvas_width, canvas_height);
    lv_canvas_set_buffer(canvas, cbuf,
        canvas_width, canvas_height, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvas, 0, lv_color_black());
    lv_canvas_set_palette(canvas, 1, lv_color_white());

    lv_color_t cb;
    lv_color_t cw;

    cb.full = 0;
    cw.full = 1;

    lv_canvas_fill_bg(canvas, cw, LV_OPA_COVER);

    // 背景颜色白色，有边框
    // lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);
    //lv_layer_t layer;
    //lv_canvas_init_layer(canvas, &layer);
    //// 画十字
    //lv_draw_line_dsc_t dsc1;
    //lv_draw_line_dsc_init(&dsc1);
    //dsc1.color = lv_color_black();
    //dsc1.width = 2;
    //dsc1.round_end = 1;
    //dsc1.round_start = 1;
    //dsc1.p1.x = canvas_width/2;
    //dsc1.p1.y = 0;
    //dsc1.p2.x = canvas_width / 2;
    //dsc1.p2.y = canvas_height;
    //lv_draw_line(&layer, &dsc1);
    for (int i = 0; i < canvas_width; i++) {
        lv_canvas_set_px(canvas, i, canvas_height / 2, cb);
    }
    for (int i = 0; i < canvas_height; i++) {
        lv_canvas_set_px(canvas, canvas_width / 2, i, cb);
    }

    //黑色边框
    for (int i = 0; i < canvas_width; i++) {
        lv_canvas_set_px(canvas, i, 0, cb);
        lv_canvas_set_px(canvas, i, canvas_height - 1, cb);
    }
    for (int i = 0; i < canvas_height; i++) {
        lv_canvas_set_px(canvas, 0, i, cb);
        lv_canvas_set_px(canvas, canvas_width - 1, i, cb);
    }




    // label显示信息，设置字体为中文
    lv_obj_t* status1 = lv_label_create(win2_cont);
    lv_label_set_text(status1, "Lat: 32.13722133");
    // lv_obj_set_style_text_font(status1, &lv_font_siyuan_small, 0);
    lv_obj_t * status2 = lv_label_create(win2_cont);
    lv_label_set_text(status2, "Lon.69514016");
    // lv_obj_set_style_text_font(status2, &lv_font_siyuan_small, 0);
    lv_obj_t * status3 = lv_label_create(win2_cont);
    lv_label_set_text(status3, "Heig.8");
    // lv_obj_set_style_text_font(status3, &lv_font_siyuan_small, 0);
    lv_obj_t* status4 = lv_label_create(win2_cont);
    lv_label_set_text(status4, "Value: 7");
    // lv_obj_set_style_text_font(status4, &lv_font_siyuan_small, 0);
    lv_obj_t* status5 = lv_label_create(win2_cont);
    lv_label_set_text(status5, "State: RTK");
    // lv_obj_set_style_text_font(status5, &lv_font_siyuan_small, 0);
    lv_obj_t* status6 = lv_label_create(win2_cont);
    lv_label_set_text(status6, "Netstate: 4G");
    // lv_obj_set_style_text_font(status6, &lv_font_siyuan_small, 0);
}


// 初始化隐藏的win3窗口
static void win3_init() {
    // 窗口3
    win3 = lv_win_create(lv_scr_act(), 40);




    lv_win_add_title(win3, "Btn3");
    lv_obj_add_flag(win3, LV_OBJ_FLAG_HIDDEN); // 隐藏
    lv_obj_t* close_btn3 = lv_win_add_btn(win3, LV_SYMBOL_CLOSE, 50);
    lv_obj_add_event_cb(close_btn3, win3_close_event_cb, LV_EVENT_CLICKED, NULL);

    // 创建容器，大小与win3相同，使用flex布局
    lv_obj_t* win3_cont = lv_win_get_content(win3);
    lv_obj_set_flex_flow(win3_cont, LV_FLEX_FLOW_COLUMN_WRAP);

    lv_obj_set_style_pad_all(win3_cont, 10, LV_PART_MAIN); // 内部元素距离上下左右的距离
    lv_obj_set_flex_flow(win3_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(win3_cont, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(win3_cont, 20, LV_PART_MAIN);
    lv_obj_set_style_pad_column(win3_cont, 20, LV_PART_MAIN);
    lv_obj_clear_flag(win3_cont, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动条



    lv_obj_t* bstartsavemsg = lv_btn_create(win3_cont);
    lv_obj_set_size(bstartsavemsg, 100, 90);
    lv_obj_t* bstartsavemsg_label = lv_label_create(bstartsavemsg);
    lv_label_set_text(bstartsavemsg_label, "start save");
    lv_obj_add_event_cb(bstartsavemsg, btn_startsavemsg_event_cb, LV_EVENT_CLICKED, bstartsavemsg);
    // 按钮图标位于中心
    lv_obj_set_align(bstartsavemsg_label, LV_ALIGN_CENTER);


    lv_obj_t* bsavemsg = lv_btn_create(win3_cont);
    lv_obj_set_size(bsavemsg, 100, 90);
    lv_obj_t* bsavemsg_label = lv_label_create(bsavemsg);
    lv_label_set_text(bsavemsg_label, "save");
    lv_obj_add_event_cb(bsavemsg, btn_savemsg_event_cb, LV_EVENT_CLICKED, bsavemsg);
    // 按钮图标位于中心
    lv_obj_set_align(bsavemsg_label, LV_ALIGN_CENTER);

    lv_obj_t* calculate = lv_btn_create(win3_cont);
    lv_obj_set_size(calculate, 100, 90);
    lv_obj_t* calculate_label = lv_label_create(calculate);
    lv_label_set_text(calculate_label, "calcu");
    lv_obj_add_event_cb(calculate, btn_calculate_event_cb, LV_EVENT_CLICKED, calculate);
    // 按钮图标位于中心
    lv_obj_set_align(calculate_label, LV_ALIGN_CENTER);

    lv_obj_t* bstartsaveimu = lv_btn_create(win3_cont);
    lv_obj_set_size(bstartsaveimu, 100, 90);
    lv_obj_t* bstartsaveimu_label = lv_label_create(bstartsaveimu);
    lv_label_set_text(bstartsaveimu_label, "start save imu");
    lv_obj_add_event_cb(bstartsaveimu, btn_bstartsaveimu_event_cb, LV_EVENT_CLICKED, bstartsaveimu);
    // 按钮图标位于中心
    lv_obj_set_align(bstartsaveimu_label, LV_ALIGN_CENTER);

    lv_obj_t* bsaveimu = lv_btn_create(win3_cont);
    lv_obj_set_size(bsaveimu, 100, 90);
    lv_obj_t* bsaveimu_label = lv_label_create(bsaveimu);
    lv_label_set_text(bsaveimu_label, "start save imu");
    lv_obj_add_event_cb(bsaveimu, btn_bsaveimu_event_cb, LV_EVENT_CLICKED, bsaveimu);
    // 按钮图标位于中心
    lv_obj_set_align(bsaveimu_label, LV_ALIGN_CENTER);

    // lv_obj_add_event_cb(bsavemsg, btn_plus3_event_cb, LV_EVENT_VALUE_CHANGED, bsavemsg);


    // label显示信息
    // lv_obj_t* status1 = lv_label_create(win3_cont);
    // lv_label_set_text(status1, "This is a hidden window. Click the button to show it.");
    // lv_obj_t * status2 = lv_label_create(win3_cont);
    // lv_label_set_text(status2, "This is a hidden window. Click the button to show it.");
    // lv_obj_t * status3 = lv_label_create(win3_cont);
    // lv_label_set_text(status3, "This is a hidden window. Click the button to show it.");
}

// 初始化隐藏的win4窗口
static void win4_init() {
    // 窗口4
    win4 = lv_win_create(lv_scr_act(), 40);
    lv_win_add_title(win4, "Btn4");
    lv_obj_add_flag(win4, LV_OBJ_FLAG_HIDDEN); // 隐藏
    lv_obj_t* close_btn4 = lv_win_add_btn(win4, LV_SYMBOL_CLOSE, 50);
    lv_obj_add_event_cb(close_btn4, win4_close_event_cb, LV_EVENT_CLICKED, NULL);

    // 创建容器，大小与win4相同，使用flex布局
    lv_obj_t* win4_cont = lv_win_get_content(win4);
    lv_obj_set_flex_flow(win4_cont, LV_FLEX_FLOW_COLUMN_WRAP);

    // label显示信息
    lv_obj_t* status1 = lv_label_create(win4_cont);
    lv_label_set_text(status1, "This is a hidden window. Click the button to show it.");
    lv_obj_t * status2 = lv_label_create(win4_cont);
    lv_label_set_text(status2, "This is a hidden window. Click the button to show it.");
    lv_obj_t * status3 = lv_label_create(win4_cont);
    lv_label_set_text(status3, "This is a hidden window. Click the button to show it.");
}


void my_gui(void)
{
    if(LV_HOR_RES <= 320) disp_size = DISP_SMALL;
    else if(LV_HOR_RES < 720) disp_size = DISP_MEDIUM;
    else disp_size = DISP_LARGE;

    font_large = LV_FONT_DEFAULT;
    font_normal = LV_FONT_DEFAULT;

    lv_coord_t tab_h;
    if(disp_size == DISP_LARGE) {
        tab_h = 70;
#if LV_FONT_MONTSERRAT_24
        font_large     = &lv_font_montserrat_24;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_24 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_16
        font_normal    = &lv_font_montserrat_16;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_16 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else if(disp_size == DISP_MEDIUM) {
        tab_h = 45;
#if LV_FONT_MONTSERRAT_20
        font_large     = &lv_font_montserrat_20;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_20 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_14
        font_normal    = &lv_font_montserrat_14;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_14 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else {   /* disp_size == DISP_SMALL */
        tab_h = 45;
#if LV_FONT_MONTSERRAT_18
        font_large     = &lv_font_montserrat_18;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_18 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_12
        font_normal    = &lv_font_montserrat_12;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_12 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }

#if LV_USE_THEME_DEFAULT
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                          font_normal);
#endif

    printf("mygui*: 设置风格初始化\r\n");

    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, font_large);

    lv_style_init(&style_icon);
    lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon, font_large);

    lv_style_init(&style_bullet);
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);


     // 创建无边框样式
    
    lv_style_init(&borderless);
    lv_style_set_border_opa(&borderless, LV_OPA_TRANSP);

    // 创建透明样式
    lv_style_init(&transparent);
    lv_style_set_bg_opa(&transparent, LV_OPA_0);
    lv_style_set_border_opa(&transparent, LV_OPA_0);

    //
    printf("mygui*: 创建scr\r\n");
    scr = lv_obj_create(lv_scr_act());
    lv_obj_set_size(scr, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
    lv_obj_align(scr, LV_ALIGN_CENTER, 0, 0); // Center the screen
    lv_obj_set_style_pad_all(scr, 25, LV_PART_MAIN); // 内部元素距离上下左右的距离
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动条
    lv_obj_set_flex_flow(scr, LV_FLEX_FLOW_COLUMN_WRAP);

    printf("mygui*: 创建title\r\n");
    title = lv_label_create(scr);
    lv_label_set_text(title, "chufanghe");
    lv_obj_set_size(title, 750, 60);
    // lv_obj_set_style_text_font(title, &lv_font_siyuan_small, 0);
    lv_obj_set_style_text_align(title, LV_ALIGN_TOP_MID, 0);

    printf("mygui*: 创建panel1\r\n");
    panel1 = lv_obj_create(scr); // 创建一个面板
    lv_obj_set_size(panel1, 750, 350); // 设置面板的大小
    lv_obj_add_style(panel1, &borderless, 0); // 设置面板的样式
    lv_obj_set_style_pad_all(panel1, 10, LV_PART_MAIN); // 内部元素距离上下左右的距离
    lv_obj_set_flex_flow(panel1, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(panel1, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(panel1, 20, LV_PART_MAIN);
    lv_obj_set_style_pad_column(panel1, 20, LV_PART_MAIN);
    lv_obj_clear_flag(panel1, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动条

    // panel1 内有四个按钮

    printf("mygui*: 设置四个按钮\r\n");
    // 按钮1
    lv_obj_t * btn1 = lv_btn_create(panel1); // 创建一个按钮
    lv_obj_set_size(btn1, 250, 130); // 设置按钮的大小
    lv_obj_t * label1 = lv_label_create(btn1); // 创建一个标签 
    lv_label_set_text(label1, "Parameters"); // 设置标签的文本
    // 使用中文
    // lv_obj_set_style_text_font(label1, &lv_font_siyuan_small, 0);
    //文本位于按钮中心
    lv_obj_set_align(label1, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn1, btn1_event_handler, LV_EVENT_CLICKED, NULL); // 设置按钮的handler

    // 按钮2
    lv_obj_t * btn2 = lv_btn_create(panel1); // 创建第二个按钮
    lv_obj_set_size(btn2, 250, 130); // 设置按钮的大小
    lv_obj_t * label2 = lv_label_create(btn2); // 创建第二个标签
    lv_label_set_text(label2, "Status"); // 设置第二个标签的文本
    // 使用中文
    // lv_obj_set_style_text_font(label2, &lv_font_siyuan_small, 0);
    //文本位于按钮中心
    lv_obj_set_align(label2, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn2, btn2_event_handler, LV_EVENT_CLICKED, NULL); // 设置第二个按钮的handler

    // 按钮3
    lv_obj_t * btn3 = lv_btn_create(panel1); // 创建第三个按钮
    lv_obj_set_size(btn3, 250, 130); // 设置按钮的大小
    lv_obj_t * label3 = lv_label_create(btn3); // 创建第三个标签
    lv_label_set_text(label3, "Proc File"); // 设置第三个标签的文本
    // 使用中文
    // lv_obj_set_style_text_font(label3, &lv_font_siyuan_small, 0);
    //文本位于按钮中心
    lv_obj_set_align(label3, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn3, btn3_event_handler, LV_EVENT_CLICKED, NULL); // 设置第三个按钮的handler

    // 按钮4
    lv_obj_t * btn4 = lv_btn_create(panel1); // 创建第四个按钮
    lv_obj_set_size(btn4, 250, 130); // 设置按钮的大小
    lv_obj_t * label4 = lv_label_create(btn4); // 创建第四个标签
    lv_label_set_text(label4, "Logs"); // 设置第四个标签的文本
    // 使用中文
    // lv_obj_set_style_text_font(label4, &lv_font_siyuan_small, 0);
    //文本位于按钮中心
    lv_obj_set_align(label4, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn4, btn4_event_handler, LV_EVENT_CLICKED, NULL); // 设置第四个按钮的handler

    printf("mygui*: 设置四个window\r\n");
    




    // 主界面中隐藏的部分
    


    printf("mygui*: 设置win1\r\n");
    win1_init();
    printf("mygui*: 设置win2\r\n");
    win2_init();
    printf("mygui*: 设置win3\r\n");
    win3_init();
    printf("mygui*: 设置win4\r\n");
    win4_init();

    printf("mygui*: all work done\r\n");



    // tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, tab_h);

    // lv_obj_set_style_text_font(lv_scr_act(), font_normal, 0);

    // if(disp_size == DISP_LARGE) {
    //     lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tv);
    //     lv_obj_set_style_pad_left(tab_btns, LV_HOR_RES / 2, 0);
    //     lv_obj_t * logo = lv_img_create(tab_btns);
    //     LV_IMG_DECLARE(img_lvgl_logo);
    //     lv_img_set_src(logo, &img_lvgl_logo);
    //     lv_obj_align(logo, LV_ALIGN_LEFT_MID, -LV_HOR_RES / 2 + 25, 0);

    //     lv_obj_t * label = lv_label_create(tab_btns);
    //     lv_obj_add_style(label, &style_title, 0);
    //     lv_label_set_text(label, "LVGL v8");
    //     lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

    //     label = lv_label_create(tab_btns);
    //     lv_label_set_text(label, "Widgets demo");
    //     lv_obj_add_style(label, &style_text_muted, 0);
    //     lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
    // }

    // lv_obj_t * t1 = lv_tabview_add_tab(tv, "Profile");
    // lv_obj_t * t2 = lv_tabview_add_tab(tv, "Analytics");
    // lv_obj_t * t3 = lv_tabview_add_tab(tv, "Shop");
    // profile_create(t1);
    // analytics_create(t2);
    // shop_create(t3);

    // color_changer_create(tv);
}
