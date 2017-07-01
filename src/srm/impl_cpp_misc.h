
#ifndef _CPP_Impl_Misc_h
#define _CPP_Impl_Misc_h

#include "BaseSRF.hpp"
#include "srm_types.h"
#include "internal_api/impl_public.h"
#include "srf_impl/orm_rd_struct.h"

namespace srm
{
  enum objSrcType {
    SRF =1,
    COORD,
    DIR,
    ORI
  };

  enum memAllocType {
    CREATE = 1,
    DESTROY,
    MEM
  };

  void processStatus (Impl_Status status, const char* method_name,
                      objSrcType objSrc = SRF, memAllocType memAlloc = MEM);

// supporting functions
    bool isLegalSRFTCode ( SRM_SRFT_Code srft_code );

    bool isLegalSRFCode ( SRM_SRF_Code srf_code );

    bool isLegalRTCode (  SRM_SRF_Code srf_code, SRM_RT_Code rt_code );

    bool isLegalSRFSetCode ( SRM_SRFS_Code srfs_code );

    bool isLegalORMCode ( SRM_ORM_Code orm_code, SRM_RT_Code rt );

    bool isEqualVec2( const SRM_Vector_2D vec1, const SRM_Vector_2D vec2 );

    bool isEqualVec3( const SRM_Vector_3D vec1, const SRM_Vector_3D vec2 );

    bool isEqualMat( const SRM_Matrix_3x3 mat1, const SRM_Matrix_3x3 mat2 );

}  // namespace srm

#endif  // _CPP_Impl_Misc_h
