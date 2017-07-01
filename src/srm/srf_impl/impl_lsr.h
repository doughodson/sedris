
#ifndef __IMPL_LSR_H_INCLUDED__
#define __IMPL_LSR_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../support/srm_ctypes.h"
#include "../support/srm_internal.h"

#include "../internal_api/impl_srf_params.h"

#include "srm_types.h"

extern Impl_Status 
Impl_compute_F_u_v_w
(
 const IMPL_LSR3D_SRFP* lsr_3d_SRF_params_ptr, 
 SRM_Long_Float  F[4][4] 
 );

extern Impl_Status 
Impl_compute_F_u_v(const IMPL_LSR2D_SRFP* lsr_2d_SRF_params_ptr, 
		   SRM_Long_Float F[4][4] );

#endif
