

#ifndef __CIMPL_BASESRFWITHTANGENTPLANESURFACE_HPP_INCLUDED__
#define __CIMPL_BASESRFWITHTANGENTPLANESURFACE_HPP_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_AssociateSurfaceCoordinateTPS
(
          SRM_Object_Reference   this_object,
    const SRM_Coordinate3D      *coordinate,
          SRM_SurfaceCoordinate *on_surface_coordinate  /* OUT */
);


SRM_Status_Code cimpl_SRM_CreateSurfaceCoordinateTPS
(
    SRM_Object_Reference   this_object,
    SRM_Long_Float         first_coordinate_component,
    SRM_Long_Float         second_coordinate_component,
    SRM_SurfaceCoordinate *new_coordinate               /* OUT */
);


SRM_Status_Code cimpl_SRM_DestroySurfaceCoordinateTPS
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
);

SRM_Status_Code cimpl_SRM_DestroyThisSurfaceCoordinateTPS
(
    SRM_Object_Reference coordinate
);


SRM_Status_Code cimpl_SRM_EuclideanDistanceTPS
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *source_coordinate,
    const SRM_SurfaceCoordinate *target_coordinate,
          SRM_Long_Float        *distance           /* OUT */
);


SRM_Status_Code cimpl_SRM_GetSurfaceCoordinateValuesTPS
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *coordinate,
        SRM_Long_Float        *first_coordinate_component,  /* OUT */
        SRM_Long_Float        *second_coordinate_component  /* OUT */
);


SRM_Status_Code cimpl_SRM_PromoteSurfaceCoordinateTPS
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Coordinate3D      *coordinate          /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
