

#ifndef __CIMPL_BASESRF_HPP_INCLUDED__
#define __CIMPL_BASESRF_HPP_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_GetORMCodes 
(
    SRM_Object_Reference  this_object,                   
    SRM_ORM_Code         *orm_code,    /* OUT */
    SRM_RT_Code          *rt_code      /* OUT */
);


SRM_Status_Code cimpl_SRM_GetSRFCodes 
(
    SRM_Object_Reference  this_object,                   
    SRM_SRFT_Code        *srft_code,            
    SRM_SRF_Code         *srf_code,                     
    SRM_SRFS_Code_Info   *srfs_code_info                 
);


SRM_Status_Code cimpl_SRM_GetCSCode 
(
    SRM_Object_Reference  this_object,                   
    SRM_CS_Code          *cs_code       /* OUT cs code */
);

SRM_Status_Code cimpl_SRM_GetA
(
    SRM_Object_Reference  this_object,                   
    SRM_Long_Float       *major_semi_axis /* OUT  */            
);

SRM_Status_Code cimpl_SRM_GetF
(        
    SRM_Object_Reference  this_object,                   
    SRM_Long_Float       *flattening /* OUT  */            
);

SRM_Status_Code cimpl_SRM_Destroy 
(
    SRM_Object_Reference object /* object to destroy*/
);


#ifdef __cplusplus
}
#endif
#endif
