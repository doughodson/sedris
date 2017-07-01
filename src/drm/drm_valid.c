//
// DESCRIPTION:
//   Contains validating functions for all SEDRIS types, and for
//   an object's fields.
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
//   in order to insure that a given variable has valid values;
//   for example, SE_ValidFields() may be used by applications
//   that check that transmittals are valid, e.g. checker.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drm.h"

/*
 * GLOBAL VARIABLE: _ErrHasBeenSet
 *
 *   Whether error file pointer has been set by the user. If
 *   SE_FALSE, use stderr.
 */
static SE_Boolean _ErrHasBeenSet = SE_FALSE;

/*
 * GLOBAL VARIABLE: drm_err_file_ptr
 *
 *   The error file pointer. If this has not been set, use
 *   stderr.
 */
static FILE *drm_err_file_ptr;


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_GetErrorFilePtr
 *
 *-----------------------------------------------------------------------------
 */
FILE *
SE_GetErrorFilePtr(void)
{
    if (_ErrHasBeenSet)
        return drm_err_file_ptr;
    else
        return stderr;
} /* end SE_GetErrorFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_SetErrorFilePtr
 *
 *-----------------------------------------------------------------------------
 */
SE_DRM_Status_Code
SE_SetErrorFilePtr
(
    FILE *err_file_ptr
)
{
    SE_DRM_Status_Code status = SE_DRM_STAT_CODE_SUCCESS;

    if (err_file_ptr)
    {
        drm_err_file_ptr = err_file_ptr;
        _ErrHasBeenSet   = SE_TRUE;
        status = SE_DRM_STAT_CODE_SUCCESS;
    }
    else
    {
        status = SE_DRM_STAT_CODE_FAILURE;
        drm_err_file_ptr = stderr;
    }
    return status;
} /* end SE_SetErrorFilePtr */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_ValidCMYData
 *
 *-----------------------------------------------------------------------------
 */
SE_Boolean
SE_ValidCMYData
(
    const SE_CMY_Data         *value_ptr,
          SE_Boolean           print_error,
          SE_Integer_Unsigned *error_count_ptr
)
{
    SE_Boolean  result = SE_TRUE;
    FILE       *f_ptr = NULL;

    if (print_error)
        f_ptr = SE_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "SE_ValidCMYData: NULL value_ptr\n");
        }
        return result;
    }

    if ((value_ptr->cyan < 0.0) || (value_ptr->cyan > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal cyan value (%s)\n",
                    SE_PrintLongFloat(value_ptr->cyan));
    }

    if ((value_ptr->magenta < 0.0) || (value_ptr->magenta > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal magenta value (%s)\n",
                    SE_PrintLongFloat(value_ptr->magenta));
    }

    if ((value_ptr->yellow < 0.0) || (value_ptr->yellow > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal yellow value (%s)\n",
                    SE_PrintLongFloat(value_ptr->yellow));
    }
    return result;
} /* end SE_ValidCMYData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_ValidCMYKData
 *
 *-----------------------------------------------------------------------------
 */
SE_Boolean
SE_ValidCMYKData
(
    const SE_CMYK_Data         *value_ptr,
          SE_Boolean           print_error,
          SE_Integer_Unsigned *error_count_ptr
)
{
    SE_Boolean  result = SE_TRUE;
    FILE       *f_ptr = NULL;

    if (print_error)
        f_ptr = SE_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "SE_ValidCMYKData: NULL value_ptr\n");
        }
        return result;
    }

    if ((value_ptr->cyan < 0.0) || (value_ptr->cyan > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal cyan value (%s)\n",
                    SE_PrintLongFloat(value_ptr->cyan));
    }

    if ((value_ptr->magenta < 0.0) || (value_ptr->magenta > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal magenta value (%s)\n",
                    SE_PrintLongFloat(value_ptr->magenta));
    }

    if ((value_ptr->yellow < 0.0) || (value_ptr->yellow > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal yellow value (%s)\n",
                    SE_PrintLongFloat(value_ptr->yellow));
    }

    if ((value_ptr->black < 0.0) || (value_ptr->black > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal black value (%s)\n",
                    SE_PrintLongFloat(value_ptr->black));
    }
    return result;
} /* end SE_ValidCMYKData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_ValidHLSData
 *
 *-----------------------------------------------------------------------------
 */
SE_Boolean
SE_ValidHLSData
(
    const SE_HLS_Data          *value_ptr,
          SE_Boolean           print_error,
          SE_Integer_Unsigned *error_count_ptr
)
{
    SE_Boolean  result = SE_TRUE;
    FILE       *f_ptr = NULL;

    if (print_error)
        f_ptr = SE_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "SE_ValidHLSData: NULL value_ptr\n");
        }
        return result;
    }

    if ((value_ptr->saturation != 0.0) &&
        ((value_ptr->hue < 0.0) || (value_ptr->hue > 360.0)))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal hue value (%s)\n",
                    SE_PrintLongFloat(value_ptr->hue));
    }

    if ((value_ptr->lightness < 0.0) || (value_ptr->lightness > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal lightness value (%s)\n",
                    SE_PrintLongFloat(value_ptr->lightness));
    }

    if ((value_ptr->saturation < 0.0) || (value_ptr->saturation > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal saturation value (%s)\n",
                    SE_PrintLongFloat(value_ptr->saturation));
    }
    return result;
} /* end SE_ValidHLSData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_ValidHSVData
 *
 *-----------------------------------------------------------------------------
 */
SE_Boolean
SE_ValidHSVData
(
    const SE_HSV_Data  *value_ptr,
          SE_Boolean    print_error,
          SE_Integer_Unsigned    *error_count_ptr
)
{
    SE_Boolean  result = SE_TRUE;
    FILE       *f_ptr = NULL;

    if (print_error)
        f_ptr = SE_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "SE_ValidHSVData: NULL value_ptr\n");
        }
        return result;
    }

    if ((value_ptr->saturation < 0.0) || (value_ptr->saturation > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal saturation value (%s)\n",
                    SE_PrintLongFloat(value_ptr->saturation));
    }

    if ((value_ptr->value < 0.0) || (value_ptr->value > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal value/brightness value (%s)\n",
                    SE_PrintLongFloat(value_ptr->value));
    }
    return result;
} /* end SE_ValidHSVData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_ValidLocale
 *
 *-----------------------------------------------------------------------------
 */
SE_Boolean
SE_ValidLocale
(
    const SE_Locale           *value_ptr,
          SE_Boolean           print_error,
          SE_Integer_Unsigned *error_count_ptr
)
{
    SE_Boolean  result = SE_TRUE;
    FILE       *f_ptr = NULL;

    if (print_error)
        f_ptr = SE_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "SE_ValidLocale: NULL value_ptr\n");
        }
        return result;
    }
    else
    {
        const EDCS_ISO_3166_Entry *country_code_entry_ptr = NULL;
        const EDCS_ISO_639_Entry  *language_code_entry_ptr = NULL;
              EDCS_Locale          edcs_locale;

        edcs_locale.country[0] = (EDCS_Character)value_ptr->country[0];
        edcs_locale.country[1] = (EDCS_Character)value_ptr->country[1];
        edcs_locale.country[2] = (EDCS_Character)value_ptr->country[2];

        if (EDCS_GetCountryCodeEntry(edcs_locale.country,
            &country_code_entry_ptr) != EDCS_SC_SUCCESS)
        {
            result = SE_FALSE;
            if (error_count_ptr) (*error_count_ptr)++;
            if (print_error)
            {
                fprintf(f_ptr, "SE_ValidLocale: invalid country\n");
            }
        }
        edcs_locale.language[0] = (EDCS_Character)value_ptr->language[0];
        edcs_locale.language[1] = (EDCS_Character)value_ptr->language[1];

        if (EDCS_GetLanguageCodeEntry(edcs_locale.language,
            &language_code_entry_ptr) != EDCS_SC_SUCCESS)
        {
            result = SE_FALSE;
            if (error_count_ptr) (*error_count_ptr)++;
            if (print_error)
            {
                fprintf(f_ptr, "SE_ValidLocale: invalid language\n");
            }
        }
    }
    return result;
} /* end SE_ValidLocale */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_ValidRGBData
 *
 *-----------------------------------------------------------------------------
 */
SE_Boolean
SE_ValidRGBData
(
    const SE_RGB_Data          *value_ptr,
          SE_Boolean           print_error,
          SE_Integer_Unsigned *error_count_ptr
)
{
    SE_Boolean  result = SE_TRUE;
    FILE       *f_ptr = NULL;

    if (print_error)
        f_ptr = SE_GetErrorFilePtr();

    if (!value_ptr)
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
        {
            fprintf(f_ptr, "SE_ValidRGBData: NULL value_ptr\n");
        }
        return result;
    }

    if ((value_ptr->red < 0.0) || (value_ptr->red > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal red value (%s)\n",
                    SE_PrintLongFloat(value_ptr->red));
    }

    if ((value_ptr->green < 0.0) || (value_ptr->green > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal green value (%s)\n",
                    SE_PrintLongFloat(value_ptr->green));
    }

    if ((value_ptr->blue < 0.0) || (value_ptr->blue > 1.0))
    {
        result = SE_FALSE;
        if (error_count_ptr) (*error_count_ptr)++;
        if (print_error)
            fprintf(f_ptr, "Illegal blue value (%s)\n",
                    SE_PrintLongFloat(value_ptr->blue));
    }
    return result;
} /* end SE_ValidRGBData */
