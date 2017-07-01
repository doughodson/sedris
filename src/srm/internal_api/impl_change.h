
#ifndef _IMPL_CHANGE_H
#define _IMPL_CHANGE_H

#include "impl_private.h"
#include "impl_status.h"

//!  Changes the represenation from one SRF to another for 2D coordinates.

/*! This routine changes the representation of a 2D location from one 2D SRF to another 2D SRF.
  This routine implements changeCoordinate2DSRF() : srm::BaseSRF_2D

  \remark It is the responsiblity of the API to call the appropriate 2D or 3D version of this function.  
  \note Invalid is directly propogated to tgt if source is invalid.
  \returns IMPL_VALID for valid target coordinate
  \returns IMPL_EXTENDED for extended target coordinate
  \returns IMPL_INVALID for invalid target coordinate  
  \returns IMPL_MEMALLOC on out of memory
  \returns IMPL_SRFSRC for a bad source SRF
  \returns IMPL_SRFTGT for a bad target SRF

*/
Impl_Status
Impl_changeCoord2DSRF(void* srf_src,
		      /*!< (Input): \impl_ptr_src_def*/
		      const SRM_Long_Float coord_src[2],
		      /*!< (Input): \impl_coord_src_def*/
		      void* srf_tgt, 
		      /*!< (Input): \impl_ptr_tgt_def*/
		      SRM_Long_Float coord_tgt[2]
		      /*!< (Output): \impl_coord_tgt_def*/
		      );


Impl_Status
Impl_changeCoord2DSRFObject (void* srf_src,
			     /*!< (Input): \impl_ptr_src_def*/
			     const SRM_Long_Float coord_src[2],
			     /*!< (Input): \impl_coord_src_def*/
			     void* srf_tgt, 
			     /*!< (Input): \impl_ptr_tgt_def*/
			     SRM_Long_Float coord_tgt[2],
			     /*!< (Output): \impl_coord_tgt_def*/
			     const SRM_ORM_Transformation_2D_Parameters *hst
			     );

//!  Changes the represenation from one SRF to another for 3D coordinates.

/*! This routine changes the representation of a 3D location from one #D SRF to another #D SRF.
  This routine implements changeCoordinate3DSRF() : srm::BaseSRF_3D
  \remark It is the responsiblity of the API to call the appropriate 2D or 3D version of this function.

  \note Invalid is directly propogated to tgt if source is invalid.
  \returns IMPL_VALID for valid target coordinate
  \returns IMPL_EXTENDED for extended target coordinate
  \returns IMPL_INVALID for invalid target coordinate  
  \returns IMPL_MEMALLOC on out of memory
  \returns IMPL_SRFSRC for a bad source SRF
  \returns IMPL_SRFTGT for a bad target SRF

*/
Impl_Status
Impl_changeCoord3DSRF(void* srf_src,
		      /*!< (Input): \impl_ptr_src_def*/
		      const SRM_Long_Float coord_src[3],
		      /*!< (Input): \impl_coord_src_def*/
		      void* srf_tgt,
		      /*!< (Input): \impl_ptr_tgt_def*/ 
		      SRM_Long_Float coord_tgt[3]
		      /*!< (Output): \impl_coord_tgt_def*/
		      );


Impl_Status
Impl_changeCoord3DSRFObject(void* srf_src,
			    /*!< (Input): \impl_ptr_src_def*/
			    const SRM_Long_Float coord_src[3],
			    /*!< (Input): \impl_coord_src_def*/
			    void* srf_tgt,
			    /*!< (Input): \impl_ptr_tgt_def*/ 
			    SRM_Long_Float coord_tgt[3],
			    /*!< (Output): \impl_coord_tgt_def*/
			    const SRM_ORM_Transformation_3D_Parameters* hst
			    );

//! Changes the representation of a direction from one SRF to another.

/*! This routines changes the represnation of a direction from one SRF
  to another.  It takes as parameters the components of the direction
  object in the API, not the object, and likewise returns values in the
  same fashion. This routine implements changeDirectionSRF() : srm::BaseSRF_3D.

  \remark Directions may only have 3D locations as reference locations.
  \remark The API shall ensure that no SRF's associated with 2D locations or
  surface locations are passed here.

  \note Invalid is directly propogated to tgt if source is invalid.
  \returns IMPL_VALID for valid target direction
  \returns IMPL_EXTENDED for target direction with extended \a ref_loc_tgt[]
  \returns IMPL_INVALID for target direction invalid \a ref_loc_tgt[] 
  \returns IMPL_MEMALLOC on out of memory
  \returns IMPL_SRFSRC for a bad source SRF
  \returns IMPL_SRFTGT for a bad target SRF

*/
Impl_Status
Impl_changeDirectionSRF(void*   srf_src,
			/*!< (Input): \impl_ptr_src_def*/
			const SRM_Long_Float ref_loc_src[3],
			/*!< (Input): \impl_ref_loc_src_def*/
			const SRM_Long_Float dir_values_src[3],
			/*!< (Input): \impl_dir_values_src_def*/
			void*   srf_tgt,
			/*!< (Input): \impl_ptr_tgt_def*/
			SRM_Long_Float ref_loc_tgt[3],
			/*!< (Output): \impl_ref_loc_tgt_def*/
			SRM_Long_Float dir_values_tgt[3]
			/*!< (Output): \impl_dir_values_tgt_def*/
			);



Impl_Status
Impl_changeDirectionSRFObject(void*   srf_src,
			      /*!< (Input): \impl_ptr_src_def*/
			      const SRM_Long_Float ref_loc_src[3],
			      /*!< (Input): \impl_ref_loc_src_def*/
			      const SRM_Long_Float dir_values_src[3],
			      /*!< (Input): \impl_dir_values_src_def*/
			      void*   srf_tgt,
			      /*!< (Input): \impl_ptr_tgt_def*/
			      SRM_Long_Float ref_loc_tgt[3],
			      /*!< (Output): \impl_ref_loc_tgt_def*/
			      SRM_Long_Float dir_values_tgt[3],
			      /*!< (Output): \impl_dir_values_tgt_def*/
			      const SRM_ORM_Transformation_3D_Parameters* hst
			      );


//! Changes the representation of an orientation from one SRF to another.

/*! This routines changes the represnation of a direction from one SRF
  to another.  It takes as parameters the components of the orientation
  object in the API, not the object, and likewise returns values in the
  same fashion.  This routine implements changeOrientationSRF() : srm::BaseSRF_3D.

  \remark Orientations may only have 3D locations as reference locations.
  \remark The API shall ensure that no SRF's associated with 2D locations or
  surface locations are passed here.

  \note Invalid is directly propogated to tgt if source is invalid.
  \returns IMPL_VALID for valid target orientation
  \returns IMPL_EXTENDED for target orientation with extended \a ref_loc_tgt[]
  \returns IMPL_INVALID for target orientation invalid \a ref_loc_tgt[] 
  \returns IMPL_MEMALLOC on out of memory
  \returns IMPL_SRFSRC for a bad source SRF
  \returns IMPL_SRFTGT for a bad target SRF

*/
Impl_Status
Impl_changeOrientationSRF(void*   srf_src,
			  /*!< (Input): \impl_ptr_src_def*/
			  const SRM_Long_Float ref_loc_src[3],
			  /*!< (Input): \impl_ref_loc_src_def*/
			  const SRM_Long_Float matrix_values_src[3][3],
			  /*!< (Input): \impl_matrix_values_src_def*/
			  void*   srf_tgt,
			  /*!< (Input):\impl_ptr_tgt_def*/
			  SRM_Long_Float ref_loc_tgt[3],
			  /*!< (Output): \impl_ref_loc_tgt_def*/
			  SRM_Long_Float matrix_values_tgt[3][3]
			  /*!< (Output): \impl_matrix_values_tgt_def*/
			  );

#endif
