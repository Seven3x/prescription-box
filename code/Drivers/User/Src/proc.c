#include "proc.h"
#include "gps.h"
// #include "read.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RADIUS_OF_EARTH 6371000.0

// ���Ƕ�ת��Ϊ����
double deg2rad(double degrees) {
    return degrees * M_PI / 180.0;
}
// ������ת��Ϊ�Ƕ�
double rad2deg(double radians) {
    return radians * 180.0 / M_PI;
}



long long latdms2dd(long long dms) {
    // Convert DMS to DD 3207.95429933
    long degrees = dms / 10000000000;
    long long minutes = (dms % 10000000000) ;

    return degrees * 100000000LL  + (minutes / 60);
}
long long londms2dd(long long dms) {
    // Convert DMS to DD 11841.73948308
    long degrees = dms / 10000000000;
    long long minutes = (dms % 10000000000) ;

    return degrees * 100000000LL  + (minutes / 60);
}

double dms2dd(double dms) {
    // Convert DMS to DD 3207.95429933
    int degrees = (int)(dms / 100);
    double minutes = dms - (degrees * 100);

    return degrees + minutes / 60; 


}

/**
 * @brief ����㵽ֱ�ߵľ���
 * 
 * @param point1 ��ȷ�����꣬Ҳ���ο��ߵĵ�����
 * @param angle �ο��ߵĽǶ�
 * @param GPS_msgStructure ������GPSMSG
 */
double to_distance_angle_structure(GPS_msgTypeDef point1, double angle, GPS_msgTypeDef point2) {
    double pointa[2] = {point1.latd, point1.lond};
    double pointb[2] = {point2.latd, point2.lond};
    // printf("tdas: %.5lf, %.5lf, %.5lf, %.5lf\n", pointa[0], pointa[1], pointb[0], pointb[1]);
    
    
    return to_distance_angle(pointa, angle, pointb);
}


/**
 * @brief ����㵽ֱ�ߵľ���
 * 
 * @param point1 ��ȷ�����꣬Ҳ���ο��ߵĵ�����
 * @param angle �ο��ߵĽǶ�
 * @param points2 ����������
 */
double to_distance_angle(double points1[2], double angle, double points2[2]) {
    double m = 0;// б��
    double b = 0; // �ؾ�

    double x1, y1;
    double distances[2] = {0};
    //����Ƕ�Ϊ90 270 -90 450 ���ֶ�����һ���ܴ��б��ֵ
    if (angle >= 89.5 && angle <= 90.5 ||
        angle >= 269.5 && angle <= 270.5 ||
        angle >= -89.5 && angle <= -90.5 ||
        angle >= 449.5 && angle <= 450.5) {
            m = 100000000;
    } else {
        m = tan(deg2rad(angle));
    }
    b = points1[1] - m * points1[0];
    // printf("m is %f\n", m);
    // printf("b is %f\n", b);
    
    x1 = (m * points2[1] + points2[0] - m * b) / (m * m + 1);
    y1 = m * x1 + b;
    // printf("x1 is %f\n", x1);
    // printf("y1 is %f\n", y1);

    // printf("points2 is %f, %f\n", points2[0], points2[1]);
    distances[0] = fabs(points2[0] - x1);
    distances[1] = fabs(points2[1] - y1);
    // printf("distances is %0.9f, %0.9f\n", distances[0], distances[1]);

    return latlon_to_distance(distances, points2);

}


// ���ڽṹ���latlon_to_distance
double structure_ll2dis(GPS_msgTypeDef GPS_msgStructure, double diff[2]) {
    double points[2]= {GPS_msgStructure.latd, GPS_msgStructure.lond};

    latlon_to_distance(diff, points);
}

// ����㵽�ߵľ���
double latlon_to_distance(double distances[2], double point[2]) {
    // double R = 6371000;
    // double latDiff = 0;
    double cR;
    // ��γ�Ȳ� ת������
    // printf("distances is %0.9f, %0.9f\n", distances[0], distances[1]);
    double latDiff = deg2rad(distances[0]);
    double lonDiff = deg2rad(distances[1]);

    // ��ȡ���γ�ȣ������Ǵ�djd����ĵ�һ�л�ȡ
    double lat1 = deg2rad(point[0]);
    //�����յ�γ�ȣ�����ÿ�����γ�ȶ�Ӧһ���յ�γ��
    double lat2 = latDiff + lat1;

    // printf("lat1 is %f\n", lat1);
    // printf("lat2 is %f\n", lat2);
    // printf("latDiff is %0.9f\n", latDiff);
    // printf("lonDiff is %0.9f\n", lonDiff);

    // H��ʽ
    double a = pow(sin(latDiff / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    // printf("a is %0.20f\n", a);
    // printf("sqrta is %0.20f\n", sqrt(a));
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    // printf("c is %0.11f\n", c);
    cR = c* RADIUS_OF_EARTH;
    // printf("cR is %0.11f\n", cR);
    return cR;

}

/**
 * @brief ����
 * 
 * @param point ��⵽�ĵ�
 * @param angle �Ƕ� gamma
 */
GPS_msgTypeDef structure_nlonlat(GPS_msgTypeDef point, double* average, double angle) {
    int iangle[2] = {(int)angle + 0.5, (int)angle - 0.5};
    double pointa[2], pointb[2];
    double dl = 0, dd = 0;
    double h = 0;
    double gamma = 0;
    GPS_msgTypeDef val;

    pointa[0] = point.latd;
    pointa[1] = point.lond;
    for(int i = 0; i < 2; i++) {
        dl = average[iangle[i]];
        dd = average[(iangle[i] + 90) % 360];
        printf("dl is %0.9f\n", dl);
        printf("dd is %0.9f\n", dd);
        h = calcu_h(dl, dd);
        printf("h is %0.9f\n", h);
        gamma = calcu_gamma(dl, dd, angle);
        printf("gamma is %0.9f\n", gamma);
        nlonlat(pointa, h, gamma, pointb);
    }
    
    val.latd = pointb[0];
    val.lond = pointb[1];
    
    return val;
    
}


double calcu_gamma(double dl, double dd, double angle) {
    return 270. - atan2(dl, dd) + angle;
}

double calcu_h(double dl, double dd) {
    return sqrt(dl*dl + dd*dd);
}


/**
 * @brief ����
 * 
 * @param point ��⵽�ĵ�
 * @param distance �����ľ��� h
 * @param angle �Ƕ� gamma
 * @param target_point ����ֵ��Ϊ��������
 */
void nlonlat(double point[2], double distance, double angle, double target_point[2]) {
    double lat1 = deg2rad(point[0]);
    double lon1 = deg2rad(point[1]);
    double dangle = deg2rad(angle);
    

    // double R = 6371000;

    // �����µ�ά��
    double lat2 = asin(sin(lat1) * cos(distance / RADIUS_OF_EARTH) + cos(lat1) * sin(distance / RADIUS_OF_EARTH) * cos(angle));

    // �����µľ���
    double lon2 = lon1 
    + atan2(sin(angle) * sin(distance / RADIUS_OF_EARTH) * cos(lat1), cos(distance / RADIUS_OF_EARTH) - sin(lat1) * sin(lat2));

    lat2 = rad2deg(lat2);
    lon2 = rad2deg(lon2);

    lon2 = fmod(lon2 + 540, 360.) - 180.;
    
    target_point[0] = (lat2);
    target_point[1] = (lon2);

}
