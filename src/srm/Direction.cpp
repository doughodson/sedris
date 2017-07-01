
#include "internal_api/impl_public.h"

#include "srf_all.h"
#include "Direction.h"
#include "Exception.h"
#include "impl_cpp_misc.h"
#include <math.h>
#include <float.h>

using namespace srm;

Direction::Direction
(
          BaseSRF       *srf,
    const SRM_Vector_3D  ref_coord,
    const SRM_Vector_3D  vec
)
{
    if ( srf==NULL || ref_coord==NULL || vec==NULL )
        throw Exception(SRM_STATCOD_CREATION_FAILURE, "Null input parameter(s)" );

    _srf = srf->clone();

    for (int i=0; i<3; i++)
    {
        _ref_coord[i] = ref_coord[i];
        _vec[i] = vec[i];
    }
}

void Direction::getRefCoord( Coord3D &coord ) const
{
    if ( coord.getSRF() != _srf )
        throw Exception( SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                         "Direction::getRefCoord: Coord3D associated with a different SRF");

    coord.setValues( _ref_coord );
}

const SRM_Long_Float *Direction::getRefCoord() const
{
    return _ref_coord;
}


void Direction::getDir( SRM_Vector_3D vec ) const
{
    vec[0] = _vec[0];
    vec[1] = _vec[1];
    vec[2] = _vec[2];
}

SRM_Long_Float Direction::getVectorComp1() const
{
    return _vec[0];
}

SRM_Long_Float Direction::getVectorComp2() const
{
    return _vec[1];
}

SRM_Long_Float Direction::getVectorComp3() const
{
    return _vec[2];
}

SRM_Long_Float Direction::getVectorComp( SRM_Integer index ) const
{
    if ( index < 1 || index > 3 )
        throw Exception( SRM_STATCOD_INVALID_INPUT,
                         "Direction::getVectorComp: Vector index out of bound");

    return _vec[index-1];
}

void Direction::setVectorComp
(
    const SRM_Long_Float comp1,
    const SRM_Long_Float comp2,
    const SRM_Long_Float comp3
)
{
    _vec[0] = comp1;
    _vec[1] = comp2;
    _vec[2] = comp3;
}

void Direction::setVectorComp
(
    const SRM_Integer    index,
    const SRM_Long_Float comp
)
{
    if ( index < 1 || index > 3 )
        throw Exception( SRM_STATCOD_INVALID_INPUT,
                         "Direction::getVectorComp: Vector index out of bound");

    _vec[index-1] = comp;
}

void Direction::setVector( const SRM_Vector_3D vec )
{
    _vec[0] = vec[0];
    _vec[1] = vec[1];
    _vec[2] = vec[2];
}


bool Direction::isEqual( const Direction &dir ) const
{
    return (_srf == dir._srf &&
            srm::isEqualVec3( _vec, dir._vec ) &&
            srm::isEqualVec3( _ref_coord, dir._ref_coord ));
}


Direction* Direction::makeCopy() const
{
    return new Direction( _srf, _ref_coord, _vec );
}
