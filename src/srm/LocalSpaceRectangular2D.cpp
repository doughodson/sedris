
#include "LocalSpaceRectangular2D.h"
#include "Exception.h"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// Constructor by SRF parameter structure
SRF_LocalSpaceRectangular2D* SRF_LocalSpaceRectangular2D::create
(
          SRM_ORM_Code           orm,
          SRM_RT_Code            rt,
    const SRM_LSR_2D_Parameters &params
)
{
    Impl_Status                  status;
    void                        *impl_ptr = NULL;
    SRF_LocalSpaceRectangular2D *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
      throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_LOCAL_SPACE_RECTANGULAR_2D,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_LocalSpaceRectangular2D(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Constructor by individual SRF parameters
SRF_LocalSpaceRectangular2D* SRF_LocalSpaceRectangular2D::create
(
    SRM_ORM_Code       orm,
    SRM_RT_Code        rt,
    SRM_Axis_Direction forward_direction
)
{
    Impl_Status                  status;
    void                        *impl_ptr = NULL;
    SRF_LocalSpaceRectangular2D *this_srf = NULL;
    SRM_LSR_2D_Parameters        params;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    params.forward_direction = forward_direction;

    status = Impl_createSRFFromParams(SRM_SRFTCOD_LOCAL_SPACE_RECTANGULAR_2D,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_LocalSpaceRectangular2D(impl_ptr);
    else
        processStatus(status, "create");

    /*  only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 2D coordinate object
Coord2D* SRF_LocalSpaceRectangular2D::createCoordinate2D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2
)
{
    return (new Coord2D_LocalSpaceRectangular2D(this, coord_comp1, coord_comp2));
}


/// Returns a reference to the SRF parameter structure
const SRM_LSR_2D_Parameters& SRF_LocalSpaceRectangular2D::getSRFParameters() const
{
    Impl_Status                  status;
    static SRM_LSR_2D_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "getSRFParameters");

    return params;
}


/// Returns the forward_direction SRF parameter value
SRM_Axis_Direction SRF_LocalSpaceRectangular2D::get_forward_direction() const
{
    Impl_Status           status;
    SRM_LSR_2D_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_forward_direction");

    return params.forward_direction;
}


bool SRF_LocalSpaceRectangular2D::isEqual(const SRF_LocalSpaceRectangular2D &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}

bool SRF_LocalSpaceRectangular2D::operator==(const SRF_LocalSpaceRectangular2D &rhs) const
{
    return(Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}

SRF_LocalSpaceRectangular2D* SRF_LocalSpaceRectangular2D::makeCopy() const
{
    Impl_Status                  status;
    SRF_LocalSpaceRectangular2D *retSRF = NULL;
    void                        *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
        processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_LocalSpaceRectangular2D(impl);

    return retSRF;
}


/// Return char* of Parameter names and their values (one per line)
const char* SRF_LocalSpaceRectangular2D::toString()
{
    static char  ret_string[500];
    static char  tmp_buffer[50];
    Impl_Status  status;
    SRM_ORM_Code orm;
    SRM_RT_Code  rt;
    SRM_LSR_2D_Parameters params;

    status  = Impl_getSRFParameters(this->_impl, (void *)&params);
    status |= Impl_getORM(this->_impl, &orm);
    status |= Impl_getRT(this->_impl, &rt);

    if (status != IMPL_VALID)
      processStatus(status, "toString");

    // set the char* to null
    ret_string[0] = '\0';

    sprintf(tmp_buffer, "orm=> %i\n", orm);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "rt=> %i\n", rt);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "forward_direction=> %i\n", params.forward_direction);
    strcat(ret_string, tmp_buffer);

    return ret_string;
}

/// the coordinate equality operator
bool Coord2D_LocalSpaceRectangular2D::operator== (const Coord2D_LocalSpaceRectangular2D &rhs) const
{
    return (((*(SRF_LocalSpaceRectangular2D*)(this->_srf)) == (*(SRF_LocalSpaceRectangular2D*)(rhs._srf))) &&
	     ARE_EQUAL(_values[0], rhs._values[0]) &&
	     ARE_EQUAL(_values[1], rhs._values[1]));
}
