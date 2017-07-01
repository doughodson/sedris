
#ifndef __SRM_BASESRFWITHTANGENTPLANESURFACE_H_INCLUDED__
#define __SRM_BASESRFWITHTANGENTPLANESURFACE_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This is the Associate Surface Coordinate for Tangent Place Surface
    @param this_object in: this SRF object
    @param coordinate in: surface coordinate
    @param on_surface_coordinate out: resulting in a surface coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_AssociateSurfaceCoordinateTPS
(
        SRM_Object_Reference   this_object,
  const SRM_Coordinate3D      *coordinate,
        SRM_SurfaceCoordinate *on_surface_coordinate /* OUT */
);

/** This creates the Surface Coordinate for the Tangent Place Surface
    @param this_object in: this SRF object
    @param first_coordinate_component in: this is the first component
    @param second_coordinate_component in: this is the second component
    @param new_coordinate out: resulting in a new tangent plane coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_CreateSurfaceCoordinateTPS
(
    SRM_Object_Reference   this_object,
    SRM_Long_Float         first_coordinate_component,
    SRM_Long_Float         second_coordinate_component,
    SRM_SurfaceCoordinate *new_coordinate               /* OUT */
);

/** This destroys the Tangent Place Surface coordinate
    @param this_object in: this SRF object
    @param coordinate in: coordinate to be destroyed
    @returns a status code
*/
typedef SRM_Status_Code SRM_DestroySurfaceCoordinateTPS
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
);

/** This is the Euclidean Distance for the Tangent Plane Surface
    @param this_object in: this SRF object
    @param point1_coordinate in: surface coordinate for the source
    @param point2_coordinate in: surface coordinate for the target
    @param distance out: distance between the two coordinates
    @returns a status code
*/
typedef SRM_Status_Code SRM_EuclideanDistanceTPS
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *point1_coordinate,
  const SRM_SurfaceCoordinate *point2_coordinate,
        SRM_Long_Float        *distance           /* OUT */
);

/** This gets the Surface Coordinate values for the Tangent Place Surface
    @param this_object in: th SRF object
    @param point1_coordinate in: surface coordinate for the source
    @param point2_coordinate in: surface coordinate for the target
    @param distance out: distance between the two coordinates
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetSurfaceCoordinateValuesTPS
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *coordinate,
        SRM_Long_Float        *first_coordinate_component,  /* OUT */
        SRM_Long_Float        *second_coordinate_component  /* OUT */
);

/** This is the Promote Surface Coordinate for the Tangent Place Surface
    @param this_object in: this SRF object
    @param surface_coordinate in: surface coordinate for the source
    @param point2_coordinate in: surface coordinate for the target
    @param coordinate out: resulting in a coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_PromoteSurfaceCoordinateTPS
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *surface_coordinate,
        SRM_Coordinate3D      *coordinate          /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
