
#include "srm.h"
#include "cimpl_BaseSRF.hpp"
#include "cimpl_BaseSRF3D.hpp"
#include "cimpl_BaseMapProjection.hpp"
#include "cimpl_BaseSRFwithEllipsoidalHeight.hpp"
#include "cimpl_TransverseMercator.hpp"
#include "srm_level_0_int_types.hpp"

extern "C"
{

SRM_Status_Code cimpl_SRM_TM_GetSRFParameters
(
    SRM_Object_Reference  this_object,
    SRM_TM_Parameters    *parameters /* OUT */
)
{
    if (this_object == NULL ||
        parameters == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else if (!INT_SRF(srf)->isA(BaseSRF::SRF_TYP_TM))
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else
    {
       try
       {
           *parameters =
              ((SRF_TransverseMercator *)INT_SRF(srf))->getSRFParameters();
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code SRM_TM_Create
(
          SRM_ORM_Code            orm_code,
          SRM_RT_Code             rt_code,
    const SRM_TM_Parameters      *parameters,
          SRM_TransverseMercator *new_srf  /* OUT */
)
{
    if (!new_srf)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    else if ((new_srf->methods = new SRM_TM_Method_List)==NULL)
    {
        return SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
    }
    new_srf->methods->AssociateSurfaceCoordinate          = &cimpl_SRM_AssociateSurfaceCoordinateEH;
    new_srf->methods->ChangeCoordinate3DSRF               = &cimpl_SRM_ChangeCoordinate3DSRF;
    new_srf->methods->ChangeCoordinate3DArraySRF          = &cimpl_SRM_ChangeCoordinate3DArraySRF;
    new_srf->methods->ChangeCoordinate3DSRFObject         = &cimpl_SRM_ChangeCoordinate3DSRFObject;
    new_srf->methods->ChangeCoordinate3DArraySRFObject    = &cimpl_SRM_ChangeCoordinate3DArraySRFObject;
    new_srf->methods->ChangeDirectionArraySRF             = &cimpl_SRM_ChangeDirectionArraySRF;
    new_srf->methods->ChangeDirectionSRF                  = &cimpl_SRM_ChangeDirectionSRF;
    new_srf->methods->ChangeOrientationSRF                = &cimpl_SRM_ChangeOrientationSRF;
    new_srf->methods->ChangeDirectionSRFObject            = &cimpl_SRM_ChangeDirectionSRFObject;
    new_srf->methods->ChangeOrientationSRFObject          = &cimpl_SRM_ChangeOrientationSRFObject;
    new_srf->methods->ChangeDirectionArraySRFObject       = &cimpl_SRM_ChangeDirectionArraySRFObject;
    new_srf->methods->ConvergenceOfTheMeridian            = &cimpl_SRM_ConvergenceOfTheMeridian;
    new_srf->methods->CreateCoordinate3D                  = &cimpl_SRM_CreateCoordinate3D;
    new_srf->methods->CreateDirection                     = &cimpl_SRM_CreateDirection;
    new_srf->methods->CreateOrientation                   = &cimpl_SRM_CreateOrientation;
    new_srf->methods->CreateLocalTangentSpaceEuclideanSRF = &cimpl_SRM_CreateLocalTangentSpaceEuclideanSRF;
    new_srf->methods->CreateSurfaceCoordinate             = &cimpl_SRM_CreateSurfaceCoordinateEH;
    new_srf->methods->Destroy                             = &cimpl_SRM_Destroy;
    new_srf->methods->DestroyCoordinate3D                 = &cimpl_SRM_DestroyCoordinate3D;
    new_srf->methods->DestroyDirection                    = &cimpl_SRM_DestroyDirection;
    new_srf->methods->DestroyOrientation                  = &cimpl_SRM_DestroyOrientation;
    new_srf->methods->DestroySurfaceCoordinate            = &cimpl_SRM_DestroySurfaceCoordinateEH;
    new_srf->methods->EuclideanDistance3D                 = &cimpl_SRM_EuclideanDistance3D;
    new_srf->methods->EuclideanDistanceEH                 = &cimpl_SRM_EuclideanDistanceEH;
    new_srf->methods->GeodesicDistance                    = &cimpl_SRM_GeodesicDistance;
    new_srf->methods->GetCoordinate3DValues               = &cimpl_SRM_GetCoordinate3DValues;
    new_srf->methods->GetCSCode                           = &cimpl_SRM_GetCSCode;
    new_srf->methods->GetA                                = &cimpl_SRM_GetA;
    new_srf->methods->GetF                                = &cimpl_SRM_GetF;
    new_srf->methods->GetDirectionValues                  = &cimpl_SRM_GetDirectionValues;
    new_srf->methods->GetExtendedValidGeodeticRegion      = &cimpl_SRM_GetExtendedValidGeodeticRegion;
    new_srf->methods->GetExtendedValidRegion              = &cimpl_SRM_GetExtendedValidRegion;
    new_srf->methods->GetNaturalSRFSMemberCode            = &cimpl_SRM_GetNaturalSRFSMemberCode;
    new_srf->methods->GetOrientationValues                = &cimpl_SRM_GetOrientationValues;
    new_srf->methods->GetORMCodes                         = &cimpl_SRM_GetORMCodes;
    new_srf->methods->GetSRFCodes                         = &cimpl_SRM_GetSRFCodes;
    new_srf->methods->GetSRFParameters                    = &cimpl_SRM_TM_GetSRFParameters;
    new_srf->methods->GetSurfaceCoordinateValues          = &cimpl_SRM_GetSurfaceCoordinateValuesEH;
    new_srf->methods->GetValidGeodeticRegion              = &cimpl_SRM_GetValidGeodeticRegion;
    new_srf->methods->GetValidRegion                      = &cimpl_SRM_GetValidRegion;
    new_srf->methods->MapAzimuth                          = &cimpl_SRM_MapAzimuth;
    new_srf->methods->PromoteSurfaceCoordinate            = &cimpl_SRM_PromoteSurfaceCoordinateEH;
    new_srf->methods->PointDistortion                     = &cimpl_SRM_PointDistortion;
    new_srf->methods->SetCoordinate3DValues               = &cimpl_SRM_SetCoordinate3DValues;
    new_srf->methods->SetExtendedValidGeodeticRegion      = &cimpl_SRM_SetExtendedValidGeodeticRegion;
    new_srf->methods->SetExtendedValidRegion              = &cimpl_SRM_SetExtendedValidRegion;
    new_srf->methods->SetValidGeodeticRegion              = &cimpl_SRM_SetValidGeodeticRegion;
    new_srf->methods->SetValidRegion                      = &cimpl_SRM_SetValidRegion;
    new_srf->methods->VerticalOffset                      = &cimpl_SRM_VerticalOffset;

    SRM_SRF         srf = new SRF_Wrapper;
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (srf == NULL)
    {
        status = SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
    }
    else
    {
        try
        {
            INT_SRF(srf) = SRF_TransverseMercator::create(orm_code,
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
