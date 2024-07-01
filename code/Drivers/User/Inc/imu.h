#ifndef __IMU_H
#define __IMU_H

// #include 

#include "stm32h7xx_hal.h"

//FDlink candata
#define FRAME_HEAD 0xfc
#define FRAME_END 0xfd
#define TYPE_IMU 0x40
#define TYPE_AHRS 0x41
#define TYPE_INSGPS 0x42
#define TYPE_GROUND 0xf0
#define TYPE_GEODETIC_POS 0x5c
#define IMU_LEN  0x38   //56+8  8组数据
#define AHRS_LEN 0x30   //48+8  7组数据
#define INSGPS_LEN 0x42 //72+8  10组数据
#define GEODETIC_POS_LEN 32
#define IMU_CAN 9
#define AHRS_CAN 8
#define INSGPS_CAN 11



#define FRAME_HEADER      0X7B //Frame_header //??
#define FRAME_TAIL        0X7D //Frame_tail   //?β
#define SEND_DATA_SIZE    24
#define RECEIVE_DATA_SIZE 11
#define IMU_RS 64
#define AHRS_RS 56
#define INSGPS_RS 80
#define GEODETIC_POS_RS 40
#define RS485_RX_DE		rsgeo_flagPAout(11)	//485模式控制.0,接收;1,发送.
#define RS485_RX_RE		PAout(12)	//485模式控制.0,接收;1,发送.

typedef struct IMU_GEO_Packet_t{
    double   latitude;         //纬度
    double   longitude;        //经度
    double   altitude;         //高度
    float   hAcc;           //水平精度
    float   vAcc;          //垂直精度
}GEOData_Packet_t;

typedef struct IMUData_Packet_t{
		float gyroscope_x;          //unit: rad/s
		float gyroscope_y;          //unit: rad/s
		float gyroscope_z;          //unit: rad/s
		float accelerometer_x;      //m/s^2
		float accelerometer_y;      //m/s^2
		float accelerometer_z;      //m/s^2
		float magnetometer_x;       //mG
		float magnetometer_y;       //mG
		float magnetometer_z;       //mG
		float imu_temperature;      //C
		float Pressure;             //Pa
		float pressure_temperature; //C
		uint32_t Timestamp;          //us
} IMUData_Packet_t;

typedef struct AHRSData_Packet_t
{
	float RollSpeed;   //unit: rad/s
	float PitchSpeed;  //unit: rad/s
	float HeadingSpeed;//unit: rad/s
	float Roll;        //unit: rad
	float Pitch;       //unit: rad
	float Heading;     //unit: rad
	float Qw;//w          //Quaternion
	float Qx;//x
	float Qy;//y
	float Qz;//z
	uint32_t Timestamp; //unit: us
}AHRSData_Packet_t;


extern IMUData_Packet_t IMUData_Packet;
extern AHRSData_Packet_t AHRSData_Packet;
extern uint8_t ttl_receive;
extern uint8_t Fd_data[64];
extern uint8_t Fd_rsimu[64];
extern uint8_t Fd_rsahrs[56];
extern uint8_t Fd_rsgeo[48];
extern int rs_imutype;
extern int rs_ahrstype;
extern int rsgeo_flag;
extern int Time_count;
extern int rs_geotype;
extern uint8_t imu_save_flag;

uint8_t TTL_Hex2Dec(void);
void print_imu_data(GEOData_Packet_t* data);
long long timestamp(uint8_t Data_1, uint8_t Data_2, uint8_t Data_3, uint8_t Data_4);
#endif // !__IMU_H