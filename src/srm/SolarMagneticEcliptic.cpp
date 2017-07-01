
#include "SolarMagneticEcliptic.h"
#include "Exception.h"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// SRF_SolarMagneticEcliptic only constructor by ORM and RT codes
SRF_SolarMagneticEcliptic* SRF_SolarMagneticEcliptic::create
(
    SRM_ORM_Code orm,
    SRM_RT_Code rt
)
{
    Impl_Status                status;
    void                      *impl_ptr = NULL;
    SRF_SolarMagneticEcliptic *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_SOLAR_MAGNETIC_ECLIPTIC,
                                      orm,
                                      rt,
                                      NULL,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_SolarMagneticEcliptic(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 3D coordinate object
Coord3D* SRF_SolarMagneticEcliptic::createCoordinate3D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2,
    SRM_Long_Float coord_comp3
)
{
    return (new Coord3D_SolarMagneticEcliptic(this, coord_comp1, coord_comp2, coord_comp3));
}


bool SRF_SolarMagneticEcliptic::isEqual(const SRF_SolarMagneticEcliptic &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}

bool SRF_SolarMagneticEcliptic::operator== (const SRF_SolarMagneticEcliptic &rhs) const
{
  return(Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}


SRF_SolarMagneticEcliptic* SRF_SolarMagneticEcliptic::makeCopy() const
{
    Impl_Status                status;
    SRF_SolarMagneticEcliptic *retSRF = NULL;
    void                      *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
        processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_SolarMagneticEcliptic(impl);

    return retSRF;
}


/// Return char* ORM parameter
const char* SRF_SolarMagneticEcliptic::toString()
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
bool Coord3D_SolarMagneticEcliptic::operator== (const Coord3D_SolarMagneticEcliptic &rhs) const
{
  return (((*(SRF_SolarMagneticEcliptic*)(this->_srf)) == (*(SRF_SolarMagneticEcliptic*)(rhs._srf))) &&
	   ARE_EQUAL(_values[0], rhs._values[0]) &&
	   ARE_EQUAL(_values[1], rhs._values[1]) &&
	   ARE_EQUAL(_values[2], rhs._values[2]));
}
