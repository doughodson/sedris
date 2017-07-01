
#ifndef __SRM_DIRECTION_H_INCLUDED__
#define __SRM_DIRECTION_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Destroys the Direction Method List
       @param Destroy in: method list to destroy
*/
typedef struct {
   SRM_Destroy                               *Destroy;                                 
} SRM_Direction_Method_List;

/** SRM_Direction struct
       @param state in: this state
	   @param methods in: methods for direction
*/
typedef struct {
   void                                      *state;                                   
   SRM_Direction_Method_List                 *methods;                                 
} SRM_Direction;


#ifdef __cplusplus
}
#endif
#endif
