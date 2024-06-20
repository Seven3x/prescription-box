#ifndef __READ_H
#define __READ_H
typedef struct {
    long long lat;
    double latd;
    char lat_dir;
    long long lon;
    double lond;
    char lon_dir;
}  GPS_msgTypeDef;

int read_msg(char * msg_str, GPS_msgTypeDef *msg);
void printmsg(GPS_msgTypeDef msg);

int read_file(const char *path);
#endif // !__READ_H