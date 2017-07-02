
#include "srm.h"
#include "cimpl_BaseSRF.hpp"
#include "cimpl_BaseSRF3D.hpp"
#include "cimpl_BaseSRFwithTangentPlaneSurface.hpp"
#include "cimpl_BaseSRFwithEllipsoidalHeight.hpp"
#include "cimpl_BaseMapProjection.hpp"
#include "cimpl_TransverseMercator.hpp"
#include "cimpl_LambertConformalConic.hpp"
#include "srm_level_0_int_types.hpp"

extern "C"
{

SRM_Status_Code SRM_QuerySRFTSupport
(
    SRM_SRFT_Code  srft_code,
    SRM_Boolean   *supported  /* OUT */
)
{
    if (supported  == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    try
    {
        if (BaseSRF::querySRFTSupport(srft_code))
            *supported = SRM_TRUE;
        else
            *supported = SRM_FALSE;
    }
    catch (Exception e)
    {
        status = e.getCode();
    }
    return status;
}

}    // end Extern "C"
