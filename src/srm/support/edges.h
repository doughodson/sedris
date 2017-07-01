
#ifndef __INCLUDED_EDGES_H__
#define __INCLUDED_EDGES_H__

#include "../internal_api/impl_private.h"

#include "srm_internal.h"

void *SRM_set_ec_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_cd_to_ec_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_cc_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_cd_to_cc_constants
(
    Impl_Private_Data *cd_orm,
    Impl_Private_Data *cc_orm
);


void *SRM_set_cc_to_lte_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_lte_to_cc_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_cc_to_lce_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_lce_to_cc_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_cd_to_lcc1_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_lcc1_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_cd_to_lcc2_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_lcc2_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_cd_to_m_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_m_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_cd_to_om_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_om_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_cd_to_tm_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_tm_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);


void *SRM_set_cd_to_ps_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_ps_to_cd_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_dshift_constants
(
    Impl_Private_Data *source_srf_struct,
    Impl_Private_Data *dest_srf_struct
);

void *SRM_set_lsr3D_to_lsr3D_constants
(
    Impl_Private_Data *lsr3d_srf_src,
    Impl_Private_Data *lsr3d_srf_tgt
);


void *SRM_set_lsr2D_to_lsr2D_constants
(
    Impl_Private_Data *lsr2d_srf_src,
    Impl_Private_Data *lsr2d_srf_tgt
);

void *SRM_set_pos2_to_lsr2D_constants
(
    Impl_Private_Data *lsr2d_srf_tgt,
    Impl_Private_Data *unused
);

void *SRM_set_lsr2D_to_pos2_constants
(
    Impl_Private_Data *lsr2d_srf_src,
    Impl_Private_Data *unused
);

void *SRM_set_pos3_to_lsr3D_constants
(
    Impl_Private_Data *lsr3d_srf_tgt,
    Impl_Private_Data *unused
);

void *SRM_set_lsr3D_to_pos3_constants
(
    Impl_Private_Data *lsr3d_srf_src,
    Impl_Private_Data *unused
);

void *SRM_set_pos_to_pos_constants
(
    Impl_Private_Data *unused1,
    Impl_Private_Data *unused2
);

void* SRM_set_LAST_LTSE_constants
(
    Impl_Private_Data *last_srf_src,
    Impl_Private_Data *ltse_srf_tgt
);

void* SRM_set_LTSE_LAST_constants
(
    Impl_Private_Data *ltse_srf_tgt,
    Impl_Private_Data *last_srf_src
);

void* SRM_set_LCTP_LTSE_constants
(
    Impl_Private_Data *last_srf_src,
    Impl_Private_Data *ltse_srf_tgt
);

void* SRM_set_LTSE_LCTP_constants
(
    Impl_Private_Data *ltse_srf_tgt,
    Impl_Private_Data *last_srf_src
);



void SRM_dealloc_ec_to_cd_constants( void* dealloc_me );

void SRM_dealloc_cd_to_ec_constants( void* dealloc_me );

void SRM_dealloc_cc_to_cd_constants( void* dealloc_me );

void SRM_dealloc_cc_to_lte_constants( void* dealloc_me );

void SRM_dealloc_lte_to_cc_constants( void* dealloc_me );

void SRM_dealloc_cc_to_lce_constants( void* dealloc_me );

void SRM_dealloc_lce_to_cc_constants( void* dealloc_me );

void SRM_dealloc_cd_to_lcc1_constants( void* dealloc_me );

void SRM_dealloc_lcc1_to_cd_constants( void* dealloc_me );

void SRM_dealloc_cd_to_lcc2_constants( void* dealloc_me );

void SRM_dealloc_lcc2_to_cd_constants( void* dealloc_me );

void SRM_dealloc_cd_to_m_constants( void* dealloc_me );

void SRM_dealloc_m_to_cd_constants( void* dealloc_me );

void SRM_dealloc_cd_to_om_constants( void* dealloc_me );

void SRM_dealloc_om_to_cd_constants( void* dealloc_me );

void SRM_dealloc_cd_to_tm_constants( void* dealloc_me );

void SRM_dealloc_tm_to_cd_constants( void* dealloc_me );

void SRM_dealloc_cd_to_ps_constants( void* dealloc_me );

void SRM_dealloc_ps_to_cd_constants( void* dealloc_me );

void SRM_dealloc_dshift_constants( void* dealloc_me );

void SRM_dealloc_cd_to_cc_constants( void* dealloc_me );

void SRM_dealloc_lsr3D_to_lsr3D_constants( void* dealloc_me );

void SRM_dealloc_lsr2D_to_lsr2D_constants( void* dealloc_me );

void SRM_dealloc_LAST_to_LTSE_constants(void * dealloc_me );

void SRM_dealloc_LTSE_to_LAST_constants(void * dealloc_me );

void SRM_dealloc_LCTP_to_LTSE_constants(void * dealloc_me );

void SRM_dealloc_LTSE_to_LCTP_constants(void * dealloc_me );

Impl_ORM_Data* Impl_getEconstantsForORMCode ( SRM_ORM_Code orm );

#endif
