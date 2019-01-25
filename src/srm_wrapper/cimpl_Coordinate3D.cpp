
#include "srm.h"
#include "srm_level_0_int_types.hpp"

extern "C"
{

SRM_Status_Code cimpl_SRM_GetMGRS
(
          SRM_Object_Reference   this_object,
          SRM_Integer            precision,
    const char                 **mgrs_string
)
{
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (this_object == 0 || mgrs_string == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_SRF coord = (SRM_SRF)((SRM_Coordinate3D *)this_object)->state;

    if(!VALID_COORD_HANDLE( coord ))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *mgrs_string = ((srm::Coord3D*)INT_COORD( coord ))->getMGRS(precision);
        }
        catch (Exception ex)
        {
            status = ex.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_SetCoord
(
          SRM_Object_Reference  this_object,
    const char                 *mgrs_string  /* IN params */
)
{
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (this_object == 0 || mgrs_string == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_SRF coord = (SRM_SRF)((SRM_Coordinate3D *)this_object)->state;

    if (!VALID_COORD_HANDLE( coord ))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            ((srm::Coord3D*)INT_COORD( coord ))->setCoord(mgrs_string);
        }
        catch (Exception ex)
        {
            status =  ex.getCode();
        }
    }
    return status;
}

} // end Extern "C"
