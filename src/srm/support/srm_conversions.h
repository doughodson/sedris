
#ifndef __SRM_CONVERSIONS_H_INCLUDED__
#define __SRM_CONVERSIONS_H_INCLUDED__

#include "srm_internal.h" 

#define NO_OP_REQUIRED 0xFFFF

extern Impl_Status
SRM_ConstructBFSMap
(
    int source_cs, 
	int** parent_matrix, 
	int** distance_matrix, 
	const SRM_Integer* (*plist[])(),
	      int rows
);

extern const SRM_Integer* (*Edge[])();
extern const SRM_Integer* (*ds_Edge[])();
extern const SRM_Integer NUM_EDGES;
extern const SRM_Integer table_height;
extern const SRM_Integer ds_table_height;

extern void SRM_PrintConversionPath
(
          FILE* handle,
          int source_frameid,
          int     dest_frameid, 
    const SRM_Integer* (*plist[])() , 
          int     rows
);


extern SRM_Integer
GetDirectionTreatmentFrameid
(
    SRM_SRFT_Code srft_code
);

extern SRM_Integer
GetDirectionCase
(
    SRM_Integer frame_id_src,
    SRM_Integer frame_id_tgt
);
  
#if 0
extern const char* SRM_tangle_srf_string(SRM_Integer srf);
extern const char* SRM_tangle_srf_3D_Coord(SRM_Integer srf);
extern const char* SRM_tangle_srf_2D_Coord(SRM_Integer srf);
extern const char* SRM_tangle_srf_Surf_Coord(SRM_Integer srf);
#endif

#endif
