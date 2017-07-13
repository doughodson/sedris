
#ifndef __types_HPP__
#define __types_HPP__

#include "srm_types.h"

#include <cmath>
#include <string>

#define MAX_DIFF 0.001

#define toRad std::atan(1.0)/45.0
#define toDeg 45.0/std::atan(1.0)

#define PI_OVER_4 std::atan(1.0)
#define PI_OVER_2 std::atan(1.0)*2.0
#define PI        std::atan(1.0)*4.0
#define TWO_PI    std::atan(1.0)*8.0

#define WGS84_A    6.3781370000000e6
#define WGS84_F    1.0/2.9825722356300e2
#define WGS84_e    std::sqrt(2*WGS84_F - WGS84_F*WGS84_F)
#define MAX_A      6400000.0
#define MAX_F      1.0/150.0
#define MAX_e      std::sqrt(2*MAX_F - MAX_F*MAX_F)
#define SPHR_A     20000000.0/PI
#define SPHR_F     0.0
#define SPHR_e     0.0

#define NEY_P1     70.*toRad
#define NEY_P2     (89.0+(59.0/60.0)+(58.0/3600.0))*toRad 

#define CENTRAL_MERIDIAN 0
#define ORIGIN_LATITUDE 1
#define SCALE_FACTOR 2
#define STANDARD_PARALLEL_ONE 3
#define STANDARD_PARALLEL_TWO 4
#define LONGITUDE_DOWN_FROM_POLE 5
#define LATITUDE_OF_TRUE_SCALE 6
#define FALSE_EASTING 7
#define FALSE_NORTHING 8
#define NO_HEIGHT 9
#define ELLIPSOID_HEIGHT 10
#define DATUM 11
#define COORDINATES 12
#define PROJECTION 13

#define TRANSVERSE_MARCATOR 0
#define MERCATOR 1
#define POLAR_STEREOGRAPHIC 2
#define NEY 3
#define GEODETIC 4
#define LAMBERT_COMFORMAL_CONIC 5
#define GEOCENTRIC 6
#define SPHERICAL 7
#define ELLIPSOIDAL 8

typedef struct
{
   SRM_Vector_3D var;
} doubleArray3;

typedef struct
{
   std::string path;
   std::string file_name_1;
   std::string file_name_2;
} configInfo;

typedef struct
{
   char           type[50];
   char           datum_name[20];
   SRM_ORM_Code   orm;
   SRM_RT_Code    rt;
   double         floatParam[DATUM];
} srfParams;

typedef struct
{
   char           datum_name_in[20];
   char           datum_name_out[20];
   double         gd_coord_in[3];
   double         gd_coord_out[3];
   double         comp_coord_out[3];
   double         diff;
} gdDatumCoord;

typedef struct
{
   char           datum_name_in[20];
   char           datum_name_out[20];
   int            count;
   double         min;
   double         max;
} gdDatumStat;

typedef struct
{
   double diff;
   int    dataPoint;
   doubleArray3 compOut;
} diffInfo;

typedef struct
{
   int count;
   double min;
   double max;
   double mean;
   double stdDev;
   bool exceededThreshold;
   int num_exceeded;
   char message[500];
   // other data
   doubleArray3 compOut;
   int dataPoint;
   bool isCD;
} statInfo;

#endif
