
#include "srm.h"
#include "cimpl_BaseSRF.hpp"
#include "cimpl_BaseSRF3D.hpp"
#include "cimpl_BaseSRFwithTangentPlaneSurface.hpp"
#include "srm_level_0_int_types.hpp"

extern "C"
{

SRM_Status_Code cimpl_SRM_AssociateSurfaceCoordinateTPS
(
          SRM_Object_Reference   this_object,
    const SRM_Coordinate3D      *coordinate,
          SRM_SurfaceCoordinate *on_surface_coordinate /* OUT */
)
{
    if (this_object           == 0 ||
        coordinate            == 0 ||
        on_surface_coordinate == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle source_coordinate =
      (SRM_Coordinate_Handle)((SRM_Coordinate3D *)coordinate)->state;

    SRM_Coordinate_Handle surf_coord =
      (SRM_Coordinate_Handle)(on_surface_coordinate)->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(source_coordinate) ||
        !VALID_COORD_HANDLE(surf_coord))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else if (!INT_SRF(srf)->isA(BaseSRF::SRF_TYP_WITH_TANGENT_PLANE_SURFACE))
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
            ((BaseSRF_WithTangentPlaneSurface *) INT_SRF(srf))->
              getAssociatedSurfaceCoordinate(*((Coord3D *)INT_COORD(source_coordinate)),
                                              *((CoordSurf *)INT_COORD(surf_coord)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_CreateSurfaceCoordinateTPS
(
    SRM_Object_Reference    this_object,
    SRM_Long_Float          first_coordinate_component,
    SRM_Long_Float          second_coordinate_component,
    SRM_SurfaceCoordinate  *new_coordinate               /* OUT */
)
{
    if (this_object == 0 || new_coordinate == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !INT_SRF(srf)->isA(BaseSRF::SRF_TYP_WITH_TANGENT_PLANE_SURFACE))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        Coord_Wrapper * new_coord = new Coord_Wrapper;

        if (new_coord == 0)
        {
            return SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
        }

        try
        {
            INT_COORD(new_coord) = ((BaseSRF_WithTangentPlaneSurface *)INT_SRF(srf))->
              createSurfaceCoordinate(first_coordinate_component, second_coordinate_component);

            new_coord->_magic_number = SRM_COORD_MAGIC_NUMBER;

            new_coordinate->state = (void *)new_coord;
            new_coordinate->methods = new SRM_SurfaceCoordinate_Method_List;
            new_coordinate->methods->Destroy = &cimpl_SRM_DestroyThisSurfaceCoordinateTPS;

            return SRM_STATCOD_SUCCESS;
        }
        catch (Exception e)
        {
            delete new_coord;
            return e.getCode();
        }
    }
}


SRM_Status_Code cimpl_SRM_DestroyThisSurfaceCoordinateTPS
(
    SRM_Object_Reference coordinate
)
{
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (coordinate == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Coordinate_Handle tmp_coordinate =
      ((SRM_SurfaceCoordinate *)coordinate)->state;

    if (!VALID_COORD_HANDLE(tmp_coordinate))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    Coord *tmp_coord = INT_COORD(tmp_coordinate);

    if (tmp_coord->isA(Coord:: COORD_TYP_SURFACE) ||
        !(tmp_coord->isA(Coord::COORD_TYP_SURF_LTSAS) ||
          tmp_coord->isA(Coord::COORD_TYP_SURF_LTSE)  ||
          tmp_coord->isA(Coord::COORD_TYP_SURF_LTSC)))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }

    try
    {
        BaseSRF_WithTangentPlaneSurface *my_srf  = ((BaseSRF_WithTangentPlaneSurface *)tmp_coord->getSRF());
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
    return status;
}


SRM_Status_Code cimpl_SRM_DestroySurfaceCoordinateTPS
(
    SRM_Object_Reference this_object,
    SRM_Object_Reference coordinate
)
{
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (this_object == 0 || coordinate  == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle tmp_coordinate =
      ((SRM_SurfaceCoordinate *)coordinate)->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(tmp_coordinate))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    Coord *tmp_coord = INT_COORD(tmp_coordinate);

    if (tmp_coord->isA(Coord:: COORD_TYP_SURFACE) ||
        !(tmp_coord->isA(Coord::COORD_TYP_SURF_LTSAS) ||
          tmp_coord->isA(Coord::COORD_TYP_SURF_LTSE)  ||
          tmp_coord->isA(Coord::COORD_TYP_SURF_LTSC)))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }

    try
    {
        ((BaseSRF_WithTangentPlaneSurface *)INT_SRF(srf))->freeSurfaceCoordinate((CoordSurf *)tmp_coord);
        delete (Coord_Wrapper *)tmp_coordinate;
        delete ((SRM_SurfaceCoordinate *)coordinate)->methods;
        ((SRM_SurfaceCoordinate *)coordinate)->methods = 0;
        ((SRM_SurfaceCoordinate *)coordinate)->state   = 0;
    }
    catch(Exception e)
    {
        status = e.getCode();
    }
    return status;
}


SRM_Status_Code cimpl_SRM_EuclideanDistanceTPS
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *source_coordinate,
    const SRM_SurfaceCoordinate *target_coordinate,
          SRM_Long_Float        *distance           /* OUT */
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
      (SRM_Coordinate_Handle)source_coordinate->state;

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


SRM_Status_Code cimpl_SRM_GetSurfaceCoordinateValuesTPS
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *coordinate,
          SRM_Long_Float        *first_coordinate_component,  /* OUT */
          SRM_Long_Float        *second_coordinate_component  /* OUT */
)
{
    if (this_object                 == 0  ||
        coordinate                  == 0  ||
        first_coordinate_component  == 0  ||
        second_coordinate_component == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle tmp_coordinate = (SRM_Coordinate_Handle)coordinate->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(tmp_coordinate))
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

            status = SRM_STATCOD_SUCCESS;
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_PromoteSurfaceCoordinateTPS
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Coordinate3D      *coordinate          /* OUT */
)
{
    if (this_object        == 0 ||
        surface_coordinate == 0 ||
        coordinate         == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    SRM_Coordinate_Handle source_coordinate =
      (SRM_Coordinate_Handle)surface_coordinate->state;

    if (!VALID_SRF_HANDLE(srf) ||
       !VALID_COORD_HANDLE(source_coordinate))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else if (!INT_SRF(srf)->isA(BaseSRF::SRF_TYP_WITH_TANGENT_PLANE_SURFACE))
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

            ((BaseSRF_WithTangentPlaneSurface *) INT_SRF(srf))->
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

} // end Extern "C"
