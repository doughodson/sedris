
#include "srm_stds.h"

#ifdef SRM_BIG_ENDIAN
    const unsigned int __srm_64_pos_infinity[2] = { 0x7ff00000, 0x00000000 };
    const unsigned int __srm_64_neg_infinity[2] = { 0xfff00000, 0x00000000 };
#else
    const unsigned int __srm_64_pos_infinity[2] = { 0x00000000, 0x7ff00000 };
    const unsigned int __srm_64_neg_infinity[2] = { 0x00000000, 0xfff00000 };
#endif


// SRM_GetImplVerInfo returns the version number of this implementation.
const char *
SRM_GetImplVerInfo(void)
{
    return "4.1.4";
}
