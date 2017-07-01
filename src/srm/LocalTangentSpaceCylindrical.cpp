
#include "LocalTangentSpaceCylindrical.h"
#include "Exception.h"
#include "internal_api/impl_public.h"
#include "impl_cpp_misc.h"

using namespace srm;

/// Constructor by SRF parameter structure
SRF_LocalTangentSpaceCylindrical* SRF_LocalTangentSpaceCylindrical::create
(
          SRM_ORM_Code                  orm,
          SRM_RT_Code                   rt,
    const SRM_Local_Tangent_Parameters &params
)
{
    Impl_Status                       status;
    void                             *impl_ptr = NULL;
    SRF_LocalTangentSpaceCylindrical *this_srf = NULL;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    status = Impl_createSRFFromParams(SRM_SRFTCOD_LOCAL_TANGENT_SPACE_CYLINDRICAL,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_LocalTangentSpaceCylindrical(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Constructor by individual SRF parameters
SRF_LocalTangentSpaceCylindrical* SRF_LocalTangentSpaceCylindrical::create
(
    SRM_ORM_Code   orm,
    SRM_RT_Code    rt,
    SRM_Long_Float geodetic_longitude,
    SRM_Long_Float geodetic_latitude,
    SRM_Long_Float azimuth,
    SRM_Long_Float height_offset
)
{
    Impl_Status                       status;
    void                             *impl_ptr = NULL;
    SRF_LocalTangentSpaceCylindrical *this_srf = NULL;
    SRM_Local_Tangent_Parameters      params;

    if (!isLegalORMCode(orm, rt))
        throw Exception(SRM_STATCOD_INVALID_CODE, "create: Invalid ORM code");

    params.geodetic_longitude = geodetic_longitude;
    params.geodetic_latitude = geodetic_latitude;
    params.azimuth = azimuth;
    params.height_offset = height_offset;

    status = Impl_createSRFFromParams(SRM_SRFTCOD_LOCAL_TANGENT_SPACE_CYLINDRICAL,
                                      orm,
                                      rt,
                                      (void*) &params,
                                      &impl_ptr);

    if (status == IMPL_VALID)
        this_srf = new SRF_LocalTangentSpaceCylindrical(impl_ptr);
    else
        processStatus(status, "create");

    /* only return if status == IMPL_VALID */
    return this_srf;
}


/// Returns a 3D coordinate object
Coord3D* SRF_LocalTangentSpaceCylindrical::createCoordinate3D
(
    SRM_Long_Float coord_comp1,
    SRM_Long_Float coord_comp2,
    SRM_Long_Float coord_comp3
)
{
    return (new Coord3D_LocalTangentSpaceCylindrical(this, coord_comp1, coord_comp2, coord_comp3));
}


/// Returns a surface coordinate object
CoordSurf* SRF_LocalTangentSpaceCylindrical::createSurfaceCoordinate
(
    SRM_Long_Float coord_surf_comp1,
    SRM_Long_Float coord_surf_comp2
)
{
    return (new CoordSurf_LocalTangentSpaceCylindrical(this, coord_surf_comp1, coord_surf_comp2));
}


/// Returns a reference to the SRF parameter structure
const SRM_Local_Tangent_Parameters& SRF_LocalTangentSpaceCylindrical::getSRFParameters() const
{
    Impl_Status status;
    static SRM_Local_Tangent_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "getSRFParameters");

    return params;
}


/// Returns the geodetic_longitude SRF parameter value
SRM_Long_Float SRF_LocalTangentSpaceCylindrical::get_geodetic_longitude() const
{
    Impl_Status                  status;
    SRM_Local_Tangent_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_geodetic_longitude");

    return params.geodetic_longitude;
}


/// Returns the geodetic_latitude SRF parameter value
SRM_Long_Float SRF_LocalTangentSpaceCylindrical::get_geodetic_latitude() const
{
    Impl_Status                  status;
    SRM_Local_Tangent_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_geodetic_latitude");

    return params.geodetic_latitude;
}


/// Returns the azimuth SRF parameter value
SRM_Long_Float SRF_LocalTangentSpaceCylindrical::get_azimuth() const
{
    Impl_Status                  status;
    SRM_Local_Tangent_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_azimuth");

    return params.azimuth;
}


/// Returns the height_offset SRF parameter value
SRM_Long_Float SRF_LocalTangentSpaceCylindrical::get_height_offset() const
{
    Impl_Status                  status;
    SRM_Local_Tangent_Parameters params;

    status = Impl_getSRFParameters(this->_impl, (void *)&params);

    processStatus(status, "get_height_offset");

    return params.height_offset;
}


bool SRF_LocalTangentSpaceCylindrical::isEqual(const SRF_LocalTangentSpaceCylindrical &srf) const
{
    return (Impl_compareSRFParameters(_impl, srf._impl) == 0);
}

bool SRF_LocalTangentSpaceCylindrical::operator== (const SRF_LocalTangentSpaceCylindrical &rhs) const
{
    return(Impl_compareSRFParameters(_impl, rhs._impl) == 0);
}

SRF_LocalTangentSpaceCylindrical* SRF_LocalTangentSpaceCylindrical::makeCopy() const
{
    Impl_Status                       status;
    SRF_LocalTangentSpaceCylindrical *retSRF = NULL;
    void                             *impl = NULL;

    status = Impl_copySRF(_impl, &impl);

    if (status != IMPL_VALID)
      processStatus(status, "makeCopy", SRF, MEM);

    retSRF = new SRF_LocalTangentSpaceCylindrical(impl);

    return retSRF;
}


/// Return char* of Parameter names and their values (one per line)
const char* SRF_LocalTangentSpaceCylindrical::toString()
{
    static char                  ret_string[500];
    static char                  tmp_buffer[50];
    Impl_Status                  status;
    SRM_ORM_Code                 orm;
    SRM_RT_Code                  rt;
    SRM_Local_Tangent_Parameters params;

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
    sprintf(tmp_buffer, "geodetic_longitude=> %f\n", params.geodetic_longitude);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "geodetic_latitude=> %f\n", params.geodetic_latitude);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "azimuth=> %f\n", params.azimuth);
    strcat(ret_string, tmp_buffer);
    sprintf(tmp_buffer, "height_offset=> %f\n", params.height_offset);
    strcat(ret_string, tmp_buffer);

    return ret_string;
}

/// the coordinate equality operator
bool Coord3D_LocalTangentSpaceCylindrical::operator== (const Coord3D_LocalTangentSpaceCylindrical &rhs) const
{
    return ((*(SRF_LocalTangentSpaceCylindrical*)(this->_srf)) == (*(SRF_LocalTangentSpaceCylindrical*)(rhs._srf)) &&
            ARE_EQUAL(_values[0], rhs._values[0]) &&
            ARE_EQUAL(_values[1], rhs._values[1]) &&
            ARE_EQUAL(_values[2], rhs._values[2]));
}

/// the coordinate equality operator
bool CoordSurf_LocalTangentSpaceCylindrical::operator== (const CoordSurf_LocalTangentSpaceCylindrical &rhs) const
{
    return (((*(SRF_LocalTangentSpaceCylindrical*)(this->_srf)) == (*(SRF_LocalTangentSpaceCylindrical*)(rhs._srf))) &&
            ARE_EQUAL(_values[0], rhs._values[0]) &&
            ARE_EQUAL(_values[1], rhs._values[1]));
}
