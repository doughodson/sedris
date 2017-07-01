
#ifndef __SRM_LOCALSPACERECTANGULAR3D_H_INCLUDED__
#define __SRM_LOCALSPACERECTANGULAR3D_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This gets the Local Space Rectangular 3D SRF parameters.
    @param this_object in: this SRF object
    @param parameters out: resulting in the parameters of Local Space Rectangular 3D
    @returns a status code
*/
typedef SRM_Status_Code SRM_LSR_3D_GetSRFParameters
(
    SRM_Object_Reference   this_object,
    SRM_LSR_3D_Parameters *parameters /* OUT */
);


typedef struct
{
    SRM_ChangeCoordinate3DArraySRF       *ChangeCoordinate3DArraySRF;
    SRM_ChangeCoordinate3DArraySRFObject *ChangeCoordinate3DArraySRFObject;
    SRM_ChangeCoordinate3DSRF            *ChangeCoordinate3DSRF;
    SRM_ChangeCoordinate3DSRFObject      *ChangeCoordinate3DSRFObject;
    SRM_ChangeDirectionArraySRF          *ChangeDirectionArraySRF;
    SRM_ChangeDirectionArraySRFObject    *ChangeDirectionArraySRFObject;
    SRM_ChangeDirectionSRF               *ChangeDirectionSRF;
    SRM_ChangeOrientationSRF             *ChangeOrientationSRF;
    SRM_ChangeDirectionSRFObject         *ChangeDirectionSRFObject;
    SRM_CreateCoordinate3D               *CreateCoordinate3D;
    SRM_CreateDirection                  *CreateDirection;
    SRM_CreateOrientation                *CreateOrientation;
    SRM_ChangeOrientationSRFObject       *ChangeOrientationSRFObject;
    SRM_Destroy                          *Destroy;
    SRM_DestroyCoordinate3D              *DestroyCoordinate3D;
    SRM_DestroyDirection                 *DestroyDirection;
    SRM_DestroyOrientation               *DestroyOrientation;
    SRM_EuclideanDistance3D              *EuclideanDistance3D;
    SRM_GetCoordinate3DValues            *GetCoordinate3DValues;
    SRM_GetCSCode                        *GetCSCode;
    SRM_GetDirectionValues               *GetDirectionValues;
    SRM_GetNaturalSRFSMemberCode         *GetNaturalSRFSMemberCode;
    SRM_GetOrientationValues             *GetOrientationValues;
    SRM_GetExtendedValidRegion           *GetExtendedValidRegion;
    SRM_GetORMCodes                      *GetORMCodes;
    SRM_GetSRFCodes                      *GetSRFCodes;
    SRM_LSR_3D_GetSRFParameters          *GetSRFParameters;
    SRM_GetValidRegion                   *GetValidRegion;
    SRM_SetCoordinate3DValues            *SetCoordinate3DValues;
    SRM_SetExtendedValidRegion           *SetExtendedValidRegion;
    SRM_SetValidRegion                   *SetValidRegion;
} SRM_LSR_3D_Method_List;

/** This is the struct for the Local Space Rectangular 3D SRF.
    @param state in: this SRF state
    @param methods in: this SRF methods list
*/
typedef struct
{
    void                   *state;
    SRM_LSR_3D_Method_List *methods;
} SRM_LocalSpaceRectangular3D;


/** This creates a new local space rectangular 3D SRF.
    @param orm_code in: this object reference model
    @param rt_code in: this reference transformation
    @param parameters in: parameters for Local Space Rectangular 3D
    @param new_srf out: results in a new SRF
    @returns a status code
*/
extern SRM_Status_Code
SRM_LSR_3D_Create
(
          SRM_ORM_Code                 orm_code,
          SRM_RT_Code                  rt_code,
    const SRM_LSR_3D_Parameters       *parameters,
          SRM_LocalSpaceRectangular3D *new_srf /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
