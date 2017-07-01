
#include "EquidistantCylindrical.h"
#include "Exception.h"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// Constructor by SRF parameter structure
SRF_EquidistantCylindrical* SRF_EquidistantCylindrical::create
(
          SRM_ORM_Code       orm,
          SRM_RT_Code        rt,
    const SRM_EC_Parameters &params
)
{
    Impl_Status                 status;
    void                       *impl_ptr = NULL;
    SRF_EquidistantCylindrical *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_EQUIDISTANT_CYLINDRICAL,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_EquidistantCylindrical(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Constructor by individual SRF parameters
SRF_EquidistantCylindrical* SRF_EquidistantCylindrical::create
(
    SRM_ORM_Code   orm,
    SRM_RT_Code    rt,
    SRM_Long_Float origin_longitude,
    SRM_Long_Float central_scale,
    SRM_Long_Float false_easting,
    SRM_Long_Float false_northing
)
{
    Impl_Status                 status;
    void                       *impl_ptr = NULL;
    SRF_EquidistantCylindrical *this_srf = NULL;
    SRM_EC_Parameters           params;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    params.origin_longitude = origin_longitude;
    params.central_scale = central_scale;
    params.false_easting = false_easting;
    params.false_northing = false_northing;

    status = Impl_createSRFFromParams(SRM_SRFTCOD_EQUIDISTANT_CYLINDRICAL,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_EquidistantCylindrical(impl_ptr);
    else
        processStatus(status, "create");

    /*  only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 3D coordinate object
Coord3D* SRF_EquidistantCylindrical::createCoordinate3D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2,
    SRM_Long_Float coord_comp3
)
{
    return (new Coord3D_EquidistantCylindrical(this, coord_comp1, coord_comp2, coord_comp3));
}


/// Returns a surface coordinate object
CoordSurf* SRF_EquidistantCylindrical::createSurfaceCoordinate
(
    SRM_Long_Float coord_surf_comp1,
    SRM_Long_Float coord_surf_comp2
)
{
    return (new CoordSurf_EquidistantCylindrical(this, coord_surf_comp1, coord_surf_comp2));
}


/// Returns a reference to the SRF parameter structure
const SRM_EC_Parameters& SRF_EquidistantCylindrical::getSRFParameters() const
{
    Impl_Status              status;
    static SRM_EC_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "getSRFParameters");

    return params;
}


/// Returns the origin_longitude SRF parameter value
SRM_Long_Float SRF_EquidistantCylindrical::get_origin_longitude() const
{
    Impl_Status       status;
    SRM_EC_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_origin_longitude");

    return params.origin_longitude;
}


/// Returns the central_scale SRF parameter value
SRM_Long_Float SRF_EquidistantCylindrical::get_central_scale() const
{
    Impl_Status       status;
    SRM_EC_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_central_scale");

    return params.central_scale;
}


/// Returns the false_easting SRF parameter value
SRM_Long_Float SRF_EquidistantCylindrical::get_false_easting() const
{
    Impl_Status       status;
    SRM_EC_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_false_easting");

    return params.false_easting;
}


/// Returns the false_northing SRF parameter value
SRM_Long_Float SRF_EquidistantCylindrical::get_false_northing() const
{
    Impl_Status       status;
    SRM_EC_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_false_northing");

    return params.false_northing;
}


bool SRF_EquidistantCylindrical::isEqual(const SRF_EquidistantCylindrical &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}


bool SRF_EquidistantCylindrical::operator== (const SRF_EquidistantCylindrical &rhs) const
{
    return (Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}


SRF_EquidistantCylindrical* SRF_EquidistantCylindrical::makeCopy() const
{
    Impl_Status                 status;
    SRF_EquidistantCylindrical *retSRF = NULL;
    void                       *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
        processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_EquidistantCylindrical(impl);

    return retSRF;
}


/// Return char* of Parameter names and their values (one per line)
const char* SRF_EquidistantCylindrical::toString()
{
    static char       ret_string[500];
    static char       tmp_buffer[50];
    Impl_Status       status;
    SRM_ORM_Code      orm;
    SRM_RT_Code       rt;
    SRM_EC_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    if (status != IMPL_VALID)
        processStatus(status, "toString");

    status = Impl_getORM(this->_impl, &orm);

    if (status != IMPL_VALID)
        processStatus(status, "toString");

    status = Impl_getRT(this->_impl, &rt);

    if (status != IMPL_VALID)
        processStatus(status, "toString");

    // set the char* to null
    ret_string[0] = '\0';

    sprintf(tmp_buffer, "orm=> %i\n", orm);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "rt=> %i\n", rt);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "origin_longitude=> %f\n", params.origin_longitude);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "central_scale=> %f\n", params.central_scale);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "false_easting=> %f\n", params.false_easting);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "false_northing=> %f\n", params.false_northing);
    strcat(ret_string, tmp_buffer);

    return ret_string;
}

/// the coordinate equality operator
bool Coord3D_EquidistantCylindrical::operator== (const Coord3D_EquidistantCylindrical &rhs) const
{
  return (((*(SRF_EquidistantCylindrical*)(this->_srf)) == (*(SRF_EquidistantCylindrical*)(rhs._srf))) &&
           ARE_EQUAL(_values[0], rhs._values[0]) &&
           ARE_EQUAL(_values[1], rhs._values[1]) &&
           ARE_EQUAL(_values[2], rhs._values[2]));
}

/// the coordinate equality operator
bool CoordSurf_EquidistantCylindrical::operator== (const CoordSurf_EquidistantCylindrical &rhs) const
{
  return (((*(SRF_EquidistantCylindrical*)(this->_srf)) == (*(SRF_EquidistantCylindrical*)(rhs._srf))) &&
           ARE_EQUAL(_values[0], rhs._values[0]) &&
           ARE_EQUAL(_values[1], rhs._values[1]));
}
