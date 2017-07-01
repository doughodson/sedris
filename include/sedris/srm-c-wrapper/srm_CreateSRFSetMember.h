
#ifndef __SRM_CREATESRFSETMEMBER_H_INCLUDED__
#define __SRM_CREATESRFSETMEMBER_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Creates an SRF from a SRF set code, a set member code specific to
        that set, and an ORM code.
        @note The returned SRF should be freed by calling its Destroy()
              method.
        @param srfs_code_info in:  srfs code
        @param orm_code in:  the ORM code to use in the created SRF
        @param rt_code in: the RT code to use in the created SRF
        @param new_srf out: results in new srf
        @returns a status code
*/
extern SRM_Status_Code 
SRM_CreateSRFSetMember 
(
        SRM_SRFS_Code_Info                                srfs_code_info,           
        SRM_ORM_Code                                      orm_code,                 
        SRM_RT_Code                                       rt_code,                 
        SRM_Object_Reference                              *new_srf             /* OUT */
);


#ifdef __cplusplus
}
#endif
#endif
