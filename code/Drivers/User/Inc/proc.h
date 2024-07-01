#ifndef __PROC_H
#define __PROC_H
#include "gps.h"
#define M_PI        3.14159265358979323846
long long latdms2dd(long long dms);
long long londms2dd(long long dms);
double dms2dd(double dms);

double to_distance_angle_structure(GPS_msgTypeDef point1, double angle, GPS_msgTypeDef point2);
double to_distance_angle(double points1[2], double angle, double points2[2]);
double latlon_to_distance(double distances[2], double point[2]);
GPS_msgTypeDef structure_nlonlat(GPS_msgTypeDef point, double* average, double angle);
double calcu_gamma(double dl, double dd, double angle);
double calcu_h(double dl, double dd);
double rad2deg(double radians);
void nlonlat(double point[2], double distance, double angle, double target_point[2]);
#endif // !__PROC_H