
#ifndef __SRM_COORDINATE3D_H_INCLUDED__
#define __SRM_COORDINATE3D_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This method gets the MGRS string for this coordinate
*/
typedef SRM_Status_Code SRM_GetMGRS 
(
        SRM_Object_Reference        this_object,
		SRM_Integer                 precision,
  const char                        **mgrs_string
);

/** This method sets this coordinate based on the input MGRS string
*/
typedef SRM_Status_Code SRM_SetCoord 
(
        SRM_Object_Reference        this_object,                   
  const char                        *mgrs_string
);

/** This is to destroy the Coordinate 3D
    @param Destroy in: coordinate to be destroyed
*/
typedef struct {
   SRM_GetMGRS                               *GetMGRS;
   SRM_SetCoord                              *SetCoord;
   SRM_Destroy                               *Destroy;                                 
} SRM_Coordinate3D_Method_List;


/** This is the struct for Coordinate 3D 
      @param state in: this 3D coordinate
      @param methods in: this method list
*/
typedef struct {
   void                                      *state;                                   
   SRM_Coordinate3D_Method_List              *methods;                                 
} SRM_Coordinate3D;


#ifdef __cplusplus
}
#endif
#endif




