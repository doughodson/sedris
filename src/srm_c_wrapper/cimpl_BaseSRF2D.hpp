

#ifndef __CIMPL_BASESRF2D_HPP_INCLUDED__
#define __CIMPL_BASESRF2D_HPP_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_ChangeCoordinate2DArraySRF
(
          SRM_Object_Reference    this_object,
    const SRM_Object_Reference    source_srf,
    const SRM_Coordinate2D_Array *source_coordinate_array,
          SRM_Coordinate2D_Array *target_coordinate_array, /* OUT */
          SRM_Integer_Positive   *index                    /* OUT */
);

SRM_Status_Code cimpl_SRM_ChangeCoordinate2DArraySRFObject
(
          SRM_Object_Reference                  this_object,
    const SRM_Object_Reference                  source_srf,
    const SRM_Coordinate2D_Array               *source_coordinate_array,
    const SRM_ORM_Transformation_2D_Parameters *h_st,
          SRM_Coordinate2D_Array               *target_coordinate_array, /* OUT */
          SRM_Integer_Positive                 *index                    /* OUT */
);

SRM_Status_Code cimpl_SRM_ChangeCoordinate2DSRF
(
          SRM_Object_Reference  this_object,
    const SRM_Object_Reference  source_srf,
    const SRM_Coordinate2D     *source_coordinate,
          SRM_Coordinate2D     *target_coordinate  /* OUT */
);


SRM_Status_Code cimpl_SRM_ChangeCoordinate2DSRFObject
(
          SRM_Object_Reference                  this_object,
    const SRM_Object_Reference                  source_srf,
    const SRM_Coordinate2D                     *source_coordinate,
    const SRM_ORM_Transformation_2D_Parameters *h_st,
          SRM_Coordinate2D                     *target_coordinate /* OUT */
);


SRM_Status_Code cimpl_SRM_CreateCoordinate2D
(
    SRM_Object_Reference  this_object,
    SRM_Long_Float        first_coordinate_component,
    SRM_Long_Float        second_coordinate_component,
    SRM_Coordinate2D     *new_coordinate               /* OUT */
);


SRM_Status_Code cimpl_SRM_DestroyCoordinate2D
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
);


SRM_Status_Code cimpl_SRM_DestroyThisCoordinate2D
(
    SRM_Object_Reference coordinate
);


SRM_Status_Code cimpl_SRM_EuclideanDistance2D
(
          SRM_Object_Reference  this_object,
    const SRM_Coordinate2D     *source_coordinate,
    const SRM_Coordinate2D     *target_coordinate,
          SRM_Long_Float       *distance          /* OUT */
);


SRM_Status_Code cimpl_SRM_GetCoordinate2DValues
(
          SRM_Object_Reference  this_object,
    const SRM_Coordinate2D     *coordinate,
          SRM_Long_Float       *first_coordinate_component,  /* OUT */
          SRM_Long_Float       *second_coordinate_component  /* OUT */
);


SRM_Status_Code cimpl_SRM_SetCoordinate2DValues
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
