
#ifndef __SRM_COORD_OFFSETS_H_INCLUDED__
#define __SRM_COORD_OFFSETS_H_INCLUDED__

#include "../internal_api/impl_status.h"

#include "srm_types.h"

extern Impl_Status Impl_getOffsetNone(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToCELESTIOCENTRIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToLOC_SPACE_RECT_3D(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToLOC_SPACE_RECT_2D(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToCELESTIODETIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToLOC_TAN_EUCLIDEAN(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToLOC_TAN_AZ_SPHER(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToAZIMUTHAL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToLOC_TAN_CYL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToPOLAR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToCELESTIOMAGNETIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToEQUATORIAL_INERTIAL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToSOLAR_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToSOLAR_EQUATORIAL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToSOLAR_MAGNETIC_DIPOLE(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToSOLAR_MAGNETIC_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToHELIO_ARIES_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToHELIO_EARTH_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToHELIO_EARTH_EQUAT(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToMERCATOR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToOBLIQUE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToTRANSVERSE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToLAMBERT_CONF_CONIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToPOLAR_STEREOGRAPHIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetToEQUIDISTANT_CYL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromCELESTIOCENTRIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromLOC_SPACE_RECT_3D(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromLOC_SPACE_RECT_2D(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromCELESTIODETIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromLOC_TAN_EUCLIDEAN(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromLOC_TAN_AZ_SPHER(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromAZIMUTHAL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromLOC_TAN_CYL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromPOLAR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromCELESTIOMAGNETIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromEQUATORIAL_INERTIAL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromSOLAR_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromSOLAR_EQUATORIAL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromSOLAR_MAGNETIC_DIPOLE(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromSOLAR_MAGNETIC_EQUATORIAL(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromHELIO_ARIES_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromHELIO_EARTH_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromHELIO_EARTH_EQUAT(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromMERCATOR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromOBLIQUE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromTRANSVERSE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromLAMBERT_CONF_CONIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromPOLAR_STEREOGRAPHIC(void* input_srfp, SRM_Long_Float offset[3]);
extern Impl_Status Impl_getOffsetFromEQUIDISTANT_CYL(void* input_srfp, SRM_Long_Float offset[3]);
#endif
