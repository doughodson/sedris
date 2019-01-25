
#include "srm.h"
#include "cimpl_BaseMapProjection.hpp"
#include "srm_level_0_int_types.hpp"

using namespace srm;

extern "C"
{

SRM_Status_Code cimpl_SRM_ConvergenceOfTheMeridian
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Long_Float        *gamma     /* OUT */
)
{
    if (this_object        == NULL ||
        surface_coordinate == NULL ||
        gamma              == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;
    SRM_Coordinate_Handle origin_coordinate =
      (SRM_Coordinate_Handle)surface_coordinate->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(origin_coordinate) ||
        !(INT_COORD(origin_coordinate)->isA(Coord::COORD_TYP_SURFACE)) ||
        !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_MAP_PROJECTION)))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *gamma = ((BaseSRF_MapProjection *)INT_SRF(srf))->
              calculateConvergenceOfTheMeridian(*((CoordSurf *)INT_COORD(origin_coordinate)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_GetExtendedValidGeodeticRegion
(
   SRM_Object_Reference  this_object,
   SRM_Integer           component,
   SRM_Interval_Type    *type,           /* OUT */
   SRM_Long_Float       *extended_lower, /* OUT */
   SRM_Long_Float       *lower,          /* OUT */
   SRM_Long_Float       *upper,          /* OUT */
   SRM_Long_Float       *extended_upper  /* OUT */
)
{
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (this_object     == NULL ||
        type            == NULL ||
        extended_lower  == NULL ||
        lower           == NULL ||
        upper           == NULL ||
        extended_upper  == NULL ||
        (component < 1) || (component > 2))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if(!VALID_SRF_HANDLE(srf) ||
       !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_MAP_PROJECTION)) )
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else
    {
        try
        {
            ((BaseSRF_MapProjection *)INT_SRF(srf))->
              getExtendedValidGeodeticRegion( component,
                                              *type,
                                              *extended_lower,
                                              *lower,
                                              *upper,
                                              *extended_upper);
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_GetValidGeodeticRegion
(
     SRM_Object_Reference  this_object,
     SRM_Integer           component,
     SRM_Interval_Type    *type,   /* OUT */
     SRM_Long_Float       *lower,  /* OUT */
     SRM_Long_Float       *upper   /* OUT */
)
{
    if (this_object == NULL ||
        type        == NULL ||
        lower       == NULL ||
        upper       == NULL ||
        (component < 1) || (component > 2))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if(!VALID_SRF_HANDLE(srf) ||
       !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_MAP_PROJECTION)))
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else
    {
        try
        {
            ((BaseSRF_MapProjection *)INT_SRF(srf))->
              getValidGeodeticRegion( component,
                                      *type,
                                      *lower,
                                      *upper);
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_MapAzimuth
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
    const SRM_SurfaceCoordinate *target_coordinate,
          SRM_Long_Float        *azimuth  /* OUT */
)
{
    if (this_object        == NULL ||
        surface_coordinate == NULL ||
        target_coordinate  == NULL ||
        azimuth == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;
    SRM_Coordinate_Handle coord_from =
      (SRM_Coordinate_Handle)surface_coordinate->state;
    SRM_Coordinate_Handle coord_to =
      (SRM_Coordinate_Handle)target_coordinate->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(coord_from) ||
        !VALID_COORD_HANDLE(coord_to) ||
        !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_MAP_PROJECTION)))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *azimuth = ((BaseSRF_MapProjection *)INT_SRF(srf))->
              calculateMapAzimuth(*((CoordSurf *)INT_COORD(coord_from)),
                                  *((CoordSurf *)INT_COORD(coord_to)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_PointDistortion
(
          SRM_Object_Reference   this_object,
    const SRM_SurfaceCoordinate *surface_coordinate,
          SRM_Long_Float        *scale   /* OUT */
)
{
    if (this_object        == NULL ||
        surface_coordinate == NULL ||
        scale              == NULL)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;
    SRM_Coordinate_Handle coordinate =
      (SRM_Coordinate_Handle)surface_coordinate->state;

    if (!VALID_SRF_HANDLE(srf) ||
        !VALID_COORD_HANDLE(coordinate) ||
        !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_MAP_PROJECTION)))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else
    {
        try
        {
            *scale = ((BaseSRF_MapProjection *)INT_SRF( srf ))->
              calculatePointDistortion(*((CoordSurf *)INT_COORD(coordinate)));
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_SetExtendedValidGeodeticRegion
(
    SRM_Object_Reference this_object,
    SRM_Integer          component,
    SRM_Interval_Type    type,
    SRM_Long_Float       extended_lower,
    SRM_Long_Float       lower,
    SRM_Long_Float       upper,
    SRM_Long_Float       extended_upper
)
{
    if (this_object == NULL ||
        (component < 1) || (component > 2))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if(!VALID_SRF_HANDLE(srf) ||
       !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_MAP_PROJECTION)))
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else
    {
        try
        {
            ((BaseSRF_MapProjection *)INT_SRF(srf))->
              setExtendedValidGeodeticRegion( component,
                                              type,
                                              extended_lower,
                                              lower,
                                              upper,
                                              extended_upper);
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code cimpl_SRM_SetValidGeodeticRegion
(
    SRM_Object_Reference this_object,
    SRM_Integer          component,
    SRM_Interval_Type    type,
    SRM_Long_Float       lower,
    SRM_Long_Float       upper
)
{
    if (this_object == NULL ||
        (component < 1) || (component > 2))
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if(!VALID_SRF_HANDLE ( srf ) ||
       !(INT_SRF(srf)->isA(BaseSRF::SRF_TYP_MAP_PROJECTION)) )
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else
    {
        try
        {
            ((BaseSRF_MapProjection * )INT_SRF( srf ))->
              setValidGeodeticRegion( component,
                                      type,
                                      lower,
                                      upper );
        }
        catch ( Exception e )
        {
            status = e.getCode();
        }
    }
    return status;
}

}    // end Extern "C"
