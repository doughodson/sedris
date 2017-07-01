
#ifndef _EDCS_H_INCLUDED_
#define _EDCS_H_INCLUDED_

//
// DESCRIPTION:
//      Main header for entire EDCS.  Including this file includes all necessary
//      EDCS headers.
//
//      *** IMPORTANT NOTE ***
//      This file is generated automatically from the EDCS database tables using
//      the EDCS Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
//      be made in the EDCS database and EDCS Code generator templates, and will be
//      reflected in this file when the system is rebuilt.
//

#include "edcs_types.h"
#include "edcs_class_dict.h"
#include "edcs_attr_dict.h"
#include "edcs_enum_dict.h"
#include "edcs_value_characteristic_dict.h"
#include "edcs_unit_dict.h"
#include "edcs_scale_dict.h"
#include "edcs_unit_equivalence_dict.h"
#include "edcs_org_schema_dict.h"
#include "edcs_group_dict.h"
#include "edcs_conversions.h"
#include "edcs_valid.h"
#include "edcs_print.h"
#include "edcs_util.h"
#include "edcs_default.h"

/*
 * Allow C++ compilers to use this API without problems.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetHighestCodesUsed
 *
 *   Given a dictionary type, this function will return the highest code that
 *   is in the ISO standard for that dictionary, and the highest code from the
 *   the EDCS registry that is in this implementation.
 *
 * PARAMETERS:
 *
 *   dictionary_name - the EDCS dictionary for which to retrieve code
 *       information.
 *
 *   standard_code_out_ptr - pointer to user's memory space to which the
 *       highest ISO standard code will be copied.
 *
 *   registered_code_out_ptr - pointer to user's memory space to which the
 *       highest registered code will be copied.
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *standard_code_out_ptr and *registered_code_out_ptr
 *     will be set to their proper values if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and both *standard_code_out_ptr and
 *     *registered_code_out_ptr are left unchanged, if either output parameter
 *     is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_DICTIONARY - and both *standard_code_out_ptr and
 *     *registered_code_out_ptr will be set to zero, if the dictionary_name
 *     input parameter is not a valid EDCS_Dictionary_Type.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_GetHighestCodesUsed
(
    EDCS_Dictionary_Type  dictionary_name,
    EDCS_Integer         *standard_code_out_ptr,
    EDCS_Integer         *registerd_code_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_PrettyPrintLabel
 *
 *   Given a character string representing an EDCS label, this function will
 *   return a character string that has been smartly capitalized, for
 *   presentation purposes.  Abbreviations in EDCS labels will retain their
 *   capitalization.
 *
 * PARAMETERS:
 *
 *   label_in_ptr - the EDCS label to be pretty-printed.
 *
 * RETURNS:
 *
 *   const char * representing the formated label.  If the label_in_ptr is
 *   NULL, then this string will read "NULL" and if the label_in_ptr is a 0
 *   length string a 0 length string will be returned.
 *
 *-----------------------------------------------------------------------------
 */
extern const char *
EDCS_PrettyPrintLabel
(
    const char *label_in_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetImplVerInfo
 *
 *   This function returns the implementation version of the EDCS component.
 *
 * PARAMETERS:
 *
 *   none
 *
 * RETURNS:
 *
 *   The appropriate string representing the current version of the EDCS SDK.
 *   For example, if this were the EDCS SDK Version 4.2, this function would
 *   return the string "4.2".
 *
 *-----------------------------------------------------------------------------
 */
extern const char *
EDCS_GetImplVerInfo
(
    void
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetVersionInformation
 *
 *   This function returns the version of the implementation of the
 *   EDCS used to define the given transmittal.
 *
 *   Major versions are specified by an integer that is incremented
 *   whenever large changes are made to the implementation.
 *
 *   Minor versions are specified by an integer that is incremented
 *   whenever any small changes are made to the implementation.
 *
 *   Interim versions are specified using a lower case letter that
 *   is incremented whenever a new interim version of the
 *   implementation is released.
 *
 * PARAMETERS:
 *
 *   major_EDCS_version - a pointer to a EDCS_Count in the user's memory
 *     space that will be set to an integer value greaterthan or equal to 1
 *
 *   minor_EDCS_version - a pointer to a EDCS_Count in the user's memory
 *     space that will be set to an integer value between 0 and 99, inclusive
 *
 *   interim_EDCS_version - a pointer to a EDCS_Character in the user's
 *     memory space that will be set to a value between 'a' and 'z' inclusive.
 *     If it was not an interim version of the EDCS, then the value will
 *     be set to '\0'.
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and the output parameters are set, if valid parameters
 *     were passed in and all operations succeeded.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and the output parameters are
 *     left unchanged, if major_EDCS_version, minor_EDCS_version, or
 *     interim_EDCS_version was NULL.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_GetVersionInformation
(
    EDCS_Count     *major_EDCS_version,
    EDCS_Count     *minor_EDCS_version,
    EDCS_Character *interim_EDCS_version
);
#ifdef __cplusplus
}
#endif

#endif
