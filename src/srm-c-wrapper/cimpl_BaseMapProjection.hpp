
#ifndef __CIMPL_BASEMAPPROJECTION_HPP_INCLUDED__
#define __CIMPL_BASEMAPPROJECTION_HPP_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_ConvergenceOfTheMeridian
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *surface_coordinate,
        SRM_Long_Float        *gamma               /* OUT */
);


SRM_Status_Code cimpl_SRM_GetExtendedValidGeodeticRegion
(
    SRM_Object_Reference  this_object,
    SRM_Integer           component,
    SRM_Interval_Type    *type,            /* OUT */
    SRM_Long_Float       *extended_lower,  /* OUT */
    SRM_Long_Float       *lower,           /* OUT */
    SRM_Long_Float       *upper,           /* OUT */
    SRM_Long_Float       *extended_upper   /* OUT */
);


SRM_Status_Code cimpl_SRM_GetValidGeodeticRegion
(
    SRM_Object_Reference  this_object,
    SRM_Integer           component,
    SRM_Interval_Type    *type,        /* OUT */
    SRM_Long_Float       *lower,       /* OUT */
    SRM_Long_Float       *upper        /* OUT */
);


SRM_Status_Code cimpl_SRM_MapAzimuth
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
    const SRM_SurfaceCoordinate *target_coordinate,
          SRM_Long_Float        *azimuth             /* OUT */
);


SRM_Status_Code cimpl_SRM_PointDistortion
(
        SRM_Object_Reference                              this_object,
  const SRM_SurfaceCoordinate                             *surface_coordinate,
        SRM_Long_Float                                    *distortion                       /* OUT */
);


SRM_Status_Code cimpl_SRM_SetExtendedValidGeodeticRegion
(
    SRM_Object_Reference this_object,
    SRM_Integer          component,
    SRM_Interval_Type    type,
    SRM_Long_Float       extended_lower,
    SRM_Long_Float       lower,
    SRM_Long_Float       upper,
    SRM_Long_Float       extended_upper
);


SRM_Status_Code cimpl_SRM_SetValidGeodeticRegion
(
    SRM_Object_Reference this_object,
    SRM_Integer          component,
    SRM_Interval_Type    type,
    SRM_Long_Float       lower,
    SRM_Long_Float       upper
);

#ifdef __cplusplus
}
#endif
#endif
