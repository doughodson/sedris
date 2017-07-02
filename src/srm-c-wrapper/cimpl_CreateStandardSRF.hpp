
#ifndef CIMPL_CREATESTANDARDSRF_HPP_INCLUDED
#define CIMPL_CREATESTANDARDSRF_HPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code SRM_CreateStandardSRF
(
    SRM_SRF_Code          srf_code,
    SRM_RT_Code           rt_code,
    SRM_Object_Reference *new_srf   /* OUT */
)

#ifdef __cplusplus
}
#endif
#endif
