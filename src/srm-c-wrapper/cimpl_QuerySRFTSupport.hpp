
#ifndef CIMPL_QUERYSRFTSUPPORT_HPP_INCLUDED
#define CIMPL_QUERYSRFTSUPPORT_HPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_QuerySRFTSupport
(
    SRM_SRFT_Code  srft_code,
    SRM_Boolean   *supported  /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
