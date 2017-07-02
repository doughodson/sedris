

#ifndef CIMPL_LAMBERTCONFORMALCONIC_HPP_INCLUDED
#define CIMPL_LAMBERTCONFORMALCONIC_HPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif


SRM_Status_Code cimpl_SRM_LCC_GetSRFParameters 
(
        SRM_Object_Reference     this_object,         
        SRM_LCC_Parameters       *parameters         /* OUT */
);


#ifdef __cplusplus
}
#endif
#endif
