
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Coord.hpp"
#include "Exception.hpp"
#include "internal_api/impl_mgrs.h"

using namespace srm;

const char* Coord2D::toString()
{
    static char ret_string[50];
    sprintf(ret_string,"[ %lf, %lf ]\n", _values[0],  _values[1]);
    return ret_string;
}

const char* CoordSurf::toString()
{
    static char ret_string[50];
    sprintf( ret_string,"[ %lf, %lf ]\n", _values[0], _values[1] );
    return ret_string;
}

const char* Coord3D::toString()
{
    static char ret_string[75];
    sprintf(ret_string, "[ %lf, %lf, %lf ]\n",
            _values[0],  _values[1],  _values[2]);
    return ret_string;
}

const char* Coord3D::getMGRS(SRM_Integer precision)
{
    static char mgrs[20];
    Impl_Status status;

    status = impl_get_MGRS(this->getSRF()->_impl,
                           this,
                           precision,
                           mgrs);

    if (status != IMPL_VALID)
        throw Exception(SRM_STATCOD_INVALID_INPUT,
                        "getMGRS: Invalid input for MGRS conversion from coordinate");

    return mgrs;
}

void Coord3D::setCoord(const char* mgrs)
{
    Impl_Status status;
    static char my_mgrs[16];

    strcpy(my_mgrs, mgrs);

    status = impl_set_coord(this->getSRF()->_impl,
                             my_mgrs,
                             this);

    if (status != IMPL_VALID)
        throw Exception(SRM_STATCOD_INVALID_INPUT,
                        "setCoord: Invalid input for MGRS conversion to coordinate");
}
