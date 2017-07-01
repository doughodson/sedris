
#include "impl_private.h"
#include "impl_status.h"
#include "impl_alloc.h"
#include "impl_change.h"
#include "impl_check.h"
#include "impl_generated.h"

Impl_Status
Impl_checkCoordinate2D
(
          void           *srf_org,
    const SRM_Long_Float  coord_org[]
)
{
    Impl_SRF_ptr my_srf_org=static_cast<Impl_SRF_ptr>(srf_org);
    CHECK_SRFSRC(my_srf_org);
    return IMPL_UNIMPLEM;
}

Impl_Status
Impl_checkCoordinate3D
(
          void           *srf_org,
    const SRM_Long_Float  coord_org[3]
)
{
    Impl_Status status=IMPL_VALID;
    Impl_SRF_ptr my_srf_org=static_cast<Impl_SRF_ptr>(srf_org);

    SRM_SRFT_Code my_bSRFTCode;
    SRM_RT_Code   my_bdRTCode;
    SRM_ORM_Code  my_bdORMCode;

    void *my_bdSRFT = NULL;

    SRM_SRF_Parameters_Info_Code srf_params_info_code;
    void *validation_srf=NULL;

    SRM_Long_Float coord_tgt[3];

    CHECK_SRFSRC(my_srf_org);

    if ((my_srf_org->srf_code | my_srf_org->srfs_code_info.srfs_code)==0)
    {
        /*This is the SRFT case*/
        srf_params_info_code=SRM_SRFPARAMINFCOD_TEMPLATE;
    }
    else if (my_srf_org->srfs_code_info.srfs_code>0)
    {
        srf_params_info_code=SRM_SRFPARAMINFCOD_SET;
    }
    else if (my_srf_org->srf_code>0)
    {
        srf_params_info_code=SRM_SRFPARAMINFCOD_INSTANCE;
    }
    else
    {
        /*The case where we have multiple ones true*/
        status=IMPL_INACTBLE;
        return status;
    }

  /*!\note  This routine does validity for SRFS and SRFT based SRF's correctly.
    For the CD version of the standard it is correct.  It assumes however
    that predefined SRF's are handled by exactly the same mechanism as SRFT's
    except that the parameters are predefined.  In the case of SRFS's,
    different validity criteria can be specified than for the SRFT.  In the case
    of the predefined SRF, this should be implemented by modifying the ops table
    and the bfs search etc but since none of the provided cases require doing so
    (CC and CD cases mainly with no appreciable valid criteria),  We're going to
    be good Extreme Programmers and defer the nasty infrastructure modifications until later.
  */
    switch (srf_params_info_code)
    {
        case SRM_SRFPARAMINFCOD_TEMPLATE:
        case SRM_SRFPARAMINFCOD_INSTANCE:
             my_bSRFTCode = Impl_bSRFTforSRFT[my_srf_org->template_code]();

            if (my_bSRFTCode==0)
            {
                status=IMPL_INACTBLE;
                return status;
            }
            my_bdSRFT    = Impl_bdSRFTforSRFT[my_srf_org->template_code](my_srf_org->orm_code);
            my_bdORMCode = Impl_bdORMforSRFT[my_srf_org->template_code](my_srf_org->orm_code);
            my_bdRTCode  = Impl_bdRTforSRFT[my_srf_org->template_code](my_srf_org->rt_code);
            break;
        case SRM_SRFPARAMINFCOD_SET:
            my_bSRFTCode = Impl_bSRFTforSRFS[my_srf_org->srfs_code_info.srfs_code]();

           if (my_bSRFTCode==0)
           {
               status=IMPL_INACTBLE;
               return status;
           }
           my_bdSRFT    = Impl_bdSRFTforSRFS[my_srf_org->srfs_code_info.srfs_code](my_srf_org->orm_code);
           my_bdORMCode = Impl_bdORMforSRFS[my_srf_org->srfs_code_info.srfs_code](my_srf_org->orm_code);
           my_bdRTCode  = Impl_bdRTforSRFS[my_srf_org->srfs_code_info.srfs_code](my_srf_org->rt_code);
           break;
       default:
           return status;
    }
    {
        if (my_bSRFTCode!=my_srf_org->template_code)
        {
        /*!\note
          This case is where the validity boundaries for
          an SRF are in a different SRF from the SRF itself
        */

        /* my_bdSRFT can legitimately be zero since the parameters are not
          handled inside the structure anymore, so don't need to trap for that
        */
            status=Impl_createSRFFromParams(my_bSRFTCode,
                                            my_bdORMCode, /*Note that this is almost always the input ORM*/
                                            my_bdRTCode, /*Note that this is always the input RT RCS 1.36*/
                                            my_bdSRFT, /*Note that this is always NULL now RCS 1.36*/
                                            &validation_srf);

            if (!(status&IMPL_BADSTAT))
                status|=Impl_changeCoord3DSRF(srf_org,coord_org,validation_srf,coord_tgt);

            if (status&IMPL_BADSTAT)
            {
                Impl_releaseSRF(&validation_srf);
                SIMPLIFY_STATUS(status);
                return status;
            }

        /*We want to override any status that we got during the conversion that
          wasn't bad so that we are sure that we get the status from the
          validation routine which is authoritative as opposed to the conversion
          routine which returns defined in cases where the validation
          calculation is not necessarily on the conversion path used
          This is why set status rather than bitwise oring with it in the switch
        */
            switch (srf_params_info_code)
            {
                case SRM_SRFPARAMINFCOD_TEMPLATE:
                     status=Impl_validcoord3DSRFT[my_srf_org->template_code](my_srf_org->private_data,coord_tgt);
                     break;
                case SRM_SRFPARAMINFCOD_SET:
                     status=Impl_validcoord3DSRFS[my_srf_org->srfs_code_info.srfs_code](my_srf_org->private_data,coord_tgt);
                     break;
                case SRM_SRFPARAMINFCOD_INSTANCE:
                     status=Impl_validcoord3DSRFT[my_srf_org->template_code](my_srf_org->private_data,coord_tgt);
                     break;
            }
            free(my_bdSRFT);
            status|=Impl_releaseSRF(&validation_srf);
        }
        else
        {
            /*!\note this is the easy case where the boundaries are in the same srf*/
            if (status&IMPL_BADSTAT)
            {
                Impl_releaseSRF(&validation_srf);
            }
            else
            {
            /*We want to override any status that we got during the conversion that
              wasn't bad so that we are sure that we get the status from the
              validation routine which is authoritative as opposed to the conversion
              routine which returns defined in cases where the validation
              calculation is not necessarily on the conversion path used
              This is why set status rather than bitwise oring with it in the switch
            */
                switch (srf_params_info_code)
                {
                    case SRM_SRFPARAMINFCOD_TEMPLATE:
                         status=Impl_validcoord3DSRFT[my_bSRFTCode](my_srf_org->private_data,
                                                                    const_cast<SRM_Long_Float*>(coord_org));
                         break;
                    case SRM_SRFPARAMINFCOD_SET:
                         status=Impl_validcoord3DSRFS[my_srf_org->srfs_code_info.srfs_code](my_srf_org->private_data,
                                                                             const_cast<SRM_Long_Float*>(coord_org));
                         break;
                    case SRM_SRFPARAMINFCOD_INSTANCE:
                         status=Impl_validcoord3DSRFT[my_bSRFTCode](my_srf_org->private_data,
                                                                     const_cast<SRM_Long_Float*>(coord_org));
                         break;
                }
            }
        }
        SIMPLIFY_STATUS(status);
        return status;
    }
}


Impl_Status
Impl_checkCoordinateSurface
(
          void           *srf_org,
    const SRM_Long_Float  coord_org[]
)
{
    SRM_Long_Float my_coord_org[3]={coord_org[0],coord_org[1],0.0};

  /*Since this is a passthrough, we don't bother checking the
    validity as the called routine will
  */
    return Impl_checkCoordinate3D(srf_org,my_coord_org);
}

Impl_Status
Impl_checkDirection
(
          void           *srf_org,
    const SRM_Long_Float  ref_loc_org[3],
    const SRM_Long_Float  dir_values_org[3]
)
{
    Impl_Status status;

  /*checkCoordinate3D will check the validity of the SRF object so no
    need to do it again here
  */

    status=Impl_checkCoordinate3D(srf_org,ref_loc_org);
    if ((status & ~( IMPL_BADSTAT)))
    {
        if ((SQUARE(dir_values_org[0])+SQUARE(dir_values_org[1])+SQUARE(dir_values_org[2]))> EPSILON*EPSILON)
        {
            status|=IMPL_VALID;
          /*return the status of the coordinate as long as
            the direction is not of zero magnitude*/
        }
        else
        {
            /*The vector is of zero magnitude*/
            status|=IMPL_INVALID;
        }
    }
    SIMPLIFY_STATUS(status);

    return status;
}

Impl_Status
Impl_checkOrientation
(
          void           *srf_org,
    const SRM_Long_Float  ref_loc_org[3],
    const SRM_Long_Float  matrix_values_org[3][3]
)
{
    Impl_Status status=IMPL_VALID;

    /*checkCoordinate3D will check SRF validity
      so no need to do it again in this routine.
      don't bother with: CHECK_SRFSRC(srf_org);
    */
    status|=Impl_checkCoordinate3D(srf_org,ref_loc_org);

    if (!(status & IMPL_BADSTAT))
    {
        if (Impl_det(matrix_values_org,3)<EPSILON)
            status|=IMPL_INVALID;
        else
            status|=IMPL_VALID;
    }
    SIMPLIFY_STATUS(status);

    return status;
}
