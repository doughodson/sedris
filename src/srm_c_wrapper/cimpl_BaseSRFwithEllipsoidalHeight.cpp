

#include "srm.h"
#include "cimpl_BaseSRF.hpp"
#include "cimpl_BaseSRF3D.hpp"
#include "cimpl_BaseSRFwithEllipsoidalHeight.hpp"
#include "cimpl_BaseSRFwithTangentPlaneSurface.hpp"
#include "cimpl_LocalTangentSpaceEuclidean.hpp"
#include "srm_level_0_int_types.hpp"

using namespace srm;

extern "C"
{

SRM_Status_Code cimpl_SRM_AssociateSurfaceCoordinateEH
(
          SRM_Object_Reference   this_object,
    const SRM_Coordinate3D      *coordinate,
          SRM_SurfaceCoordinate *on_surface_coordinate /* OUT */
)
{
    if (this_object == 0 ||
        coordinate  == 0 ||
        on_surface_coordinate == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF source_srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle source_coordinate =
      (SRM_Coordinate_Handle)(coordinate)->state;

    SRM_Coordinate_Handle surf_coord =
      (SRM_Coordinate_Handle)(on_surface_coordinate)->state;

    if (!VALID_SRF_HANDLE(source_srf) ||
        !VALID_COORD_HANDLE(source_coordinate) ||
        !VALID_COORD_HANDLE(surf_coord))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else if (!INT_SRF(source_srf)->isA(BaseSRF::SRF_TYP_WITH_ELLIPSOIDAL_HEIGHT))
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else if (!INT_COORD(source_coordinate)->isA(Coord::COORD_TYP_THREE_D))
    {
        status = SRM_STATCOD_INVALID_SOURCE_COORDINATE;
    }
    else if (!INT_COORD(surf_coord)->isA(Coord::COORD_TYP_SURFACE))
    {
        status = SRM_STATCOD_INVALID_TARGET_COORDINATE;
    }
    else
    {
        try
        {
            ((BaseSRF_WithEllipsoidalHeight *) INT_SRF(source_srf))->
              getAssociatedSurfaceCoordinate
              (*((Coord3D *)INT_COORD(source_coordinate)),
               *((CoordSurf *)INT_COORD(surf_coord)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_CreateLocalTangentSpaceEuclideanSRF
(
          SRM_Object_Reference            this_object,
    const SRM_SurfaceCoordinate          *surface_coordinate,
          SRM_Long_Float                  azimuth,
          SRM_Long_Float                  false_x_origin,
          SRM_Long_Float                  false_y_origin,
          SRM_Long_Float                  offset_height,
          SRM_LocalTangentSpaceEuclidean *local_tangent_Euclidean_srf  /* OUT */
)
{
    if (this_object                 == 0 ||
        surface_coordinate          == 0 ||
        local_tangent_Euclidean_srf == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF this_srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;
    SRM_Coordinate_Handle coordinate =
      (SRM_Coordinate_Handle)((SRM_BaseWrapper *)surface_coordinate)->state;

    if (!VALID_SRF_HANDLE(this_srf) ||
        !VALID_COORD_HANDLE(coordinate))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        SRF_Wrapper *srf = new SRF_Wrapper;

        if (srf == 0)
        {
            status = SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
        }
        else
        {
            try
            {
                INT_SRF(srf) = ((BaseSRF_WithEllipsoidalHeight *)INT_SRF(this_srf))->
                  createLocalTangentSpaceEuclideanSRF(*((CoordSurf *)INT_COORD(coordinate)),
                                                       azimuth,
                                                       false_x_origin,
                                                       false_y_origin,
                                                       offset_height);

                ((SRF_Wrapper *)srf)->_magic_number = SRM_SRF_MAGIC_NUMBER;
                local_tangent_Euclidean_srf->state = (void *)srf;

                local_tangent_Euclidean_srf->methods = new SRM_LTSE_Method_List;
                local_tangent_Euclidean_srf->methods->AssociateSurfaceCoordinate  = &cimpl_SRM_AssociateSurfaceCoordinateTPS;
                local_tangent_Euclidean_srf->methods->ChangeCoordinate3DSRF       = &cimpl_SRM_ChangeCoordinate3DSRF;
                local_tangent_Euclidean_srf->methods->ChangeCoordinate3DSRFObject = &cimpl_SRM_ChangeCoordinate3DSRFObject;
                local_tangent_Euclidean_srf->methods->ChangeDirectionSRF          = &cimpl_SRM_ChangeDirectionSRF;
                local_tangent_Euclidean_srf->methods->ChangeDirectionSRFObject    = &cimpl_SRM_ChangeDirectionSRFObject;
                local_tangent_Euclidean_srf->methods->CreateCoordinate3D          = &cimpl_SRM_CreateCoordinate3D;
                local_tangent_Euclidean_srf->methods->CreateDirection             = &cimpl_SRM_CreateDirection;
                local_tangent_Euclidean_srf->methods->CreateSurfaceCoordinate     = &cimpl_SRM_CreateSurfaceCoordinateTPS;
                local_tangent_Euclidean_srf->methods->Destroy                     = &cimpl_SRM_Destroy;
                local_tangent_Euclidean_srf->methods->DestroyCoordinate3D         = &cimpl_SRM_DestroyCoordinate3D;
                local_tangent_Euclidean_srf->methods->DestroyDirection            = &cimpl_SRM_DestroyDirection;
                local_tangent_Euclidean_srf->methods->DestroySurfaceCoordinate    = &cimpl_SRM_DestroySurfaceCoordinateTPS;
                local_tangent_Euclidean_srf->methods->EuclideanDistance3D         = &cimpl_SRM_EuclideanDistance3D;
                local_tangent_Euclidean_srf->methods->EuclideanDistanceTPS        = &cimpl_SRM_EuclideanDistanceTPS;
                local_tangent_Euclidean_srf->methods->GetCoordinate3DValues       = &cimpl_SRM_GetCoordinate3DValues;
                local_tangent_Euclidean_srf->methods->GetCSCode                   = &cimpl_SRM_GetCSCode;
                local_tangent_Euclidean_srf->methods->GetDirectionValues          = &cimpl_SRM_GetDirectionValues;
                local_tangent_Euclidean_srf->methods->GetExtendedValidRegion      = &cimpl_SRM_GetExtendedValidRegion;
                local_tangent_Euclidean_srf->methods->GetORMCodes                 = &cimpl_SRM_GetORMCodes;
                local_tangent_Euclidean_srf->methods->GetSRFCodes                 = &cimpl_SRM_GetSRFCodes;
                local_tangent_Euclidean_srf->methods->GetSRFParameters            = &cimpl_SRM_LTSE_GetSRFParameters;
                local_tangent_Euclidean_srf->methods->GetSurfaceCoordinateValues  = &cimpl_SRM_GetSurfaceCoordinateValuesTPS;
                local_tangent_Euclidean_srf->methods->GetValidRegion              = &cimpl_SRM_GetValidRegion;
                local_tangent_Euclidean_srf->methods->PromoteSurfaceCoordinate    = &cimpl_SRM_PromoteSurfaceCoordinateTPS;
                local_tangent_Euclidean_srf->methods->SetCoordinate3DValues       = &cimpl_SRM_SetCoordinate3DValues;
                local_tangent_Euclidean_srf->methods->SetExtendedValidRegion      = &cimpl_SRM_SetExtendedValidRegion;
                local_tangent_Euclidean_srf->methods->SetValidRegion              = &cimpl_SRM_SetValidRegion;
            }
            catch (Exception e)
            {
                delete srf;
                status = e.getCode();
            }
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_CreateSurfaceCoordinateEH
(
    SRM_Object_Reference   this_object,
    SRM_Long_Float         first_coordinate_component,
    SRM_Long_Float         second_coordinate_component,
    SRM_SurfaceCoordinate *new_coordinate /* OUT */
)
{
    if (this_object    == 0  ||
        new_coordinate == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (!VALID_SRF_HANDLE(srf) ||
        !INT_SRF(srf)->isA(BaseSRF::SRF_TYP_WITH_ELLIPSOIDAL_HEIGHT))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        Coord_Wrapper * new_coord = new Coord_Wrapper;

        if (new_coord == 0)
        {
            status = SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
        }
        else
        {
            try
            {
                INT_COORD(new_coord) = ((BaseSRF_WithEllipsoidalHeight *)INT_SRF(srf))->
                  createSurfaceCoordinate(first_coordinate_component,
                                          second_coordinate_component);

                new_coord->_magic_number = SRM_COORD_MAGIC_NUMBER;

                new_coordinate->methods          = new SRM_SurfaceCoordinate_Method_List;
                new_coordinate->methods->Destroy = &cimpl_SRM_DestroyThisSurfaceCoordinateEH;
                new_coordinate->state            = (void *)new_coord;
            }
            catch (Exception e)
            {
                delete new_coord;
                status = e.getCode();
            }
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_DestroyThisSurfaceCoordinateEH
(
    SRM_Object_Reference coordinate
)
{
    if (coordinate == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_Coordinate_Handle tmp_coordinate = (SRM_Coordinate_Handle)((SRM_SurfaceCoordinate *)coordinate)->state;

    if (!VALID_COORD_HANDLE(tmp_coordinate))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        Coord *tmp_coord = INT_COORD(tmp_coordinate);

        if (!tmp_coord->isA(Coord::COORD_TYP_SURFACE) &&
             tmp_coord->isA(Coord::COORD_TYP_SURF_LTSAS) ||
             tmp_coord->isA(Coord::COORD_TYP_SURF_LTSE) ||
             tmp_coord->isA(Coord::COORD_TYP_SURF_LTSC))
        {
            status = SRM_STATCOD_INVALID_INPUT;
        }
        else
        {
            try
            {
                BaseSRF_WithEllipsoidalHeight *my_srf  = ((BaseSRF_WithEllipsoidalHeight *)tmp_coord->getSRF());
                my_srf->freeSurfaceCoordinate((CoordSurf *)tmp_coord);
                delete (Coord_Wrapper *)tmp_coordinate;
                delete ((SRM_SurfaceCoordinate *)coordinate)->methods;
                ((SRM_SurfaceCoordinate *)coordinate)->methods = 0;
                ((SRM_SurfaceCoordinate *)coordinate)->state   = 0;
            }
            catch(Exception e)
            {
                status = e.getCode();
            }
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_DestroySurfaceCoordinateEH
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
)
{
    if (this_object == 0 ||
        coordinate  == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_Coordinate_Handle tmp_coordinate = (SRM_Coordinate_Handle)((SRM_SurfaceCoordinate *)coordinate)->state;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(tmp_coordinate))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        Coord *tmp_coord = INT_COORD(tmp_coordinate);

        if (!tmp_coord->isA(Coord::COORD_TYP_SURFACE)   ||
            tmp_coord->isA(Coord::COORD_TYP_SURF_LTSAS) ||
            tmp_coord->isA(Coord::COORD_TYP_SURF_LTSE) ||
            tmp_coord->isA(Coord::COORD_TYP_SURF_LTSC))
        {
            status = SRM_STATCOD_INVALID_INPUT;
        }
        else
        {
            try
            {
                ((BaseSRF_WithEllipsoidalHeight *)INT_SRF(srf))->freeSurfaceCoordinate((CoordSurf *)tmp_coord);
                delete (Coord_Wrapper *)tmp_coordinate;
                delete ((SRM_SurfaceCoordinate *)coordinate)->methods;
                ((SRM_SurfaceCoordinate *)coordinate)->methods = 0;
                ((SRM_SurfaceCoordinate *)coordinate)->state   = 0;
            }
            catch(Exception e)
            {
                status = e.getCode();
            }
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_EuclideanDistanceEH
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *source_coordinate,
    const SRM_SurfaceCoordinate *target_coordinate,
          SRM_Long_Float        *distance /* OUT */
)
{
    if (this_object       == 0 ||
        source_coordinate == 0 ||
        target_coordinate == 0 ||
        distance          == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle origin_coordinate =
      (SRM_Coordinate_Handle)((SRM_BaseWrapper *)source_coordinate)->state;

    SRM_Coordinate_Handle destination_coordinate =
      (SRM_Coordinate_Handle)target_coordinate->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(origin_coordinate) ||
        !VALID_COORD_HANDLE(destination_coordinate) ||
        (INT_COORD(destination_coordinate)->getSRF() != INT_COORD(origin_coordinate)->getSRF()))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *distance = INT_SRF(srf)->
              calculateEuclideanDistance(*(INT_COORD(origin_coordinate)),
                                         *(INT_COORD(destination_coordinate)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_GeodesicDistance
(
         SRM_Object_Reference   this_object,
   const SRM_SurfaceCoordinate *source_coordinate,
   const SRM_SurfaceCoordinate *target_coordinate,
         SRM_Long_Float        *distance  /* OUT */
)
{
    if (this_object       == 0 ||
        source_coordinate == 0 ||
        target_coordinate == 0 ||
        distance          == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle coord_from =
      (SRM_Coordinate_Handle)((SRM_BaseWrapper *)source_coordinate)->state;

    SRM_Coordinate_Handle coord_to   =
      (SRM_Coordinate_Handle)((SRM_BaseWrapper *)target_coordinate)->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(coord_from) ||
        !VALID_COORD_HANDLE(coord_to) ||
        !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_WITH_ELLIPSOIDAL_HEIGHT)))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *distance = ((BaseSRF_WithEllipsoidalHeight *)INT_SRF(srf))->
              calculateGeodesicDistance(*((CoordSurf *)INT_COORD(coord_from)),
                                        *((CoordSurf *)INT_COORD(coord_to)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_GetSurfaceCoordinateValuesEH
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *coordinate,
          SRM_Long_Float        *first_coordinate_component,  /* OUT */
          SRM_Long_Float        *second_coordinate_component  /* OUT */
)
{
    if (this_object                 == 0 ||
        coordinate                  == 0 ||
        first_coordinate_component  == 0 ||
        second_coordinate_component == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_Coordinate_Handle tmp_coordinate = (SRM_Coordinate_Handle)coordinate->state;

    if (!VALID_COORD_HANDLE(tmp_coordinate))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            const SRM_Long_Float *values = ((CoordSurf *) INT_COORD(tmp_coordinate))->getValues();

            *first_coordinate_component  = values[0];
            *second_coordinate_component = values[1];
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_PromoteSurfaceCoordinateEH
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Coordinate3D      *coordinate /* OUT */
)
{
    if (this_object        == 0 ||
        surface_coordinate == 0 ||
        coordinate         == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF source_srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle source_coordinate = surface_coordinate->state;

    if (!VALID_SRF_HANDLE(source_srf) ||
        !VALID_COORD_HANDLE(source_coordinate))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else if (!INT_SRF(source_srf)->isA(BaseSRF::SRF_TYP_WITH_ELLIPSOIDAL_HEIGHT))
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else if (!INT_COORD(source_coordinate)->isA(Coord::COORD_TYP_SURFACE))
    {
        status = SRM_STATCOD_INVALID_SOURCE_COORDINATE;
    }
    else
    {
        try
        {
            SRM_Coordinate_Handle tmp_coord = (SRM_Coordinate_Handle)coordinate->state;

            ((BaseSRF_WithEllipsoidalHeight *) INT_SRF(source_srf))->
              getPromotedSurfaceCoordinate(*((CoordSurf *)INT_COORD(source_coordinate)),
                                            *((Coord3D *)INT_COORD(tmp_coord)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_VerticalOffset
(
          SRM_Object_Reference   this_object,
          SRM_DSS_Code           dss_code,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Long_Float        *separation /* OUT */
)
{
    if (this_object        == 0 ||
        surface_coordinate == 0 ||
        separation         == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle tmp_coordinate =
      (SRM_Coordinate_Handle)surface_coordinate->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(tmp_coordinate) ||
        !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_WITH_ELLIPSOIDAL_HEIGHT)))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *separation = ((BaseSRF_WithEllipsoidalHeight *)INT_SRF(srf))->
              calculateVerticalSeparationOffset(dss_code,*((CoordSurf *)INT_COORD(tmp_coordinate)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}

}    // end Extern "C"
