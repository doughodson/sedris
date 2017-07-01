
#ifndef __SRM_BASESRF_H_INCLUDED__
#define __SRM_BASESRF_H_INCLUDED__

#include "srm_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Gets the ORM Codes
    @param this_object in: this SRF object
    @param orm_code out: outputs a ORM Code
    @param rt_code out: outputs a  RT Code
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetORMCodes
(
    SRM_Object_Reference  this_object,
    SRM_ORM_Code         *orm_code, /* OUT */
    SRM_RT_Code          *rt_code   /* OUT */
);

/** Gets SRF Codes
    @param this_object in: this SRF object
    @param srft_code out: srft code
    @param srf_code out: srf code
    @param srfs_code_info out: srfs code info
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetSRFCodes
(
    SRM_Object_Reference  this_object,
    SRM_SRFT_Code        *srft_code,     /* OUT */
    SRM_SRF_Code         *srf_code,      /* OUT */
    SRM_SRFS_Code_Info   *srfs_code_info /* OUT */
);

/** Gets major semi-axis value (a).
    @param this_object in: this SRF object
    @param major_semi_axis out: major semi axis value
*/
typedef SRM_Status_Code SRM_GetA
(
    SRM_Object_Reference  this_object,
    SRM_Long_Float       *major_semi_axis /* OUT  */
);

/** Gets flattening value (f).
    @param this_object in: this SRF object
    @param flattening out: flattening value
*/
typedef SRM_Status_Code SRM_GetF
(
    SRM_Object_Reference  this_object,
    SRM_Long_Float       *flattening  /* OUT  */
);


/** Gets the CS Code .
    @param this_object in: this SRF object
    @param cs_code out: results with the cs code
    @returns a status code
*/
typedef SRM_Status_Code SRM_GetCSCode
(
    SRM_Object_Reference  this_object,
    SRM_CS_Code          *cs_code /* OUT cs code */
);

/** Destroys the SRF
    @param object in: object that is two be destroyed
    @returns a status code
*/
typedef SRM_Status_Code SRM_Destroy
(
    SRM_Object_Reference object /* object to destroy*/
);

#ifdef __cplusplus
}
#endif
#endif
