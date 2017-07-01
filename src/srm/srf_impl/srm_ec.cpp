/*
 * SRM API
 *
 * FILE       : srm_ec.cpp
 *
 * PROGRAMMERS: Cameron Kellough (SRI) Dan Toms (SRI)
 *
 * DESCRIPTION: Provide reusable functions for conversions between
 *              various flavors of EC SRFs.
 *              This file is internal to the SRM API.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../support/srm_ctypes.h"
#include "../support/srm_sincos.h"
#include "../support/srm_internal.h"

#include "../internal_api/impl_srf_params.h"

#include "srm_types.h"

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: set_ec_constants
 *
 *   Computes and stores the constants used for conversions involving EC
 *
 * PARAMETERS:
 *
 *   e_constants - pointer to the converted ellipse constants
 *
 *   ec - a pointer to the parameters of a (destination) EC system
 *
 *   ec_spec - a pointer to where the constants will be stored for an
 *             EC to CD conversion
 *
 * RETURNS: nothing
 *   Instead of returning a value, this function sets constants in the
 *   the structure pointed to by the ec_spec parameter.
 *
 *----------------------------------------------------------------------------
 */
void
set_ec_constants
(
    const Impl_ORM_Data             *e_constants,
    const IMPL_EQUIDISTANT_CYL_SRFP *ec_srf,
          SRM_EC_Specific_Constants *ec_spec
)
{
    ec_spec->longitude_origin = ec_srf->origin_longitude;
    ec_spec->e_constants      = *e_constants;
    ec_spec->scale_factor     = ec_srf->central_scale;
    ec_spec->scale_factor_inv = 1.0/ec_spec->scale_factor;

    /*Note that this is the same conap from tm_cd*/
    ec_spec->conap=
      e_constants->A* (1.0-
               e_constants->Eps2*
               (.250+
            e_constants->Eps2*
            (.0468750+
             e_constants->Eps2* (0.019531250+
                         0.010681152343750*
                         e_constants->Eps2))));

    ec_spec->conap_inv=1.0/ec_spec->conap;
    Impl_ComputeArcLengthConstants(e_constants,&ec_spec->al);
    Impl_ComputeFootpointConstants(e_constants,
                   &ec_spec->al, /*Relies on arc length initialization constants*/
                   &ec_spec->fp,
                   1.0);

    /*The central scale factor is 1.0 in the latitude coordinate curve by
     * definition in equidistant cylindrical due to the fact the equidistant
     * implies that the change in y mapp coordinates is always proportional to
     * the arc length.
     */
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeCD_EC
 *
 *   For spherical ORMs only, no height conversion.
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeCD_EC
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    Impl_Status istat=IMPL_VALID;
    SRM_EC_Specific_Constants *cd_ec_spec =(SRM_EC_Specific_Constants*)(constants);
    Impl_ORM_Data  *e_constants=&cd_ec_spec->e_constants;
    SRM_Long_Float *dest_x_ptr=&dest_generic_coordinate[0],
                   *dest_y_ptr=&dest_generic_coordinate[1],
                   *dest_z_ptr=&dest_generic_coordinate[2],
                   source_lon=source_generic_coordinate[0],
                   source_lat=source_generic_coordinate[1],
                   source_elv=source_generic_coordinate[2],
                   lambda_star;

    GET_LAMBDA_STAR(source_lon, cd_ec_spec->longitude_origin, lambda_star);

    *dest_x_ptr = e_constants->A*cd_ec_spec->scale_factor*lambda_star;

   /* Note that the y term does not have the scale factor k0 in it,
      because equidistant cylindrical would not be an equidistant
      projection if it did
    */
    if (e_constants->Eps2 != 0.0) /* ellipsoidal case */
    {
        *dest_y_ptr = Impl_ArcLength(&cd_ec_spec->al,
                      source_lat,
                      srm_sin(source_lat),
                      srm_cos(source_lat));
    }
    else /* spherical case */
    {
        *dest_y_ptr=source_lat*e_constants->A;
    }
    *dest_z_ptr=source_elv;

    return istat;
}

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeEC_CD
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeEC_CD
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    Impl_Status   istat = IMPL_VALID;
    SRM_EC_Specific_Constants *ec_cd_spec = (SRM_EC_Specific_Constants *)constants;

    Impl_ORM_Data*  e_constants=&ec_cd_spec->e_constants;

    SRM_Long_Float
    *dest_lon_ptr= &dest_generic_coordinate[0],
    *dest_lat_ptr= &dest_generic_coordinate[1],
    source_x = source_generic_coordinate[0],
    source_y = source_generic_coordinate[1],
    source_z = source_generic_coordinate[2];

    SRM_Long_Float lambda, lambda_star;

    lambda =
        source_x * ec_cd_spec->scale_factor_inv * e_constants->A_inv;

    GET_LAMBDA_STAR( lambda, (-ec_cd_spec->longitude_origin), lambda_star);
  /*We have to use -ec_cd_spec->longitude_origin as the macro was designed
    for the forward case where you subtract the offset and we are in the inverse
    case where we need to add it.
  */

    *dest_lon_ptr = lambda_star;

    if (e_constants->Eps2!=0.0)
    { /*Ellipsoidal case*/
        *dest_lat_ptr=Impl_Footpoint(e_constants,
                     &ec_cd_spec->al,
                     &ec_cd_spec->fp,
                     source_y*ec_cd_spec->conap_inv);
    /*Note k0 is always unity and false northing is handled externally by the
      offset mechanism meaning that the footpoint just needs to be
      computed on source_y
      here*/
    }
    else
    { /*Spherical Case*/
        *dest_lat_ptr = (source_y * e_constants->A_inv);
    }
    dest_generic_coordinate[2]= source_z;

    SE_FIX_LONGITUDE(*dest_lon_ptr);

    return istat;
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_COM_EC
 *
 *   Returns sin and cos of gamma=0 in the first two arguments of dest_generic_coordinate
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_COM_EC
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    dest_generic_coordinate[0]=0.0; /* sin(gamma=0.0)=0.0*/
    dest_generic_coordinate[0]=1.0; /* cos(gamma=0.0)=1.0*/

    return IMPL_VALID;
}
