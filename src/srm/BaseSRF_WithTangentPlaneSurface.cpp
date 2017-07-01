
#include "srf_all.hpp"
#include "Exception.hpp"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

void BaseSRF_WithTangentPlaneSurface::getSurfaceCoordinateValues
(
    const CoordSurf      &coord_surf,
          SRM_Long_Float &coord_surf_comp1,
          SRM_Long_Float &coord_surf_comp2
) const
{
    if (coord_surf.getSRF() != (BaseSRF*)this)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE, "getSurfaceCoordinateValues: Surface coordinate associated with a different SRF");

    coord_surf_comp1 = coord_surf.getValues()[0];
    coord_surf_comp2 = coord_surf.getValues()[1];
}


void BaseSRF_WithTangentPlaneSurface::freeSurfaceCoordinate(CoordSurf *coord_surf)
{
    if (coord_surf->getSRF() != (BaseSRF*)this)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE, "freeSurfaceCoordinate: Surface coordinate associated with a different SRF");

    delete(coord_surf);
}

void BaseSRF_WithTangentPlaneSurface::getAssociatedSurfaceCoordinate
(
    const Coord3D   &coord,
          CoordSurf &on_surface_coord
)
{
    SRM_Long_Float coord_surf_values[2];

    if (coord.getSRF() != (BaseSRF*)this)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE, "getAssociatedSurfaceCoordinate: Source coordinate associated with a different SRF");
    if (on_surface_coord.getSRF() != (BaseSRF*)this)
        throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE, "getAssociatedSurfaceCoordinate: Target coordinate associated with a different SRF");

    // use only the first two component values from the 3d coordinate
    coord_surf_values[0] = coord.getValues()[0];
    coord_surf_values[1] = coord.getValues()[1];

    on_surface_coord.setValues(coord_surf_values);
}


void BaseSRF_WithTangentPlaneSurface::getPromotedSurfaceCoordinate
(
    const CoordSurf &surf_coord,
            Coord3D &three_d_coord
)
{
    SRM_Long_Float coord_3d_values[3];

    if (surf_coord.getSRF() != (BaseSRF*)this)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE, "getPromotedSurfaceCoordinate: Source coordinate associated with a different SRF");
    if (three_d_coord.getSRF() != (BaseSRF*)this)
        throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE, "getPromotedSurfaceCoordinate: Target coordinate associated with a different SRF");

    // the component values from the 2d coordinate and set the their component to 0.0
    coord_3d_values[0] = surf_coord.getValues()[0];
    coord_3d_values[1] = surf_coord.getValues()[1];
    coord_3d_values[2] = 0.0;

    three_d_coord.setValues(coord_3d_values);
}


SRM_Long_Float BaseSRF_WithTangentPlaneSurface::calculateEuclideanDistance
(
    const CoordSurf &coord1,
    const CoordSurf &coord2
)
{
    Impl_Status status;
    SRM_Long_Float ret_distance;

    status = Impl_calculateEuclideanDistanceSurface(((BaseSRF_WithTangentPlaneSurface*)coord1.getSRF())->getImpl(), coord1.getValues(),
                                                     ((BaseSRF_WithTangentPlaneSurface*)coord2.getSRF())->getImpl(), coord2.getValues(), &ret_distance);

    if (status != IMPL_VALID)
        processStatus(status, "calculateEuclideanDistance", COORD, MEM);

    // return distance if status is valid.
    return ret_distance;
}
