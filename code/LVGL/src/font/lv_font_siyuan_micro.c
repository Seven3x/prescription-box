/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font SourceHanSansCN-Medium-2.otf --symbols 处方盒系统作业参数设置显示界面处方文件选择作业日志当前位置当前处方航向作业轨迹图：1234567890车体间距L1车体间距L2车体间距L3m作业类型播种施肥喷药经度纬度高程米处方值定位模式网络状态作业轨迹.QWERTYUIOPASDFGHJKLZXCVBNM示意图A:播种  B:施肥  C:喷药保存 --format lvgl -o lv_font_siyuan_micro.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_FONT_SIYUAN_MICRO
#define LV_FONT_SIYUAN_MICRO 1
#endif

#if LV_FONT_SIYUAN_MICRO

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002E "." */
    0xc0,

    /* U+0030 "0" */
    0x3c, 0x66, 0x42, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x42, 0x66, 0x3c,

    /* U+0031 "1" */
    0x31, 0xe0, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x60, 0xc7, 0xf0,

    /* U+0032 "2" */
    0x78, 0xcc, 0x6, 0x6, 0x6, 0xe, 0xc, 0x1c,
    0x38, 0x30, 0x60, 0xff,

    /* U+0033 "3" */
    0x7d, 0x8c, 0x18, 0x30, 0xc7, 0x3, 0x3, 0x7,
    0xe, 0x33, 0xc0,

    /* U+0034 "4" */
    0xe, 0xe, 0x1e, 0x16, 0x36, 0x66, 0x66, 0xc6,
    0xff, 0x6, 0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0x60, 0x60, 0x60, 0x7c, 0x46, 0x3, 0x3,
    0x3, 0x3, 0xc6, 0x7c,

    /* U+0036 "6" */
    0x1e, 0x62, 0x60, 0xc0, 0xc0, 0xde, 0xe7, 0xc3,
    0xc3, 0x43, 0x66, 0x3c,

    /* U+0037 "7" */
    0xff, 0x6, 0xe, 0xc, 0x18, 0x18, 0x18, 0x30,
    0x30, 0x30, 0x30, 0x30,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1e, 0x36, 0x47, 0x1f, 0x67, 0xc7,
    0x8f, 0x99, 0xe0,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xe7, 0x7b, 0x3,
    0x3, 0x6, 0x46, 0x78,

    /* U+003A ":" */
    0xc0, 0x0, 0xc0,

    /* U+0041 "A" */
    0xc, 0x7, 0x81, 0xe0, 0x58, 0x33, 0xc, 0xc2,
    0x31, 0xfe, 0x61, 0x98, 0x6c, 0xb, 0x3,

    /* U+0042 "B" */
    0xfe, 0x63, 0xb0, 0xd8, 0x6c, 0x67, 0xe3, 0xd,
    0x83, 0xc1, 0xe0, 0xf0, 0xdf, 0xc0,

    /* U+0043 "C" */
    0x1f, 0x18, 0x98, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x30, 0xc, 0x63, 0xe0,

    /* U+0044 "D" */
    0xfc, 0x63, 0x30, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe1, 0xb1, 0x9f, 0x80,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x7, 0xf0,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x18, 0x3f, 0x60, 0xc1,
    0x83, 0x6, 0x0,

    /* U+0047 "G" */
    0x1f, 0x18, 0x98, 0x18, 0xc, 0x6, 0x3, 0x1f,
    0x83, 0xc1, 0xb0, 0xcc, 0x63, 0xe0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6,
    0xf, 0x33, 0xc0,

    /* U+004B "K" */
    0xc3, 0x63, 0x31, 0x99, 0x8d, 0x87, 0xc3, 0xf1,
    0xcc, 0xc6, 0x61, 0xb0, 0xd8, 0x30,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0x7, 0xf0,

    /* U+004D "M" */
    0xe1, 0xf8, 0x7e, 0x1f, 0x8f, 0xf2, 0xf4, 0xbd,
    0x2f, 0x73, 0xcc, 0xf3, 0x3c, 0xcf, 0x3,

    /* U+004E "N" */
    0xc1, 0xf0, 0xfc, 0x7e, 0x3d, 0x9e, 0xcf, 0x37,
    0x9b, 0xc7, 0xe3, 0xf0, 0xf8, 0x30,

    /* U+004F "O" */
    0x1e, 0x1c, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x67, 0x38, 0x78,

    /* U+0050 "P" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1e, 0x18, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0x61, 0xd8, 0x63, 0xf0, 0x30, 0x6,
    0x0, 0xf0,

    /* U+0052 "R" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc, 0xcc,
    0xcc, 0xc6, 0xc7, 0xc3,

    /* U+0053 "S" */
    0x1f, 0x10, 0x98, 0xc, 0x7, 0x81, 0xf0, 0x7c,
    0xf, 0x1, 0x80, 0xd8, 0xc7, 0xc0,

    /* U+0054 "T" */
    0xff, 0x8c, 0x6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x0,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xd8, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xc1, 0xb0, 0x66, 0x19, 0x84, 0x63, 0x8, 0xc3,
    0x30, 0xc8, 0x16, 0x7, 0x81, 0xc0, 0x70,

    /* U+0057 "W" */
    0xc3, 0xd, 0x8c, 0x36, 0x38, 0x98, 0xe2, 0x66,
    0x99, 0x9a, 0x62, 0x4d, 0x8d, 0x34, 0x3c, 0xd0,
    0xf1, 0x43, 0x87, 0x6, 0x1c,

    /* U+0058 "X" */
    0x61, 0xb1, 0x8c, 0xc6, 0xc1, 0xe0, 0xe0, 0x70,
    0x2c, 0x36, 0x11, 0x98, 0xc8, 0x30,

    /* U+0059 "Y" */
    0x61, 0x98, 0x63, 0x30, 0xcc, 0x12, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xff, 0x7, 0x6, 0xc, 0xc, 0x18, 0x18, 0x30,
    0x60, 0x60, 0xc0, 0xff,

    /* U+006D "m" */
    0xdc, 0xee, 0x73, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+4E1A "业" */
    0xc, 0xc0, 0x33, 0x0, 0xcc, 0x13, 0x32, 0x4c,
    0xcd, 0xb3, 0x26, 0xcd, 0x8b, 0x34, 0x3c, 0xf0,
    0x33, 0x0, 0xcc, 0x3, 0x30, 0xff, 0xfc,

    /* U+4EF6 "件" */
    0x10, 0xc0, 0x4b, 0x3, 0x6c, 0x9, 0xfe, 0x64,
    0xc3, 0xb3, 0xe, 0xc, 0x8, 0x30, 0x2f, 0xfc,
    0x83, 0x2, 0xc, 0x8, 0x30, 0x20, 0xc0, 0x83,
    0x0,

    /* U+4F4D "位" */
    0x8, 0x40, 0x30, 0xc0, 0x61, 0x81, 0x9f, 0xe7,
    0x0, 0x1e, 0x21, 0x2c, 0x42, 0x18, 0xcc, 0x31,
    0x98, 0x63, 0x30, 0xc6, 0x41, 0x80, 0x83, 0x7f,
    0xe6, 0x0, 0x0,

    /* U+4F53 "体" */
    0x10, 0xc0, 0x21, 0x80, 0x83, 0x1, 0x7f, 0xe6,
    0x1e, 0x1c, 0x3c, 0x28, 0xfc, 0x11, 0x68, 0x26,
    0xd8, 0x59, 0x98, 0xef, 0xd1, 0x6, 0x2, 0xc,
    0x4, 0x18, 0x0,

    /* U+4F5C "作" */
    0x0, 0x0, 0x33, 0x0, 0x64, 0x1, 0x9f, 0xf3,
    0x2c, 0xe, 0xd8, 0x3d, 0x30, 0x7a, 0x7e, 0x30,
    0xc0, 0x61, 0x80, 0xc3, 0xf9, 0x86, 0x3, 0xc,
    0x6, 0x18, 0xc, 0x30, 0x0,

    /* U+4FDD "保" */
    0x10, 0x0, 0x5f, 0xe3, 0x40, 0x89, 0x2, 0x64,
    0xb, 0x9f, 0xee, 0xc, 0x28, 0x30, 0x2f, 0xfc,
    0x87, 0x82, 0x3f, 0x9, 0xb4, 0x2e, 0xdc, 0xb3,
    0x32, 0xc, 0x0,

    /* U+503C "值" */
    0x10, 0xc0, 0xff, 0xf2, 0x8, 0x18, 0x20, 0x67,
    0xfb, 0x90, 0x2a, 0x7f, 0x89, 0x2, 0x27, 0xf8,
    0x90, 0x22, 0x7f, 0x89, 0x2, 0x24, 0x8, 0xbf,
    0xf0,

    /* U+524D "前" */
    0x0, 0x0, 0x40, 0xc1, 0x86, 0x3f, 0xff, 0x0,
    0x0, 0x0, 0x27, 0xec, 0x91, 0xb2, 0x7e, 0xc9,
    0x1b, 0x24, 0x6c, 0x9f, 0xb2, 0x46, 0x9, 0x18,
    0x24, 0xe3, 0x80,

    /* U+53C2 "参" */
    0x0, 0x0, 0x3b, 0x1, 0x86, 0xf, 0xfe, 0x6,
    0x18, 0x10, 0xf, 0xff, 0xc6, 0x18, 0x33, 0xb3,
    0xf8, 0x7c, 0x1c, 0xc7, 0xcc, 0x8, 0x60, 0x1f,
    0x3, 0xe0, 0x0,

    /* U+5411 "向" */
    0x2, 0x0, 0x30, 0x1, 0x81, 0xff, 0xfc, 0x0,
    0xe0, 0x7, 0x3f, 0x39, 0x9, 0xc8, 0x4e, 0x42,
    0x73, 0xf3, 0x90, 0x1c, 0x0, 0xe0, 0x1c,

    /* U+55B7 "喷" */
    0x0, 0xc3, 0xdf, 0xe9, 0xc, 0x24, 0x84, 0x9f,
    0xfe, 0x48, 0x49, 0x7f, 0xa5, 0x86, 0x96, 0x1b,
    0xdb, 0x68, 0x6d, 0x80, 0x28, 0x7, 0x1c, 0x30,
    0x10,

    /* U+56FE "图" */
    0xff, 0xfc, 0x0, 0x63, 0x3, 0x3f, 0xdb, 0x8c,
    0xd3, 0xc6, 0x3f, 0x3f, 0xd, 0x87, 0x8c, 0x80,
    0x63, 0xf3, 0x0, 0x9f, 0xff, 0xc0, 0x4,

    /* U+578B "型" */
    0x7f, 0x48, 0x91, 0x22, 0x44, 0x89, 0x12, 0xff,
    0x48, 0x90, 0x26, 0x40, 0xb1, 0xe, 0x7, 0x20,
    0xff, 0xc0, 0x30, 0x0, 0xc0, 0x3, 0x3, 0xff,
    0xf0,

    /* U+5904 "处" */
    0x10, 0x60, 0x60, 0xc0, 0xfd, 0x81, 0x13, 0x82,
    0x27, 0x8c, 0xcd, 0x9d, 0x9b, 0x2a, 0x32, 0x1c,
    0x60, 0x18, 0xc0, 0x71, 0x81, 0xb0, 0x7, 0x38,
    0x1c, 0xf, 0xc0,

    /* U+5B58 "存" */
    0x3, 0x0, 0x4, 0x1, 0xff, 0xf8, 0x20, 0x0,
    0xc0, 0x3, 0x3f, 0x86, 0x6, 0x18, 0x18, 0x70,
    0x20, 0xaf, 0xfc, 0x40, 0x80, 0x81, 0x1, 0x2,
    0x2, 0x3c, 0x0,

    /* U+5B9A "定" */
    0x3, 0x0, 0x6, 0x1, 0xff, 0xf2, 0x0, 0x64,
    0x0, 0xc3, 0xfc, 0x0, 0xc0, 0x9, 0x80, 0x33,
    0xf8, 0x66, 0x0, 0xcc, 0x1, 0x58, 0x4, 0xf0,
    0x18, 0x7f, 0x80,

    /* U+5EA6 "度" */
    0x1, 0x0, 0xc, 0x7, 0xff, 0xd0, 0x0, 0x44,
    0x21, 0xff, 0xf4, 0x42, 0x11, 0x8, 0x47, 0xe1,
    0x0, 0x7, 0xff, 0x13, 0xc, 0xc7, 0xe3, 0x1f,
    0x8b, 0xe7, 0xc0,

    /* U+5F0F "式" */
    0x0, 0x90, 0x2, 0x60, 0x8, 0xbf, 0xff, 0x0,
    0xc0, 0x3, 0x7, 0xec, 0x6, 0x30, 0x18, 0x40,
    0x61, 0x1, 0x86, 0x47, 0xd9, 0xfe, 0x37, 0x0,
    0x70,

    /* U+5F53 "当" */
    0x3, 0x3, 0x18, 0xc8, 0xcc, 0x66, 0x40, 0x30,
    0x3f, 0xfc, 0x0, 0x60, 0x3, 0x0, 0x1b, 0xff,
    0xc0, 0x6, 0x0, 0x3f, 0xff, 0x80, 0xc,

    /* U+5FD7 "志" */
    0x3, 0x0, 0xc, 0xf, 0xff, 0xc0, 0xc0, 0x3,
    0x0, 0xc, 0x7, 0xff, 0x80, 0x80, 0x3, 0x1,
    0x66, 0x45, 0x89, 0x96, 0xa, 0xd8, 0x2c, 0x3f,
    0x80,

    /* U+6001 "态" */
    0x3, 0x0, 0xc, 0xf, 0xff, 0xc1, 0xe0, 0x6,
    0xc0, 0x33, 0x1, 0xe7, 0x1c, 0xef, 0xc1, 0xd,
    0x6c, 0x47, 0x99, 0x96, 0x2a, 0xd8, 0x2f, 0x3f,
    0x80,

    /* U+610F "意" */
    0x3, 0x1, 0xff, 0xe1, 0x86, 0x3f, 0xff, 0x0,
    0x0, 0xff, 0xc2, 0x1, 0xf, 0xfc, 0x20, 0x10,
    0xff, 0xc0, 0x70, 0x1a, 0x66, 0xc8, 0x6e, 0x3f,
    0x0,

    /* U+62E9 "择" */
    0x27, 0xf8, 0x84, 0x62, 0x1b, 0x3e, 0x28, 0x20,
    0xe0, 0x9e, 0xf3, 0xe4, 0xde, 0x10, 0xe3, 0xf8,
    0x81, 0x2, 0x4, 0x9, 0xff, 0x20, 0x41, 0x81,
    0x0,

    /* U+64AD "播" */
    0x27, 0xf8, 0x46, 0xd8, 0x8d, 0xa7, 0xcb, 0x42,
    0x7f, 0xe4, 0x3e, 0x8, 0xdb, 0x3f, 0x33, 0xe3,
    0xfc, 0x44, 0xc8, 0x8f, 0xf1, 0x13, 0x22, 0x26,
    0x5c, 0x7f, 0x80,

    /* U+6570 "数" */
    0x5a, 0x60, 0xb4, 0xc1, 0x61, 0x7, 0xfb, 0xf3,
    0xcc, 0xcf, 0x59, 0x36, 0x7a, 0x8, 0xfc, 0xfe,
    0x38, 0x4c, 0x61, 0xd0, 0xc0, 0xe3, 0xc3, 0x6c,
    0xdc, 0x30, 0xc0,

    /* U+6587 "文" */
    0x2, 0x0, 0xc, 0x0, 0x10, 0x3f, 0xff, 0x10,
    0x20, 0x61, 0x80, 0x86, 0x3, 0x30, 0x7, 0x80,
    0x1e, 0x0, 0x78, 0x3, 0x30, 0x78, 0x7b, 0x80,
    0x70,

    /* U+65B9 "方" */
    0x0, 0x0, 0xc, 0x0, 0x10, 0x3f, 0xff, 0xc,
    0x0, 0x30, 0x0, 0xc0, 0x3, 0xfc, 0x8, 0x10,
    0x60, 0x41, 0x81, 0x4, 0xc, 0x30, 0x31, 0x80,
    0xcc, 0x1e, 0x0,

    /* U+65BD "施" */
    0x31, 0x80, 0x46, 0x2, 0x1f, 0xff, 0xc0, 0x62,
    0x21, 0x8c, 0xf7, 0xd7, 0xdb, 0x79, 0x6f, 0x25,
    0xa4, 0x94, 0x92, 0xd2, 0x48, 0xc9, 0x6, 0xe7,
    0xf0,

    /* U+65E5 "日" */
    0xff, 0xf8, 0xf, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xff, 0xfe, 0x3, 0xc0, 0x78, 0xf, 0x1, 0xe0,
    0x3f, 0xff, 0x80, 0xc0,

    /* U+663E "显" */
    0x3f, 0xf8, 0x60, 0x30, 0xff, 0xe1, 0xff, 0xc3,
    0x1, 0x87, 0xff, 0x0, 0x0, 0x2, 0x20, 0x24,
    0x4c, 0x68, 0xb0, 0x51, 0x40, 0x22, 0xf, 0xff,
    0xe0,

    /* U+6A21 "模" */
    0x21, 0x30, 0x9f, 0xf2, 0x13, 0x3f, 0xfe, 0x26,
    0x8, 0xdf, 0xe7, 0x60, 0x9d, 0xfe, 0x60, 0xc2,
    0x83, 0xa, 0xff, 0xc8, 0x68, 0x27, 0x38, 0xb8,
    0x30,

    /* U+72B6 "状" */
    0x10, 0x80, 0x42, 0xcd, 0x9, 0x9c, 0x20, 0x3f,
    0xf8, 0x42, 0x1, 0xc, 0xc, 0x70, 0x71, 0x43,
    0x45, 0x89, 0x32, 0x5, 0x8c, 0x1e, 0x18, 0x50,
    0x20,

    /* U+754C "界" */
    0x3f, 0xf8, 0x46, 0x30, 0x8c, 0x61, 0xff, 0xc2,
    0x31, 0x84, 0x63, 0xf, 0xfe, 0x6, 0x20, 0x38,
    0x71, 0xd0, 0xbc, 0x21, 0x0, 0xc2, 0x3, 0x84,
    0x6, 0x8, 0x0,

    /* U+76D2 "盒" */
    0x3, 0x0, 0x1e, 0x1, 0xce, 0x1f, 0xff, 0xc0,
    0xc, 0xff, 0xc3, 0x3, 0xf, 0xfc, 0x0, 0x1,
    0xff, 0xe6, 0x49, 0x99, 0x26, 0x64, 0x9b, 0xff,
    0xf0,

    /* U+793A "示" */
    0x7f, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff,
    0xfc, 0xc, 0x0, 0x30, 0xc, 0xcc, 0x23, 0x19,
    0x8c, 0x6c, 0x30, 0xe0, 0xc3, 0xe, 0x0,

    /* U+79CD "种" */
    0xc, 0x63, 0xe1, 0x81, 0x6, 0x4, 0xff, 0xfe,
    0x64, 0xc9, 0x93, 0xa6, 0x5f, 0x99, 0x57, 0xff,
    0x49, 0x99, 0x6, 0x4, 0x18, 0x10, 0x60, 0x41,
    0x80,

    /* U+7A0B "程" */
    0x3d, 0xfc, 0xe2, 0x8, 0x44, 0x10, 0x88, 0x27,
    0xdf, 0xc2, 0x0, 0xe, 0xff, 0x9e, 0x10, 0x74,
    0x20, 0xa3, 0xf9, 0x40, 0x80, 0x81, 0x1, 0x2,
    0x2, 0x7f, 0xc0,

    /* U+7C73 "米" */
    0x3, 0x1, 0x8c, 0x62, 0x31, 0x8c, 0xcc, 0x13,
    0x20, 0xc, 0xf, 0xff, 0xc1, 0xe0, 0xf, 0xc0,
    0x6d, 0x83, 0x33, 0x18, 0xc7, 0xc3, 0xc, 0xc,
    0x0,

    /* U+7C7B "类" */
    0x3, 0x10, 0x66, 0x60, 0x6d, 0x87, 0xff, 0xe0,
    0xfc, 0x3, 0x6e, 0x3c, 0xc7, 0x61, 0x80, 0x3,
    0x1, 0xff, 0xf8, 0x1e, 0x0, 0x66, 0xf, 0x87,
    0xdc, 0x3, 0x80,

    /* U+7CFB "系" */
    0x0, 0xf1, 0xff, 0x0, 0xc2, 0x6, 0x38, 0x7f,
    0x80, 0x1c, 0x81, 0xc3, 0xc, 0x6, 0x7f, 0xe8,
    0xc, 0x23, 0x37, 0x18, 0xc6, 0xc3, 0xc, 0x3c,
    0x0,

    /* U+7EAC "纬" */
    0x30, 0x60, 0x81, 0x86, 0x3f, 0xd2, 0x18, 0xd8,
    0x63, 0xcf, 0xe3, 0x6, 0x18, 0x18, 0xdf, 0xff,
    0xc1, 0x90, 0x6, 0x47, 0x19, 0xf8, 0x7e, 0x1,
    0x80,

    /* U+7ECF "经" */
    0x20, 0x0, 0xcf, 0xe2, 0x1, 0x9a, 0xc, 0x4c,
    0x63, 0xe3, 0xcf, 0x3b, 0x8d, 0xc3, 0x60, 0x3,
    0xef, 0xee, 0x4, 0x0, 0x10, 0x18, 0x43, 0xe1,
    0x8, 0x7f, 0xc0,

    /* U+7EDC "络" */
    0x0, 0x80, 0x31, 0x80, 0xc7, 0xf1, 0xc, 0x26,
    0xe8, 0x9f, 0x4f, 0x1e, 0x1c, 0x18, 0xee, 0x6f,
    0x7, 0xf3, 0xf8, 0x4, 0x10, 0x28, 0x23, 0xd0,
    0x5e, 0x3f, 0x80, 0x41, 0x0,

    /* U+7EDF "统" */
    0x18, 0x60, 0x60, 0x40, 0xcf, 0xfb, 0x66, 0x4,
    0x8c, 0x9f, 0x31, 0x8c, 0xff, 0x91, 0x83, 0x78,
    0x91, 0xe3, 0x20, 0x6, 0x40, 0xec, 0x9f, 0x31,
    0x20, 0xc3, 0xc0,

    /* U+7F51 "网" */
    0xff, 0xfc, 0x0, 0x61, 0x1b, 0x18, 0xda, 0xf4,
    0xdc, 0xe6, 0x63, 0x33, 0x99, 0x9c, 0xed, 0xbd,
    0x6c, 0x4b, 0xc6, 0x18, 0x0, 0xc0, 0x3c,

    /* U+7F6E "置" */
    0x7f, 0xf9, 0x32, 0x27, 0xff, 0x80, 0xc0, 0xff,
    0xfc, 0x8, 0x3, 0xff, 0x8, 0xc, 0x3f, 0xf0,
    0x80, 0xc3, 0xff, 0xf, 0xfc, 0x20, 0x33, 0xff,
    0xf0,

    /* U+80A5 "肥" */
    0x79, 0xfc, 0x92, 0x49, 0x24, 0x92, 0x49, 0x27,
    0x92, 0x49, 0x24, 0x92, 0x7f, 0x24, 0xfc, 0x79,
    0x0, 0x92, 0x1, 0x24, 0x12, 0x48, 0x3c, 0x90,
    0x57, 0x3f, 0x80,

    /* U+822A "航" */
    0x10, 0x40, 0x60, 0x81, 0xf1, 0x82, 0x3f, 0xf7,
    0x40, 0xa, 0x80, 0x15, 0x3c, 0x22, 0x78, 0xfc,
    0x90, 0x89, 0x21, 0x52, 0x42, 0xa4, 0x84, 0x59,
    0x28, 0xa2, 0x67, 0xc7, 0x80,

    /* U+836F "药" */
    0x18, 0x43, 0xff, 0xf1, 0x84, 0xc, 0x20, 0x21,
    0x81, 0xa7, 0xfc, 0xb0, 0xfc, 0x83, 0x30, 0x89,
    0xf3, 0x2f, 0x84, 0x80, 0x2, 0xfc, 0xb, 0x81,
    0xe0,

    /* U+8BBE "设" */
    0x61, 0xf0, 0xc4, 0x41, 0x11, 0x0, 0x44, 0x2,
    0x13, 0xb8, 0x32, 0x0, 0x9, 0xfe, 0x23, 0x18,
    0x8c, 0x42, 0x9b, 0xe, 0x38, 0x33, 0xf8, 0x9c,
    0x70,

    /* U+8DDD "距" */
    0x7e, 0xfe, 0x8d, 0x1, 0x1a, 0x2, 0x34, 0x7,
    0xef, 0xc2, 0x10, 0x94, 0x21, 0x2f, 0x42, 0x50,
    0xfc, 0xa1, 0x1, 0x5a, 0x3, 0xf4, 0xe, 0xf,
    0xe0,

    /* U+8F66 "车" */
    0x6, 0x0, 0x30, 0xf, 0xff, 0xc6, 0x0, 0x19,
    0x80, 0xc6, 0x3, 0x18, 0x1f, 0xfe, 0x1, 0x80,
    0x6, 0xf, 0xff, 0xc0, 0x60, 0x1, 0x80, 0x6,
    0x0,

    /* U+8F68 "轨" */
    0x10, 0x40, 0x60, 0x83, 0xf9, 0x1, 0x7, 0xc6,
    0x84, 0x89, 0x9, 0x3f, 0x92, 0x4, 0x24, 0x8,
    0x48, 0x3d, 0x13, 0xf2, 0x26, 0x4c, 0x50, 0x98,
    0xa1, 0x61, 0xc0,

    /* U+8FF9 "迹" */
    0x0, 0x81, 0x3, 0x3, 0xff, 0xc0, 0x48, 0x5,
    0x2b, 0x94, 0xa2, 0xd2, 0xca, 0x49, 0x2b, 0x24,
    0x88, 0x82, 0x62, 0xb, 0x38, 0x58, 0x6, 0x1f,
    0xf0,

    /* U+9009 "选" */
    0x0, 0xc3, 0x1b, 0x6, 0x7f, 0x8b, 0x30, 0x0,
    0xc0, 0x3f, 0xfe, 0xff, 0xc8, 0x48, 0x23, 0x20,
    0x98, 0x92, 0xc3, 0xdc, 0x0, 0x78, 0x3, 0x1f,
    0xf0,

    /* U+95F4 "间" */
    0x0, 0x1, 0xbf, 0xf3, 0x0, 0xc0, 0x3, 0xc0,
    0xf, 0x3f, 0x3c, 0x84, 0xf2, 0x13, 0xcf, 0xcf,
    0x21, 0x3c, 0x84, 0xf3, 0xf3, 0xc0, 0xf, 0x0,
    0x3c, 0x1, 0xc0,

    /* U+9762 "面" */
    0xff, 0xfc, 0xc, 0x0, 0x20, 0x0, 0x80, 0x7f,
    0xf9, 0x23, 0x24, 0x8c, 0x93, 0xf2, 0x48, 0xc9,
    0x3f, 0x24, 0x8c, 0x92, 0x32, 0x7f, 0xf9, 0x0,
    0x20,

    /* U+9AD8 "高" */
    0x0, 0x0, 0xc, 0xf, 0xff, 0xc0, 0x0, 0x3f,
    0xf0, 0xc0, 0xc3, 0xff, 0x0, 0x0, 0x7f, 0xfd,
    0x0, 0x34, 0xfc, 0xd2, 0x13, 0x48, 0x4d, 0x3f,
    0x34, 0x3, 0x80,

    /* U+FF1A "：" */
    0xfc, 0x0, 0x0, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 76, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 76, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 159, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 165, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 179, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 145, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 179, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 189, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 79, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 170, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 212, .box_w = 10, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 188, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 193, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 166, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 193, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 342, .adv_w = 168, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 156, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 156, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 188, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 152, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 229, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 153, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 142, .box_w = 10, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 241, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 535, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 562, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 589, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 618, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 645, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 670, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 697, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 724, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 747, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 772, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 795, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 820, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 847, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 874, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 901, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 928, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 953, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 976, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1001, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1026, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1051, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1076, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1103, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1130, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1155, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1182, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1207, .adv_w = 256, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1227, .adv_w = 256, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1252, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1277, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1302, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1329, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1354, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1377, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1402, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1429, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1454, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1481, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1506, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1531, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1558, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1587, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1614, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1637, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1662, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1689, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1718, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1743, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1768, .adv_w = 256, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1793, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1818, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1845, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1870, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1895, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1922, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1947, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1974, .adv_w = 256, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xe
};

static const uint16_t unicode_list_3[] = {
    0x0, 0x4dad, 0x4e89, 0x4ee0, 0x4ee6, 0x4eef, 0x4f70, 0x4fcf,
    0x51e0, 0x5355, 0x53a4, 0x554a, 0x5691, 0x571e, 0x5897, 0x5aeb,
    0x5b2d, 0x5e39, 0x5ea2, 0x5ee6, 0x5f6a, 0x5f94, 0x60a2, 0x627c,
    0x6440, 0x6503, 0x651a, 0x654c, 0x6550, 0x6578, 0x65d1, 0x69b4,
    0x7249, 0x74df, 0x7665, 0x78cd, 0x7960, 0x799e, 0x7c06, 0x7c0e,
    0x7c8e, 0x7e3f, 0x7e62, 0x7e6f, 0x7e72, 0x7ee4, 0x7f01, 0x8038,
    0x81bd, 0x8302, 0x8b51, 0x8d70, 0x8ef9, 0x8efb, 0x8f8c, 0x8f9c,
    0x9587, 0x96f5, 0x9a6b, 0xfead
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 15, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 3,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 26, .glyph_id_start = 14,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 109, .range_length = 65198, .glyph_id_start = 40,
        .unicode_list = unicode_list_3, .glyph_id_ofs_list = NULL, .list_length = 60, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 3, 4,
    5, 6, 0, 7, 8, 0, 0, 9,
    10, 11, 0, 0, 6, 12, 6, 13,
    14, 15, 16, 17, 18, 19, 20, 21,
    22, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 3, 0,
    4, 0, 0, 0, 4, 0, 0, 5,
    0, 0, 0, 0, 4, 0, 4, 0,
    6, 7, 8, 9, 10, 11, 12, 13,
    14, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, -28, -6,
    -20, -10, 0, -28, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 0, 0, -2, -3,
    0, 0, -17, -4, -4, 0, 0, -4,
    -2, 0, 0, 0, 0, 0, -5, -4,
    -7, 0, -2, -2, -2, -4, -2, 0,
    0, 0, 0, -9, -3, -7, -5, -4,
    -2, -2, -2, -3, -3, 0, 0, 0,
    -3, 0, -13, 0, -7, 0, -3, -2,
    -6, -6, -6, 0, -23, 0, -11, -3,
    -39, -6, 0, 0, 0, 0, -7, -1,
    -9, -6, 0, 0, -2, 0, 0, 0,
    -6, 0, -4, -2, 0, 0, 0, 0,
    -7, 0, 0, 0, -12, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -6, 0, -4, -6, -4, -4, -3,
    0, -6, 0, 0, 0, 0, 0, -8,
    0, -7, -35, -9, -22, -16, 0, -23,
    0, 0, -34, 0, -14, 0, -42, -3,
    -6, 0, 0, 0, -7, -3, -20, 0,
    0, 0, -2, 0, -5, -4, -4, 0,
    0, 2, -2, -2, -3, 0, 0, 0,
    0, 0, -4, -4, -6, 0, 0, 0,
    0, -4, 0, 0, -31, -6, -12, -7,
    -36, -10, 0, 0, 0, 0, -6, -4,
    -15, -13, -6, 0, -4, 0, -14, -3,
    0, 0, -2, 0, -3, -4, 0, 0,
    -20, 0, -4, -3, -20, -3, 0, -3,
    3, 0, 0, 0, -5, -6, -10, 0,
    0, -2, -17, -2, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, -6,
    -2, -4, -6, -3, 0, 0, 0, 0,
    0, 0, -28, -8, -4, -4, -29, -5,
    -4, -3, 0, 0, 0, 0, -7, -12,
    0, 0, -2, -6, -9, -9, 0, -3,
    -2, -2, 0, -4, -4, 0, 0, 0,
    0, 0, 0, 0, -7, 0, -3, 0,
    0, -6, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 22,
    .right_class_cnt     = 14,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 4,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

extern const lv_font_t lv_font_siyuan_micro;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_font_siyuan_micro = {
#else
lv_font_t lv_font_siyuan_micro = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_siyuan_micro,
#endif
    .user_data = NULL,
};



#endif /*#if LV_FONT_SIYUAN_MICRO*/

