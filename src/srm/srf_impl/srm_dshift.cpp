
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../support/srm_internal.h"

#include "orm_rd_struct.h"

void
set_dshift_constants
(
    SRM_ORM_Code                    orm_src,
    SRM_RT_Code                     rt_src,
    SRM_ORM_Code                    orm_tgt,
    SRM_RT_Code                     rt_tgt,
    Impl_Dshift_Specific_Constants *dshift_spec
)
{
    const Impl_RT_Struct *hs=Impl_getRTstruct(orm_src,rt_src);
    const Impl_RT_Struct *ht=Impl_getRTstruct(orm_tgt,rt_tgt);

    SRM_Long_Float T_SR[4][4],T_RT[4][4];

    memcpy(T_SR,Impl_Identity_Matrix4x4,sizeof(Impl_Identity_Matrix4x4));
    memcpy(T_RT,Impl_Identity_Matrix4x4,sizeof(Impl_Identity_Matrix4x4));

  /*\bug  This test is an emergency workaround for a code generator issue
   The test can be removed when there aren't Nan's in the identity matrices
  */
   /* Need to check if hs has NaNs in it, and allow for it
    * - identity :  hs is all NaN
    * - translate: hs is NaN for everything but the translate parameters
    */
  /*We initialize the scale values here since they only become non-unity
    if one of the conditions below is met
  */

    if (hs->delta_x==hs->delta_x)
    {
        SRM_WGS84_Transformation_Matrix(T_SR,
                                      hs->delta_x,
                                      hs->delta_y,
                                      hs->delta_z,
                                      hs->omega_1,  /* omega_1 rot around x_axis*/
                                      hs->omega_2,  /* omega_2 rot around y_axis*/
                                      hs->omega_3,  /* omega_3 rot around z_axis*/
                                      hs->delta_scale
                                      );
    }

    if (ht->delta_x==ht->delta_x)
    {
        SRM_WGS84_InverseTransformation_Matrix(T_RT,
                                             ht->delta_x,
                                             ht->delta_y,
                                             ht->delta_z,
                                             ht->omega_1,  /* omega_1 rot around x_axis*/
                                             ht->omega_2,  /* omega_2 rot around y_axis*/
                                             ht->omega_3,  /* omega_3 rot around z_axis*/
                                             ht->delta_scale
                                             );
    }
    Impl_matrix_multiply4x4(T_RT,T_SR,dshift_spec->Tst);
}


Impl_Status
SRM_ChangeCCA_CCB
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    Impl_Dshift_Specific_Constants* dshift_spec = (Impl_Dshift_Specific_Constants*) constants;

    Impl_MultMatrixVector(dshift_spec->Tst,
                          source_generic_coordinate,
                          dest_generic_coordinate,
                          4);

    return IMPL_VALID;
}


Impl_Status
SRM_ChangePOS2A_POS2B
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    Impl_Dshift_Specific_Constants* dshift_spec = (Impl_Dshift_Specific_Constants*) constants;

    Impl_MultMatrixVector(dshift_spec->Tst,
                          source_generic_coordinate,
                          dest_generic_coordinate,
                          4);

    return IMPL_VALID;
}


Impl_Status
SRM_ChangePOS3A_POS3B
(
          void           *constants,
    const SRM_Long_Float  source_generic_coordinate[4],
          SRM_Long_Float  dest_generic_coordinate[4]
)
{
    Impl_Dshift_Specific_Constants* dshift_spec = (Impl_Dshift_Specific_Constants*) constants;

    Impl_MultMatrixVector(
                        dshift_spec->Tst,
                        source_generic_coordinate,
                        dest_generic_coordinate,
                        4);

    return IMPL_VALID;
}
