
#ifndef __SRM_ORIENTATION_H_INCLUDED__
#define __SRM_ORIENTATION_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

/** Destroys the Orientation method list
    @param Orientation in: method list to destroy
*/
typedef struct
{
    SRM_Destroy *Destroy;                                 
} SRM_Orientation_Method_List;

/** SRM_Orientation struct
    @param state in: this state
    @param methods in: methods for orientation
*/
typedef struct
{
    void                        *state;                                   
    SRM_Orientation_Method_List *methods;                                 
} SRM_Orientation;


#ifdef __cplusplus
}
#endif
#endif
