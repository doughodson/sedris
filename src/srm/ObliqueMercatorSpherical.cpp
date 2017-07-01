
#include "ObliqueMercatorSpherical.hpp"
#include "Exception.hpp"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// Constructor by SRF parameter structure
SRF_ObliqueMercatorSpherical* SRF_ObliqueMercatorSpherical::create
(
          SRM_ORM_Code                     orm,
          SRM_RT_Code                      rt,
    const SRM_Oblique_Mercator_Parameters &params
)
{
    Impl_Status                   status;
    void                         *impl_ptr = NULL;
    SRF_ObliqueMercatorSpherical *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
      throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_OBLIQUE_MERCATOR_SPHERICAL,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_ObliqueMercatorSpherical(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Constructor by individual SRF parameters
SRF_ObliqueMercatorSpherical* SRF_ObliqueMercatorSpherical::create
(
    SRM_ORM_Code   orm,
    SRM_RT_Code    rt,
    SRM_Long_Float longitude1,
    SRM_Long_Float latitude1,
    SRM_Long_Float longitude2,
    SRM_Long_Float latitude2,
    SRM_Long_Float central_scale,
    SRM_Long_Float false_easting,
    SRM_Long_Float false_northing
)
{
    Impl_Status                      status;
    void                            *impl_ptr = NULL;
    SRF_ObliqueMercatorSpherical    *this_srf = NULL;
    SRM_Oblique_Mercator_Parameters  params;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    params.longitude1 = longitude1;
    params.latitude1 = latitude1;
    params.longitude2 = longitude2;
    params.latitude2 = latitude2;
    params.central_scale = central_scale;
    params.false_easting = false_easting;
    params.false_northing = false_northing;

    status = Impl_createSRFFromParams(SRM_SRFTCOD_OBLIQUE_MERCATOR_SPHERICAL,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_ObliqueMercatorSpherical(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 3D coordinate object
Coord3D* SRF_ObliqueMercatorSpherical::createCoordinate3D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2,
    SRM_Long_Float coord_comp3
)
{
    return (new Coord3D_ObliqueMercatorSpherical(this, coord_comp1, coord_comp2, coord_comp3));
}


/// Returns a surface coordinate object
CoordSurf* SRF_ObliqueMercatorSpherical::createSurfaceCoordinate
(
    SRM_Long_Float coord_surf_comp1,
    SRM_Long_Float coord_surf_comp2
)
{
    return (new CoordSurf_ObliqueMercatorSpherical(this, coord_surf_comp1, coord_surf_comp2));
}


/// Returns a reference to the SRF parameter structure
const SRM_Oblique_Mercator_Parameters& SRF_ObliqueMercatorSpherical::getSRFParameters() const
{
    Impl_Status                            status;
    static SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "getSRFParameters");

    return params;
}


/// Returns the longitude1 SRF parameter value
SRM_Long_Float SRF_ObliqueMercatorSpherical::get_longitude1() const
{
    Impl_Status                     status;
    SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_longitude1");

    return params.longitude1;
}


/// Returns the latitude1 SRF parameter value
SRM_Long_Float SRF_ObliqueMercatorSpherical::get_latitude1() const
{
    Impl_Status                     status;
    SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_latitude1");

    return params.latitude1;
}


/// Returns the longitude2 SRF parameter value
SRM_Long_Float SRF_ObliqueMercatorSpherical::get_longitude2() const
{
    Impl_Status                     status;
    SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_longitude2");

    return params.longitude2;
}


/// Returns the latitude2 SRF parameter value
SRM_Long_Float SRF_ObliqueMercatorSpherical::get_latitude2() const
{
    Impl_Status                     status;
    SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_latitude2");

    return params.latitude2;
}


/// Returns the central_scale SRF parameter value
SRM_Long_Float SRF_ObliqueMercatorSpherical::get_central_scale() const
{
    Impl_Status                     status;
    SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_central_scale");

    return params.central_scale;
}


/// Returns the false_easting SRF parameter value
SRM_Long_Float SRF_ObliqueMercatorSpherical::get_false_easting() const
{
    Impl_Status                     status;
    SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_false_easting");

    return params.false_easting;
}


/// Returns the false_northing SRF parameter value
SRM_Long_Float SRF_ObliqueMercatorSpherical::get_false_northing() const
{
    Impl_Status                     status;
    SRM_Oblique_Mercator_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_false_northing");

    return params.false_northing;
}


bool SRF_ObliqueMercatorSpherical::isEqual(const SRF_ObliqueMercatorSpherical &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}

bool SRF_ObliqueMercatorSpherical::operator== (const SRF_ObliqueMercatorSpherical &rhs) const
{
    return(Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}

SRF_ObliqueMercatorSpherical* SRF_ObliqueMercatorSpherical::makeCopy() const
{
    Impl_Status                   status;
    SRF_ObliqueMercatorSpherical *retSRF = NULL;
    void                         *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
        processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_ObliqueMercatorSpherical(impl);

    return retSRF;
}


/// Return char* of Parameter names and their values (one per line)
const char* SRF_ObliqueMercatorSpherical::toString()
{
    static char                     ret_string[500];
    static char                     tmp_buffer[50];
    Impl_Status                     status;
    SRM_ORM_Code                    orm;
    SRM_RT_Code                     rt;
    SRM_Oblique_Mercator_Parameters params;

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
    sprintf(tmp_buffer, "longitude1=> %f\n", params.longitude1);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "latitude1=> %f\n", params.latitude1);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "longitude2=> %f\n", params.longitude2);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "latitude2=> %f\n", params.latitude2);
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
bool Coord3D_ObliqueMercatorSpherical::operator== (const Coord3D_ObliqueMercatorSpherical &rhs) const
{
    return (((*(SRF_ObliqueMercatorSpherical*)(this->_srf)) == (*(SRF_ObliqueMercatorSpherical*)(rhs._srf))) &&
         ARE_EQUAL(_values[0], rhs._values[0]) &&
         ARE_EQUAL(_values[1], rhs._values[1]) &&
         ARE_EQUAL(_values[2], rhs._values[2]));
}

/// the coordinate equality operator
bool CoordSurf_ObliqueMercatorSpherical::operator== (const CoordSurf_ObliqueMercatorSpherical &rhs) const
{
    return (((*(SRF_ObliqueMercatorSpherical*)(this->_srf)) == (*(SRF_ObliqueMercatorSpherical*)(rhs._srf))) &&
         ARE_EQUAL(_values[0], rhs._values[0]) &&
         ARE_EQUAL(_values[1], rhs._values[1]));
}
