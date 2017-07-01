
#include "Planetodetic.hpp"
#include "Exception.hpp"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// SRF_Planetodetic only constructor by ORM and RT codes
SRF_Planetodetic* SRF_Planetodetic::create
(
    SRM_ORM_Code orm,
    SRM_RT_Code  rt
)
{
    Impl_Status       status;
    void             *impl_ptr = NULL;
    SRF_Planetodetic *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_PLANETODETIC,
                                      orm,
                                      rt,
                                      NULL,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_Planetodetic(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 3D coordinate object
Coord3D* SRF_Planetodetic::createCoordinate3D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2,
    SRM_Long_Float coord_comp3
)
{
    return (new Coord3D_Planetodetic(this, coord_comp1, coord_comp2, coord_comp3));
}


/// Returns a surface coordinate object
CoordSurf* SRF_Planetodetic::createSurfaceCoordinate
(
    SRM_Long_Float coord_surf_comp1,
    SRM_Long_Float coord_surf_comp2
)
{
    return (new CoordSurf_Planetodetic(this, coord_surf_comp1, coord_surf_comp2));
}


bool SRF_Planetodetic::isEqual(const SRF_Planetodetic &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}

bool SRF_Planetodetic::operator== (const SRF_Planetodetic &rhs) const
{
    return(Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}

SRF_Planetodetic* SRF_Planetodetic::makeCopy() const
{
    Impl_Status       status;
    SRF_Planetodetic *retSRF = NULL;
    void             *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
        processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_Planetodetic(impl);

    return retSRF;
}


/// Return char* ORM parameter
const char* SRF_Planetodetic::toString()
{
    static char ret_string[20];
    static char tmp_buffer[10];
    Impl_Status status;
    SRM_ORM_Code orm;
    SRM_RT_Code rt;

    status  = Impl_getORM(this->_impl, &orm);
    status |= Impl_getRT(this->_impl, &rt);

    if (status != IMPL_VALID)
        processStatus(status, "toString");

    // set the char* to null
    ret_string[0] = '\0';

    sprintf(tmp_buffer, "orm=> %i\n", orm);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "rt=> %i\n", rt);
    strcat(ret_string, tmp_buffer);

    return ret_string;
}

/// the coordinate equality operator
bool Coord3D_Planetodetic::operator== (const Coord3D_Planetodetic &rhs) const
{
    return (((*(SRF_Planetodetic*)(this->_srf)) == (*(SRF_Planetodetic*)(rhs._srf))) &&
            ARE_EQUAL(_values[0], rhs._values[0]) &&
            ARE_EQUAL(_values[1], rhs._values[1]) &&
            ARE_EQUAL(_values[2], rhs._values[2]));
}

/// the coordinate equality operator
bool CoordSurf_Planetodetic::operator== (const CoordSurf_Planetodetic &rhs) const
{
    return (((*(SRF_Planetodetic*)(this->_srf)) == (*(SRF_Planetodetic*)(rhs._srf))) &&
            ARE_EQUAL(_values[0], rhs._values[0]) &&
            ARE_EQUAL(_values[1], rhs._values[1]));
}
