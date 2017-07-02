
#ifndef __CIMPL_CREATESRFSETMEMBER_HPP_INCLUDED__
#define __CIMPL_CREATESRFSETMEMBER_HPP_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code SRM_CreateSRFSetMember
(
    const SRM_SRFS_Code_Info   *srfs_code_info,
          SRM_ORM_Code          orm_code,
          SRM_RT_Code           rt_code,
          SRM_Object_Reference  new_srf            /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
