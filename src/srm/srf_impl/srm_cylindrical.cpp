/*
 * SRM API
 *
 * FILE       : srm_cylindrical.cpp
 *
 * PROGRAMMERS: Cameron Kellough (SRI)
 *
 * DESCRIPTION: Provide reusable functions for conversions between
 *              SRFs based on cylindrical coordinates and position
 *              space (CC for object's reference ORM).
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../support/srm_ctypes.h"
#include "../support/srm_sincos.h"
#include "../support/srm_internal.h"

#include "srm_types.h"

void
set_LCTP_LTSE_constants
(
    IMPL_LOC_TAN_CYL_SRFP            *lctp_srf_src,
    IMPL_LOC_TAN_EUCLIDEAN_SRFP      *ltse_srf_tgt,
    SRM_LCTP_LTSE_Specific_Constants *lctp_ltse_spec
)
{
    lctp_ltse_spec->LCTP_Azimuth=lctp_srf_src->azimuth;
    lctp_ltse_spec->LCTP_Height_Offset=lctp_srf_src->height_offset;
    lctp_ltse_spec->LTSE_Azimuth=ltse_srf_tgt->azimuth;
    lctp_ltse_spec->LTSE_Height_Offset=ltse_srf_tgt->height_offset;
}


Impl_Status
Impl_ChangeCylindrical_CC
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    SRM_LCTP_LTSE_Specific_Constants* lctp_ltse_spec= (SRM_LCTP_LTSE_Specific_Constants*) constants;

    const SRM_Long_Float
    *theta_ptr=  &source_generic_coordinate[0],
    *rho_ptr=    &source_generic_coordinate[1],
    *zeta_ptr=   &source_generic_coordinate[2];

    SRM_Long_Float
    *x_ptr=&dest_generic_coordinate[0],
    *y_ptr=&dest_generic_coordinate[1],
    *z_ptr=&dest_generic_coordinate[2];

    SRM_Long_Float theta_star;

    GET_ALPHA_STAR(*theta_ptr,0,theta_star);

    GET_ALPHA_STAR(theta_star,lctp_ltse_spec->LCTP_Azimuth,theta_star); /*Subtract LCTP Azimuth*/
    GET_ALPHA_STAR(theta_star,-lctp_ltse_spec->LTSE_Azimuth,theta_star); /*ADD LTSE azimuth*/

    *x_ptr= (*rho_ptr) * srm_cos(theta_star);
    *y_ptr= (*rho_ptr) * srm_sin(theta_star);

    *z_ptr= (*zeta_ptr-lctp_ltse_spec->LCTP_Height_Offset+lctp_ltse_spec->LTSE_Height_Offset);

    return IMPL_VALID;
}


void
set_LTSE_LCTP_constants
(
    IMPL_LOC_TAN_EUCLIDEAN_SRFP      *ltse_srf_src,
    IMPL_LOC_TAN_CYL_SRFP            *lctp_srf_tgt,
    SRM_LTSE_LCTP_Specific_Constants *ltse_lctp_spec
)
{
    ltse_lctp_spec->LTSE_Azimuth=ltse_srf_src->azimuth;
    ltse_lctp_spec->LTSE_Height_Offset=ltse_srf_src->height_offset;

    ltse_lctp_spec->LCTP_Azimuth=lctp_srf_tgt->azimuth;
    ltse_lctp_spec->LCTP_Height_Offset=lctp_srf_tgt->height_offset;
}


Impl_Status
Impl_ChangeCC_Cylindrical
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    SRM_LTSE_LCTP_Specific_Constants* ltse_lctp_spec= (SRM_LTSE_LCTP_Specific_Constants*) constants;

    const SRM_Long_Float
    *x_ptr=&source_generic_coordinate[0],
    *y_ptr=&source_generic_coordinate[1],
    *z_ptr=&source_generic_coordinate[2];

    SRM_Long_Float
    *theta_ptr=  &dest_generic_coordinate[0],
    *rho_ptr=    &dest_generic_coordinate[1],
    *zeta_ptr=   &dest_generic_coordinate[2];

    if ((*x_ptr != 0.0) && (*y_ptr != 0.0))
    {
        *theta_ptr=atan2(*y_ptr,*x_ptr);

        GET_ALPHA_STAR(*theta_ptr,0,*theta_ptr);

        GET_ALPHA_STAR(*theta_ptr,ltse_lctp_spec->LTSE_Azimuth,*theta_ptr); /*Subtract LTSE azimuth*/
        GET_ALPHA_STAR(*theta_ptr,-(ltse_lctp_spec->LCTP_Azimuth),*theta_ptr); /*Add LCTP Azimuth*/
       /*Note that this line adds by subtracting a negative number because the macro in question subtracts*/

        *rho_ptr=sqrt(SQUARE(*x_ptr) +SQUARE(*y_ptr));
        *zeta_ptr=(*z_ptr - ltse_lctp_spec->LTSE_Height_Offset + ltse_lctp_spec->LCTP_Height_Offset );
    }
    else
    {
        *theta_ptr = 0.0;
        *rho_ptr   = 0.0;
        *zeta_ptr  = *z_ptr;
    }
    return IMPL_VALID;
}
