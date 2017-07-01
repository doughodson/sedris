
#ifndef _IMPL_MGRS_H
#define _IMPL_MGRS_H

#include "Coord.h"
#include "impl_status.h"

Impl_Status impl_get_MGRS( void* src_srf,
			   srm::Coord3D* coord, 
			   SRM_Integer precision,
			   char* mgrs);

Impl_Status impl_set_coord( void* src_srf,
			    char* mgrs,
			    srm::Coord3D *coord );

#endif
