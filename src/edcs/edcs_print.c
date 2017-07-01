
//
// DESCRIPTION:
//   Contains print functions for all EDCS types.
//

#include <stdio.h>
#include <string.h>
#include "edcs.h"
#include "edcs_print.h"

/*
 * GLOBAL VARIABLE: _OutHasBeenSet
 *
 *   Whether output file pointer has been set by the user. If
 *   EDCS_FALSE, use stdout.
 */
static EDCS_Boolean _OutHasBeenSet = EDCS_FALSE;

/*
 * GLOBAL VARIABLE: edcs_out_file_ptr
 *
 *   The output file pointer. If this has not been set, use stdout.
 */
static FILE *edcs_out_file_ptr;

/*
 * GLOBAL VARIABLE: _MinWidth
 *
 *   Minimum field width. If the converted argument is smaller than
 *   _MinWidth, it will be padded on the left with spaces to make
 *   up the field width.
 */
static EDCS_Count _MinWidth  = 12;

/*
 * GLOBAL_VARIABLE: _Precision
 *
 *   Number of digits to be printed after the decimal point, when printing
 *   a EDCS_Float or EDCS_Long_Float.
 */
static EDCS_Count _Precision = 5;


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetMinWidth
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Count
EDCS_GetMinWidth(void)
{
    return _MinWidth;
} /* end EDCS_GetMinWidth */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetOutFilePtr
 *
 *-----------------------------------------------------------------------------
 */
FILE *
EDCS_GetOutFilePtr(void)
{
    if (_OutHasBeenSet)
        return edcs_out_file_ptr;
    else
        return stdout;
} /* end EDCS_GetOutFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetPrecision
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Count
EDCS_GetPrecision(void)
{
    return _Precision;
} /* end EDCS_GetPrecision */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SetMinWidth
 *
 *-----------------------------------------------------------------------------
 */
void
EDCS_SetMinWidth
(
    EDCS_Count min_width
)
{
    _MinWidth = min_width;
} /* end EDCS_SetMinWidth */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SetOutFilePtr
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_SetOutFilePtr
(
    FILE *out_file_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (out_file_ptr)
    {
        _OutHasBeenSet = EDCS_TRUE;
        edcs_out_file_ptr = out_file_ptr;
        status = EDCS_SC_SUCCESS;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_SetOutFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SetPrecision
 *
 *-----------------------------------------------------------------------------
 */
void
EDCS_SetPrecision
(
    EDCS_Count precision
)
{
    _Precision = precision;
} /* end EDCS_SetPrecision */
