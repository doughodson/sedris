
#ifndef __SRM_VALIDCOORD_H__
#define __SRM_VALIDCOORD_H__

//    This file provides prototypes for coordinate validation functions

#include "../internal_api/impl_private.h"
#include "../internal_api/impl_alloc.h"
#include "../internal_api/impl_change.h"

#include "srm_internal.h"

extern Impl_Status Impl_validcoord3D_NULL_SRFS(Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DNoRestriction              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord2DNoRestriction              (Impl_Private_Data pdat, SRM_Long_Float v_coord[2]);
extern Impl_Status Impl_validcoord3DIllegal                    (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);

extern Impl_Status Impl_validcoord2DLSR                        (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DLSR                        (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);

extern Impl_Status Impl_validcoord2DCELESTIODETIC_cs(SRM_Long_Float *longitude, SRM_Long_Float *geodetic_latitude);

extern Impl_Status Impl_validcoord3DCELESTIODETIC              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DPLANETODETIC               (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord2DAZIMUTHAL                  (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DLOC_TAN_CYL                (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord2DPOLAR                      (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DMERCATOR_cd                (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DMERCATOR_native            (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DOBLIQUE_MERCATOR_cd        (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DOBLIQUE_MERCATOR_native    (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DTRANSVERSE_MERCATOR_cd     (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DTRANSVERSE_MERCATOR_native (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DLAMBERT_CONF_CONIC_cd      (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DLAMBERT_CONF_CONIC_native  (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DPOLAR_STEREOGRAPHIC_cd     (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DPOLAR_STEREOGRAPHIC_native (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DEQUIDISTANT_CYL_cd         (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DEQUIDISTANT_CYL_native     (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);

extern Impl_Status Impl_validcoordSpherical            (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoordAzSpherical          (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3DCylindrical        (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);

extern Impl_Status Impl_validcoord3D_ALSP_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_GCSG                 (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_GCSG_cd_special      (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_UPST_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_UTMC_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_WISP_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_LNTF_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_MTMB_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_MTMP_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
extern Impl_Status Impl_validcoord3D_JRPS_cd              (Impl_Private_Data pdat, SRM_Long_Float v_coord[3]);
#endif
