
#ifndef __SRM_POINTSCALE_H__
#define __SRM_POINTSCALE_H__

#include "srm_internal.h"

Impl_Status
Impl_pointscale_undefined
(
    void           *srf_org,
    Impl_ORM_Data  *e_constants,
    SRM_Long_Float  coord[3],
    SRM_Long_Float *point_scale
);

Impl_Status
Impl_pointscaleMERCATOR
(
    void           *srf_org,
    Impl_ORM_Data  *e_constants,
    SRM_Long_Float  cd_coord[3],
    SRM_Long_Float *point_scale
);

Impl_Status
Impl_pointscaleOBLIQUE_MERCATOR
(
    void           *srf_org,
    Impl_ORM_Data  *e_constants,
    SRM_Long_Float  cd_coord[3],
    SRM_Long_Float *point_scale
);

Impl_Status
Impl_pointscaleTRANSVERSE_MERCATOR
(
    void           *srf_org,
    Impl_ORM_Data  *e_constants,
    SRM_Long_Float  cd_coord[3],
    SRM_Long_Float *point_scale
);

Impl_Status
Impl_pointscaleLAMBERT_CONF_CONIC
(
    void           *srf_org,
    Impl_ORM_Data  *e_constants,
    SRM_Long_Float  cd_coord[3],
    SRM_Long_Float *point_scale
);


Impl_Status
Impl_pointscalePOLAR_STEREOGRAPHIC
(
    void           *srf_org,
    Impl_ORM_Data  *e_constants,
    SRM_Long_Float  cd_coord[3],
    SRM_Long_Float *point_scale
);

Impl_Status
Impl_pointscaleEQUIDISTANT_CYL
(
    void           *srf_org,
    Impl_ORM_Data  *e_constants,
    SRM_Long_Float  cd_coord[3],
    SRM_Long_Float *point_scale
);

#endif
