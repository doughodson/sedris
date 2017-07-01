
#include "BaseSRF.h"
#include "Coord.h"
#include "Exception.h"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

void BaseSRF_MapProjection::setValidGeodeticRegion
(
    const SRM_Integer       component,
    const SRM_Interval_Type type,
    const SRM_Long_Float    lower,
    const SRM_Long_Float    upper
)
{
    Impl_Status status;

    if (component < 1 || component > 2)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setValidGeodeticRegion: component out of range [ 1, 2 ]");

    if (type >= SRM_IVLTYP_GT_SEMI_INTERVAL && type <=  SRM_IVLTYP_LE_SEMI_INTERVAL )
        throw Exception(SRM_STATCOD_INVALID_INPUT,
                         "setValidGeodeticRegion: cannot be a semi-interval region");

    if (component == 1 && !(type==SRM_IVLTYP_UNBOUNDED) &&
        lower<=-SRM_PI && lower>SRM_PI &&
        upper<=-SRM_PI && upper>SRM_PI)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setValidGeodeticRegion: component 1 (longitude) out of range (-PI, PI]");

    if (!(type==SRM_IVLTYP_UNBOUNDED) && lower == upper)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setValidGeodeticRegion: lower and upper bounds are the same");

    if (component == 2 && !(type==SRM_IVLTYP_UNBOUNDED) &&
        lower<=-SRM_PI_DIV_2 && lower>=SRM_PI_DIV_2 &&
        upper<=-SRM_PI_DIV_2 && upper>=SRM_PI_DIV_2)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setValidGeodeticRegion: component 2 (latitude) out of range (-PI/2, PI/2)");

    status = Impl_setValidGeodeticRegion(this->getImpl(), component, type, lower, upper);

    if (status != IMPL_VALID)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setValidGeodeticRegion: invalid input");
}


void BaseSRF_MapProjection::setExtendedValidGeodeticRegion
(
    const SRM_Integer component,
    const SRM_Interval_Type type,
    const SRM_Long_Float extended_lower,
    const SRM_Long_Float lower,
    const SRM_Long_Float upper,
    const SRM_Long_Float extended_upper
)
{
    Impl_Status status;

    if (component < 1 || component > 2)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setExtendedValidGeodeticRegion: component out of range [ 1, 2 ]");

    if (type >= SRM_IVLTYP_GT_SEMI_INTERVAL && type <=  SRM_IVLTYP_LE_SEMI_INTERVAL )
        throw Exception(SRM_STATCOD_INVALID_INPUT,
                         "setExtendedValidGeodeticRegion: cannot be a semi-interval region");

    if (component == 1 && !(type==SRM_IVLTYP_UNBOUNDED) &&
         lower<=-SRM_PI && lower>SRM_PI &&
         upper<=-SRM_PI && upper>SRM_PI)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setExtendedValidGeodeticRegion: component 1 (longitude) out of range (-PI, PI]");

    if (component == 2 && !(type==SRM_IVLTYP_UNBOUNDED) &&
         lower<=-SRM_PI_DIV_2 && lower>=SRM_PI_DIV_2 &&
         upper<=-SRM_PI_DIV_2 && upper>=SRM_PI_DIV_2)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setExtendedValidGeodeticRegion: component 2 (latitude) out of range (-PI/2, PI/2)");

    if (!(type==SRM_IVLTYP_UNBOUNDED) && lower == upper)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setExtendedValidGeodeticRegion: lower and upper bounds are the same");

    if (!(type==SRM_IVLTYP_UNBOUNDED))
        if (lower < upper  && (extended_lower > lower || extended_upper < upper))
            throw Exception(SRM_STATCOD_INVALID_INPUT,
                             "setExtendedValidGeodeticRegion: extended bounds falls within valid region");
        else if (lower > upper && (extended_lower < lower || extended_upper > upper))
            throw Exception(SRM_STATCOD_INVALID_INPUT,
                            "setExtendedValidGeodeticRegion: extended bounds falls within valid region");

    status = Impl_setExtendedValidGeodeticRegion(this->getImpl(), component, type, extended_lower, lower, upper, extended_upper);

    if (status != IMPL_VALID)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "setExtendedValidGeodeticRegion: invalid input");
}


void BaseSRF_MapProjection::getValidGeodeticRegion
(
    const SRM_Integer        component,
          SRM_Interval_Type &type,
          SRM_Long_Float    &lower,
          SRM_Long_Float    &upper
)
{
    Impl_Status status;

    if (component < 1 || component > 2)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "getValidGeodeticRegion: component out of range [ 1, 2 ]");

    status = Impl_getValidGeodeticRegion(this->getImpl(), component, type, lower, upper);

    if (status != IMPL_VALID)
        throw Exception(SRM_STATCOD_INACTIONABLE, "getValidGeodeticRegion: error retriving valid region bounds");
}


void BaseSRF_MapProjection::getExtendedValidGeodeticRegion
(
    const SRM_Integer        component,
          SRM_Interval_Type &type,
          SRM_Long_Float    &extended_lower,
          SRM_Long_Float    &lower,
          SRM_Long_Float    &upper,
          SRM_Long_Float    &extended_upper
)
{
    Impl_Status status;

    if (component < 1 || component > 2)
        throw Exception(SRM_STATCOD_INVALID_INPUT, "getExtendedValidGeodeticRegion: component out of range [ 1, 2 ]");

    status = Impl_getExtendedValidGeodeticRegion(this->getImpl(), component, type, extended_lower, lower,
                                                  upper, extended_upper);

    if (status != IMPL_VALID)
        throw Exception(SRM_STATCOD_INACTIONABLE, "getValidGeodeticRegion: error retriving extended valid region bounds");
}


// BaseSRF_MapProjection method bodies invoking internal implementation functions
SRM_Long_Float BaseSRF_MapProjection::calculateConvergenceOfTheMeridian(const CoordSurf &surf_coord)
{
    Impl_Status status;
    SRM_Long_Float ret_com;

    if (surf_coord.getSRF() != this)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE, "calculateConvergenceOfTheMeridian: Surface coordinate associated with a different SRF");

    // calculate distance
    status = Impl_calculateConvergenceOfTheMeridian(this->getImpl(), surf_coord.getValues(), &ret_com);

    if (status != IMPL_VALID)
        processStatus(status, "calculateConvergenceOfTheMeridian", COORD, MEM);

    // return distance if status is valid.
    return ret_com;
}


SRM_Long_Float BaseSRF_MapProjection::calculatePointDistortion(const CoordSurf &surf_coord)
{
    Impl_Status status;
    SRM_Long_Float ret_scale;

    if (surf_coord.getSRF() != this)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE, "calculatePointDistortion: Surface coordinate associated with a different SRF");

    // calculate distance
    status = Impl_calculatePointScale(this->getImpl(), surf_coord.getValues(), &ret_scale);

    if (status != IMPL_VALID)
        processStatus(status, "calculatePointDistortion", COORD, MEM);

    // return distance if status is valid.
    return ret_scale;
}


SRM_Long_Float BaseSRF_MapProjection::calculateMapAzimuth
(
    const CoordSurf &src_coord,
    const CoordSurf &des_coord
)
{
    Impl_Status status;
    SRM_Long_Float ret_distance;

    if (src_coord.getSRF() != this || des_coord.getSRF() != this)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE, "calculateMapAzimuth: surface coordinate associated with a different SRF");

    // calculate distance
    status = Impl_calculateMapAzimuth(this->getImpl(), src_coord.getValues(),
                                     des_coord.getValues(), &ret_distance);

    if (status != IMPL_VALID)
        processStatus(status, "calculateMapAzimuth", COORD, MEM);

    // return distance if status is valid.
    return ret_distance;
}
