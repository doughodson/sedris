
#ifndef __SRM_COM_H__
#define __SRM_COM_H__

#include"../internal_api/impl_status.h"

#include"srm_stds.h"
#include"srm_types.h"
#include"srm_internal.h"

Impl_Status
Impl_com_undefined
(void* srf_org,
 Impl_ORM_Data* e_constants,
 SRM_Long_Float coord[3], 
 SRM_Long_Float* com_value
 );

Impl_Status
Impl_comMERCATOR
(
 void* srf_org,
 Impl_ORM_Data* e_constants, 
 SRM_Long_Float cd_coord[3], 
 SRM_Long_Float* com_value
 );

Impl_Status
Impl_comOBLIQUE_MERCATOR
(
 void* srf_org, 
 Impl_ORM_Data* e_constants,
 SRM_Long_Float cd_coord[3],
 SRM_Long_Float* com_value
 );

Impl_Status
Impl_comTRANSVERSE_MERCATOR
(
 void* srf_org,   
 Impl_ORM_Data* e_constants,
 SRM_Long_Float cd_coord[3],
 SRM_Long_Float* com_value
 );

Impl_Status
Impl_comLAMBERT_CONF_CONIC
(
 void* srf_org, 
 Impl_ORM_Data* e_constants,
 SRM_Long_Float cd_coord[3],
 SRM_Long_Float* com_value
 );	


Impl_Status
Impl_comPOLAR_STEREOGRAPHIC
(
 void* srf_org,
 Impl_ORM_Data* e_constants, 
 SRM_Long_Float cd_coord[3],
 SRM_Long_Float* com_value
 );

Impl_Status
Impl_comEQUIDISTANT_CYL
(void* srf_org,
 Impl_ORM_Data* e_constants,
 SRM_Long_Float cd_coord[3],
 SRM_Long_Float* com_value
 );       

#endif
