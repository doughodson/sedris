
#ifndef __SRM_CHECK_H__
#define __SRM_CHECK_H__

// Contains prototypes for functions that validate SRF parameters.

#include "srm_internal.h"

#include "../srf_impl/orm_rd_struct.h"

extern Impl_Status Impl_checksrfNULL(void* input_srfp);
extern Impl_Status Impl_checksrfCELESTIOCENTRIC(void* input_srfp);
extern Impl_Status Impl_checksrfLOC_SPACE_RECT_3D(void* input_srfp);
extern Impl_Status Impl_checksrfLOC_SPACE_RECT_2D(void* input_srfp);
extern Impl_Status Impl_checksrfCELESTIODETIC(void* input_srfp);
extern Impl_Status Impl_checksrfPLANETODETIC(void* input_srfp);
extern Impl_Status Impl_checksrfLOC_TAN_EUCLIDEAN(void* input_srfp);
extern Impl_Status Impl_checksrfLOC_TAN_AZ_SPHER(void* input_srfp);
extern Impl_Status Impl_checksrfAZIMUTHAL(void* input_srfp);
extern Impl_Status Impl_checksrfLOC_TAN_CYL(void* input_srfp);
extern Impl_Status Impl_checksrfPOLAR(void* input_srfp);
extern Impl_Status Impl_checksrfCELESTIOMAGNETIC(void* input_srfp);
extern Impl_Status Impl_checksrfEQUATORIAL_INERTIAL(void* input_srfp);
extern Impl_Status Impl_checksrfSOLAR_ECLIPTIC(void* input_srfp);
extern Impl_Status Impl_checksrfSOLAR_EQUATORIAL(void* input_srfp);
extern Impl_Status Impl_checksrfSOLAR_MAGNETIC_ECLIPTIC(void* input_srfp);
extern Impl_Status Impl_checksrfSOLAR_MAGNETIC_DIPOLE(void* input_srfp);
extern Impl_Status Impl_checksrfHELIO_ARIES_ECLIPTIC(void* input_srfp);
extern Impl_Status Impl_checksrfHELIO_EARTH_ECLIPTIC(void* input_srfp);
extern Impl_Status Impl_checksrfHELIO_EARTH_EQUAT(void* input_srfp);
extern Impl_Status Impl_checksrfMERCATOR(void* input_srfp);
extern Impl_Status Impl_checksrfOBLIQUE_MERCATOR(void* input_srfp);
extern Impl_Status Impl_checksrfTRANSVERSE_MERCATOR(void* input_srfp);
extern Impl_Status Impl_checksrfLAMBERT_CONF_CONIC(void* input_srfp);
extern Impl_Status Impl_checksrfPOLAR_STEREOGRAPHIC(void* input_srfp);
extern Impl_Status Impl_checksrfEQUIDISTANT_CYL(void* input_srfp);
extern Impl_Status Impl_checksrfLOCOCENTRIC_EUCLIDEAN(void* input_srfp);


/*!< The functions here shall return
  IMPL_SRFSRC,  bad SRF
  IMPL_BADORM   bad ORM
  IMPL_VALID,   no problem
  IMPL_UNIMPLEM unimplemented validation
*/

#endif
