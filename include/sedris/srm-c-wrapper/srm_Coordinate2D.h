
#ifndef __SRM_COORDINATE2D_H_INCLUDED__
#define __SRM_COORDINATE2D_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This is to destroy the Coordinate 2D
      @param Destroy in: coordinate to be destroyed
*/
typedef struct {
   SRM_Destroy                               *Destroy;                                 
} SRM_Coordinate2D_Method_List;



/** This is the struct for Coordinate 2D 
      @param state in: this 2D coordinate
      @param methods in: this method list
*/
typedef struct {
   void                                      *state;                                   
   SRM_Coordinate2D_Method_List              *methods;                                 
} SRM_Coordinate2D;


#ifdef __cplusplus
}
#endif
#endif
