
#ifndef CIMPL_DESTROYSRF_HPP_INCLUDED
#define CIMPL_DESTROYSRF_HPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srm_types.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code
cimpl_SRM_DestroySRF
(
    SRM_Object_Reference object,
    int                  class_type
);

#ifdef __cplusplus
}
#endif
#endif
