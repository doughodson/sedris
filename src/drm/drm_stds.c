
//
// DESCRIPTION:
//   This file initializes the __xxx_infinity arrays with the IEEE definitions
//   for positive and negative infinity, taking into account whether the
//   machine is Big Endian or Little Endian.
//

#include "drm_stds.h"

const unsigned int __se_32_pos_infinity[1] = { 0x7f800000 };
const unsigned int __se_32_neg_infinity[1] = { 0xff800000 };

#ifdef SE_BIG_ENDIAN
    const unsigned int __se_64_pos_infinity[2] = { 0x7ff00000, 0x00000000 };
    const unsigned int __se_64_neg_infinity[2] = { 0xfff00000, 0x00000000 };
#else
    const unsigned int __se_64_pos_infinity[2] = { 0x00000000, 0x7ff00000 };
    const unsigned int __se_64_neg_infinity[2] = { 0x00000000, 0xfff00000 };
#endif

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: SE_GetImplVerInfo
 *
 *----------------------------------------------------------------------------
 */
const char *
SE_GetDRMImplVerInfo(void)
{
    return "4.1";
} /* end SE_GetDRMImplVerInfo */
