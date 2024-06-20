#include "gps.h"
#include "string.h"
#include "stdlib.h"
// static char *_strtok = NULL;

uint64_t read_latlon(char * msg_str);
// uint8_t * strcopy(char * dest, char * src);

GPS_msgTypeDef read_msg(char * msg_str) {
    char c[] = ",";
    char msgcopy[200] = "";
    char * token = NULL;
    // uint8_t counter = 0, i = 0;
    GPS_msgTypeDef result_msgStructure = {0,0,0,0,0,0};

    strcpy(msgcopy, msg_str);
    
    token = strtok(msgcopy, c);  // 返回指令
    if (strcmp(token, "$command") == 0) return result_msgStructure;

    token = strtok(NULL, c);  // 时间
    token = strtok(NULL, c);  // 纬度
    if (*token > '9' || *token < '0') return result_msgStructure;
    // printf("lat:%s\n", token);
    // result_msgStructure.lat = read_latlon(token);
    result_msgStructure.latd = strtod(read_latlon(token));
    token = strtok(NULL, c);  // 纬度方向
    // printf("latd:%s\n", token);
    result_msgStructure.lat_dir = *token;
    token = strtok(NULL, c);  // 经度
    // printf("lon:%s\n", token);
    // result_msgStructure.lon = read_latlon(token);
    // result_msgStructure.lond = (long double)result_msgStructure.lon / 10000000;
    result_msgStructure.lond = strtod(read_latlon(token));
    
    token = strtok(NULL, c);  // 经度方向
    // printf("lond:%s\n", token);
    result_msgStructure.lon_dir = *token;
    // token = strtok(NULL, c);  // 定位状态

    return result_msgStructure;
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
    printf("lat:%llf\r\n", msg.latd);
    printf("lat_dir:%c\r\n", msg.lat_dir);
    printf("lon:%llf\r\n", msg.lond);
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

