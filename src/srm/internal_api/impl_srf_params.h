
//    This file contains the internal representation of SRF parameters used
//    by the implementation.  Under no circumstances should this file
//    be exported outside of the implementation's internal API.

#ifndef _IMPL_SRF_PARAMS_H
#define _IMPL_SRF_PARAMS_H

#include "srm_types.h"

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
}  IMPL_NOPARAM_SRFP;

typedef IMPL_NOPARAM_SRFP IMPL_CELESTIOCENTRIC_SRFP;


typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Axis_Direction up_direction;
  SRM_Axis_Direction forward_direction;
} IMPL_LSR3D_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Axis_Direction forward_direction;
} IMPL_LSR2D_SRFP;

typedef IMPL_NOPARAM_SRFP IMPL_CELESTIODETIC_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_PLANETODETIC_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Long_Float geodetic_longitude;
  SRM_Long_Float geodetic_latitude;
  SRM_Long_Float azimuth;
  SRM_Long_Float x_false_origin;
  SRM_Long_Float y_false_origin;
  SRM_Long_Float height_offset;
} IMPL_LOC_TAN_EUCLIDEAN_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Long_Float geodetic_longitude;
  SRM_Long_Float geodetic_latitude;
  SRM_Long_Float azimuth;
  SRM_Long_Float height_offset;
} IMPL_LT_SRFP;

typedef IMPL_LT_SRFP      IMPL_LOC_TAN_AZ_SPHER_SRFP;
typedef IMPL_LT_SRFP      IMPL_LOC_TAN_AZ_CYL_SRFP;  /*SRM_SRFT_SURFACE_LOCAL_AZIMUTHAL_TANGENT_PLANE*/
typedef IMPL_NOPARAM_SRFP IMPL_AZIMUTHAL_SRFP;
typedef IMPL_LT_SRFP      IMPL_LOC_TAN_CYL_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_POLAR_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_CELESTIOMAGNETIC_SRFP; 
typedef IMPL_NOPARAM_SRFP IMPL_EQUATORIAL_INERTIAL_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_SOLAR_ECLIPTIC_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_SOLAR_ECLIPTIC_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_SOLAR_EQUATORIAL_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_SOLAR_EQUATORIAL_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_SOLAR_MAGNETIC_ECLIPTIC_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_SOLAR_MAGNETIC_DIPOLE_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_HELIO_ARIES_ECLIPTIC_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_HELIO_EARTH_ECLIPTIC_SRFP;
typedef IMPL_NOPARAM_SRFP IMPL_HELIO_EARTH_EQUAT_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Long_Float origin_longitude;
  SRM_Long_Float central_scale;
  SRM_Long_Float false_easting;
  SRM_Long_Float false_northing;
} IMPL_MERCATOR_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Long_Float origin_longitude;
  SRM_Long_Float origin_latitude;
  SRM_Long_Float central_scale;
  SRM_Long_Float false_easting;
  SRM_Long_Float false_northing;
} IMPL_TRANSVERSE_MERCATOR_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Long_Float longitude1;
  SRM_Long_Float latitude1;
  SRM_Long_Float longitude2;
  SRM_Long_Float latitude2;
  SRM_Long_Float central_scale;
  SRM_Long_Float false_easting;
  SRM_Long_Float false_northing;
} IMPL_OBLIQUE_MERCATOR_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Long_Float origin_longitude;
  SRM_Long_Float origin_latitude;
  SRM_Long_Float latitude1;
  SRM_Long_Float latitude2;
  SRM_Long_Float false_easting;
  SRM_Long_Float false_northing;
} IMPL_LAMBERT_CONF_CONIC_SRFP;

typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Polar_Aspect polar_aspect;
  SRM_Long_Float   origin_longitude;
  SRM_Long_Float   central_scale;
  SRM_Long_Float   false_easting;
  SRM_Long_Float   false_northing;
} IMPL_POLAR_STEREOGRAPHIC_SRFP;

/*!
 * STRUCT: SRM_EC_Parameters
 *
 *  Equidistant Cylindrical (EC) SRF Parameters are used as a means
 *  of specifying the EC spatial coordinate systems
 */
typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Long_Float origin_longitude;
  SRM_Long_Float central_scale;
  SRM_Long_Float false_easting;
  SRM_Long_Float false_northing;
} IMPL_EQUIDISTANT_CYL_SRFP;

/*!
 * STRUCT: SRM_LCE_SRF_Parameters
 *
 *  Localcentric Euclidean 3D (LCE) SRF Parameters are used as a means
 *  of specifying the LCE spatial coordinate systems
 */
typedef struct
{
  union
  {
    SRM_ORM_Code orm;
    SRM_Integer dummy1;
  };
  union
  {
    SRM_RT_Code rt;
    SRM_Integer dummy2;
  };
  SRM_Vector_3D lococentre;
  SRM_Vector_3D primary_axis;
  SRM_Vector_3D secondary_axis;
} IMPL_LOCOCENTRIC_EUCLIDEAN_SRFP;

#endif
