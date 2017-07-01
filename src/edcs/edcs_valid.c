
//
// DESCRIPTION:
//   Contains validating functions for all EDCS types.
//
//   A type's validating function checks that:
//   - any enumerators have valid values
//   - any array that is allocated at run-time is non-NULL if
//     it has a non-zero array count
//
//   Some types do not have validating functions because they
//   contain nothing that can be checked. For a struct type,
//   the corresponding validating function will check only
//   those fields that need validating.
//
//   These functions are intended for use by any application
//   in order to insure that a given variable has valid values.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edcs.h"

/*
 * GLOBAL VARIABLE: _ErrHasBeenSet
 *
 *   Whether error file pointer has been set by the user. If
 *   EDCS_FALSE, use stderr.
 */
static EDCS_Boolean _ErrHasBeenSet = EDCS_FALSE;

/*
 * GLOBAL VARIABLE: edcs_err_file_ptr
 *
 *   The error file pointer. If this has not been set, use
 *   stderr.
 */
static FILE *edcs_err_file_ptr;


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetErrorFilePtr
 *
 *-----------------------------------------------------------------------------
 */
FILE *
EDCS_GetErrorFilePtr(void)
{
    if (_ErrHasBeenSet)
        return edcs_err_file_ptr;
    else
        return stderr;
} /* end EDCS_GetErrorFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SetErrorFilePtr
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_SetErrorFilePtr
(
    FILE *err_file_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (err_file_ptr)
    {
        edcs_err_file_ptr = err_file_ptr;
        _ErrHasBeenSet   = EDCS_TRUE;
        status = EDCS_SC_SUCCESS;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
        edcs_err_file_ptr = stderr;
    }
    return status;
} /* end EDCS_SetErrorFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidCountInterval
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Boolean
EDCS_ValidCountInterval
(
    const EDCS_Count_Interval *value_ptr,
          EDCS_Boolean         print_error,
          EDCS_Count          *error_count_ptr
)
{
    EDCS_Boolean  result = EDCS_TRUE;
    FILE         *f_ptr = NULL;

    if (print_error)
        f_ptr = EDCS_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = EDCS_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "EDCS_ValidCountInterval: NULL value_ptr\n");
        }
    }
    else if (value_ptr->lower_bound > value_ptr->upper_bound)
    {
        result = EDCS_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "EDCS_ValidCountInterval: "\
                    "lower_bound > upper_bound\n");
        }
    }
    return result;
} /* end EDCS_ValidCountInterval */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidIntegerInterval
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Boolean
EDCS_ValidIntegerInterval
(
    const EDCS_Integer_Interval *value_ptr,
          EDCS_Boolean           print_error,
          EDCS_Count            *error_count_ptr
)
{
    EDCS_Boolean  result = EDCS_TRUE;
    FILE         *f_ptr = NULL;

    if (print_error)
        f_ptr = EDCS_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = EDCS_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "EDCS_ValidIntegerInterval: NULL value_ptr\n");
        }
    }
    else if (value_ptr->lower_bound > value_ptr->upper_bound)
    {
        result = EDCS_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "EDCS_ValidIntegerInterval: "\
                    "lower_bound > upper_bound\n");
        }
    }
    return result;
} /* end EDCS_ValidIntegerInterval */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidLongFloatInterval
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Boolean
EDCS_ValidLongFloatInterval
(
    const EDCS_Long_Float_Interval *value_ptr,
          EDCS_Boolean              print_error,
          EDCS_Count               *error_count_ptr
)
{
    EDCS_Boolean  result = EDCS_TRUE;
    FILE         *f_ptr = NULL;

    if (print_error)
        f_ptr = EDCS_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = EDCS_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "EDCS_ValidLongFloatInterval: NULL value_ptr\n");
        }
    }
    else if (value_ptr->lower_bound > value_ptr->upper_bound)
    {
        result = EDCS_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "EDCS_ValidLongFloatInterval: "\
                    "lower_bound > upper_bound\n");
        }
    }
    return result;
} /* end EDCS_ValidLongFloatInterval */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidLocale
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Boolean
EDCS_ValidLocale
(
    const EDCS_Locale           *value_ptr,
          EDCS_Boolean           print_error,
          EDCS_Count            *error_count_ptr
)
{
    EDCS_Boolean  result = EDCS_TRUE;
    FILE         *f_ptr = NULL;

    if (print_error)
        f_ptr = EDCS_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = EDCS_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "EDCS_ValidLocale: NULL value_ptr\n");
        }
    }
    else
    {
        const EDCS_ISO_3166_Entry *country_code_entry_ptr = NULL;
        const EDCS_ISO_639_Entry  *language_code_entry_ptr = NULL;

        if (EDCS_GetCountryCodeEntry(value_ptr->country,
            &country_code_entry_ptr) != EDCS_SC_SUCCESS)
        {
            result = EDCS_FALSE;
            if (error_count_ptr) (*error_count_ptr)++;
            if (print_error)
            {
                fprintf(f_ptr, "EDCS_ValidLocale: invalid country\n");
            }
        }

        if (EDCS_GetLanguageCodeEntry(value_ptr->language,
            &language_code_entry_ptr) != EDCS_SC_SUCCESS)
        {
            result = EDCS_FALSE;
            if (error_count_ptr) (*error_count_ptr)++;
            if (print_error)
            {
                fprintf(f_ptr, "EDCS_ValidLocale: invalid language\n");
            }
        }
    }
    return result;
} /* end EDCS_ValidLocale */
