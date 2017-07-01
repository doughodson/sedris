
#include "srf_all.hpp"
#include "Exception.hpp"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

void BaseSRF_2D::getCoordinate2DValues
(
    const Coord2D        &coord,
          SRM_Long_Float &coord_comp1,
          SRM_Long_Float &coord_comp2
) const
{
    if (coord.getSRF() != (BaseSRF*)this)
        throw Exception( SRM_STATCOD_INVALID_SOURCE_COORDINATE, "getCoordinate2DValues: Coordinate not associated with this SRF" );

    coord_comp1 = coord.getValues()[0];
    coord_comp2 = coord.getValues()[1];
}


void BaseSRF_2D::freeCoordinate2D( Coord2D *coord )
{
    if ( coord->getSRF() != this)
        throw Exception( SRM_STATCOD_INVALID_SOURCE_COORDINATE, "freeCoordinate2D: Coordinate not associated with this SRF" );

    delete (coord);
}


void BaseSRF_2D::changeCoordinate2DSRFObject
(
    const Coord2D                              &src_coord,
    const SRM_ORM_Transformation_2D_Parameters  hst,
          Coord2D                              &des_coord
)
{
    Impl_Status status;
    SRM_Long_Float desCoord[2];

    if ( des_coord.getSRF() != this )
        throw Exception( SRM_STATCOD_INVALID_TARGET_COORDINATE, "changeCoordinate2DSRF: Target coordinate associated with a different SRF");

    if ( hst.omega >= SRM_2_PI || hst.omega <= -SRM_2_PI ||
        hst.delta_s <= -1.0 )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DSRFObject: HST values out-of-range");

    // change SRF
    status = Impl_changeCoord2DSRFObject(((BaseSRF_2D*)src_coord.getSRF())->getImpl(), src_coord.getValues(),
                                         ((BaseSRF_2D*)des_coord.getSRF())->getImpl(), desCoord,
                                         &hst);

    // set the coordinate values if status is "valid"
    if ( status == IMPL_VALID )
        des_coord.setValues( desCoord );
    else
        processStatus( status, "changeCoordinate2DSRF", COORD, MEM);
}

void BaseSRF_2D::changeCoordinate2DArraySRFObject
(
          Coord2D                              **src_coord_array,
    const SRM_ORM_Transformation_2D_Parameters   hst,
          SRM_Integer_Positive                  *index,
          Coord2D                              **des_coord_array
)
{
    Impl_Status status;
    SRM_Long_Float desCoord[2];
    SRM_Integer_Positive i;

    if ( index == NULL || *index == 0 )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRFObject: index = NULL or index = 0" );

    if ( src_coord_array == NULL )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRFObject: null source coordinate array" );

    if ( des_coord_array == NULL )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRFObject: null destination coordinate array" );

    if (hst.omega >= SRM_2_PI || hst.omega <= -SRM_2_PI ||
        hst.delta_s <= -1.0 )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRFObject: HST values out-of-range");

    try
    {
        for ( i=0; i<*index; i++ )
        {
            if ( src_coord_array[i] == NULL )
            {
                *index = i;
                throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRFObject: null source coordinate array element" );
            }

            if ( des_coord_array[i] == NULL )
            {
                *index = i;
                throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRFObject: null destination coordinate array element" );
            }

            if ( des_coord_array[i]->getSRF() != this )
            {
                *index = i;
                throw Exception( SRM_STATCOD_INVALID_TARGET_COORDINATE, "changeCoordinate2DArraySRFObject: Target coordinate associated with a different SRF");
            }

            // change SRF
            status = Impl_changeCoord2DSRFObject(((BaseSRF_2D*)src_coord_array[i]->getSRF())->getImpl(), src_coord_array[i]->getValues(),
                                                 ((BaseSRF_2D*)des_coord_array[i]->getSRF())->getImpl(), desCoord,
                                                 &hst);

            // set the coordinate values if status is "valid"
            if ( status == IMPL_VALID )
                des_coord_array[i]->setValues( desCoord );
            else
            {
                *index = i;
                processStatus( status, "changeCoordinate2DArraySRFObject", COORD, MEM);
            }
        }
    }
    catch ( ... )
    {
        *index = i;
        throw Exception( SRM_STATCOD_INACTIONABLE, "changeCoordinate2DArraySRFObject: Inactionable");
    }
}


void BaseSRF_2D::changeCoordinate2DSRF
(
    const Coord2D &src_coord,
          Coord2D &des_coord
)
{
    Impl_Status status;
    SRM_Long_Float desCoord[2];

    if ( des_coord.getSRF() != this )
        throw Exception( SRM_STATCOD_INVALID_TARGET_COORDINATE, "changeCoordinate2DSRF: Target coordinate associated with a different SRF");

    // change SRF
    status = Impl_changeCoord2DSRF(((BaseSRF_2D*)src_coord.getSRF())->getImpl(), src_coord.getValues(),
                                   ((BaseSRF_2D*)des_coord.getSRF())->getImpl(), desCoord);

    // set the coordinate values if status is "valid"
    if ( status == IMPL_VALID )
        des_coord.setValues( desCoord );
    else
        processStatus( status, "changeCoordinate2DSRF", COORD, MEM);
}


void BaseSRF_2D::changeCoordinate2DArraySRF
(
    Coord2D              **src_coord_array,
    SRM_Integer_Positive  *index,
    Coord2D              **des_coord_array
)
{
    Impl_Status status;
    SRM_Long_Float desCoord[2];
    SRM_Integer_Positive i;

    if ( index == NULL || *index == 0 )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRF: index = NULL or index = 0" );

    if ( src_coord_array == NULL )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRF: null source coordinate array" );

    if ( des_coord_array == NULL )
        throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRF: null destination coordinate array" );

    try
    {
        for ( i=0; i<*index; i++ )
        {
            if ( src_coord_array[i] == NULL )
            {
                *index = i;
                throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRF: null source coordinate array element" );
            }

            if ( des_coord_array[i] == NULL )
            {
                *index = i;
                throw Exception( SRM_STATCOD_INVALID_INPUT, "changeCoordinate2DArraySRF: null destination coordinate array element" );
            }

            if ( des_coord_array[i]->getSRF() != this )
            {
                *index = i;
                throw Exception( SRM_STATCOD_INVALID_TARGET_COORDINATE, "changeCoordinate2DArraySRF: Target coordinate associated with a different SRF");
            }

            // change SRF
            status = Impl_changeCoord2DSRF(((BaseSRF_2D*)src_coord_array[i]->getSRF())->getImpl(), src_coord_array[i]->getValues(),
                                           ((BaseSRF_2D*)des_coord_array[i]->getSRF())->getImpl(), desCoord);

            // set the coordinate values if status is "valid"
            if ( status == IMPL_VALID || status == IMPL_EXTENDED || status == IMPL_DEFINED )
                des_coord_array[i]->setValues( desCoord );
            else
            {
                *index = i;
                processStatus( status, "changeCoordinate2DArraySRF", COORD, MEM);
            }
        }
    }
    catch ( ... )
    {
        *index = i;
        throw Exception( SRM_STATCOD_INACTIONABLE, "changeCoordinate2DArraySRF: Inactionable");
    }
}


SRM_Long_Float BaseSRF_2D::calculateEuclideanDistance
(
    const Coord2D &coord1,
    const Coord2D &coord2
)
{
    Impl_Status status;
    SRM_Long_Float ret_distance;

    status = Impl_calculateEuclideanDistance2D( ((BaseSRF_2D*)coord1.getSRF())->getImpl(), coord1.getValues(),
                                                ((BaseSRF_2D*)coord2.getSRF())->getImpl(), coord2.getValues(), &ret_distance );

    if ( status != IMPL_VALID )
        processStatus( status, "calculateEuclideanDistance", COORD, MEM);

    // return distance if status is valid.
    return ret_distance;
}
