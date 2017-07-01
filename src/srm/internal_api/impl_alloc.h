
#ifndef _IMPL_ALLOC_H
#define _IMPL_ALLOC_H

#include "srm_types.h"
#include "impl_private.h"
#include "impl_status.h"

//!This returns the size of the data to be copied when
//!passed a code into the brackets.
extern SRM_Integer (*Impl_sizeof_templ_param[])();

//!Creates an SRF from the appropriate parameters structure

/*!This routine creates an SRF object form the appropriate struct definition in the API
defined in ISO18026 clause 11.
This method implements the create() method of the API on each concrete SRF class.

\returns IMPL_VALID on successful allocation
\returns IMPL_MEMALLOC on out of memory
\returns IMPL_SRCSRF  for defective srf parameters

*/

Impl_Status
Impl_createSRFFromParams(SRM_SRFT_Code template_code,
			 /*!< (Input): ISO 18026 compliant SRF template code*/
			 SRM_ORM_Code          orm,
			 /*<! (Input): ISO 18026 Compliant orm code*/
			 SRM_RT_Code          rt,
			 /*<! (Input): ISO 18026 Compliant rt code*/
			 void*                 api_template_parm_struct_ptr,
			 /*!< (Input): pointer to clause 11 structure representing SRF parameters
			   which is cast to a void pointer by the caller and recast to
			   the proper form by the implementation using the code stored
			   in \a t_code */
			 void**    api_srf_representation_ptr_ptr
			 /*!< (Output): \api_ptr_ptr_def */
			 );



//!Creates an SRF from the appropriate standard SRF code.

/*!This routine creates an internal SRF object form the standard SRF code
  defined in ISO18026 clause 11.
  This routine implements createStandardSRF() : srm::BaseSRF of the API

  \returns IMPL_VALID on successful allocation
  \returns IMPL_MEMALLOC on out of memory
  \remark Doesn't return anything for bad codes because API verifies codes are good.
*/
Impl_Status
Impl_createSRFStandard(SRM_SRF_Code srf_code,
		       /*!< (Input): ISO18026 compliant Predefined SRF Code*/
		       SRM_RT_Code  rt_code,
		       /*<! (Input): ISO 18026 Compliant rt code*/
		       void** impl_srf_representation_ptr_ptr
		       /*!< (Output): \impl_ptr_ptr_def */
		       );


//!Creates an interal SRF object from the appropriate set code, member code, and ORM.

/*!This routine creates an internal SRF object using the appropriate set code, member code,
  and ORM as defined in ISO18026 clause 11.
  This routine implements the createSRFSetMember() : srm::BaseSRF of the API

  \returns IMPL_VALID on successful allocation
  \returns IMPL_MEMALLOC on out of memory
  \remark Doesn't return anything for bad codes because API verifies codes are good.
*/

Impl_Status
Impl_createSRFSetMember(SRM_SRFS_Info srfs_info,
			/*!< (Input): An ISO 18026 Compliant SRF Set/Set Member/ORM Code*/
			SRM_RT_Code rt,
			/*!< (Input): An ISO 18026 Compliant Hsr code*/
			void** api_srf_representation_ptr_ptr
			/*!< (Output): \impl_ptr_ptr_def */
			);

Impl_Status
Impl_copySRF(  void* src_api_srf_handle,
	       void** tgt_api_srf_handle
	       );

void Impl_setValidateCoordinate( void* api_template_parm_struct_ptr,
				 bool set );

bool Impl_ValidateCoordinateIsOn( void*  api_template_parm_struct_ptr );


//! Releases Any storage held by the implementation for the API.

/*! \a Impl_releaseSRF() releases any storage held by the implementation for the API under an \a Impl_SRF_ptr.
It takes \a Impl_SRF_ptr** so that it can be used to write the API's storage of the pointer
to NULL after deallocating the storage thus preventing the API from accidentally trying to re-reference
the deallocated pointer.
This routine implements release() : srm::BaseSRF.

\remark It should be called by the API when the  reference count reaches 0 for an SRF object.

\returns IMPL_VALID on success
\returns IMPL_MEMALLOC on failure deallocating the object
*/
Impl_Status
Impl_releaseSRF(void**  impl_srf_representation_ptr_ptr
		/*!< (Input/Output): \impl_ptr_ptr_def */);


#endif
