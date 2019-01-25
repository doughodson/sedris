
#ifndef __SRM_LAMBERTCONFORMALCONIC_H_INCLUDED__
#define __SRM_LAMBERTCONFORMALCONIC_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This gets the Lambert Conformal Conic SRF parameters.
    @param this_object in: this SRF object
    @param parameters out: resulting in the parameters of lambert conformal conic
    @returns a status code
*/
typedef SRM_Status_Code SRM_LCC_GetSRFParameters
(
    SRM_Object_Reference  this_object,
    SRM_LCC_Parameters   *parameters /* OUT */
);

typedef struct
{
    SRM_AssociateSurfaceCoordinateEH        *AssociateSurfaceCoordinate;
    SRM_ChangeCoordinate3DArraySRF          *ChangeCoordinate3DArraySRF;
    SRM_ChangeCoordinate3DArraySRFObject    *ChangeCoordinate3DArraySRFObject;
    SRM_ChangeCoordinate3DSRF               *ChangeCoordinate3DSRF;
    SRM_ChangeCoordinate3DSRFObject         *ChangeCoordinate3DSRFObject;
    SRM_ChangeDirectionArraySRF             *ChangeDirectionArraySRF;
    SRM_ChangeDirectionArraySRFObject       *ChangeDirectionArraySRFObject;
    SRM_ChangeDirectionSRF                  *ChangeDirectionSRF;
    SRM_ChangeOrientationSRF                *ChangeOrientationSRF;
    SRM_ChangeDirectionSRFObject            *ChangeDirectionSRFObject;
    SRM_ChangeOrientationSRFObject          *ChangeOrientationSRFObject;
    SRM_ConvergenceOfTheMeridian            *ConvergenceOfTheMeridian;
    SRM_CreateCoordinate3D                  *CreateCoordinate3D;
    SRM_CreateDirection                     *CreateDirection;
    SRM_CreateOrientation                   *CreateOrientation;
    SRM_CreateLocalTangentSpaceEuclideanSRF *CreateLocalTangentSpaceEuclideanSRF;
    SRM_CreateSurfaceCoordinateEH           *CreateSurfaceCoordinate;
    SRM_Destroy                             *Destroy;
    SRM_DestroyCoordinate3D                 *DestroyCoordinate3D;
    SRM_DestroyDirection                    *DestroyDirection;
    SRM_DestroyOrientation                  *DestroyOrientation;
    SRM_DestroySurfaceCoordinateEH          *DestroySurfaceCoordinate;
    SRM_EuclideanDistance3D                 *EuclideanDistance3D;
    SRM_EuclideanDistanceEH                 *EuclideanDistanceEH;
    SRM_GeodesicDistance                    *GeodesicDistance;
    SRM_GetCoordinate3DValues               *GetCoordinate3DValues;
    SRM_GetCSCode                           *GetCSCode;
    SRM_GetA                                *GetA;
    SRM_GetF                                *GetF;
    SRM_GetDirectionValues                  *GetDirectionValues;
    SRM_GetNaturalSRFSMemberCode            *GetNaturalSRFSMemberCode;
    SRM_GetOrientationValues                *GetOrientationValues;
    SRM_GetExtendedValidGeodeticRegion      *GetExtendedValidGeodeticRegion;
    SRM_GetExtendedValidRegion              *GetExtendedValidRegion;
    SRM_GetORMCodes                         *GetORMCodes;
    SRM_GetSRFCodes                         *GetSRFCodes;
    SRM_LCC_GetSRFParameters                *GetSRFParameters;
    SRM_GetSurfaceCoordinateValuesEH        *GetSurfaceCoordinateValues;
    SRM_GetValidGeodeticRegion              *GetValidGeodeticRegion;
    SRM_GetValidRegion                      *GetValidRegion;
    SRM_MapAzimuth                          *MapAzimuth;
    SRM_PromoteSurfaceCoordinateEH          *PromoteSurfaceCoordinate;
    SRM_PointDistortion                     *PointDistortion;
    SRM_SetCoordinate3DValues               *SetCoordinate3DValues;
    SRM_SetExtendedValidGeodeticRegion      *SetExtendedValidGeodeticRegion;
    SRM_SetExtendedValidRegion              *SetExtendedValidRegion;
    SRM_SetValidGeodeticRegion              *SetValidGeodeticRegion;
    SRM_SetValidRegion                      *SetValidRegion;
    SRM_VerticalOffset                      *VerticalOffset;
} SRM_LCC_Method_List;

/** This is the struct for the Lambert Conformal Conic SRF.
    @param state in: this SRF state
    @param methods in: this SRF methods list
*/
typedef struct
{
    void                *state;
    SRM_LCC_Method_List *methods;
} SRM_LambertConformalConic;


/** This creates a new Lambert Conformal Conic SRF.
    @param orm_code in: this object reference model
    @param rt_code in: this reference transformation
    @param parameters out: parameters for Lambert Conformal Conic
    @param new_srf out: results in a new SRF
    @returns a status code
*/
extern SRM_Status_Code
SRM_LCC_Create
(
          SRM_ORM_Code               orm_code,
          SRM_RT_Code                rt_code,
    const SRM_LCC_Parameters        *parameters, /* OUT */
          SRM_LambertConformalConic *new_srf     /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
