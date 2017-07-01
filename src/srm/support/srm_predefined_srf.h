
#ifndef __SRM_PREDEFINED_SRF_H__
#define __SRM_PREDEFINED_SRF_H__

#include "srm_internal.h"

/*The following functions allocate standard (predefined SRFs).*/
extern void *Impl_allocsrfNULL_SRF( SRM_RT_Code rt_code );
extern void *Impl_allocsrfBRITISH_NAT_GRID( SRM_RT_Code rt_code );
extern void *Impl_allocsrfBRITISH_OSGRS80_GRID( SRM_RT_Code rt_code );
extern void *Impl_allocsrfDELAWARE_SPCS( SRM_RT_Code rt_code );
extern void *Impl_allocsrfGC_WGS_1984( SRM_RT_Code rt_code );
extern void *Impl_allocsrfGD_AUSTRALIA_1984( SRM_RT_Code rt_code );
extern void *Impl_allocsrfGD_WGS_1984( SRM_RT_Code rt_code );
extern void *Impl_allocsrfGD_N_AMERICAN_1983( SRM_RT_Code rt_code );
extern void *Impl_allocsrfIRISH_GRID( SRM_RT_Code rt_code );
extern void *Impl_allocsrfIRISH_TRANS_MERCATOR( SRM_RT_Code rt_code );
extern void *Impl_allocsrfLAMBERT_93( SRM_RT_Code rt_code );
extern void *Impl_allocsrfLAMBERT_II_WIDE( SRM_RT_Code rt_code );
extern void *Impl_allocsrfMARS_PLANETOCENTRIC_2000( SRM_RT_Code rt_code );
extern void *Impl_allocsrfMARS_PLANETOGRAPHIC_2000( SRM_RT_Code rt_code );
extern void *Impl_allocsrfMARYLAND_SPCS( SRM_RT_Code rt_code );


/*The following group of functions returns the SRFT code for a given
  predefined standard SRF
*/
extern SRM_SRFT_Code Impl_templcodeNULL_SRF();
extern SRM_SRFT_Code Impl_templcodeBRITISH_NAT_GRID();
extern SRM_SRFT_Code Impl_templcodeBRITISH_OSGRS80_GRID();
extern SRM_SRFT_Code Impl_templcodeDELAWARE_SPCS();
extern SRM_SRFT_Code Impl_templcodeGC_WGS_1984();
extern SRM_SRFT_Code Impl_templcodeGD_AUSTRALIA_1984();
extern SRM_SRFT_Code Impl_templcodeGD_WGS_1984();
extern SRM_SRFT_Code Impl_templcodeGD_N_AMERICAN_1983();
extern SRM_SRFT_Code Impl_templcodeIRISH_GRID();
extern SRM_SRFT_Code Impl_templcodeIRISH_TRANS_MERCATOR();
extern SRM_SRFT_Code Impl_templcodeLAMBERT_93();
extern SRM_SRFT_Code Impl_templcodeLAMBERT_II_WIDE();
extern SRM_SRFT_Code Impl_templcodeMARS_PLANETOCENTRIC_2000();
extern SRM_SRFT_Code Impl_templcodeMARS_PLANETOGRAPHIC_2000();
extern SRM_SRFT_Code Impl_templcodeMARYLAND_SPCS();

#endif
