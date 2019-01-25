

#include "cimpl_BaseSRF.hpp"
#include "srm_level_0_int_types.hpp"
#include "cimpl_DestroySRF.hpp"

using namespace srm;

extern "C"
{
SRM_Status_Code cimpl_SRM_GetORMCodes
(
    SRM_Object_Reference  this_object,
    SRM_ORM_Code         *orm_code, /* OUT */
    SRM_RT_Code          *rt_code   /* OUT */
)
{
    if (this_object == NULL ||
        orm_code    == NULL ||
        rt_code     == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *orm_code = INT_SRF(srf)->getOrm();
            *rt_code = INT_SRF(srf)->getRt();
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_GetSRFCodes
(
    SRM_Object_Reference  this_object,
    SRM_SRFT_Code        *srft_code,     /* OUT srf template code */
    SRM_SRF_Code         *srf_code,      /* OUT srf code          */
    SRM_SRFS_Code_Info   *srfs_code_info /* OUT srf set code info */
)
{
    if (this_object    == NULL ||
        srft_code      == NULL ||
        srf_code       == NULL ||
        srfs_code_info == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            INT_SRF(srf)->getCodes(*srft_code,
                                   *srf_code,
                                   *srfs_code_info);
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_GetA
(
    SRM_Object_Reference  this_object,
    SRM_Long_Float       *major_semi_axis /* OUT cs code */
)
{
    if (this_object == NULL ||
        major_semi_axis == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *major_semi_axis = INT_SRF(srf)->getA();
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}

SRM_Status_Code cimpl_SRM_GetF
(
    SRM_Object_Reference  this_object,
    SRM_Long_Float       *flattening   /* OUT cs code */
)
{
    if (this_object == NULL ||
        flattening == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *flattening = INT_SRF(srf)->getF();
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_GetCSCode
(
    SRM_Object_Reference  this_object,
    SRM_CS_Code          *cs_code     /* OUT cs code */
)
{
    if (this_object == NULL ||
        cs_code == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *cs_code = INT_SRF(srf)->getCSCode();
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}

SRM_Status_Code cimpl_SRM_Destroy
(
    SRM_Object_Reference object     /* object to destroy*/
)
{
    if (object == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            SRM_SRFT_Code      srft;
            SRM_SRF_Code       std_srf;
            SRM_SRFS_Code_Info srfs_info;

            BaseSRF::SRF_ClassType class_type = INT_SRF(srf)->getClassType();
            INT_SRF(srf)->getCodes(srft, std_srf, srfs_info);

            status = cimpl_SRM_DestroySRF(object, class_type);
            INT_SRF(srf)->release();
            delete (SRF_Wrapper *)srf;

            if (std_srf != SRM_SRFCOD_UNSPECIFIED ||
                srfs_info.srfs_code != SRM_SRFSCOD_UNSPECIFIED)
            {
                delete((SRM_BaseWrapper *)object);
            }
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}

}    // end Extern "C"
