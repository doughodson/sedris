
#ifndef __SRM_SURFACECOORDINATE_H_INCLUDED__
#define __SRM_SURFACECOORDINATE_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** This destroys the Surface Coordinate method list
    @param Destroy in: method list going to be destroyed
*/
typedef struct
{
    SRM_Destroy *Destroy;
} SRM_SurfaceCoordinate_Method_List;

/** This is the Surface Coordinate struct
    @param state in: this surface coordinate SRF
    @param methods in: this surface coordinate methods
*/
typedef struct
{
    void                              *state;
    SRM_SurfaceCoordinate_Method_List *methods;
} SRM_SurfaceCoordinate;

#ifdef __cplusplus
}
#endif
#endif
