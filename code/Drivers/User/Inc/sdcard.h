#ifndef __SDCARD_H
#define __SDCARD_H

#include "sdmmc_sd.h"
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include "stdio.h"


void FatFs_Check(void);				// 判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
void FatFs_GetVolume(void);		// 计算设备容量
uint8_t  FatFs_FileTest(void);	// 文件创建和写入测试
void SystemClock_Config(void);	// 系统时钟配置

#endif // !__SDCARD_H

