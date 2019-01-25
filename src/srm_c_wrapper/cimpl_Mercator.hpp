
#ifndef CIMPL_MERCATOR_HPP_INCLUDED
#define CIMPL_MERCATOR_HPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_M_GetSRFParameters
(
    SRM_Object_Reference  this_object,
    SRM_M_Parameters     *parameters  /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
