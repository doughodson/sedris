
/*
 * SRM API
 *
 * FILE       : srm_pd.cpp
 *
 * PROGRAMMERS: Cameron Kellough (SRI)
 *
 * SRM SDK Release 4.1.4 - July 1, 2011
 *
 * - SRM spec. 4.1
 *
 * DESCRIPTION:
 *   This file is internal to the SRM API.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../support/srm_internal.h"

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangePD_CD
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangePD_CD
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    // pd_lon = - cd_lon
    dest_generic_coord[0] = - source_generic_coord[0];

    // pd_lat = cd_lat
    dest_generic_coord[1] = source_generic_coord[1];

    // height - height
    dest_generic_coord[2] = source_generic_coord[2];

    return status;
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeCD_PD
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeCD_PD
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    // cd_lon = - pd_lon
    dest_generic_coord[0] = - source_generic_coord[0];

    // cd_lat = pd_lat
    dest_generic_coord[1] = source_generic_coord[1];

    // height - height
    dest_generic_coord[2] = source_generic_coord[2];

    return status;
}
