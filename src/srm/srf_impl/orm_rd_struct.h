
#ifndef __ORM_RD_STRUCT_H_INCLUDED__
#define __ORM_RD_STRUCT_H_INCLUDED__

/*
 * FILE       : orm_rd_struct.h
 *
 * PROGRAMMERS: Automatically generated from SRM database
 *
 * DESCRIPTION:
 *     Internal ORM/RD structure definitions for SRM
 *
 *      *** IMPORTANT NOTE ***
 *      This file is generated automatically from the SRM database tables using
 *      the SRM Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
 *      be made in the SRM database and SRM Code generator templates, and will be
 *      reflected in this file when the system is rebuilt.
 *
 * SRM SDK Release 4.1.4 - July 1, 2011
 * - SRM spec. 4.1
 */

#include "srm_types.h"

typedef SRM_Integer SRM_OBRS_Code;

#define SRM_OBRSCOD_FIXED ((SRM_OBRS_Code)0)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_EQUATORIAL_INERTIAL
 *
 * Description:
 *     equatorial inertial
 */
#define SRM_OBRSCOD_EQUATORIAL_INERTIAL ((SRM_OBRS_Code)1)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_SOLAR_ECLIPTIC
 *
 * Description:
 *     solar ecliptic
 */
#define SRM_OBRSCOD_SOLAR_ECLIPTIC ((SRM_OBRS_Code)2)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_SOLAR_EQUATORIAL
 *
 * Description:
 *     solar equatorial
 */
#define SRM_OBRSCOD_SOLAR_EQUATORIAL ((SRM_OBRS_Code)3)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_HELIOCENTRIC_ARIES_ECLIPTIC
 *
 * Description:
 *     heliocentric Aries ecliptic
 */
#define SRM_OBRSCOD_HELIOCENTRIC_ARIES_ECLIPTIC ((SRM_OBRS_Code)4)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_HELIOCENTRIC_PLANET_ECLIPTIC
 *
 * Description:
 *     heliocentric planet ecliptic
 */
#define SRM_OBRSCOD_HELIOCENTRIC_PLANET_ECLIPTIC ((SRM_OBRS_Code)5)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_HELIOCENTRIC_PLANET_EQUATORIAL
 *
 * Description:
 *     heliocentric planet equatorial
 */
#define SRM_OBRSCOD_HELIOCENTRIC_PLANET_EQUATORIAL ((SRM_OBRS_Code)6)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_CELESTIOMAGNETIC
 *
 * Description:
 *     celestiomagnetic
 */
#define SRM_OBRSCOD_CELESTIOMAGNETIC ((SRM_OBRS_Code)7)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_SOLAR_MAGNETIC_ECLIPTIC
 *
 * Description:
 *     solar magnetic ecliptic
 */
#define SRM_OBRSCOD_SOLAR_MAGNETIC_ECLIPTIC ((SRM_OBRS_Code)8)

/*
 * GLOBAL CONSTANT: SRM_OBRSCOD_SOLAR_MAGNETIC_DIPOLE
 *
 * Description:
 *     solar magnetic dipole
 */
#define SRM_OBRSCOD_SOLAR_MAGNETIC_DIPOLE ((SRM_OBRS_Code)9)

/*
 * Upper bound
 */
#define SRM_OBRS_CODE_UBOUND 9

typedef struct
{
          SRM_RD_Code     rd_code;
          SRM_Long_Float  a;
          SRM_Long_Float  f_inverse;
          SRM_Long_Float  r;
          SRM_Long_Float  b;
          SRM_Long_Float  c;
    const char           *rd_category;
} Impl_RD_Struct;

typedef struct
{
          SRM_RT_Code    rt_code;
          SRM_ORM_Code   orm_code;
          SRM_Long_Float delta_x;
          SRM_Long_Float delta_y;
          SRM_Long_Float delta_z;
          SRM_Long_Float omega_1;
          SRM_Long_Float omega_2;
          SRM_Long_Float omega_3;
          SRM_Long_Float delta_scale;
          SRM_Long_Float region_ll_lat;
          SRM_Long_Float region_ll_long;
          SRM_Long_Float region_ur_lat;
          SRM_Long_Float region_ur_long;
} Impl_RT_Struct;

typedef struct
{
          SRM_ORM_Code    orm_code;
          SRM_ORMT_Code   ormt_code;
          SRM_OBRS_Code   obrs_code;
          SRM_ORM_Code    reference_orm;
          SRM_RD_Code     rd_code;
          SRM_Integer     rt_count;
    const Impl_RT_Struct *rt_array;
} Impl_ORM_Struct;

extern Impl_ORM_Struct Impl_ORM_array[];

extern Impl_RD_Struct Impl_RD_array[];

extern bool
Impl_wellFormedORMCode(SRM_ORM_Code orm_code);

extern bool
Impl_wellFormedRTCode(SRM_ORM_Code orm_code, SRM_RT_Code rt_code);

/*
 * function assumes orm_code and rt_code have
 * already been verified as well-formed before
 * being passed in.
 */
extern const Impl_RT_Struct *
Impl_getRTstruct(SRM_ORM_Code orm_code, SRM_RT_Code rt_code);

#endif
