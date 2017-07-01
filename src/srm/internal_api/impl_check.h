
#ifndef _IMPL_CHECK_H
#define _IMPL_CHECK_H

#include"impl_private.h"

//!This routine checks a coordinate for validity based on the library's internal criteria.

/*!This routine checks a coordinate for validity based on the library's internal criteria
  for the mathematical validity of operations on it.  In many cases this operation will involve
  an implicit conversion performed internal to the library.  This routine implements 
  checkCoordinate() : srm::BaseSRF.  Return is through the status code.
  
  \return IMPL_VALID    The passed coordinate is valid
  \return IMPL_EXTENDED The passed coordinate is extended
  \return IMPL_INVALID  The passed coordinate is invalid
  \return IMPL_DEFINED  The passed coordinate is defined but not extended or valid
  \return IMPL_MEMALLOC A probelm obtaining memory for the test occurred
  \return IMPL_SRFSRC   The passed SRF has parameters that are not consistent with their definitions

*/
Impl_Status
Impl_checkCoordinate2D(void* srf_org,
		     /*!< (Input): \impl_ptr_org_def*/
		       const SRM_Long_Float coord_org[]
		     /*!< (Input): \impl_coord_org_def*/
		     );

//!This routine checks a coordinate for validity based on the library's internal criteria.

/*!This routine checks a coordinate for validity based on the library's internal criteria
  for the mathematical validity of operations on it.  In many cases this operation will involve
  an implicit conversion performed internal to the library.  This routine implements 
  checkCoordinate() : srm::BaseSRF.  Return is through the status code.
  
  \return IMPL_VALID    The passed coordinate is valid
  \return IMPL_EXTENDED The passed coordinate is extended
  \return IMPL_INVALID  The passed coordinate is invalid
  \return IMPL_DEFINED  The passed coordinate is defined but not extended or valid
  \return IMPL_MEMALLOC A problem obtaining memory for the test occurred
  \return IMPL_SRFSRC   The passed SRF has parameters that are not consistent with their definitions

*/
Impl_Status
Impl_checkCoordinate3D(void* srf_org,
		     /*!< (Input): \impl_ptr_org_def*/
		     const SRM_Long_Float coord_org[]
		     /*!< (Input): \impl_coord_org_def*/
		     );

//!This routine checks a surface coordinate for validity based on the library's internal criteria.

/*!This routine checks a surface coordinate for validity based on the library's internal criteria
  for the mathematical validity of operations on it.  In many cases this operation will involve
  an implicit conversion performed internal to the library.  This routine implements 
  checkCoordinate() : srm::BaseSRF.  Return is through the status code.
  
  \return IMPL_VALID    The passed coordinate is valid
  \return IMPL_EXTENDED The passed coordinate is extended
  \return IMPL_INVALID  The passed coordinate is invalid
  \return IMPL_DEFINED  The passed coordinate is defined but not extended or valid
  \return IMPL_MEMALLOC A probelm obtaining memory for the test occurred
  \return IMPL_SRFSRC   The passed SRF has parameters that are not consistent with their definitions

*/
Impl_Status
Impl_checkCoordinateSurface(void* srf_org,
			    /*!< (Input): \impl_ptr_org_def*/
			    const SRM_Long_Float coord_org[]
			    /*!< (Input): \impl_coord_org_def*/
			    );

//!This routine checks a direction for validity based on the library's internal criteria.

/*!This routine checks a direction for validity based on the library's internal criteria
  for the mathematical validity of operations on it.  In many cases this operation will involve
  an implicit conversion performed internally by the library.  This routine implements 
  checkDirection() : srm::BaseSRF_3D.  Return is through the status code.

  \returns IMPL_VALID for valid direction
  \returns IMPL_EXTENDED for direction with extended \a ref_loc_org[]
  \returns IMPL_INVALID for direction with invalid \a ref_loc_org[]
  \returns IMPL_OBJSRC for direction within epsilon of having zero magnitude 
  \returns IMPL_MEMALLOC on out of memory
  \returns IMPL_SRFSRC for a bad \a srf_org

*/
Impl_Status
Impl_checkDirection(void*   srf_org,
		    /*!< (Input): \impl_ptr_org_def*/
		    const SRM_Long_Float ref_loc_org[3],
		    /*!< (Input): \impl_ref_loc_org_def*/
		    const SRM_Long_Float dir_values_org[3]
		    /*!< (Input): \impl_dir_values_org_def*/
		    );

//!This routine checks an orientation for validity based on the library's internal criteria.

/*!This routine checks a orientation for validity based on the library's internal criteria
  for the mathematical validity of operations on it.  In many cases this operation will involve
  an implicit conversion performed internally by the library.  This routine implements 
  checkOrientation() : srm::BaseSRF_3D. Return is through the status code.

  \returns IMPL_VALID for valid orientation
  \returns IMPL_EXTENDED for orientation with extended \a ref_loc_tgt[]
  \returns IMPL_INVALID for orientation with invalid \a ref_loc_tgt[] 
  \returns IMPL_MEMALLOC on out of memory
  \returns IMPL_SRFSRC for a bad source SRF

*/
Impl_Status
Impl_checkOrientation(void*   srf_org,
		      /*!< (Input) \impl_ptr_org_def*/
		      const SRM_Long_Float ref_loc_org[3],
		      /*!< (Input): \impl_ref_loc_org_def*/
		      const SRM_Long_Float matrix_values_org[3][3]
		      /*!< (Input): \impl_dir_values_org_def*/		      
		      );
#endif
