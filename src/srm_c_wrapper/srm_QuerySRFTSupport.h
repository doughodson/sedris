
#ifndef __SRM_QUERYSRFTSUPPORT_H_INCLUDED__
#define __SRM_QUERYSRFTSUPPORT_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Queries for the SRFT support by the implementation.
    @param srft_code in: the SRF Template code
    @param supported out: return true if the SRFT is supported by this implementation.
    @returns a status code
*/
extern SRM_Status_Code
SRM_QuerySRFTSupport
(
    SRM_SRFT_Code  srft_code,
    SRM_Boolean   *supported /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
