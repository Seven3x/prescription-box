#ifndef __PROC_H
#define __PROC_H
#include "read.h"
long long latdms2dd(long long dms);
long long londms2dd(long long dms);
double dms2dd(double dms);

double to_distance_angle_structure(GPS_msgTypeDef point1, double angle, GPS_msgTypeDef point2);
double to_distance_angle(double points1[2], double angle, double points2[2]);
double latlon_to_distance(double distances[2], double point[2]);

#endif // !__PROC_H