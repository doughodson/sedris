
#include "srm.h"
#include "cimpl_BaseSRF.hpp"
#include "cimpl_BaseSRF2D.hpp"
#include "cimpl_LocalSpaceRectangular2D.hpp"
#include "srm_level_0_int_types.hpp"

extern "C"
{

SRM_Status_Code cimpl_SRM_LSR2D_GetSRFParameters
(
    SRM_Object_Reference   this_object,
    SRM_LSR_2D_Parameters *parameters  /* OUT */
)
{
    if (this_object == NULL ||
        parameters  == NULL)
    {
       return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else if(!INT_SRF(srf)->isA(BaseSRF::SRF_TYP_LSR_2D))
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else
    {
        try
        {
            *parameters =
               ((SRF_LocalSpaceRectangular2D *)INT_SRF( srf ))->getSRFParameters();
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code SRM_LSR_2D_Create
(
          SRM_ORM_Code                 orm_code,
          SRM_RT_Code                  rt_code,
    const SRM_LSR_2D_Parameters       *parameters,
          SRM_LocalSpaceRectangular2D *new_srf    /* OUT */
)
{
    if (!new_srf)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    else if ((new_srf->methods = new SRM_LSR_2D_Method_List)==NULL)
    {
        return SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
    }
    new_srf->methods->ChangeCoordinate2DArraySRF       = &cimpl_SRM_ChangeCoordinate2DArraySRF;
    new_srf->methods->ChangeCoordinate2DArraySRFObject = &cimpl_SRM_ChangeCoordinate2DArraySRFObject;
    new_srf->methods->ChangeCoordinate2DSRF            = &cimpl_SRM_ChangeCoordinate2DSRF;
    new_srf->methods->ChangeCoordinate2DSRFObject      = &cimpl_SRM_ChangeCoordinate2DSRFObject;
    new_srf->methods->CreateCoordinate2D               = &cimpl_SRM_CreateCoordinate2D;
    new_srf->methods->Destroy                          = &cimpl_SRM_Destroy;
    new_srf->methods->DestroyCoordinate2D              = &cimpl_SRM_DestroyCoordinate2D;
    new_srf->methods->EuclideanDistance2D              = &cimpl_SRM_EuclideanDistance2D;
    new_srf->methods->GetCoordinate2DValues            = &cimpl_SRM_GetCoordinate2DValues;
    new_srf->methods->GetCSCode                        = &cimpl_SRM_GetCSCode;
    new_srf->methods->GetORMCodes                      = &cimpl_SRM_GetORMCodes;
    new_srf->methods->GetSRFCodes                      = &cimpl_SRM_GetSRFCodes;
    new_srf->methods->GetSRFParameters                 = &cimpl_SRM_LSR2D_GetSRFParameters;
    new_srf->methods->SetCoordinate2DValues            = &cimpl_SRM_SetCoordinate2DValues;

    SRM_SRF         srf    = new SRF_Wrapper;
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (srf == NULL)
    {
        status = SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
    }
    else
    {
        try
        {
            INT_SRF(srf) = SRF_LocalSpaceRectangular2D::create(orm_code,
                                                               rt_code,
                                                               *parameters);

            ((SRF_Wrapper *)srf)->_magic_number = SRM_SRF_MAGIC_NUMBER;
            new_srf->state = (void *)srf;
        }
        catch (Exception e)
        {
            delete (SRF_Wrapper *)srf;
            srf = NULL;
            status = e.getCode();
        }
    }
    return status;
}

}    // end Extern "C"
