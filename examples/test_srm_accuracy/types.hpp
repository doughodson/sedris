
#ifndef __types_HPP__
#define __types_HPP__

#include "srm_types.h"

typedef struct
{
   SRM_Vector_3D var;
} doubleArray3;

typedef struct
{
   char path[100];
   char file_name_1[50];
   char file_name_2[50];
} configInfo;

#endif
