
#ifndef __SRM_BASEMAPPROJECTION_H_INCLUDED__
#define __SRM_BASEMAPPROJECTION_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This is the ConvergenceOfMeridian.
    @param this_object in: this SRF object
    @param surface_coordinate in: surface coordinate
    @param gamma out: resulting convergence of the meridian
    @returns a status code
*/
typedef SRM_Status_Code SRM_ConvergenceOfTheMeridian
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Long_Float        *gamma               /* OUT */
);


/** Gets the Extended Valid Geodetic Region for this SRF.  This is the Lat/Long Coordinates.
    @note Given a coordinate component, the last invocation of this
          method or the setValidGeodeticRegion method determines
          the valid and extended valid intervals of the coordinate
          component values.
    @param this_object in: this SRF object
    @param component_identifier in: the coordinate component (1, 2, or 3)
    @param interval_type out: the type of interval
    @param extendend_lower_bound out: the extended lower value of the interval
    @param lower_bound out: the lower value of the interval
    @param upper_bound out: the upper value of the interval
    @param extended_upper_bound out: the extended_upper value of the interval
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetExtendedValidGeodeticRegion
(
    SRM_Object_Reference  this_object,
    SRM_Integer           component_identifier,
    SRM_Interval_Type    *interval_type,         /* OUT */
    SRM_Long_Float       *extended_lower_bound,  /* OUT */
    SRM_Long_Float       *lower_bound,           /* OUT */
    SRM_Long_Float       *upper_bound,           /* OUT */
    SRM_Long_Float       *extended_upper_bound   /* OUT */
);

/** Get the Valid Geodetic Region for this SRF.
     @note: Given a coordinate component, the last invocation of this
           method or the setExtendedValidGeodeticRegion method determines
           the valid and extended valid intervals of the coordinate
           component values.
    @param this_object in: this SRF object
    @param component_identifier in: the coordinate component (1 or 2)
    @param interval_type out: the type of the interval
    @param lower_bound out: the lower value of the interval
    @param upper_bound out: the upper value of the interval
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetValidGeodeticRegion
(
    SRM_Object_Reference  this_object,
    SRM_Integer           component_identifier,
    SRM_Interval_Type    *interval_type,          /* OUT */
    SRM_Long_Float       *lower_bound,            /* OUT */
    SRM_Long_Float       *upper_bound             /* OUT */
);

/** This is the MapAzimith for the SRF
    @note What is Azimith
    @param this_object in: this SRF object
    @param point1_coordinate in: surface coordinate
    @param point2_coordinate in: target coordinate
    @param azimuth out: result is azimuth
    @returns a status code
*/
typedef SRM_Status_Code SRM_MapAzimuth
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *point1_coordinate,
  const SRM_SurfaceCoordinate *point2_coordinate,
        SRM_Long_Float        *azimuth              /* OUT */
);

/** Point Distortion for the SRF
    @note
    @param this_object in: this SRF object
    @param surface_coordinate in: surface coordinate
    @param distortion in: returning distortion
    @returns a status code
*/
typedef SRM_Status_Code SRM_PointDistortion
(
        SRM_Object_Reference   this_object,
  const SRM_SurfaceCoordinate *surface_coordinate,
        SRM_Long_Float        *distortion          /* OUT */
);

/** Set the Extended Valid Region for this SRF.
    @note Given a coordinate component, the last invocation of this
          method or the setValidRegion method determines
          the valid and extended valid intervals of the coordinate
          component values.
    @note Upper or Lower value is ignored if the interval is a
          semi-interval or unbounded.
    @note The Lower value must be strictly less than the Upper value.
    @note The Extended_Lower value must be strictly greater than the Lower value and
          the Extended_Upper value must be strictly smaller than the Lower value.
    @param this_object in: this SRF object
    @param component_identifier in: the coordinate component (1, 2, or 3)
    @param interval_type in: the type of interval
    @param extended_lower_bound in: the extended lower value of the interval
    @param lower_bound in: the lower value of the interval
    @param upper_bound in: the upper value of the interval
    @param extended_upper_bound in: the extended_upper value of the interval
    @returns a status code
*/
typedef SRM_Status_Code SRM_SetExtendedValidGeodeticRegion
(
    SRM_Object_Reference  this_object,
    SRM_Integer           component_identifier,
    SRM_Interval_Type     interval_type,
    SRM_Long_Float        extended_lower_bound,
    SRM_Long_Float        lower_bound,
    SRM_Long_Float        upper_bound,
    SRM_Long_Float        extended_upper_bound
);

/** Set the Valid Region for this SRF in geodetic coordinates (lon/lat).
    @note Given a coordinate component, the last invocation of this
          method or the setExtendedValidGeodeticRegion method determines
          the valid and extended valid intervals of the coordinate
          component values.
    @note Upper or Lower value is ignored if the interval is a
          semi-interval or unbounded.
    @note The Lower value must be strictly less than the Upper bound value.
    @param this_object in: this SRF object
    @param component_identifier in: the coordinate component (1 or 2)
    @param interval_type in: the type of interval
    @param lower_bound in: the lower bound value of the interval
    @param upper_bound in: the upper bound value of the interval
    @returns a status code
*/
typedef SRM_Status_Code SRM_SetValidGeodeticRegion
(
    SRM_Object_Reference this_object,
    SRM_Integer          component_identifier,
    SRM_Interval_Type    interval_type,
    SRM_Long_Float       lower_bound,
    SRM_Long_Float       upper_bound
);

#ifdef __cplusplus
}
#endif
#endif
