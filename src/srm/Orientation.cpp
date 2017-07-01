
#include "srf_all.h"
#include "Orientation.h"
#include "Direction.h"
#include "Exception.h"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

Orientation::Orientation
(
          BaseSRF        *srf,
    const SRM_Vector_3D   ref_coord,
    const SRM_Matrix_3x3  mat
)
{
    if (srf==NULL || ref_coord==NULL || mat==NULL)
        throw Exception(SRM_STATCOD_CREATION_FAILURE, "Null input parameter(s)");

    _srf = srf->clone();

    for (int i=0; i<3; i++)
    {
        _ref_coord[i] = ref_coord[i];

        for (int j=0; j<3; j++)
            _mat[i][j] = mat[i][j];
    }
}

Orientation::~Orientation()
{
    _srf->release();
}

void Orientation::getRefCoord(Coord3D &coord) const
{
    if (coord.getSRF() != _srf)
        throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                        "Orientation::getRefCoord: Coord3D associated with a different SRF");

    coord.setValues(_ref_coord);
}

void Orientation::getMatrix(SRM_Matrix_3x3 mat) const
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            mat[i][j] = _mat[i][j];
}

void Orientation::getDirectionComp1(Direction &dir) const
{
    if (dir.getSRF() != _srf || !isEqualVec3(dir.getRefCoord(), _ref_coord))
        throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                        "Orientation::getDirectionComp1: Direction using a different reference coordinate");

    dir.setVectorComp(_mat[0][0], _mat[0][1], _mat[0][2]);
}

void Orientation::getDirectionComp2(Direction &dir) const
{
    if (dir.getSRF() != _srf || !isEqualVec3(dir.getRefCoord(), _ref_coord))
        throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                       "Orientation::getDirectionComp2: Direction using a different reference coordinate");

    dir.setVectorComp(_mat[1][0], _mat[1][1], _mat[1][2]);
}

void Orientation::getDirectionComp3(Direction &dir) const
{
    if (dir.getSRF() != _srf || !isEqualVec3(dir.getRefCoord(), _ref_coord))
        throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                        "Orientation::getDirectionComp3: Direction using a different reference coordinate");

    dir.setVectorComp(_mat[2][0], _mat[2][1], _mat[2][2]);
}

void Orientation::getDirectionComp(SRM_Integer index, Direction &dir) const
{
    if (dir.getSRF() != _srf || !isEqualVec3(dir.getRefCoord(), _ref_coord))
        throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                        "Orientation::getDirectionComp: Direction using a different reference coordinate");

    if (index < 1 || index > 3)
        throw Exception(SRM_STATCOD_INVALID_INPUT,
                        "Direction::getDirectionComp: Vector index out of bound");

    dir.setVectorComp(_mat[index-1][0], _mat[index-1][1], _mat[index-1][2]);
}

void Orientation::setDirectionComp
(
    const Direction &dir1,
    const Direction &dir2,
    const Direction &dir3
)
{
    if (dir1.getSRF() != _srf || dir2.getSRF() != _srf || dir3.getSRF() != _srf ||
         !isEqualVec3(dir1.getRefCoord(), _ref_coord) ||
         !isEqualVec3(dir2.getRefCoord(), _ref_coord) ||
         !isEqualVec3(dir3.getRefCoord(), _ref_coord))
       throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION, "setDirectionComp: Invalid input direction objects");

    for (int j=0; j<3; j++)
    {
        _mat[0][j] = dir1.getVectorComp(j+1);
        _mat[1][j] = dir2.getVectorComp(j+1);
        _mat[2][j] = dir3.getVectorComp(j+1);
    }
}

void Orientation::setDirectionComp
(
    const SRM_Integer  index,
    const Direction   &dir
)
{
    if (dir.getSRF() != _srf || !isEqualVec3(dir.getRefCoord(), _ref_coord))
        throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                        "Orientation::setDirectionComp: Direction using a different reference coordinate");

    if (index < 1 || index > 3)
        throw Exception(SRM_STATCOD_INVALID_INPUT,
                        "Direction::setDirectionComp: Vector index out of bound");

    for (int j=0; j<3; j++)
    {
        _mat[index-1][j] = dir.getVectorComp(j+1);
    }
}

void Orientation::setMatrix(const SRM_Matrix_3x3 mat)
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            _mat[i][j] = mat[i][j];
}

bool Orientation::isEqual(const Orientation &ori) const
{
    return (_srf == ori._srf &&
            srm::isEqualMat(_mat, ori._mat) &&
            srm::isEqualVec3(_ref_coord, ori._ref_coord));
}

bool Orientation::operator==(const Orientation &rhs) const
{
    return (_srf == rhs._srf &&
            srm::isEqualMat(_mat, rhs._mat) &&
            srm::isEqualVec3(_ref_coord, rhs._ref_coord));
}

Orientation* Orientation::makeCopy() const
{
    return new Orientation(_srf, _ref_coord, _mat);
}
