
#ifndef __SRM_BASESRFWITHELLIPSOIDALHEIGHT_H_INCLUDED__
#define __SRM_BASESRFWITHELLIPSOIDALHEIGHT_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Associate Surface Coordinate
    @param this_object in: this SRF object
    @param coordinate in: surface coordinate
    @param on_surface_coordinate out: resulting in a surface coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_AssociateSurfaceCoordinateEH
(
        SRM_Object_Reference   this_object,
  const SRM_Coordinate3D      *coordinate,
        SRM_SurfaceCoordinate *on_surface_coordinate  /* OUT */
);

/** Creates a Local Tangent Space Euclidean SRF
    @param this_object in: this SRF object
    @param surface_coordinate in: SRF surface coordiante
    @param azimuth in: azimuth
    @param false_x_origin in: false x origin
    @param false_y_origin in: false y origin
    @param offset_height in: offset height
    @param local_tangent_Euclidean_srf out: this SRF object
    @returns a status code
*/
typedef SRM_Status_Code SRM_CreateLocalTangentSpaceEuclideanSRF
(
        SRM_Object_Reference            this_object,
  const SRM_SurfaceCoordinate          *surface_coordinate,
        SRM_Long_Float                  azimuth,
        SRM_Long_Float                  false_x_origin,
        SRM_Long_Float                  false_y_origin,
        SRM_Long_Float                  offset_height,
        SRM_LocalTangentSpaceEuclidean *local_tangent_Euclidean_srf  /* OUT */
);

/** Creates a Ellipsoidal Height surface coordinate object.
    @param this_object in: this SRF object
    @param first_coordinate_component in: this is the first coordinate of the two
    @param second_coordinate_component in: second coordinate
    @param new_coordinate out: resulting in a new coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_CreateSurfaceCoordinateEH
(
    SRM_Object_Reference   this_object,
    SRM_Long_Float         first_coordinate_component,
    SRM_Long_Float         second_coordinate_component,
    SRM_SurfaceCoordinate *new_coordinate               /* OUT */
);

/** Destroys the  Ellipsoidal Height surface coordinate
    @param this_object in: this SRF object
    @param coordinate in: coordinate to be destroyed
    @returns a status code
*/
typedef SRM_Status_Code SRM_DestroySurfaceCoordinateEH
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
);

/** This is the Euclidean Distance Ellipsoidal Height
    @param this_object in: this SRF object
    @param point1_coordinate in: Ellposoidal Height surface coordinate
    @param point2_coordinate in: Ellposoidal Height target surface coordinate
    @param distance out: resulting in the distance between the two points
    @returns a status code
*/
typedef SRM_Status_Code SRM_EuclideanDistanceEH
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *point1_coordinate,
  const SRM_SurfaceCoordinate *point2_coordinate,
        SRM_Long_Float        *distance           /* OUT */
);

/** This is the Geodesic Distance
    @param this_object in: this SRF object
    @param point1_coordinate in: Geodesic Distance surface coordinate
    @param point2_coordinate in: Geodesic Distance target surface coordinate
    @param distance out: resulting in the distance between the two points
    @returns a status code
*/
typedef SRM_Status_Code SRM_GeodesicDistance
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *point1_coordinate,
  const SRM_SurfaceCoordinate *point2_coordinate,
        SRM_Long_Float        *distance           /* OUT */
);

/** Retrieves the Surface Coordinate values for Ellipsoidal Height
    @param this_object in: this SRF object
    @param coordinate in: surface coordinate
    @param first_coordinate_component out: this is the first coordinate component
    @param second_coordinate_component out: this is the second coordinate component
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetSurfaceCoordinateValuesEH
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *coordinate,
        SRM_Long_Float        *first_coordinate_component,  /* OUT */
        SRM_Long_Float        *second_coordinate_component  /* OUT */
);

/** This is a 3D coordinate representing the same location as specified
    by a surface coordinate.
    @param this_object in: this SRF object
    @param surface_coordinate in: this is the surface coordinate
    @param coordinate out: this is the 3D new coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_PromoteSurfaceCoordinateEH
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *surface_coordinate,
        SRM_Coordinate3D      *coordinate          /* OUT */
);

/** Returns the Vertical Offset  (in metres) at a position.
    @param this_object in: this SRF object
    @param dss_code in: this is the vertical offset
    @param surface_coordinate in: surface coordinate for the object
    @param separation out: resulting in the separation for the object
    @returns a status code
*/
typedef SRM_Status_Code SRM_VerticalOffset
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
