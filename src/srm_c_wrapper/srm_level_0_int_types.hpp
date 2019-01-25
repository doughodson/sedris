
#ifndef _SRM_LEVEL_0_INT_TYPES_HPP_INCLUDED
#define _SRM_LEVEL_0_INT_TYPES_HPP_INCLUDED

//
// DESCRIPTION: Provide the SRM C API internal types
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "srm_types.h"
#include "srf_all.hpp"
#include "Coord.hpp"
#include "Exception.hpp"
#include "Orientation.hpp"
#include "Direction.hpp"

using namespace srm;

typedef void *SRM_SRF;

typedef void *SRM_Coordinate_Handle;

typedef struct
{
    void *state;
    void *methods;
} SRM_BaseWrapper;

typedef SRM_BaseWrapper SRM_BaseSRF;

#define SRM_SRF_MAGIC_NUMBER 28086
#define SRM_COORD_MAGIC_NUMBER 28186
#define SRM_DIR_MAGIC_NUMBER 28286
#define SRM_ORNT_MAGIC_NUMBER 28386

#define VALID_SRF_HANDLE(_a) ((_a) && (((SRF_Wrapper *)_a)->_magic_number == SRM_SRF_MAGIC_NUMBER))
#define VALID_COORD_HANDLE(_a) ((_a) && (((Coord_Wrapper *)_a)->_magic_number == SRM_COORD_MAGIC_NUMBER))
#define VALID_DIR_HANDLE(_a) ((_a) && (((Direction_Wrapper *)_a)->_magic_number == SRM_DIR_MAGIC_NUMBER))
#define VALID_ORNT_HANDLE(_a) ((_a) && (((Orientation_Wrapper *)_a)->_magic_number == SRM_ORNT_MAGIC_NUMBER))

// Define some macros for unwrapping the internal C++ stuff.

#define INT_SRF(_a) (((SRF_Wrapper *)_a)->_int_srf)
#define INT_COORD(_a) (((Coord_Wrapper *)_a)->_int_coord)
#define INT_DIR(_a) (((Direction_Wrapper *)_a)->_int_direction)
#define INT_ORNT(_a) (((Orientation_Wrapper *)_a)->_int_orientation)

// This is the SRF wrapper. It is returned by the functions and when free
// is called, it calls the release method of the BaseSRF.  The C++ API will
// do all of our memory management for us.
typedef struct
{
    short int  _magic_number;
    BaseSRF   *_int_srf;
} SRF_Wrapper;


// This is the coordinate wrapper, works like the SRF wrapper
typedef struct
{
    short int  _magic_number;
    Coord     *_int_coord;
} Coord_Wrapper;


// This is the direction wrapper, works like the SRF wrapper
typedef struct
{
    short int   _magic_number;
    Direction *_int_direction;
} Direction_Wrapper;


// This is the orientation wrapper, works like the SRF wrapper
typedef struct
{
    short int     _magic_number;
    Orientation *_int_orientation;
} Orientation_Wrapper;

#endif
