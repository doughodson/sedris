
#ifndef __EDCS_VALID_H_INCLUDED__
#define __EDCS_VALID_H_INCLUDED__

//
// PROGRAMMERS: Automatically generated file
//
// DESCRIPTION:
//   Contains prototypes for validating functions for all EDCS types.
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

/*
 * Allow C++ compilers to use this API without any problems
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h> /* needed for FILE */
#include "edcs_types.h"


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetErrorFilePtr
 *
 *   Returns the FILE pointer to which error messages are directed.
 *
 * PARAMETERS:
 *
 *   nothing
 *
 * RETURNS:
 *
 *   FILE pointer to stream to which error messages are to be output
 *
 *-----------------------------------------------------------------------------
 */
extern FILE *
EDCS_GetErrorFilePtr(void);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SetErrorFilePtr
 *
 *   Sets the FILE pointer to which error messages are directed,
 *   if error messages are requested.
 *
 *   WARNING: If you close this file after calling this function,
 *            remember that the EDCS functions will still try to use it.
 *
 * PARAMETERS:
 *
 *   err_file_ptr -- stream to which error messages are to be output
 *
 * RETURNS:
 *
 *   EDCS_SC_OTHER_FAILURE - and nothing is changed, if err_file_ptr is NULL
 *
 *   EDCS_SC_SUCCESS - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_SetErrorFilePtr
(
    FILE *err_file_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidLocale
 *
 *   Checks the information in the given EDCS_Locale.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Locale whose contents are to be checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Locale is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidLocale
(
    const EDCS_Locale           *value_ptr,
          EDCS_Boolean           print_error,
          EDCS_Count            *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidNonNullString
 *
 *   Checks that given EDCS_String is valid and contains a non-empty string.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_String whose contents are to be checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_String is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidNonNullString
(
    const EDCS_String           *value_ptr,
          EDCS_Boolean           print_error,
          EDCS_Count            *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidAttributeValue
 *
 *   Checks the information in the given EDCS_Attribute_Value.
 *
 * PARAMETERS:
 *
 *   attr_code -- meaning
 *
 *   value_ptr -- pointer to EDCS_Attribute_Value whose contents are to be
 *                checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Attribute_Value is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidAttributeValue
(
          EDCS_Attribute_Code     attr_code,
    const EDCS_Attribute_Value *value_ptr,
          EDCS_Boolean          print_error,
          EDCS_Count           *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidAttributeValueType
 *
 *   Checks if the given value is a valid EDCS_Attribute_Value_Type.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidAttributeValueType
(
    EDCS_Attribute_Value_Type value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidBoolean
 *
 *   Checks if the given value is a valid EDCS_Boolean.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidBoolean
(
    EDCS_Boolean value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidConceptStatus
 *
 *   Checks if the given value is a valid EDCS_Concept_Status.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidConceptStatus
(
    EDCS_Concept_Status value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidCountInterval
 *
 *   Checks the information in the given EDCS_Count_Interval.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Count_Interval whose contents are to be
 *                checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Count_Interval is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidCountInterval
(
    const EDCS_Count_Interval *value_ptr,
          EDCS_Boolean         print_error,
          EDCS_Count          *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidCountValue
 *
 *   Checks the information in the given EDCS_Count_Value.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Count_Value whose contents are to be checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Count_Value is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidCountValue
(
    const EDCS_Count_Value *value_ptr,
          EDCS_Boolean      print_error,
          EDCS_Count       *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidDictionaryType
 *
 *   Checks if the given value is a valid EDCS_Dictionary_Type.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidDictionaryType
(
    EDCS_Dictionary_Type value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidIntegerInterval
 *
 *   Checks the information in the given EDCS_Integer_Interval.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Integer_Interval whose contents are to be
 *                checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Integer_Interval is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidIntegerInterval
(
    const EDCS_Integer_Interval *value_ptr,
          EDCS_Boolean           print_error,
          EDCS_Count            *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidIntegerValue
 *
 *   Checks the information in the given EDCS_Integer_Value.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Integer_Value whose contents are to be
 *                checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Integer_Value is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidIntegerValue
(
    const EDCS_Integer_Value *value_ptr,
          EDCS_Boolean        print_error,
          EDCS_Count         *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidLongFloatInterval
 *
 *   Checks the information in the given EDCS_Long_Float_Interval.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Long_Float_Interval whose contents are to be
 *                checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Long_Float_Interval is stored; if NULL, no counting is
 *     performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidLongFloatInterval
(
    const EDCS_Long_Float_Interval *value_ptr,
          EDCS_Boolean              print_error,
          EDCS_Count               *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidLongFloatValue
 *
 *   Checks the information in the given EDCS_Long_Float_Value.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Long_Float_Value whose contents are to be
 *                checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Long_Float_Value is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidLongFloatValue
(
    const EDCS_Long_Float_Value *value_ptr,
          EDCS_Boolean           print_error,
          EDCS_Count            *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidNull
 *
 *   Checks if the given value is a valid EDCS_Null.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidNull
(
    EDCS_Null value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidNumericValueType
 *
 *   Checks if the given value is a valid EDCS_Numeric_Value_Type.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidNumericValueType
(
    EDCS_Numeric_Value_Type value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidRealValue
 *
 *   Checks the information in the given EDCS_Real_Value.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_Real_Value whose contents are to be checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_Real_Value is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidRealValue
(
    const EDCS_Real_Value *value_ptr,
          EDCS_Boolean     print_error,
          EDCS_Count      *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidReferenceType
 *
 *   Checks if the given value is a valid EDCS_Reference_Type.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidReferenceType
(
    EDCS_Reference_Type value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidStatusCode
 *
 *   Checks if the given value is a valid EDCS_Status_Code.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidStatusCode
(
    EDCS_Status_Code value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidString
 *
 *   Checks the information in the given EDCS_String.
 *
 * PARAMETERS:
 *
 *   value_ptr -- pointer to EDCS_String whose contents are to be checked
 *
 *   print_error -- whether to print error messages
 *
 *   error_count_ptr -- pointer to a variable in which the error count for
 *     this EDCS_String is stored; if NULL, no counting is performed
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value_ptr is non-NULL and *value_ptr contains valid
 *     information
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidString
(
    const EDCS_String *value_ptr,
          EDCS_Boolean  print_error,
          EDCS_Count  *error_count_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidUnitStatus
 *
 *   Checks if the given value is a valid EDCS_Unit_Status.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidUnitStatus
(
    EDCS_Unit_Status value
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidValueCharacteristicApplicability
 *
 *   Checks if the given value is a valid
 * EDCS_Value_Characteristic_Applicability.
 *
 * PARAMETERS:
 *
 *   value -- value to be checked
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if value is valid
 *
 *   EDCS_FALSE - otherwise
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidValueCharacteristicApplicability
(
    EDCS_Value_Characteristic_Applicability value
);
#ifdef __cplusplus
}
#endif
#endif
