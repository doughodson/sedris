
#include "LocalSpaceAzimuthal.h"
#include "Exception.h"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// SRF_LocalSpaceAzimuthal only constructor by ORM and RT codes
SRF_LocalSpaceAzimuthal* SRF_LocalSpaceAzimuthal::create
(
     SRM_ORM_Code orm,
     SRM_RT_Code  rt
)
{
    Impl_Status              status;
    void                    *impl_ptr = NULL;
    SRF_LocalSpaceAzimuthal *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_LOCAL_SPACE_AZIMUTHAL_2D,
                                      orm,
                                      rt,
                                      NULL,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_LocalSpaceAzimuthal(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 2D coordinate object
Coord2D* SRF_LocalSpaceAzimuthal::createCoordinate2D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2
)
{
    return (new Coord2D_LocalSpaceAzimuthal(this, coord_comp1, coord_comp2));
}


bool SRF_LocalSpaceAzimuthal::isEqual(const SRF_LocalSpaceAzimuthal &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}

bool SRF_LocalSpaceAzimuthal::operator==(const SRF_LocalSpaceAzimuthal &rhs) const
{
  return(Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}

SRF_LocalSpaceAzimuthal* SRF_LocalSpaceAzimuthal::makeCopy() const
{
    Impl_Status              status;
    SRF_LocalSpaceAzimuthal *retSRF = NULL;
    void                    *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
        processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_LocalSpaceAzimuthal(impl);

    return retSRF;
}


/// Return char* ORM parameter
const char* SRF_LocalSpaceAzimuthal::toString()
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
bool Coord2D_LocalSpaceAzimuthal::operator== (const Coord2D_LocalSpaceAzimuthal &rhs) const
{
  return (((*(SRF_LocalSpaceAzimuthal*)(this->_srf)) == (*(SRF_LocalSpaceAzimuthal*)(rhs._srf))) &&
	   ARE_EQUAL(_values[0], rhs._values[0]) &&
	   ARE_EQUAL(_values[1], rhs._values[1]));
}
