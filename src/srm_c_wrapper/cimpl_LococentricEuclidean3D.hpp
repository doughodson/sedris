
#ifndef CIMPL_LOCOCENTRICEUCLIDEAN3D_HPP_INCLUDED
#define CIMPL_LOCOCENTRICEUCLIDEAN3D_HPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_LCE3D_GetSRFParameters
(
    SRM_Object_Reference   this_object,
    SRM_LCE_3D_Parameters *parameters /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
