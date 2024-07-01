#include "gui.h"

#include "FreeRTOS.h"
#include "freertos_os2.h"
#include "cmsis_os2.h"
#include "gps.h"
#include "imu.h"


//*****************************��ֲ��lvgl��һ�������Լ����ɵ������ļ��ͻῨ����������֮���޷���ʾ����***************** */



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
lv_obj_t* panel1; // ����һ�����
lv_obj_t* panel2;
lv_obj_t* win1, * win2;
lv_obj_t* win3, * win4;


 // ��ťhandler
static void btn1_event_handler(lv_event_t* event) {
    // button pressed
    
        lv_obj_clear_flag(win1, LV_OBJ_FLAG_HIDDEN);
}
// ��ťbtn2��handler
static void btn2_event_handler(lv_event_t* event) {
    // button pressed
    lv_obj_clear_flag(win2, LV_OBJ_FLAG_HIDDEN);
}
// ��ťbtn3��handler
static void btn3_event_handler(lv_event_t* event) {
    // button pressed
    lv_obj_clear_flag(win3, LV_OBJ_FLAG_HIDDEN);
}
// ��ťbtn4��handler
static void btn4_event_handler(lv_event_t* event) {
    // button pressed
    lv_obj_clear_flag(win4, LV_OBJ_FLAG_HIDDEN);
}


static void win1_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win1, LV_OBJ_FLAG_HIDDEN);
}
// ����2�Ĺر�handler
static void win2_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win2, LV_OBJ_FLAG_HIDDEN);
}
// ����3�Ĺر�handler
static void win3_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win3, LV_OBJ_FLAG_HIDDEN);
}
// ����4�Ĺر�handler
static void win4_close_event_cb(lv_event_t* event) {
    // button pressed
    lv_obj_add_flag(win4, LV_OBJ_FLAG_HIDDEN);
}


lv_style_t borderless;
// ͸����ʽ
lv_style_t transparent;

int contorller1_num = 0;
// �ӺŰ�ťbp1��handler
static void btn_plus1_event_cb(lv_event_t* event) {
       // button pressed
    contorller1_num++;
    lv_obj_t* bp1_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp1_txt, "%d", contorller1_num);
}
// ���Ű�ťbm1��handler
static void btn_minus1_event_cb(lv_event_t* event) {
    // button pressed
    contorller1_num--;
    lv_obj_t* bp1_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp1_txt, "%d", contorller1_num);
}

int contorller2_num = 0;
// �ӺŰ�ťbp2��handler
static void btn_plus2_event_cb(lv_event_t* event) {
    // button pressed
    contorller2_num++;
    lv_obj_t* bp2_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp2_txt, "%d", contorller2_num);
}
// ���Ű�ťbm2��handler
static void btn_minus2_event_cb(lv_event_t* event) {
    // button pressed
    contorller2_num--;
    lv_obj_t* bp2_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp2_txt, "%d", contorller2_num);
}


int contorller3_num = 0;
// �ӺŰ�ťbp3��handler
static void btn_plus3_event_cb(lv_event_t* event) {
    // button pressed
    contorller3_num++;
    lv_obj_t* bp3_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp3_txt, "%d", contorller3_num);
}
// ���Ű�ťbm3��handler
static void btn_minus3_event_cb(lv_event_t* event) {
    // button pressed
    contorller3_num--;
    lv_obj_t* bp3_txt = lv_obj_get_child(lv_obj_get_parent(event->current_target), 2);
    lv_label_set_text_fmt(bp3_txt, "%d", contorller3_num);
}


// �������handler
static void ddlist_event_handler(lv_event_t* event) {
    // button pressed
    lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t * obj = lv_event_get_target(event);
    uint16_t c = lv_dropdown_get_selected(obj);
}

//���水ť��handler
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
    osMessageQueuePut(gpshuart_flagqHandle, &flag, 2U, 0U); //�����յ������ݷ��͵�����
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
//���������Ĵ�С
#define CTN_WIDTH 220
#define CTN_HEIGHT 60

// ��ʼ�����ص�win1����
static void win1_init() {
    // ����1
    win1 = lv_win_create(lv_scr_act(),70);
    lv_win_add_title(win1, "   ");
    
    lv_obj_add_flag(win1, LV_OBJ_FLAG_HIDDEN); // ����
    lv_obj_t* close_btn1 = lv_win_add_btn(win1, LV_SYMBOL_CLOSE, 70);
    lv_obj_add_event_cb(close_btn1, win1_close_event_cb, LV_EVENT_CLICKED, NULL);

    // ������������С��win1��ͬ��ʹ��flex���֣�����Ԫ�ؾ���
    lv_obj_t* win1_cont = lv_win_get_content(win1);
    lv_obj_set_flex_flow(win1_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(win1_cont, 5, LV_PART_MAIN);
    //����ʾ������
    // lv_obj_clear_flag(win1_cont, LV_OBJ_FLAG_SCROLLABLE);

    // �Ϸ�������͸��
    lv_obj_t* up_cont = lv_obj_create(win1_cont);
    lv_obj_add_style(up_cont, &transparent, 0);
    lv_obj_set_flex_flow(up_cont, LV_FLEX_FLOW_COLUMN_WRAP);
    // lv_obj_set_flex_align(up_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(up_cont, 5, LV_PART_MAIN);
    lv_obj_clear_flag(up_cont, LV_OBJ_FLAG_SCROLLABLE);
    // �趨��С
    lv_obj_set_size(up_cont, 780, 360);


    // ͼƬ����
    lv_obj_t * img_cont = lv_obj_create(up_cont);
    // �趨��С 428x208
    lv_obj_set_size(img_cont, 460, 340);
    // �ޱ߿�
    lv_obj_add_style(img_cont, &transparent, 0);
    // ����ʾ������
    lv_obj_clear_flag(img_cont, LV_OBJ_FLAG_SCROLLABLE);
    // flex���򲼾�
    lv_obj_set_flex_flow(img_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(img_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    LV_IMG_DECLARE(img1);
    lv_obj_t* img1_obj = lv_img_create(img_cont);
    lv_img_set_src(img1_obj, &img1);
    // imgλ������
    // lv_obj_set_align(img1_obj, LV_ALIGN_CENTER);
    // img �·��ı�
    lv_obj_t* img1_txt = lv_label_create(img_cont);
    lv_label_set_text(img1_txt, "Schema");
    // ����
    // lv_obj_set_style_text_font(img1_txt, &lv_font_siyuan_micro, 0);

    // �ı�
    //lv_obj_t* win1_txt = lv_label_create(win1_cont);
    //lv_label_set_text(win1_txt, "This is a hidden window. Click the button to show it.");

    // �������������ĸ�С����
    lv_obj_t* option_cont2 = lv_obj_create(up_cont);    
    lv_obj_set_flex_flow(option_cont2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(option_cont2, 5, LV_PART_MAIN);
    lv_obj_clear_flag(option_cont2, LV_OBJ_FLAG_SCROLLABLE);
    //͸��
    lv_obj_add_style(option_cont2, &transparent, 0);
    // ��С
    lv_obj_set_size(option_cont2, 400, 400);


    // ����1������һ���ӺŰ�ť��һ���ı���һ�����Ű�ť��flex���򲼾֣�ָ����С��������͸��
    lv_obj_t* contorller1 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller1, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller1, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller1, &transparent, 0); // �����ʼ��transparent��ʽ!!
    lv_obj_set_flex_align(contorller1, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //����ʾ������
    lv_obj_clear_flag(contorller1, LV_OBJ_FLAG_SCROLLABLE);
    
    // �ı�ʹ��ָ������
    lv_obj_t* bp1_txt1 = lv_label_create(contorller1);
    lv_label_set_text(bp1_txt1, "L1");
    // lv_obj_set_style_text_font(bp1_txt1, &lv_font_siyuan_micro, 0);
    // �ӺŰ�ť�����º�ı������ı�����ť��С����С��������С
    lv_obj_t* bp1 = lv_btn_create(contorller1);
    lv_obj_set_size(bp1, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bp1_label = lv_label_create(bp1);
    lv_label_set_text(bp1_label, "+");
    // ��ťͼ��λ������
    lv_obj_set_align(bp1_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bp1, btn_plus1_event_cb, LV_EVENT_CLICKED, bp1);
    // �ı�
    lv_obj_t* bp1_txt = lv_label_create(contorller1);
    lv_label_set_text(bp1_txt, "0");
    //�ı�λ������
    lv_obj_set_align(bp1_txt, LV_ALIGN_CENTER);
    // ���Ű�ť�����º�ı�ǰ����ı�����ť��С����С��������С
    lv_obj_t* bm1 = lv_btn_create(contorller1);
    lv_obj_set_size(bm1, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bm1_label = lv_label_create(bm1);
    lv_label_set_text(bm1_label, "-");
    // ��ťͼ��λ������
    lv_obj_set_align(bm1_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bm1, btn_minus1_event_cb, LV_EVENT_CLICKED, bm1);


    // ����2������һ���ı����ӺŰ�ť��һ���ı���һ�����Ű�ť��flex���򲼾֣�ָ����С��������͸��
    lv_obj_t* contorller2 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller2, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller2, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller2, &transparent, 0); // �����ʼ��transparent��ʽ!!
    lv_obj_set_flex_align(contorller2, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //����ʾ������
    lv_obj_clear_flag(contorller2, LV_OBJ_FLAG_SCROLLABLE);
    // �ı�ʹ��ָ������
    lv_obj_t* bp2_txt1 = lv_label_create(contorller2);
    lv_label_set_text(bp2_txt1, "L2");
    // lv_obj_set_style_text_font(bp2_txt1, &lv_font_siyuan_micro, 0);
    // �ӺŰ�ť�����º�ı������ı�����ť��С����С��������С
    lv_obj_t* bp2 = lv_btn_create(contorller2);
    lv_obj_set_size(bp2, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bp2_label = lv_label_create(bp2);
    lv_label_set_text(bp2_label, "+");
    // ��ťͼ��λ������
    lv_obj_set_align(bp2_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bp2, btn_plus2_event_cb, LV_EVENT_CLICKED, bp2);
    // �ı�
    lv_obj_t* bp2_txt = lv_label_create(contorller2);
    lv_label_set_text(bp2_txt, "0");
    //�ı�λ������
    lv_obj_set_align(bp2_txt, LV_ALIGN_CENTER);
    // ���Ű�ť�����º�ı�ǰ����ı�����ť��С����С��������С
    lv_obj_t* bm2 = lv_btn_create(contorller2);
    lv_obj_set_size(bm2, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t * bm2_label = lv_label_create(bm2);
    lv_label_set_text(bm2_label, "-");
    // ��ťͼ��λ������ 
    lv_obj_set_align(bm2_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bm2, btn_minus2_event_cb, LV_EVENT_CLICKED, bm2);


    // ����3������һ���ı���һ�������flex���򲼾֣�ָ����С��������͸��
    lv_obj_t* contorller3 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller3, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller3, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller3, &transparent, 0); // �����ʼ��transparent��ʽ!!
    lv_obj_set_flex_align(contorller3, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //����ʾ������
    lv_obj_clear_flag(contorller3, LV_OBJ_FLAG_SCROLLABLE);
    // �ı�ʹ��ָ������
    lv_obj_t* bp3_txt1 = lv_label_create(contorller3);
    lv_label_set_text(bp3_txt1, "L3");
    // lv_obj_set_style_text_font(bp3_txt1, &lv_font_siyuan_micro, 0);
    // �ӺŰ�ť�����º�ı������ı�����ť��С����С��������С
    lv_obj_t* bp3 = lv_btn_create(contorller3);
    lv_obj_set_size(bp3, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t* bp3_label = lv_label_create(bp3);
    lv_label_set_text(bp3_label, "+");
    lv_obj_add_event_cb(bp3, btn_plus3_event_cb, LV_EVENT_CLICKED, bp3);

    // ��ťͼ��λ������
    lv_obj_set_align(bp3_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bp3, btn_plus3_event_cb, LV_EVENT_VALUE_CHANGED, bp3);
    // �ı�
    lv_obj_t* bp3_txt = lv_label_create(contorller3);
    lv_label_set_text(bp3_txt, "0");
    //�ı�λ������
    lv_obj_set_align(bp3_txt, LV_ALIGN_CENTER);
    // ���Ű�ť�����º�ı�ǰ����ı�����ť��С����С��������С
    lv_obj_t* bm3 = lv_btn_create(contorller3);
    lv_obj_set_size(bm3, BTN_WIDTH, BTN_WIDTH);
    lv_obj_t * bm3_label = lv_label_create(bm3);
    lv_label_set_text(bm3_label, "-");
    // ��ťͼ��λ������
    lv_obj_set_align(bm3_label, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(bm3, btn_minus3_event_cb, LV_EVENT_CLICKED, bm3);

    // ����4������һ���ı���һ����������������������ѡ�flex���򲼾֣�ָ����С��������͸��
    lv_obj_t* contorller4 = lv_obj_create(option_cont2);
    lv_obj_set_flex_flow(contorller4, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(contorller4, CTN_WIDTH, CTN_HEIGHT);
    lv_obj_add_style(contorller4, &transparent, 0); // �����ʼ��transparent��ʽ!!
    lv_obj_set_flex_align(contorller4, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //����ʾ������
    lv_obj_clear_flag(contorller4, LV_OBJ_FLAG_SCROLLABLE);
    //lv_obj_set_style_text_font(contorller4, &lv_font_siyuan_micro, 0);

    // �ı�ʹ��ָ������
    lv_obj_t* bp4_txt1 = lv_label_create(contorller4);
    lv_label_set_text(bp4_txt1, "Type");
    // lv_obj_set_style_text_font(bp4_txt1, &lv_font_siyuan_micro, 0);

    // ��ʼ�����ķ��
    lv_style_t chinese_style;
    lv_style_init(&chinese_style);
    lv_style_set_text_font(&chinese_style, &lv_font_siyuan_micro);

    // ������
    lv_obj_t* ddlist = lv_dropdown_create(contorller4);
    //lv_dropdown_set_options(ddlist, "1");

    lv_dropdown_set_options(ddlist, "A\nB\nC");
    //��������
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

    // ����˵������ѡ���
    lv_obj_t* bp4_txt = lv_label_create(option_cont2);
    lv_label_set_text(bp4_txt, "A:Sow B: Fertilize C:Spray");
    // lv_obj_set_style_text_font(bp4_txt, &lv_font_siyuan_micro, 0);

    // �·����� ͸��
    lv_obj_t* down_cont = lv_obj_create(win1_cont);
    lv_obj_add_style(down_cont, &transparent, 0);
    // ��С
    lv_obj_set_size(down_cont, 780, 40);
    // ����λ�÷��ð�ť����ť����Ϊ����
    lv_obj_t* save_btn = lv_btn_create(down_cont);
    lv_obj_set_size(save_btn, 100, 30);
    lv_obj_t* save_btn_label = lv_label_create(save_btn);
    lv_label_set_text(save_btn_label, "Save");
    // ����������
    lv_obj_set_align(save_btn_label, LV_ALIGN_CENTER);

    // lv_obj_set_style_text_font(save_btn_label, &lv_font_siyuan_micro, 0);
    lv_obj_add_event_cb(save_btn, save_btn_event_handler, LV_EVENT_CLICKED, NULL);
    //λ��������
    lv_obj_set_align(save_btn, LV_ALIGN_CENTER);
    //����ʾ������
    lv_obj_clear_flag(down_cont, LV_OBJ_FLAG_SCROLLABLE);

}


// ��ʼ�����ص�win2����
static void win2_init() {
    // ����2
    win2 = lv_win_create(lv_scr_act(), 60);
    lv_win_add_title(win2, "   ");
    lv_obj_add_flag(win2, LV_OBJ_FLAG_HIDDEN); // ����
    lv_obj_t* close_btn2 = lv_win_add_btn(win2, LV_SYMBOL_CLOSE, 60);
    lv_obj_add_event_cb(close_btn2, win2_close_event_cb, LV_EVENT_CLICKED, NULL);

    //������������С��win2��ͬ��ʹ��flex����
    lv_obj_t* win2_cont = lv_win_get_content(win2);
    lv_obj_set_flex_flow(win2_cont, LV_FLEX_FLOW_COLUMN_WRAP);

    // ��ʼ��lv_style_plain_color
    lv_style_t lv_style_plain_color;
    lv_style_init(&lv_style_plain_color);
    lv_style_set_border_color(&lv_style_plain_color, lv_color_black());

    // ��������
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

    // ������ɫ��ɫ���б߿�
    // lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);
    //lv_layer_t layer;
    //lv_canvas_init_layer(canvas, &layer);
    //// ��ʮ��
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

    //��ɫ�߿�
    for (int i = 0; i < canvas_width; i++) {
        lv_canvas_set_px(canvas, i, 0, cb);
        lv_canvas_set_px(canvas, i, canvas_height - 1, cb);
    }
    for (int i = 0; i < canvas_height; i++) {
        lv_canvas_set_px(canvas, 0, i, cb);
        lv_canvas_set_px(canvas, canvas_width - 1, i, cb);
    }




    // label��ʾ��Ϣ����������Ϊ����
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


// ��ʼ�����ص�win3����
static void win3_init() {
    // ����3
    win3 = lv_win_create(lv_scr_act(), 40);




    lv_win_add_title(win3, "Btn3");
    lv_obj_add_flag(win3, LV_OBJ_FLAG_HIDDEN); // ����
    lv_obj_t* close_btn3 = lv_win_add_btn(win3, LV_SYMBOL_CLOSE, 50);
    lv_obj_add_event_cb(close_btn3, win3_close_event_cb, LV_EVENT_CLICKED, NULL);

    // ������������С��win3��ͬ��ʹ��flex����
    lv_obj_t* win3_cont = lv_win_get_content(win3);
    lv_obj_set_flex_flow(win3_cont, LV_FLEX_FLOW_COLUMN_WRAP);

    lv_obj_set_style_pad_all(win3_cont, 10, LV_PART_MAIN); // �ڲ�Ԫ�ؾ����������ҵľ���
    lv_obj_set_flex_flow(win3_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(win3_cont, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(win3_cont, 20, LV_PART_MAIN);
    lv_obj_set_style_pad_column(win3_cont, 20, LV_PART_MAIN);
    lv_obj_clear_flag(win3_cont, LV_OBJ_FLAG_SCROLLABLE); // ��ֹ������



    lv_obj_t* bstartsavemsg = lv_btn_create(win3_cont);
    lv_obj_set_size(bstartsavemsg, 100, 90);
    lv_obj_t* bstartsavemsg_label = lv_label_create(bstartsavemsg);
    lv_label_set_text(bstartsavemsg_label, "start save");
    lv_obj_add_event_cb(bstartsavemsg, btn_startsavemsg_event_cb, LV_EVENT_CLICKED, bstartsavemsg);
    // ��ťͼ��λ������
    lv_obj_set_align(bstartsavemsg_label, LV_ALIGN_CENTER);


    lv_obj_t* bsavemsg = lv_btn_create(win3_cont);
    lv_obj_set_size(bsavemsg, 100, 90);
    lv_obj_t* bsavemsg_label = lv_label_create(bsavemsg);
    lv_label_set_text(bsavemsg_label, "save");
    lv_obj_add_event_cb(bsavemsg, btn_savemsg_event_cb, LV_EVENT_CLICKED, bsavemsg);
    // ��ťͼ��λ������
    lv_obj_set_align(bsavemsg_label, LV_ALIGN_CENTER);

    lv_obj_t* calculate = lv_btn_create(win3_cont);
    lv_obj_set_size(calculate, 100, 90);
    lv_obj_t* calculate_label = lv_label_create(calculate);
    lv_label_set_text(calculate_label, "calcu");
    lv_obj_add_event_cb(calculate, btn_calculate_event_cb, LV_EVENT_CLICKED, calculate);
    // ��ťͼ��λ������
    lv_obj_set_align(calculate_label, LV_ALIGN_CENTER);

    lv_obj_t* bstartsaveimu = lv_btn_create(win3_cont);
    lv_obj_set_size(bstartsaveimu, 100, 90);
    lv_obj_t* bstartsaveimu_label = lv_label_create(bstartsaveimu);
    lv_label_set_text(bstartsaveimu_label, "start save imu");
    lv_obj_add_event_cb(bstartsaveimu, btn_bstartsaveimu_event_cb, LV_EVENT_CLICKED, bstartsaveimu);
    // ��ťͼ��λ������
    lv_obj_set_align(bstartsaveimu_label, LV_ALIGN_CENTER);

    lv_obj_t* bsaveimu = lv_btn_create(win3_cont);
    lv_obj_set_size(bsaveimu, 100, 90);
    lv_obj_t* bsaveimu_label = lv_label_create(bsaveimu);
    lv_label_set_text(bsaveimu_label, "start save imu");
    lv_obj_add_event_cb(bsaveimu, btn_bsaveimu_event_cb, LV_EVENT_CLICKED, bsaveimu);
    // ��ťͼ��λ������
    lv_obj_set_align(bsaveimu_label, LV_ALIGN_CENTER);

    // lv_obj_add_event_cb(bsavemsg, btn_plus3_event_cb, LV_EVENT_VALUE_CHANGED, bsavemsg);


    // label��ʾ��Ϣ
    // lv_obj_t* status1 = lv_label_create(win3_cont);
    // lv_label_set_text(status1, "This is a hidden window. Click the button to show it.");
    // lv_obj_t * status2 = lv_label_create(win3_cont);
    // lv_label_set_text(status2, "This is a hidden window. Click the button to show it.");
    // lv_obj_t * status3 = lv_label_create(win3_cont);
    // lv_label_set_text(status3, "This is a hidden window. Click the button to show it.");
}

// ��ʼ�����ص�win4����
static void win4_init() {
    // ����4
    win4 = lv_win_create(lv_scr_act(), 40);
    lv_win_add_title(win4, "Btn4");
    lv_obj_add_flag(win4, LV_OBJ_FLAG_HIDDEN); // ����
    lv_obj_t* close_btn4 = lv_win_add_btn(win4, LV_SYMBOL_CLOSE, 50);
    lv_obj_add_event_cb(close_btn4, win4_close_event_cb, LV_EVENT_CLICKED, NULL);

    // ������������С��win4��ͬ��ʹ��flex����
    lv_obj_t* win4_cont = lv_win_get_content(win4);
    lv_obj_set_flex_flow(win4_cont, LV_FLEX_FLOW_COLUMN_WRAP);

    // label��ʾ��Ϣ
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

    printf("mygui*: ���÷���ʼ��\r\n");

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


     // �����ޱ߿���ʽ
    
    lv_style_init(&borderless);
    lv_style_set_border_opa(&borderless, LV_OPA_TRANSP);

    // ����͸����ʽ
    lv_style_init(&transparent);
    lv_style_set_bg_opa(&transparent, LV_OPA_0);
    lv_style_set_border_opa(&transparent, LV_OPA_0);

    //
    printf("mygui*: ����scr\r\n");
    scr = lv_obj_create(lv_scr_act());
    lv_obj_set_size(scr, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
    lv_obj_align(scr, LV_ALIGN_CENTER, 0, 0); // Center the screen
    lv_obj_set_style_pad_all(scr, 25, LV_PART_MAIN); // �ڲ�Ԫ�ؾ����������ҵľ���
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE); // ��ֹ������
    lv_obj_set_flex_flow(scr, LV_FLEX_FLOW_COLUMN_WRAP);

    printf("mygui*: ����title\r\n");
    title = lv_label_create(scr);
    lv_label_set_text(title, "chufanghe");
    lv_obj_set_size(title, 750, 60);
    // lv_obj_set_style_text_font(title, &lv_font_siyuan_small, 0);
    lv_obj_set_style_text_align(title, LV_ALIGN_TOP_MID, 0);

    printf("mygui*: ����panel1\r\n");
    panel1 = lv_obj_create(scr); // ����һ�����
    lv_obj_set_size(panel1, 750, 350); // �������Ĵ�С
    lv_obj_add_style(panel1, &borderless, 0); // ����������ʽ
    lv_obj_set_style_pad_all(panel1, 10, LV_PART_MAIN); // �ڲ�Ԫ�ؾ����������ҵľ���
    lv_obj_set_flex_flow(panel1, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(panel1, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(panel1, 20, LV_PART_MAIN);
    lv_obj_set_style_pad_column(panel1, 20, LV_PART_MAIN);
    lv_obj_clear_flag(panel1, LV_OBJ_FLAG_SCROLLABLE); // ��ֹ������

    // panel1 �����ĸ���ť

    printf("mygui*: �����ĸ���ť\r\n");
    // ��ť1
    lv_obj_t * btn1 = lv_btn_create(panel1); // ����һ����ť
    lv_obj_set_size(btn1, 250, 130); // ���ð�ť�Ĵ�С
    lv_obj_t * label1 = lv_label_create(btn1); // ����һ����ǩ 
    lv_label_set_text(label1, "Parameters"); // ���ñ�ǩ���ı�
    // ʹ������
    // lv_obj_set_style_text_font(label1, &lv_font_siyuan_small, 0);
    //�ı�λ�ڰ�ť����
    lv_obj_set_align(label1, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn1, btn1_event_handler, LV_EVENT_CLICKED, NULL); // ���ð�ť��handler

    // ��ť2
    lv_obj_t * btn2 = lv_btn_create(panel1); // �����ڶ�����ť
    lv_obj_set_size(btn2, 250, 130); // ���ð�ť�Ĵ�С
    lv_obj_t * label2 = lv_label_create(btn2); // �����ڶ�����ǩ
    lv_label_set_text(label2, "Status"); // ���õڶ�����ǩ���ı�
    // ʹ������
    // lv_obj_set_style_text_font(label2, &lv_font_siyuan_small, 0);
    //�ı�λ�ڰ�ť����
    lv_obj_set_align(label2, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn2, btn2_event_handler, LV_EVENT_CLICKED, NULL); // ���õڶ�����ť��handler

    // ��ť3
    lv_obj_t * btn3 = lv_btn_create(panel1); // ������������ť
    lv_obj_set_size(btn3, 250, 130); // ���ð�ť�Ĵ�С
    lv_obj_t * label3 = lv_label_create(btn3); // ������������ǩ
    lv_label_set_text(label3, "Proc File"); // ���õ�������ǩ���ı�
    // ʹ������
    // lv_obj_set_style_text_font(label3, &lv_font_siyuan_small, 0);
    //�ı�λ�ڰ�ť����
    lv_obj_set_align(label3, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn3, btn3_event_handler, LV_EVENT_CLICKED, NULL); // ���õ�������ť��handler

    // ��ť4
    lv_obj_t * btn4 = lv_btn_create(panel1); // �������ĸ���ť
    lv_obj_set_size(btn4, 250, 130); // ���ð�ť�Ĵ�С
    lv_obj_t * label4 = lv_label_create(btn4); // �������ĸ���ǩ
    lv_label_set_text(label4, "Logs"); // ���õ��ĸ���ǩ���ı�
    // ʹ������
    // lv_obj_set_style_text_font(label4, &lv_font_siyuan_small, 0);
    //�ı�λ�ڰ�ť����
    lv_obj_set_align(label4, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(btn4, btn4_event_handler, LV_EVENT_CLICKED, NULL); // ���õ��ĸ���ť��handler

    printf("mygui*: �����ĸ�window\r\n");
    




    // �����������صĲ���
    


    printf("mygui*: ����win1\r\n");
    win1_init();
    printf("mygui*: ����win2\r\n");
    win2_init();
    printf("mygui*: ����win3\r\n");
    win3_init();
    printf("mygui*: ����win4\r\n");
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
