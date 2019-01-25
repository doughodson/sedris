
#ifndef __SRM_BASESRF2D_H_INCLUDED__
#define __SRM_BASESRF2D_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Changes an array of coordinate values to this SRF.
    @note The destination coordinates must have been created using this SRF.
    @note The source and destination arrays must be of same size.
    @note All the coordinates in an array must be associated with the same SRF.
    @note When an exception is raised, the index will be set to the offending coordinate.
    @param this_object in: this SRF object
    @param source_srf in: source SRF
    @param source_coordinate_array out: the array of source coordinates in some other SRF
    @param target_coordinate_array out: the array of destination coordinate in this SRF
    @param index in: the number of elements in the arrays
    @returns a status code
*/
typedef SRM_Status_Code SRM_ChangeCoordinate2DArraySRF
(
          SRM_Object_Reference    this_object,
    const SRM_Object_Reference    source_srf,
    const SRM_Coordinate2D_Array *source_coordinate_array,
          SRM_Coordinate2D_Array *target_coordinate_array, /* OUT */
          SRM_Integer_Positive   *index                    /* OUT */
);

/** Changes an array of coordinate values to this SRF using tranformation object.
    @note The destination coordinates must have been created using this SRF.
    @note The source and destination arrays must be of same size.
    @note All the coordinates in an array must be associated with the same SRF.
    @note When an exception is raised, the index will be set to the offending coordinate.
    @param this_object in: this SRF object
    @param source_srf in: source SRF
    @param source_coordinate_array in: the array of source coordinates in some other SRF.
    @param h_st in: 2D ORM four parameter transformation
    @param target_coordinate_array out: the array of destination coordinate in this SRF.
    @param index out: the number of elements in the arrays
    @returns a status code
*/
typedef SRM_Status_Code SRM_ChangeCoordinate2DArraySRFObject
(
          SRM_Object_Reference                  this_object,
    const SRM_Object_Reference                  source_srf,
    const SRM_Coordinate2D_Array               *source_coordinate_array,
    const SRM_ORM_Transformation_2D_Parameters *h_st,
          SRM_Coordinate2D_Array               *target_coordinate_array, /* OUT */
          SRM_Integer_Positive                 *index                    /* OUT */
);

/** Changes a coordinate's values to this SRF.
    @note The destination coordinate must have been created using this SRF.
    @param this_object in: this SRF object.
    @param source_srf in: source SRF.
    @param source_coordinate in: the source coordinate in some other SRF.
    @param target_coordinate out: the destination coordinate in this SRF
    @returns a status code
*/
typedef SRM_Status_Code SRM_ChangeCoordinate2DSRF
(
          SRM_Object_Reference  this_object,
    const SRM_Object_Reference  source_srf,
    const SRM_Coordinate2D     *source_coordinate,
          SRM_Coordinate2D     *target_coordinate  /* OUT */
);

/** Changes a coordinate's values to this SRF using tranformation object.
    @note The destination coordinate must have been created using this SRF.
    @note The value of omega for hst must be within the range ( -2_PI, 2_PI ).
    @note The value of delta_s for hst must be stricly greater than -1.0.
    @param this_object in: this SRF object.
    @param source_srf in: source SRF.
    @param surface_coordinate in: the source coordinate in some other SRF
    @param h_st in: 2D ORM transformation
    @param target_coordinate out: the destination coordinate in this SRF
    @returns a status code
*/
typedef SRM_Status_Code SRM_ChangeCoordinate2DSRFObject
(
          SRM_Object_Reference                  this_object,
    const SRM_Object_Reference                  source_srf,
    const SRM_Coordinate2D                     *source_coordinate,
    const SRM_ORM_Transformation_2D_Parameters *h_st,
          SRM_Coordinate2D                     *target_coordinate  /* OUT */
);

/** Creates a 2D coordinate object.
    @see freeCoordinate2D()
    @param this_object in: this SRF object
    @param first_coordinate_component in:  first component
    @param second_coordinate_component in: second component
    @param new_coordinate out: new coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_CreateCoordinate2D
(
    SRM_Object_Reference  this_object,
    SRM_Long_Float        first_coordinate_component,
    SRM_Long_Float        second_coordinate_component,
    SRM_Coordinate2D     *new_coordinate               /* OUT */
);

/** Destroys the 2D Coordinate
    @param this_object in: this SRF object
    @param coordinate in: destroy this coordinate
*/
typedef SRM_Status_Code SRM_DestroyCoordinate2D
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
);

/** Euclidean Distance 2D
    @param this_object in: this SRF object
    @param surface_coordinate in: this is the surface coordinate
    @param target_coordinate in: this is the target coordinate
    @param distance out: outputs the distance
    @returns a status code
*/
typedef SRM_Status_Code SRM_EuclideanDistance2D
(
          SRM_Object_Reference  this_object,
    const SRM_Coordinate2D     *source_coordinate,
    const SRM_Coordinate2D     *target_coordinate,
          SRM_Long_Float       *distance           /* OUT */
);

/** Retrieves the 2D coordinate component values.
    @param this_object in: this SRF object
    @param coordinate in: 2D coordinate
    @param first_coordinate_component out: first coordinate
    @param second_coordinate_component out: second coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetCoordinate2DValues
(
          SRM_Object_Reference  this_object,
    const SRM_Coordinate2D     *coordinate,
          SRM_Long_Float       *first_coordinate_component,  /* OUT */
          SRM_Long_Float       *second_coordinate_component  /* OUT */
);

/** Sets the 2D coordinate component values.
    @param this_object in: this SRF object
    @param coordinate in out: 2D coordinate
    @param first_coordinate_component in: first coordinate
    @param second_coordinate_component in: second coordinate
    @returns a status code
*/
typedef SRM_Status_Code SRM_SetCoordinate2DValues
(
    SRM_Object_Reference  this_object,
    SRM_Coordinate2D     *coordinate, /* IN / OUT */
    SRM_Long_Float        first_coordinate_component,
    SRM_Long_Float        second_coordinate_component
);

#ifdef __cplusplus
}
#endif
#endif
