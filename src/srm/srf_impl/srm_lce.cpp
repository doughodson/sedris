/*
 * SRM API
 *
 * FILE       : srm_lce.cpp
 *
 * PROGRAMMERS: David Shen
 *
 * DESCRIPTION:
 *   This file is internal to the SRM API.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../support/srm_ctypes.h"
#include "../support/srm_internal.h"

#include "../internal_api/impl_srf_params.h"

#include "srm_types.h"

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeLCE_GC
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeLCE_CC
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    SRM_LCE_Specific_Constants* gc_gd_spec=(SRM_LCE_Specific_Constants*)constants;

    for (int i = 0; i < 3; i++ )
    {
        dest_generic_coord[i] =
        gc_gd_spec->lococentre[i] +
        source_generic_coord[0]*gc_gd_spec->primary_axis[i] +
        source_generic_coord[1]*gc_gd_spec->secondary_axis[i] +
        source_generic_coord[2]*gc_gd_spec->xprod_rs[i];
    }
    dest_generic_coord[3] = 1.0;

    return status;
}


void
set_lce_constants
(
    const IMPL_LOCOCENTRIC_EUCLIDEAN_SRFP *lce_srfp,
          SRM_LCE_Specific_Constants      *lce_spec
)
{
    _cross_product( lce_srfp->primary_axis, lce_srfp->secondary_axis, lce_spec->xprod_rs );
    for (int i=0; i<3; i++)
    {
        lce_spec->lococentre[i] = lce_srfp->lococentre[i];
        lce_spec->primary_axis[i] = lce_srfp->primary_axis[i];
        lce_spec->secondary_axis[i] = lce_srfp->secondary_axis[i];
    }
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeCC_LCE
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeCC_LCE
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    SRM_LCE_Specific_Constants* lce_spec=(SRM_LCE_Specific_Constants*)constants;

    SRM_Long_Float p_minus_q[3];

    for (int i=0; i<3; i++)
    {
        p_minus_q[i] = source_generic_coord[i] - lce_spec->lococentre[i];
    }
    _dot_product( p_minus_q, lce_spec->primary_axis, &dest_generic_coord[0] );
    _dot_product( p_minus_q, lce_spec->secondary_axis, &dest_generic_coord[1] );
    _dot_product( p_minus_q, lce_spec->xprod_rs, &dest_generic_coord[2] );

    return status;
}
