#include "gps.h"
#include "string.h"
#include "stdlib.h"
#include "proc.h"
// static char *_strtok = NULL;
double dir = 0;
uint64_t read_latlon(char * msg_str);
uint8_t gps_receive = '0';
// uint8_t * strcopy(char * dest, char * src);

int read_msg(char * msg_str, GPS_msgTypeDef* GPS_msgStructure) {
    char c[] = ",";
    char msgcopy[200] = "";
    char * token = NULL;
    // uint8_t counter = 0, i = 0;
    GPS_msgTypeDef result_msgStructure = {0,0,0,0};

    strcpy(msgcopy, msg_str);
    // printf("msg: %s\r\n", msgcopy);
    token = strtok(msgcopy, c);  // 返回指令
    // printf("token: %s\r\n", token);
    
    if (strcmp(token, "$GNGGA") == 0) {
        token = strtok(NULL, c);  // 时间
        token = strtok(NULL, c);  // 纬度
        if (*token > '9' || *token < '0') return -1;
        // printf("lat:%s\n", token);
        // GPS_msgStructure->lat = latdms2dd(read_latlon(token));
        // GPS_msgStructure->lat = (read_latlon(token));
        GPS_msgStructure->latd = dms2dd(strtod(token, NULL));
        // GPS_msgStructure->latd = (GPS_msgStructure->lat) / 1E8;
        token = strtok(NULL, c);  // 纬度方向
        // printf("latd:%s\n", token);
        GPS_msgStructure->lat_dir = *token;
        token = strtok(NULL, c);  // 经度
        // printf("lon:%s\n", token);
        // GPS_msgStructure->lon = londms2dd(read_latlon(token));
        // GPS_msgStructure->lon = (read_latlon(token));
        GPS_msgStructure->lond = dms2dd(strtod(token, NULL));
        // GPS_msgStructure->lond =  (GPS_msgStructure->lon) / 1E8;
        token = strtok(NULL, c);  // 经度方向
        // printf("lond:%s\n", token);
        GPS_msgStructure->lon_dir = *token;
        // token = strtok(NULL, c);  // 定位状态

        return 0;

    } else if (strcmp(token, "#HEADINGA") == 0) {
        // printf("enter headinga \r\n");
        token = strtok(NULL, c); //解状态
        token = strtok(NULL, c); //未知类型
        token = strtok(NULL, c); //基线长
        // token = strtok(NULL, c); //航向

        dir = strtod(token, NULL);
        // printf("dir:%lf\n", dir);`	
        return 1;
        // printf("dir:%c\n", dir)
        
    } else if (strcmp(token, "$GNRMC") == 0) {
        token = strtok(NULL, c);    //时间
        token = strtok(NULL, c);    //状态
        token = strtok(NULL, c);    //纬度
        if (*token > '9' || *token < '0') return -1;
        token = strtok(NULL, c);    //纬度方向
        token = strtok(NULL, c);    //经度
        if (*token > '9' || *token < '0') return -1;
        token = strtok(NULL, c);    //经度方向
        token = strtok(NULL, c);    //速度
        GPS_msgStructure->speed = strtod(token, NULL) * 0.5144;
        return 2;
    }   

    return -1;
}

uint64_t read_latlon(char * msg_str) {
    char* p = msg_str;
    uint64_t value = 0;
    while(*p) {
        // printf("%c",*p);
        if (*p == '.') {
            p++;
            continue;
        }
        value = value * 10 + (*p - '0');
        p++;
    }

    return value;
}


void printmsg(GPS_msgTypeDef msg) {
    printf("lat:%lf\r\n", msg.latd);
    printf("lat_dir:%c\r\n", msg.lat_dir);
    printf("lon:%lf\r\n", msg.lond);
    printf("lon_dir:%c\r\n", msg.lon_dir);
}

// uint8_t * strcopy(uint8_t * dest, uint8_t * src) {
//     uint8_t * p = dest;
//     while(*src) {
//         *p = *src;
//         p++;
//         src++;
//     }
//     *p = '\0';
//     return dest;
// }



// uint8_t* strtok(uint8_t* str, uint8_t const *ct) {
//     uint8_t *sbegin, *send;
//     sbegin = str;

//     while (*sbegin) {
//         if (*sbegin == *ct) {

//         }
//         sbegin ++;
//     }
// }

