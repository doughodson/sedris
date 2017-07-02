

#ifndef __CIMPL_BASESRFWITHELLIPSOIDALHEIGHT_HPP_INCLUDED__
#define __CIMPL_BASESRFWITHELLIPSOIDALHEIGHT_HPP_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_AssociateSurfaceCoordinateEH
(
          SRM_Object_Reference   this_object,
    const SRM_Coordinate3D      *coordinate,
          SRM_SurfaceCoordinate *on_surface_coordinate /* OUT */
);


SRM_Status_Code cimpl_SRM_CreateLocalTangentSpaceEuclideanSRF
(
          SRM_Object_Reference            this_object,
    const SRM_SurfaceCoordinate          *surface_coordinate,
          SRM_Long_Float                  azimuth,
          SRM_Long_Float                  false_x_origin,
          SRM_Long_Float                  false_y_origin,
          SRM_Long_Float                  offset_height,
          SRM_LocalTangentSpaceEuclidean *local_tangent_Euclidean_srf  /* OUT */
);


SRM_Status_Code cimpl_SRM_CreateSurfaceCoordinateEH
(
    SRM_Object_Reference   this_object,
    SRM_Long_Float         first_coordinate_component,
    SRM_Long_Float         second_coordinate_component,
    SRM_SurfaceCoordinate *new_coordinate               /* OUT */
);


SRM_Status_Code cimpl_SRM_DestroyThisSurfaceCoordinateEH
(
    SRM_Object_Reference coordinate
);


SRM_Status_Code cimpl_SRM_DestroySurfaceCoordinateEH
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
);


SRM_Status_Code cimpl_SRM_EuclideanDistanceEH
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *source_coordinate,
    const SRM_SurfaceCoordinate *target_coordinate,
          SRM_Long_Float        *distance           /* OUT */
);


SRM_Status_Code cimpl_SRM_GeodesicDistance
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *source_coordinate,
    const SRM_SurfaceCoordinate *target_coordinate,
          SRM_Long_Float        *distance           /* OUT */
);


SRM_Status_Code cimpl_SRM_GetSurfaceCoordinateValuesEH
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *coordinate,
          SRM_Long_Float        *first_coordinate_component,  /* OUT */
          SRM_Long_Float        *second_coordinate_component  /* OUT */
);


SRM_Status_Code cimpl_SRM_PromoteSurfaceCoordinateEH
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Coordinate3D      *coordinate          /* OUT */
);

SRM_Status_Code cimpl_SRM_VerticalOffset
(
          SRM_Object_Reference   this_object,
          SRM_DSS_Code           dss_code,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Long_Float        *separation          /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
