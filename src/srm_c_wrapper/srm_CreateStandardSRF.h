
#ifndef __SRM_CREATESTANDARDSRF_H_INCLUDED__
#define __SRM_CREATESTANDARDSRF_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Creates a Standard SRF from its SRF code.
        @note The returned SRF should be freed by calling its Destroy()
              method.
	    @param srf_code in: the code for a standard SRF to create
	    @param rt_code in: the code for a standard SRF to create
	    @param new_srf out: results in a new srf
	    @returns a status code
*/
extern SRM_Status_Code 
SRM_CreateStandardSRF 
(
        SRM_SRF_Code                                 srf_code,  
        SRM_RT_Code                                  rt_code,
        SRM_Object_Reference                         *new_srf             /* OUT */
);


#ifdef __cplusplus
}
#endif
#endif



