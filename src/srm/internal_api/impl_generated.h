
#ifndef __IMPL_GENERATED_H__
#define __IMPL_GENERATED_H__

#include <stdio.h>
#include <math.h>
#include <signal.h>

#include "../support/srm_internal.h"
#include "../support/srm_validcoord.h"
#include "../support/edges.h"
#include "../support/srm_check.h"
#include "../support/srm_conversions.h"
#include "../support/srm_coord_offsets.h"
#include "../support/srm_predefined_srf.h"
#include "../support/srm_srfp.h"
#include "../support/srm_srf_sets.h"
#include "../support/srm_srf_specific_data.h"
#include "../support/srm_validcoord.h"
#include "../support/srm_boundaries.h"

#include "impl_private.h"
#include "impl_alloc.h"
#include "impl_change.h"
#include "impl_vos.h"

extern void* (*Impl_allocsrf[SRM_SRFT_CODE_UBOUND+1])
(SRM_ORM_Code orm, SRM_RT_Code rt, void* api_templ_param_struct_ptr);

extern void* (*Impl_allocsrf_specific_data[SRM_SRFT_CODE_UBOUND+1])(void* impl_SRFP_struct );

extern Impl_Status (*Impl_checkSRFP[SRM_SRFT_CODE_UBOUND+1])(void* input_srfp);

extern SRM_SRFT_Code (*Impl_bSRFTforSRFT[SRM_SRFT_CODE_UBOUND+1])();

extern void* (*Impl_bdSRFTforSRFT[SRM_SRFT_CODE_UBOUND+1])(SRM_ORM_Code orm_dst);

extern SRM_Integer (*Impl_sizeof_templ_param[SRM_SRFT_CODE_UBOUND+1])();

extern SRM_ORM_Code (*Impl_bdORMforSRFT[SRM_SRFT_CODE_UBOUND+1])(SRM_ORM_Code orm_dst);

extern SRM_RT_Code  (*Impl_bdRTforSRFT[SRM_SRFT_CODE_UBOUND+1])(SRM_RT_Code rt_dst);

extern SRM_Integer (*Impl_sizeof_specific_data[SRM_SRFT_CODE_UBOUND+1])();

extern Impl_Status (*Impl_validcoord3DSRFT[SRM_SRFT_CODE_UBOUND+1])
  (Impl_Private_Data pdat,
   SRM_Long_Float v_coord[3]
   );

extern SRM_Integer (*Impl_get_frame_idSRFT[SRM_SRFT_CODE_UBOUND+1])(void* api_templ_param_struct_ptr);


extern SRM_SRFT_Code (*Impl_SetMembersrf_templ_code[SRM_SRFS_CODE_UBOUND+1])();

extern void* (*Impl_allocSetMembersrf[SRM_SRFS_CODE_UBOUND+1])
(SRM_SRFS_Code_Info srfs_code_info, SRM_ORM_Code orm, SRM_RT_Code rt);

extern SRM_SRFT_Code (*Impl_bSRFTforSRFS[SRM_SRFS_CODE_UBOUND+1])();

extern void* (*Impl_bdSRFTforSRFS[SRM_SRFS_CODE_UBOUND+1])(SRM_ORM_Code orm_dst);

extern SRM_ORM_Code (*Impl_bdORMforSRFS[SRM_SRFS_CODE_UBOUND+1])(SRM_ORM_Code orm_dst);

extern SRM_RT_Code (*Impl_bdRTforSRFS[SRM_SRFS_CODE_UBOUND+1])(SRM_RT_Code rt_dst);

extern Impl_Status (*Impl_validcoord3DSRFS[SRM_SRFS_CODE_UBOUND+1])
(
    Impl_Private_Data pdat,
    SRM_Long_Float    v_coord[3]
);

extern SRM_Integer (*Impl_get_frame_idSRFS[SRM_SRFS_CODE_UBOUND+1])(void* api_templ_param_struct_ptr);

extern SRM_Integer (*Impl_naturalSetMember[SRM_SRFS_CODE_UBOUND+1])( Impl_Private_Data pdat, SRM_Long_Float coordinate[3]);

extern void* (*Impl_allocStandardsrf[SRM_SRF_CODE_UBOUND+1])( SRM_RT_Code rt_code );

extern SRM_SRFT_Code (*Impl_Standardsrf_templ_code[SRM_SRF_CODE_UBOUND+1])();
#endif
