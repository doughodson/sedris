
#ifndef __SRM_LOCALSPACERECTANGULAR2D_H_INCLUDED__
#define __SRM_LOCALSPACERECTANGULAR2D_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This gets the Local Space Rectangular 2D SRF parameters.
    @param this_object in: this SRF object
    @param parameters out: resulting in the parameters of Local Space Rectangular 2D
    @returns a status code
*/
typedef SRM_Status_Code SRM_LSR_2D_GetSRFParameters
(
    SRM_Object_Reference   this_object,
    SRM_LSR_2D_Parameters *parameters /* OUT */
);


typedef struct
{
    SRM_ChangeCoordinate2DArraySRF       *ChangeCoordinate2DArraySRF;
    SRM_ChangeCoordinate2DArraySRFObject *ChangeCoordinate2DArraySRFObject;
    SRM_ChangeCoordinate2DSRF            *ChangeCoordinate2DSRF;
    SRM_ChangeCoordinate2DSRFObject      *ChangeCoordinate2DSRFObject;
    SRM_CreateCoordinate2D               *CreateCoordinate2D;
    SRM_Destroy                          *Destroy;
    SRM_DestroyCoordinate2D              *DestroyCoordinate2D;
    SRM_EuclideanDistance2D              *EuclideanDistance2D;
    SRM_GetCoordinate2DValues            *GetCoordinate2DValues;
    SRM_GetCSCode                        *GetCSCode;
    SRM_GetORMCodes                      *GetORMCodes;
    SRM_GetSRFCodes                      *GetSRFCodes;
    SRM_LSR_2D_GetSRFParameters          *GetSRFParameters;
    SRM_SetCoordinate2DValues            *SetCoordinate2DValues;
} SRM_LSR_2D_Method_List;

/** This is the struct for the Local Space Rectangular 2D SRF.
    @param state in: this SRF state
    @param methods in: this SRF methods list
*/
typedef struct
{
    void                   *state;
    SRM_LSR_2D_Method_List *methods;
} SRM_LocalSpaceRectangular2D;

/** This creates a new Local Space Rectangular 2D SRF.
    @param orm_code in: this object reference model
    @param rt_code in: this reference transformation
    @param parameters in: parameters for Local Space Rectangular 2D
    @param new_srf out: results in a new SRF
    @returns a status code
*/
extern SRM_Status_Code
SRM_LSR_2D_Create
(
          SRM_ORM_Code                 orm_code,
          SRM_RT_Code                  rt_code,
    const SRM_LSR_2D_Parameters       *parameters,
          SRM_LocalSpaceRectangular2D *new_srf  /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
