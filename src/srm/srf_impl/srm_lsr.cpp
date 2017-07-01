/*
 * SRM API
 *
 * FILE       : srm_lsr.cpp
 *
 * PROGRAMMERS: Michele L. Worley (SAIC) Cameron Kellough (SRI)
 *
 * DESCRIPTION:
 *   This file is internal to the SRM API.
 *   Provides reusable functions for conversions between
 *   various flavours of LSR.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

#include "../support/srm_internal.h"
#include "../support/srm_sincos.h"

#include "impl_lsr.h"

Impl_Status
Impl_compute_F_u_v_w
(
    const IMPL_LSR3D_SRFP *lsr_3d_SRF_params_ptr,
          SRM_Long_Float   M[4][4]
)
{
    Impl_Status istat=IMPL_INACTBLE;
  /* These values are column vectors representing the
   * axes primary secondary and tertiary
   */

    SRM_Long_Float  e1[3]={1,0,0};
    SRM_Long_Float  e2[3]={0,1,0};
    SRM_Long_Float  e3[3]={0,0,1};

  /* These values are column vecors representing the
   * Transform Matrix U columns E2 and E3.  E1=E2xE3
   * where x is the vector cross product
   */
    SRM_Long_Float  r[3];  /*direction of forward*/
    SRM_Long_Float  s[3];  /*direction of up     */
    SRM_Long_Float  t[3];  /*t=r x s*/

    switch(lsr_3d_SRF_params_ptr->forward_direction)
    {
        case SRM_AXDIR_POSITIVE_PRIMARY_AXIS:
             SET_VECTOR_EQUAL(r,e1); /*Implicitly multiplied by 1 for positive primary axis*/
             break;

        case SRM_AXDIR_POSITIVE_SECONDARY_AXIS:
             SET_VECTOR_EQUAL(r,e2); /*Implicitly multiplied by 1 for positive secondary axis*/
             break;

        case SRM_AXDIR_POSITIVE_TERTIARY_AXIS:
             SET_VECTOR_EQUAL(r,e3); /*Implicitly multiplied by 1 for positive tertiary axis*/
             break;

        case SRM_AXDIR_NEGATIVE_PRIMARY_AXIS:
             SET_VECTOR_EQUAL(r,e1);
             CONST_TIMES_VECT(-1,r); /*Explicitly multiplied by -1 for negative primary axis*/
             break;

        case SRM_AXDIR_NEGATIVE_SECONDARY_AXIS:
             SET_VECTOR_EQUAL(r,e2);
             CONST_TIMES_VECT(-1,r); /*Explicitly multiplied by -1 for negative secondary axis*/
             break;

        case SRM_AXDIR_NEGATIVE_TERTIARY_AXIS:
             SET_VECTOR_EQUAL(r,e3);
             CONST_TIMES_VECT(-1,r); /*Explicitly multiplied by -1 for negative secondary axis*/
             break;

        default:
             istat=IMPL_SRFSRC;
             return istat;
    }

    switch(lsr_3d_SRF_params_ptr->up_direction)
    {
        case SRM_AXDIR_POSITIVE_PRIMARY_AXIS:
             SET_VECTOR_EQUAL(s,e1); /*Implicitly multiplied by 1 for positive primary axis*/
             break;

        case SRM_AXDIR_POSITIVE_SECONDARY_AXIS:
             SET_VECTOR_EQUAL(s,e2); /*Implicitly multiplied by 1 for positive secondary axis*/
             break;

        case SRM_AXDIR_POSITIVE_TERTIARY_AXIS:
             SET_VECTOR_EQUAL(s,e3); /*Implicitly multiplied by 1 for positive tertiary axis*/
             break;

        case SRM_AXDIR_NEGATIVE_PRIMARY_AXIS:
             SET_VECTOR_EQUAL(s,e1);
             CONST_TIMES_VECT(-1,s); /*Explicitly multiplied by -1 for negative primary axis*/
             break;

        case SRM_AXDIR_NEGATIVE_SECONDARY_AXIS:
             SET_VECTOR_EQUAL(s,e2);
             CONST_TIMES_VECT(-1,s); /*Explicitly multiplied by -1 for negative secondary axis*/
             break;

        case SRM_AXDIR_NEGATIVE_TERTIARY_AXIS:
             SET_VECTOR_EQUAL(s,e3);
             CONST_TIMES_VECT(-1,s); /*Explicitly multiplied by -1 for negative secondary axis*/
             break;

        default:
             istat=IMPL_SRFSRC;
             return istat;
    }
    VECT_CROSS_PROD(r,s,t);  /*t= r x s*/

    if ((SQUARE(t[0])+SQUARE(t[1])+SQUARE(t[2]))<EPSILON*EPSILON)
    {
      /*This is a matrix whose axes are not orthogonal.
        The 3 axes in an LSR 3 must be orthgonal and so we test the
        magnitude of the cross product and if it is near zero,
        we have a problem as the cross product should in general
        have magnitude 1 here.  If it's not one then the user
        has slipped us a nonsense LSR and we respond appropriately.
      */
        istat=IMPL_SRFSRC;
    }
    else
    {
  /*We use t, s and  r and q as column vectors and we initialize the U matrix*/

        /*Following ISO 18026 and a personal communication
          from Paul Berner dated April 28, 2004 we finally resolved that the
          correct nomenclature for the unit vectors in LSR is r,s, and t.
          These are to be column vectors following the notation of the standard
          so that when the matrix formed of them is placed on the left of a
          column vector and multiplied, the result will be a coordinate
          with customary sign and order of the components.
        */
        M[0][0] = r[0];
        M[1][0] = r[1];
        M[2][0] = r[2];
        M[3][0] = 0.0;

        M[0][1] = s[0];
        M[1][1] = s[1];
        M[2][1] = s[2];
        M[3][1] = 0.0;

        M[0][2] = t[0];
        M[1][2] = t[1];
        M[2][2] = t[2];
        M[3][2] = 0.0;

        M[0][3] = 0.0;
        M[1][3] = 0.0;
        M[2][3] = 0.0;
        M[3][3] = 1.0;

        istat=IMPL_VALID;
    }
    return istat;
}


Impl_Status
Impl_compute_F_u_v
(
    const IMPL_LSR2D_SRFP *lsr_2d_SRF_params_ptr,
          SRM_Long_Float   F[4][4]
)
{
    Impl_Status   istat=IMPL_VALID;
  /* These values are column vectors representing the
   * axes primary secondary and
   */
    SRM_Long_Float e1[3]={1,0,0};
    SRM_Long_Float e2[3]={0,1,0};
    SRM_Long_Float s[3],t[3]; /*Where s is forward and t is the other one*/

    switch(lsr_2d_SRF_params_ptr->forward_direction)
    {
        case SRM_AXDIR_POSITIVE_PRIMARY_AXIS:
             SET_VECTOR_EQUAL(s,e1); /*Implicitly multiplied by 1 for positive primary axis*/
             SET_VECTOR_EQUAL(t,e2); /*Implicitly multiplied by 1 for positive primary axis*/
             break;

        case SRM_AXDIR_NEGATIVE_PRIMARY_AXIS:
             SET_VECTOR_EQUAL(s,e1);
             CONST_TIMES_VECT(-1,s); /*Explicitly multiplied by -1 for negative primary axis*/

             SET_VECTOR_EQUAL(t,e2);
             CONST_TIMES_VECT(-1,t); /*Explicitly multiplied by -1 for negative primary axis*/
             break;

        default:
             istat=IMPL_SRFSRC;
             return istat;
    }
    F[0][0] = s[0];
    F[1][0] = t[0];
    F[2][0] = 0.0;
    F[3][0] = 0.0;

    F[0][1] = s[1];
    F[1][1] = t[1];
    F[2][1] = 0.0;
    F[3][1] = 0.0;

    F[0][2] = 0.0;
    F[1][2] = 0.0;
    F[2][2] = 1.0;
    F[3][2] = 0.0;

    F[0][3] = 0.0;
    F[1][3] = 0.0;
    F[2][3] = 0.0;
    F[3][3] = 1.0;

    return istat;
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: set_lsr3D_lsr3D_constants
 *
 *----------------------------------------------------------------------------
 */
void
set_lsr3D_to_lsr3D_constants
(
    const IMPL_LSR3D_SRFP                *lsr3d_srf_src,
    const IMPL_LSR3D_SRFP                *lsr3d_srf_tgt,
          SRM_LSR_LSR_Specific_Constants *lsr_spec
)
{
    Impl_Status status=IMPL_VALID;

    SRM_Long_Float
      F_src[4][4],
      F_tgt[4][4],
      F_inv_tgt[4][4];

    status|=Impl_compute_F_u_v_w(lsr3d_srf_src, F_src);
    status|=Impl_compute_F_u_v_w(lsr3d_srf_tgt, F_tgt);

#if 0
    if(status!=IMPL_VALID)
        abort();

  /*! \bug $$$ this doesn't account for invalid axes*/
#endif

    Impl_transpose(F_tgt,F_inv_tgt,4);

    Impl_matrix_multiply4x4
    (
     F_inv_tgt,
     F_src,
     lsr_spec->transformation_matrix
     );
}

void
set_lsr3D_to_pos3_constants
(
    const IMPL_LSR3D_SRFP                *lsr3d_srf_src,
          SRM_LSR_LSR_Specific_Constants *lsr_spec
)
{
    Impl_compute_F_u_v_w(lsr3d_srf_src, lsr_spec->transformation_matrix);
}

void
set_pos3_to_lsr3D_constants
(
    const IMPL_LSR3D_SRFP                *lsr3d_srf_tgt,
          SRM_LSR_LSR_Specific_Constants *lsr_spec
)
{
    SRM_Long_Float F_tgt[4][4];

    Impl_compute_F_u_v_w(lsr3d_srf_tgt, F_tgt);

    Impl_transpose(F_tgt, lsr_spec->transformation_matrix, 4);
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: set_lsr2D_lsr2D_constants
 *
 *   This function returns either identity or negative identity matrix
 *
 *----------------------------------------------------------------------------
 */
void
set_lsr2D_to_pos2_constants
(
    const IMPL_LSR2D_SRFP                *lsr2d_srf_src,
          SRM_LSR_LSR_Specific_Constants *lsr_spec
)
{
    Impl_compute_F_u_v(lsr2d_srf_src, lsr_spec->transformation_matrix);
}


void
set_pos2_to_lsr2D_constants
(
    const IMPL_LSR2D_SRFP                *lsr2d_srf_tgt,
          SRM_LSR_LSR_Specific_Constants *lsr_spec
)
{
    SRM_Long_Float F_tgt[4][4];

    Impl_compute_F_u_v(lsr2d_srf_tgt, F_tgt);
    Impl_transpose(F_tgt,lsr_spec->transformation_matrix,4);
}


void
set_lsr2D_to_lsr2D_constants
(
    const IMPL_LSR2D_SRFP                    *lsr2d_srf_src,
    const IMPL_LSR2D_SRFP                    *lsr2d_srf_tgt,
          SRM_LSR2D_LSR2D_Specific_Constants *lsr_spec
)
{
    SRM_Long_Float
      F_src[4][4],
      F_tgt[4][4],
      F_inv_tgt[4][4]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    Impl_compute_F_u_v(lsr2d_srf_src, F_src);
    Impl_compute_F_u_v(lsr2d_srf_tgt, F_tgt);

    Impl_transpose(F_tgt,F_inv_tgt,4);

    Impl_matrix_multiply4x4(F_src, F_inv_tgt, lsr_spec->transformation_matrix);
}

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: Impl_ChangeLSR_LSR
 *
 *   SRM_ChangeLSR_LSR for both 2D and 3D LSR cases
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
Impl_ChangeLSR_LSR
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    const SRM_LSR_LSR_Specific_Constants *lsr_lsr_spec= (SRM_LSR_LSR_Specific_Constants*) constants;

    /*!\note This entire operation is just multiplying by the prestored
     *transformation matrix.
     */
    Impl_MultMatrixVector((lsr_lsr_spec->transformation_matrix),
                          source_generic_coordinate,
                          dest_generic_coordinate,
                          4);
    return IMPL_VALID;
} /* end SRM_ChangeLSR_LSR */


/* This function is used to convert LSR to/from POS. */
Impl_Status
SRM_ChangeLSR_POS
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    const SRM_LSR_LSR_Specific_Constants *lsr_lsr_spec= (SRM_LSR_LSR_Specific_Constants*) constants;

  /*!\note This entire operation is just multiplying by the prestored
   *transformation matrix.
   */
    Impl_MultMatrixVector((lsr_lsr_spec->transformation_matrix),
                        source_generic_coordinate,
                        dest_generic_coordinate,
                        4);
    return IMPL_VALID;
} /* end SRM_ChangeLSR_POS */

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeLSR2_AZ
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeLSR2_AZ
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    // azimuth = arctan2(u, v)
    dest_generic_coord[0] = atan2(source_generic_coord[0], source_generic_coord[1]);

    if (dest_generic_coord[0] < 0.0)
        dest_generic_coord[0]+= SRM_2_PI;

    // radius = sqrt(x^2 + y^2)
    dest_generic_coord[1] = sqrt(source_generic_coord[0] * source_generic_coord[0] +
                                 source_generic_coord[1] * source_generic_coord[1]);

    return status;
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeAZ_LSR2
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeAZ_LSR2
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    SRM_Long_Float ssrc, csrc;

    srm_sincos(source_generic_coord[0], ssrc, csrc);

    // u = radius * sin (azimuth)
    dest_generic_coord[0] = source_generic_coord[1] * ssrc;

    // v = radius * cos (azimuth)
    dest_generic_coord[1] = source_generic_coord[1] * csrc;

    return status;
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangeLSR2_POL2
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangeLSR2_POL2
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    // azimuth = arctan2(u, v)
    dest_generic_coord[0] = atan2(source_generic_coord[1], source_generic_coord[0]);

    if (dest_generic_coord[0] < 0.0)
        dest_generic_coord[0]+= SRM_2_PI;

    // radius = sqrt(x^2 + y^2)
    dest_generic_coord[1] = sqrt(source_generic_coord[0] * source_generic_coord[0] +
                                 source_generic_coord[1] * source_generic_coord[1]);
    return status;
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SRM_ChangePOL2_LSR2
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
SRM_ChangePOL2_LSR2
(
          void           *constants,
    const SRM_Long_Float  source_generic_coord[4],
          SRM_Long_Float  dest_generic_coord[4]
)
{
    Impl_Status status = IMPL_VALID;

    SRM_Long_Float ssrc, csrc;

    srm_sincos(source_generic_coord[0], ssrc, csrc);

    // u = radius * sin (azimuth)
    dest_generic_coord[0] = source_generic_coord[1] * csrc;

    // v = radius * cos (azimuth)
    dest_generic_coord[1] = source_generic_coord[1] * ssrc;

    return status;
}
