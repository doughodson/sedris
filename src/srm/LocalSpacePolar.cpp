
#include "LocalSpacePolar.hpp"
#include "Exception.hpp"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// SRF_LocalSpacePolar only constructor by ORM and RT codes
SRF_LocalSpacePolar* SRF_LocalSpacePolar::create
(
    SRM_ORM_Code orm,
    SRM_RT_Code  rt
)
{
    Impl_Status          status;
    void                *impl_ptr = NULL;
    SRF_LocalSpacePolar *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_LOCAL_SPACE_POLAR_2D,
                                      orm,
                                      rt,
                                      NULL,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_LocalSpacePolar(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 2D coordinate object
Coord2D* SRF_LocalSpacePolar::createCoordinate2D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2
)
{
    return (new Coord2D_LocalSpacePolar(this, coord_comp1, coord_comp2));
}


bool SRF_LocalSpacePolar::isEqual(const SRF_LocalSpacePolar &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}

bool SRF_LocalSpacePolar::operator==(const SRF_LocalSpacePolar &rhs) const
{
    return(Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}

SRF_LocalSpacePolar* SRF_LocalSpacePolar::makeCopy() const
{
    Impl_Status          status;
    SRF_LocalSpacePolar *retSRF = NULL;
    void                *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
      processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_LocalSpacePolar(impl);

    return retSRF;
}


/// Return char* ORM parameter
const char* SRF_LocalSpacePolar::toString()
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
bool Coord2D_LocalSpacePolar::operator== (const Coord2D_LocalSpacePolar &rhs) const
{
    return (((*(SRF_LocalSpacePolar*)(this->_srf)) == (*(SRF_LocalSpacePolar*)(rhs._srf))) &&
            ARE_EQUAL(_values[0], rhs._values[0]) &&
            ARE_EQUAL(_values[1], rhs._values[1]));
}
