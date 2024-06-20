#include "proc.h"
#include "read.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 将角度转换为弧度
double deg2rad(double degrees) {
    return degrees * M_PI / 180.0;
}

// 计算两个点之间的距离
double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371000; // 地球半径（以米为单位）

    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

// 判断点是否包含 NaN
bool is_not_nan(double x) {
    return !isnan(x);
}

// 主函数
void todistances_angle(double point1[2], double angle, double points[][2], int points_size, double distances[]) {
    // 过滤掉包含 NaN 的行
    int valid_points_size = 0;
    double valid_points[points_size][2];
    for (int i = 0; i < points_size; i++) {
        if (is_not_nan(points[i][0]) && is_not_nan(points[i][1])) {
            valid_points[valid_points_size][0] = points[i][0];
            valid_points[valid_points_size][1] = points[i][1];
            valid_points_size++;
        }
    }

    double m;
    if (angle == 90 || angle == 270 || angle == -90 || angle == 450) {
        m = 100000000;  // 对于垂直线，手动设置一个很大的斜率值
    } else {
        double angle_rad = deg2rad(angle);
        m = tan(angle_rad);  // 对于其他角度，计算其正切值作为斜率
    }
    double b = point1[1] - m * point1[0];

    double x1s1[valid_points_size];
    double y1s1[valid_points_size];

    double horizontal_distances[valid_points_size];
    double vertical_distances[valid_points_size];

    for (int i = 0; i < valid_points_size; i++) {
        double x0 = valid_points[i][0];
        double y0 = valid_points[i][1];

        // 计算点到直线的垂线交点
        double x1 = (m * y0 + x0 - m * b) / (m * m + 1);
        double y1 = m * x1 + b;

        x1s1[i] = x1;
        y1s1[i] = y1;

        // 计算点到直线最短距离的投影分解为水平和垂直距离
        horizontal_distances[i] = fabs(x0 - x1);  // 水平距离
        vertical_distances[i] = fabs(y0 - y1);    // 垂直距离
    }

    // 计算经纬度差值
    double latlon_distance[valid_points_size][2];
    for (int i = 0; i < valid_points_size; i++) {
        latlon_distance[i][0] = horizontal_distances[i];
        latlon_distance[i][1] = vertical_distances[i];
    }

    // 计算实际距离
    for (int i = 0; i < valid_points_size; i++) {
        double lat1 = points[i][0];
        distances[i] = haversine(lat1, 0, latlon_distance[i][0] + lat1, latlon_distance[i][1]);
    }
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
 * @brief 计算点到直线的距离
 * 
 * @param point1 精确点坐标，也即参考线的点坐标
 * @param angle 参考线的角度
 * @param GPS_msgStructure 线外点的GPSMSG
 */
double to_distance_angle_structure(GPS_msgTypeDef point1, double angle, GPS_msgTypeDef point2) {
    double pointa[2] = {point1.latd, point1.lond};
    double pointb[2] = {point2.latd, point2.lond};
    // printf("tdas: %ld, %ld, %ld, %ld\n", pointa[0], pointa[1], pointb[0], pointb[1]);
    
    
    return to_distance_angle(pointa, angle, pointb);
}


/**
 * @brief 计算点到直线的距离
 * 
 * @param point1 精确点坐标，也即参考线的点坐标
 * @param angle 参考线的角度
 * @param points2 线外点的坐标
 */
double to_distance_angle(double points1[2], double angle, double points2[2]) {
    double m = 0;// 斜率
    double b = 0; // 截距

    double x1, y1;
    double distances[2] = {0};
    //如果角度为90 270 -90 450 则手动设置一个很大的斜率值
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


// 对于结构体的latlon_to_distance
double structure_ll2dis(GPS_msgTypeDef GPS_msgStructure, double diff[2]) {
    double points[2]= {GPS_msgStructure.latd, GPS_msgStructure.lond};

    latlon_to_distance(diff, points);
}

// 计算点到线的距离
double latlon_to_distance(double distances[2], double point[2]) {
    double R = 6371000;
    // double latDiff = 0;
    double cR;
    // 经纬度差 转换弧度
    // printf("distances is %0.9f, %0.9f\n", distances[0], distances[1]);
    double latDiff = deg2rad(distances[0]);
    double lonDiff = deg2rad(distances[1]);

    // 提取起点纬度，现在是从djd矩阵的第一列获取
    double lat1 = deg2rad(point[0]);
    //计算终点纬度，这里每个起点纬度对应一个终点纬度
    double lat2 = latDiff + lat1;

    // printf("lat1 is %f\n", lat1);
    // printf("lat2 is %f\n", lat2);
    // printf("latDiff is %0.9f\n", latDiff);
    // printf("lonDiff is %0.9f\n", lonDiff);

    // H公式
    double a = pow(sin(latDiff / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    // printf("a is %0.20f\n", a);
    // printf("sqrta is %0.20f\n", sqrt(a));
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    // printf("c is %0.11f\n", c);
    cR = c* R;
    // printf("cR is %0.11f\n", cR);
    return cR;

}

double point_to_72line(GPS_msgTypeDef point) {
    
}



