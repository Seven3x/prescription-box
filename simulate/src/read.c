#include "read.h"
#include "proc.h"
#include "stdio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
long long read_latlon(char * msg_str);

int read_msg(char * msg_str, GPS_msgTypeDef* GPS_msgStructure) {
    char c[] = ",";
    char msgcopy[200] = "";
    char * token = NULL;
    char * ptr;
    // uint8_t counter = 0, i = 0;
    GPS_msgTypeDef result_msgStructure = {0,0,0,0,0,0};

    strcpy(msgcopy, msg_str);
    
    token = strtok(msgcopy, c);  // 返回指令
    if (strcmp(token, "$GNGGA") != 0) return -1;

    token = strtok(NULL, c);  // 时间
    token = strtok(NULL, c);  // 纬度
    if (*token > '9' || *token < '0') return -1;
    // printf("lat:%s\n", token);
    GPS_msgStructure->lat = latdms2dd(read_latlon(token));
    // GPS_msgStructure->lat = (read_latlon(token));
    // GPS_msgStructure->latd = strtold(token, &ptr);
    GPS_msgStructure->latd = (GPS_msgStructure->lat) / 1E8;
    token = strtok(NULL, c);  // 纬度方向
    // printf("latd:%s\n", token);
    GPS_msgStructure->lat_dir = *token;
    token = strtok(NULL, c);  // 经度
    // printf("lon:%s\n", token);
    GPS_msgStructure->lon = londms2dd(read_latlon(token));
    // GPS_msgStructure->lon = (read_latlon(token));
    // GPS_msgStructure->lond = strtold(token, &ptr);
    GPS_msgStructure->lond =  (GPS_msgStructure->lon) / 1E8;
    token = strtok(NULL, c);  // 经度方向
    // printf("lond:%s\n", token);
    GPS_msgStructure->lon_dir = *token;
    // token = strtok(NULL, c);  // 定位状态

    return 0;
}

long long read_latlon(char * msg_str) {
    char* p = msg_str;
    long long value = 0;
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
    printf("lat:%lld ", msg.lat);
    printf("lat_dir:%c ", msg.lat_dir);
    printf("latd:%.9lf ", msg.latd);
    printf("lon:%lld ", msg.lon);
    printf("lon_dir:%c ", msg.lon_dir);
    printf("lon:%.9lf \r\n", msg.lond);
}

int read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    GPS_msgTypeDef GPS_msgStructure = {0,0,0,0,0,0};
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return -1;
    }
    
    // 读取文件内容
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        // printf("%s", line);
        // 处理每一行数据
        if (read_msg(line, &GPS_msgStructure) == 0) {
            // puts(line);
            printmsg(GPS_msgStructure);
        }
        // ...
    }
}