
#ifndef __SRM_SRF_SETS_H__
#define __SRM_SRF_SETS_H__

//    Prototypes for functions specific to srf sets
//    including allocators, natural set member, and
//    template code.

#include <math.h>

#include "../internal_api/impl_private.h"
#include "../internal_api/impl_alloc.h"
#include "../internal_api/impl_change.h"
#include "../internal_api/impl_vos.h"

#include "srm_internal.h"
#include "srm_validcoord.h"

/*Beginning of SRF set allocators*/
extern void* Impl_allocsrfNULL_SRFS(SRM_SRFS_Code_Info srfs_code_info, SRM_ORM_Code orm, SRM_RT_Code rt);
extern void* Impl_allocsrfALABAMA_SPCS(SRM_SRFS_Code_Info srfs_code_info, SRM_ORM_Code orm, SRM_RT_Code rt);
extern void* Impl_allocsrfGTRS_GLOB_COORD_SYS(SRM_SRFS_Code_Info srfs_code_info, SRM_ORM_Code orm, SRM_RT_Code rt);
extern void* Impl_allocsrfLAMBERT_NTF(SRM_SRFS_Code_Info srfs_code_info,SRM_ORM_Code orm,SRM_RT_Code rt );
extern void* Impl_allocsrfUNIV_POLAR_STEREOG(SRM_SRFS_Code_Info srfs_code_info,SRM_ORM_Code orm, SRM_RT_Code rt);
extern void* Impl_allocsrfUNIV_TRANS_MERC(SRM_SRFS_Code_Info srfs_code_info, SRM_ORM_Code orm, SRM_RT_Code rt);
extern void* Impl_allocsrfWISCONSIN_SPCS(SRM_SRFS_Code_Info srfs_code_info, SRM_ORM_Code orm, SRM_RT_Code rt);
extern void* Impl_allocsrfJRPS(SRM_SRFS_Code_Info srfs_code_info, SRM_ORM_Code orm, SRM_RT_Code rt);
/*End of SRF set allocators*/


/*Functions to get the natural SRF member*/

extern SRM_Integer Impl_naturalSetMemberNULL_SRFS(Impl_Private_Data pdat, SRM_Long_Float coordinate[3]);
extern SRM_Integer Impl_naturalSetMemberALABAMA_SPCS(Impl_Private_Data pdat, SRM_Long_Float coordinate[3]);
extern SRM_Integer Impl_naturalSetMemberGTRS_GLOB_COORD_SYS(Impl_Private_Data pdat, SRM_Long_Float coordinate[3]);
extern SRM_Integer Impl_naturalSetMemberLAMBERT_NTF(Impl_Private_Data pdat,  SRM_Long_Float coordinate[3]);
extern SRM_Integer Impl_naturalSetMemberUNIV_POLAR_STEREOG(Impl_Private_Data pdat, SRM_Long_Float coordinate[3]);
extern SRM_Integer Impl_naturalSetMemberUNIV_TRANS_MERC( Impl_Private_Data pdat,SRM_Long_Float coordinate[3]);
extern SRM_Integer Impl_naturalSetMemberWISCONSIN_SPCS( Impl_Private_Data pdat,SRM_Long_Float coordinate[3]);
extern SRM_Integer Impl_naturalSetMemberJRPS( Impl_Private_Data pdat,SRM_Long_Float coordinate[3]);

/*!<An array of functions that returns the natural set member for a given SRF.
   \returns -1 if unimplemented.
   \returns 0 if there is no valid representation of the given coordinate (IMPL_INVALID)
   \returns zone if implemented

*/


/*Template Code Functions: Needed 1 per SRF set
 * These functions return the template code of a given SRF set
 * A function must be added to the array below each time an
 * SRF set is added ot the API.
 */
extern SRM_SRFT_Code Impl_templcodeNULL_SRFS();
extern SRM_SRFT_Code Impl_templcodeALABAMA_SPCS();
extern SRM_SRFT_Code Impl_templcodeGTRS_GLOB_COORD_SYS();
extern SRM_SRFT_Code Impl_templcodeLAMBERT_NTF();
extern SRM_SRFT_Code Impl_templcodeUNIV_POLAR_STEREOG();
extern SRM_SRFT_Code Impl_templcodeUNIV_TRANS_MERC();
extern SRM_SRFT_Code Impl_templcodeWISCONSIN_SPCS();
extern SRM_SRFT_Code Impl_templcodeJRPS();

#endif
