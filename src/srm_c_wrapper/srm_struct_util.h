
#ifndef __SRM_STRUCT_UTIL_H_INCLUDED__
#define __SRM_STRUCT_UTIL_H_INCLUDED__

/** @file   srm_struct_util.h
    @author Greg Hull (SAIC), Kevin Wertman (SAIC)
    @brief  This file provides utility methods to translate the SRM
            structures used in DRM fields (SE_SRF_Info, SRM_Coordinate) 
            into SRM handles used by the rest of the SRM C API (SRM_SRF, 
            SRM_Coordinate) so that SRM C API methods may be used for 
            conversions.
*/

/*
 * Allow C++ compilers to use this API without any problems
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "srm_types.h"

/*! Creates a new SRF based on the SRF Template Parameters
    structure being passed in.
 */
extern SRM_Status_Code
SRM_CreateSRFFromSRFTemplateParams
(
    const SRM_SRFT_Parameters  *srft_params_in_ptr,
          SRM_RT_Code          rt_code,
          SRM_Object_Reference *srf_out_ptr
);

/*! Frees an SRF template instance created by the
    SRM_CreateSRFFromSRFTemplateParams() function.
 */
extern SRM_Status_Code
SRM_DestroySRF
(
    SRM_Object_Reference srf_ptr
);

/*! Creates a new Coordinate opaque handle based 
    on the Coord structure being passed in.
 */
extern SRM_Status_Code 
SRM_CreateCoordinateFromCoordinateParams
( 
          SRM_Object_Reference    srf, 
    const SRM_Coordinate          *coord_params_in_ptr, 
          SRM_Object_Reference    *coordinate_out_ptr 
);

/*! Frees a Coordinate opaque handle created by the
    SRM_CreateCoordinateFromCoordinateParams() function.
 */
extern SRM_Status_Code 
SRM_DestroyCoordinate
( 
    SRM_Object_Reference    coordinate_ptr 
);

/*! Populates an SRM_Coordinate structure with
    the relevant information from the opaque
    SRM_Coordinate handle being passed in
 */
extern SRM_Status_Code 
SRM_GetCoordFromCoordinate
( 
    SRM_Object_Reference  coordinate, 
    SRM_Coordinate        *coord_params_out_ptr
);

/*! Generically sets the values of a coordinate.
    If the coordinate is not a 3D coordinate, 
    the oordinate3_in argument will be ignored.
 */
extern SRM_Status_Code 
SRM_SetCoordValues
( 
    SRM_Object_Reference  coord_in_ptr,  
    SRM_Long_Float        oordinate1_in,
    SRM_Long_Float        oordinate2_in,  
    SRM_Long_Float        oordinate3_in 
);

/*! Generically gets the values of a coordinate.
    If the coordinate is not a 3D coordinate, 
    the oordinate3_out_ptr argument will be ignored.
 */
extern SRM_Status_Code 
SRM_GetCoordValues
( 
      const SRM_Object_Reference  coord_in_ptr,  
            SRM_Long_Float        *oordinate1_out_ptr,
            SRM_Long_Float        *oordinate2_out_ptr, 
            SRM_Long_Float        *oordinate3_out_ptr
);

/*! Determines if the given SRM_Coordinate represents an 
    angular coordinate.
 */
extern SRM_Boolean 
SRM_IsCoordAngular
( 
	const SRM_Object_Reference coord_in_ptr
);

/*! Determines if the given SRM_Coordinate represents an 
    2D coordinate.
 */
extern SRM_Boolean 
SRM_IsCoord2D
( 
	const SRM_Object_Reference coord_in_ptr 
);

/*! Determines if the given SRM_Coordinate represents an 
    surface coordinate.
 */
extern SRM_Boolean 
SRM_IsCoordSurface
( 
	const SRM_Object_Reference coord_in_ptr 
);

/*! Determines if the given SRM_Coordinate represents an 
    3D coordinate.
 */
extern SRM_Boolean 
SRM_IsCoord3D
( 
	const SRM_Object_Reference coord_in_ptr
);

#ifdef __cplusplus
}
#endif

#endif



