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
    
    token = strtok(msgcopy, c);  // ����ָ��
    if (strcmp(token, "$GNGGA") != 0) return -1;

    token = strtok(NULL, c);  // ʱ��
    token = strtok(NULL, c);  // γ��
    if (*token > '9' || *token < '0') return -1;
    // printf("lat:%s\n", token);
    GPS_msgStructure->lat = latdms2dd(read_latlon(token));
    // GPS_msgStructure->lat = (read_latlon(token));
    // GPS_msgStructure->latd = strtold(token, &ptr);
    GPS_msgStructure->latd = (GPS_msgStructure->lat) / 1E8;
    token = strtok(NULL, c);  // γ�ȷ���
    // printf("latd:%s\n", token);
    GPS_msgStructure->lat_dir = *token;
    token = strtok(NULL, c);  // ����
    // printf("lon:%s\n", token);
    GPS_msgStructure->lon = londms2dd(read_latlon(token));
    // GPS_msgStructure->lon = (read_latlon(token));
    // GPS_msgStructure->lond = strtold(token, &ptr);
    GPS_msgStructure->lond =  (GPS_msgStructure->lon) / 1E8;
    token = strtok(NULL, c);  // ���ȷ���
    // printf("lond:%s\n", token);
    GPS_msgStructure->lon_dir = *token;
    // token = strtok(NULL, c);  // ��λ״̬

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
    
    // ��ȡ�ļ�����
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        // printf("%s", line);
        // ����ÿһ������
        if (read_msg(line, &GPS_msgStructure) == 0) {
            // puts(line);
            printmsg(GPS_msgStructure);
        }
        // ...
    }
}