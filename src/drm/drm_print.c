
//
// DESCRIPTION:
//   Contains print functions for all SEDRIS types, and for
//   an object's fields.
//

#include <stdio.h>
#include <string.h>

#include "drm.h"

/*
 * GLOBAL VARIABLE: _OutHasBeenSet
 *
 *   Whether output file pointer has been set by the user. If
 *   SE_FALSE, use stdout.
 */
static SE_Boolean _OutHasBeenSet = SE_FALSE;

/*
 * GLOBAL VARIABLE: drm_out_file_ptr
 *
 *   The output file pointer. If this has not been set, use stdout.
 */
static FILE *drm_out_file_ptr;

/*
 * GLOBAL VARIABLE: _MinWidth
 *
 *   Minimum field width. If the converted argument is smaller than
 *   _MinWidth, it will be padded on the left with spaces to make
 *   up the field width.
 */
static SE_Integer_Unsigned _MinWidth  = 12;

/*
 * GLOBAL_VARIABLE: _Precision
 *
 *   Number of digits to be printed after the decimal point, when printing
 *   a SE_Float or SE_Long_Float.
 */
static SE_Integer_Unsigned _Precision = 5;


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_GetMinWidth
 *
 *-----------------------------------------------------------------------------
 */
SE_Integer_Unsigned
SE_GetMinWidth(void)
{
    return _MinWidth;
} /* end SE_GetMinWidth */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_GetOutFilePtr
 *
 *-----------------------------------------------------------------------------
 */
FILE *
SE_GetOutFilePtr(void)
{
    if (_OutHasBeenSet)
        return drm_out_file_ptr;
    else
        return stdout;
} /* end SE_GetOutFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_GetPrecision
 *
 *-----------------------------------------------------------------------------
 */
SE_Integer_Unsigned
SE_GetPrecision(void)
{
    return _Precision;
} /* end SE_GetPrecision */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_SetMinWidth
 *
 *-----------------------------------------------------------------------------
 */
void
SE_SetMinWidth
(
    SE_Integer_Unsigned min_width
)
{
    _MinWidth = min_width;
} /* end SE_SetMinWidth */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_SetOutFilePtr
 *
 *-----------------------------------------------------------------------------
 */
SE_DRM_Status_Code
SE_SetOutFilePtr
(
    FILE *out_file_ptr
)
{
    SE_DRM_Status_Code status = SE_DRM_STAT_CODE_SUCCESS;

    if (out_file_ptr)
    {
        _OutHasBeenSet = SE_TRUE;
        drm_out_file_ptr = out_file_ptr;
        status = SE_DRM_STAT_CODE_SUCCESS;
    }
    else
    {
        status = SE_DRM_STAT_CODE_FAILURE;
    }
    return status;
} /* end SE_SetOutFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_SetPrecision
 *
 *-----------------------------------------------------------------------------
 */
void
SE_SetPrecision
(
    SE_Integer_Unsigned precision
)
{
    _Precision = precision;
} /* end SE_SetPrecision */
