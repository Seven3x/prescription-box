#ifndef __GPS_H
#define __GPS_H


#include "sdmmc_sd.h"
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include "stdio.h"

typedef struct {
    // uint64_t lat;
    double latd;
    char lat_dir;
    // uint64_t lon;
    double lond;
    char lon_dir;
}  GPS_msgTypeDef;

extern double dir;

int read_msg(char * msg_str, GPS_msgTypeDef* GPS_msgStructure);
// GPS_msgTypeDef read_msg(char * msg_str);
void printmsg(GPS_msgTypeDef msg);

#endif // !__SDCARD_H
