
#ifndef __IMPL_CTYPES_H_INCLUDED__
#define __IMPL_CTYPES_H_INCLUDED__

#include "srm_types.h"

/*
 * STRUCT: IMPL_Matrix_4x4
 *
 *   This data type is used to specify the kind of 4x4 matrix used to
 *   orient and locate models, grids, and so on in the currently scoped
 *   'world' spatial reference frame.
 */
typedef struct
{
    SRM_Long_Float mat[4][4];
} IMPL_Matrix_4x4;

/*
 * STRUCT: IMPL_Matrix_3x3
 *
 *   This data type is used to specify the kind of 3x3 matrix used to
 *   orient models, grids, and so on in the currently scoped 'world'
 *   spatial reference frame.
 */
typedef struct
{
    SRM_Long_Float mat[3][3];
} IMPL_Matrix_3x3;

#endif
