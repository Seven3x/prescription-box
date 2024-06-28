#include "imu.h"
#include "stdio.h"


void print_imu_data(GEOData_Packet_t* data){
    // print the data
    printf("lat: %lf, lon: %lf\r\n", data->altitude, data->latitude);
     
}

float DATA_Trans(uint8_t Data_1, uint8_t Data_2, uint8_t Data_3, uint8_t Data_4)
{
	long long transition_32;
	float tmp = 0;
	int sign = 0;
	int exponent = 0;
	float mantissa = 0;
	transition_32 = 0;
	transition_32 |= Data_4 << 24;
	transition_32 |= Data_3 << 16;
	transition_32 |= Data_2 << 8;
	transition_32 |= Data_1;
	sign = (transition_32 & 0x80000000) ? -1 : 1; // ����λ
	// �����Ʋ������ٰ�λ����㣬���������30��23λ��Ӧ��e
	exponent = ((transition_32 >> 23) & 0xff) - 127;
	// ��22~0ת��Ϊ10���ƣ��õ���Ӧ��xϵ��
	mantissa = 1 + ((float)(transition_32 & 0x7fffff) / 0x7fffff);
	tmp = sign * mantissa * pow(2, exponent);
	return tmp;
}


uint8_t TTL_Hex2Dec(void)
{
	uint8_t i;

    static GEOData_Packet_t GEOData_Packet;

	if (rs_ahrstype == 1)
	{
		if (Fd_rsahrs[1] == TYPE_AHRS && Fd_rsahrs[2] == AHRS_LEN)
		{
			AHRSData_Packet.RollSpeed = DATA_Trans(Fd_rsahrs[7], Fd_rsahrs[8], Fd_rsahrs[9], Fd_rsahrs[10]);	   // ������ٶ�
			AHRSData_Packet.PitchSpeed = DATA_Trans(Fd_rsahrs[11], Fd_rsahrs[12], Fd_rsahrs[13], Fd_rsahrs[14]);   // �������ٶ�
			AHRSData_Packet.HeadingSpeed = DATA_Trans(Fd_rsahrs[15], Fd_rsahrs[16], Fd_rsahrs[17], Fd_rsahrs[18]); // ƫ�����ٶ�

			AHRSData_Packet.Roll = DATA_Trans(Fd_rsahrs[19], Fd_rsahrs[20], Fd_rsahrs[21], Fd_rsahrs[22]);	  // �����
			AHRSData_Packet.Pitch = DATA_Trans(Fd_rsahrs[23], Fd_rsahrs[24], Fd_rsahrs[25], Fd_rsahrs[26]);	  // ������
			AHRSData_Packet.Heading = DATA_Trans(Fd_rsahrs[27], Fd_rsahrs[28], Fd_rsahrs[29], Fd_rsahrs[30]); // ƫ����

			AHRSData_Packet.Qw = DATA_Trans(Fd_rsahrs[31], Fd_rsahrs[32], Fd_rsahrs[33], Fd_rsahrs[34]); // ��Ԫ��
			AHRSData_Packet.Qx = DATA_Trans(Fd_rsahrs[35], Fd_rsahrs[36], Fd_rsahrs[37], Fd_rsahrs[38]);
			AHRSData_Packet.Qy = DATA_Trans(Fd_rsahrs[39], Fd_rsahrs[40], Fd_rsahrs[41], Fd_rsahrs[42]);
			AHRSData_Packet.Qz = DATA_Trans(Fd_rsahrs[43], Fd_rsahrs[44], Fd_rsahrs[45], Fd_rsahrs[46]);
			AHRSData_Packet.Timestamp = timestamp(Fd_rsahrs[47], Fd_rsahrs[48], Fd_rsahrs[49], Fd_rsahrs[50]); // ʱ���
			// AHRSData2PC();
		}
		rs_ahrstype = 0;
	}
	if (rs_imutype == 1)
	{
		if (Fd_rsimu[1] == TYPE_IMU && Fd_rsimu[2] == IMU_LEN)
		{
			IMUData_Packet.gyroscope_x = DATA_Trans(Fd_rsimu[7], Fd_rsimu[8], Fd_rsimu[9], Fd_rsimu[10]); // ���ٶ�
			IMUData_Packet.gyroscope_y = DATA_Trans(Fd_rsimu[11], Fd_rsimu[12], Fd_rsimu[13], Fd_rsimu[14]);
			IMUData_Packet.gyroscope_z = DATA_Trans(Fd_rsimu[15], Fd_rsimu[16], Fd_rsimu[17], Fd_rsimu[18]);

			IMUData_Packet.accelerometer_x = DATA_Trans(Fd_rsimu[19], Fd_rsimu[20], Fd_rsimu[21], Fd_rsimu[22]); // �߼��ٶ�
			IMUData_Packet.accelerometer_y = DATA_Trans(Fd_rsimu[23], Fd_rsimu[24], Fd_rsimu[25], Fd_rsimu[26]);
			IMUData_Packet.accelerometer_z = DATA_Trans(Fd_rsimu[27], Fd_rsimu[28], Fd_rsimu[29], Fd_rsimu[30]);

			IMUData_Packet.magnetometer_x = DATA_Trans(Fd_rsimu[31], Fd_rsimu[32], Fd_rsimu[33], Fd_rsimu[34]); // ����������
			IMUData_Packet.magnetometer_y = DATA_Trans(Fd_rsimu[35], Fd_rsimu[36], Fd_rsimu[37], Fd_rsimu[38]);
			IMUData_Packet.magnetometer_z = DATA_Trans(Fd_rsimu[39], Fd_rsimu[40], Fd_rsimu[41], Fd_rsimu[42]);

			IMUData_Packet.Timestamp = timestamp(Fd_rsimu[55], Fd_rsimu[56], Fd_rsimu[57], Fd_rsimu[58]); // ʱ���
			// IMUData2PC();
		}
		rs_imutype = 0;
	}
    if (rs_geotype == 1){
        if(Fd_rsgeo[1] == TYPE_GEODETIC_POS && Fd_rsgeo[2] == GEODETIC_POS_LEN){
                
            GEOData_Packet.latitude = DATA_Trans(Fd_rsgeo[7], Fd_rsgeo[8], Fd_rsgeo[9], Fd_rsgeo[10]); // γ��
            GEOData_Packet.longitude = DATA_Trans(Fd_rsgeo[11], Fd_rsgeo[12], Fd_rsgeo[13], Fd_rsgeo[14]); // ����
            
        }
    }
	return 0;
}

long long timestamp(uint8_t Data_1, uint8_t Data_2, uint8_t Data_3, uint8_t Data_4)
{
	uint32_t transition_32;
	transition_32 = 0;
	transition_32 |= Data_4 << 24;
	transition_32 |= Data_3 << 16;
	transition_32 |= Data_2 << 8;
	transition_32 |= Data_1;
	return transition_32;
}
