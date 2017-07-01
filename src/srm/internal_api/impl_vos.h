
#ifndef _IMPL_VOS_H
#define _IMPL_VOS_H

#include "../support/srm_internal.h"

#include "srm_types.h"
#include "impl_private.h"

Impl_Status Impl_calcDSS_EGM96_GEOID(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_IGLD_1955(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_IGLD_1985(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_MSL(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_NAVD_1988(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_NGVD_1929(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_OSGM_2002(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_WGS84_ELLIPSOID(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);
Impl_Status Impl_calcDSS_WGS84_GEOID(Impl_SRF_ptr srf, SRM_Long_Float wgs84_cd_coord[3], SRM_Long_Float* retval);

extern float WGS84_GeoidSeparationTable[1038961];

extern Impl_Status(*Impl_calcDSS[SRM_DSS_CODE_UBOUND+1])(Impl_SRF_ptr srf, SRM_Long_Float coord[3], SRM_Long_Float* retval);

#endif

