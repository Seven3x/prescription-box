#include <stdio.h>
#include "proc.h"
#include "read.h"
#include <string.h>
#include <stdlib.h>

double average_distances[360] = {0};
GPS_msgTypeDef GPS_msgs[100];

int main(int argc, char *argv[])
{
    char *p;
    GPS_msgTypeDef bei = {0}, point = {0};
    GPS_msgTypeDef val = {0};

    bei.lat = 3213257165;
    bei.latd = 32.13257165;
    bei.lon = 11869565805;
    bei.lond = 118.69565805;

// point_bei = [32.132552229,118.695644051];
    point.latd = 32.132552229;
    point.lond = 118.695644051;
    read_file("../data/bei.log");

    
    // for (double  angle = 0.; angle < 360.; angle += 1) {
    //     printf("%.9lf\n", to_distance_angle_structure(point, angle, bei));
    // }

    // printf("distance : %.9Lf\n", to_distance_angle_structure(point, 30., bei));
    // printf("sizeof ld %d\n", sizeof(long double));
    // printf("sizeof d: %d\n", sizeof(double));
    // printf("test: %Lf\n", strtod("3207.95429933", &p));
    // printf("%.9lf\n", dms2dd(3207.95429933));
    // printf("%lld\n", latdms2dd(320795429933));
    // printf("%.9lf\n", dms2dd(11841.73948308));
    // printf("%lld\n", londms2dd(1184173948308));
    

    for (int i = 0; i < 360; i ++) {
        double average = 0.;
        for (int j = 0; j < 100; j ++) {
            average += to_distance_angle_structure(point, (double)i, GPS_msgs[j]);
        }
        average /= 100;
        average_distances[i] = average;
        printf("average: %.9lf\n", average);
    }

    printmsg(bei);
    val = structure_nlonlat(bei, average_distances, 50);

    printmsg(val);

    return 0;
}

