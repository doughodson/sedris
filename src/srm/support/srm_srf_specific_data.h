
#include "srm_types.h"

/*The following group of functions computes the size of the implementation
  private data structures used to represent certain SRF's internally for computational
  purposes*/
extern SRM_Integer Impl_sizeofprivdatNULL();
extern SRM_Integer Impl_sizeofprivdatCELESTIOCENTRIC();
extern SRM_Integer Impl_sizeofprivdatLOC_SPACE_RECT_3D();
extern SRM_Integer Impl_sizeofprivdatLOC_SPACE_RECT_2D();
extern SRM_Integer Impl_sizeofprivdatCELESTIODETIC();
extern SRM_Integer Impl_sizeofprivdatPLANETODETIC();
extern SRM_Integer Impl_sizeofprivdatLOC_TAN_EUCLIDEAN();
extern SRM_Integer Impl_sizeofprivdatLOC_TAN_AZ_SPHER();
extern SRM_Integer Impl_sizeofprivdatAZIMUTHAL();
extern SRM_Integer Impl_sizeofprivdatLOC_TAN_CYL();
extern SRM_Integer Impl_sizeofprivdatPOLAR();
extern SRM_Integer Impl_sizeofprivdatCELESTIOMAGNETIC();
extern SRM_Integer Impl_sizeofprivdatEQUATORIAL_INERTIAL();
extern SRM_Integer Impl_sizeofprivdatSOLAR_ECLIPTIC();
extern SRM_Integer Impl_sizeofprivdatSOLAR_EQUATORIAL();
extern SRM_Integer Impl_sizeofprivdatSOLAR_MAGNETIC_ECLIPTIC();
extern SRM_Integer Impl_sizeofprivdatSOLAR_MAGNETIC_DIPOLE();
extern SRM_Integer Impl_sizeofprivdatHELIO_ARIES_ECLIPTIC();
extern SRM_Integer Impl_sizeofprivdatHELIO_EARTH_ECLIPTIC();
extern SRM_Integer Impl_sizeofprivdatHELIO_EARTH_EQUAT();
extern SRM_Integer Impl_sizeofprivdatMERCATOR();
extern SRM_Integer Impl_sizeofprivdatOBLIQUE_MERCATOR();
extern SRM_Integer Impl_sizeofprivdatTRANSVERSE_MERCATOR();
extern SRM_Integer Impl_sizeofprivdatLAMBERT_CONF_CONIC();
extern SRM_Integer Impl_sizeofprivdatPOLAR_STEREOGRAPHIC();
extern SRM_Integer Impl_sizeofprivdatEQUIDISTANT_CYL();
extern SRM_Integer Impl_sizeofprivdatLOCOCENTRIC_EUCLIDEAN();



/*The following group of functions allocates internal representations
  of SRF's for use by the API.  This was originally created as a mechanism
  for LTP SRF's to store there generating functions as 4x4 matrices
  internally because there are a fair number of computations needed
  to get to this form and because the code for directions and orientations
  needed to be able to get at this information.*/


/*!<This function returns a valid memory location whose
  address can be used in tests as a value to imply that
  the routine had nothing to return as opposed to NULL
  meaning that the routien got some sort of memory error
*/
extern void* Impl_allocprivdatNONE(void* local_SRFP_struct);
extern void* Impl_allocprivdatCELESTIOCENTRIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatLOC_SPACE_RECT_3D(void* local_SRFP_struct);
extern void* Impl_allocprivdatLOC_SPACE_RECT_2D(void* local_SRFP_struct);
extern void* Impl_allocprivdatCELESTIODETIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatLOC_TAN_EUCLIDEAN(void* local_SRFP_struct);
extern void* Impl_allocprivdatLOC_TAN_AZ_SPHER(void* local_SRFP_struct);
extern void* Impl_allocprivdatAZIMUTHAL(void* local_SRFP_struct);
extern void* Impl_allocprivdatLOC_TAN_CYL(void* local_SRFP_struct);
extern void* Impl_allocprivdatPOLAR(void* local_SRFP_struct);
extern void* Impl_allocprivdatCELESTIOMAGNETIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatEQUATORIAL_INERTIAL(void* local_SRFP_struct);
extern void* Impl_allocprivdatSOLAR_ECLIPTIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatSOLAR_EQUATORIAL(void* local_SRFP_struct);
extern void* Impl_allocprivdatSOLAR_MAGNETIC_DIPOLE(void* local_SRFP_struct);
extern void* Impl_allocprivdatSOLAR_MAGNETIC_ECLIPTIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatHELIO_ARIES_ECLIPTIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatHELIO_EARTH_ECLIPTIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatHELIO_EARTH_EQUAT(void* local_SRFP_struct);
extern void* Impl_allocprivdatMERCATOR(void* local_SRFP_struct);
extern void* Impl_allocprivdatOBLIQUE_MERCATOR(void* local_SRFP_struct);
extern void* Impl_allocprivdatTRANSVERSE_MERCATOR(void* local_SRFP_struct);
extern void* Impl_allocprivdatLAMBERT_CONF_CONIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatPOLAR_STEREOGRAPHIC(void* local_SRFP_struct);
extern void* Impl_allocprivdatEQUIDISTANT_CYL(void* local_SRFP_struct);
extern void* Impl_allocprivdatLOCOCENTRIC_EUCLIDEAN(void* local_SRFP_struct);
