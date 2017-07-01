
//
// PROGRAMMERS: Automatically generated file
//
// DESCRIPTION:
//   EDCS utilities.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "edcs.h"

/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToAttributeValueType
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToAttributeValueType
(
    const char *enum_name_in_ptr,
          EDCS_Attribute_Value_Type *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_AVT_", 9) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_REAL") == 0)
    {
        *result_out_ptr = EDCS_AVT_REAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_INTEGER") == 0)
    {
        *result_out_ptr = EDCS_AVT_INTEGER;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_COUNT") == 0)
    {
        *result_out_ptr = EDCS_AVT_COUNT;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_INDEX") == 0)
    {
        *result_out_ptr = EDCS_AVT_INDEX;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_STRING") == 0)
    {
        *result_out_ptr = EDCS_AVT_STRING;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_CONSTRAINED_STRING") == 0)
    {
        *result_out_ptr = EDCS_AVT_CONSTRAINED_STRING;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_KEY") == 0)
    {
        *result_out_ptr = EDCS_AVT_KEY;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_ENUMERATION") == 0)
    {
        *result_out_ptr = EDCS_AVT_ENUMERATION;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_BOOLEAN") == 0)
    {
        *result_out_ptr = EDCS_AVT_BOOLEAN;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_AVT_NULL") == 0)
    {
        *result_out_ptr = EDCS_AVT_NULL;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToAttributeValueType */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToBoolean
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToBoolean
(
    const char *enum_name_in_ptr,
          EDCS_Boolean *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_FALSE") == 0)
    {
        *result_out_ptr = EDCS_FALSE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_TRUE") == 0)
    {
        *result_out_ptr = EDCS_TRUE;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToBoolean */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToConceptStatus
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToConceptStatus
(
    const char *enum_name_in_ptr,
          EDCS_Concept_Status *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_CONCEPT_STAT_", 18) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_CONCEPT_STAT_ISO") == 0)
    {
        *result_out_ptr = EDCS_CONCEPT_STAT_ISO;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_CONCEPT_STAT_DEPRECATED") == 0)
    {
        *result_out_ptr = EDCS_CONCEPT_STAT_DEPRECATED;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_CONCEPT_STAT_REGISTRY") == 0)
    {
        *result_out_ptr = EDCS_CONCEPT_STAT_REGISTRY;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToConceptStatus */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToDictionaryType
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToDictionaryType
(
    const char *enum_name_in_ptr,
          EDCS_Dictionary_Type *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_DT_", 8) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_CLASSIFICATION") == 0)
    {
        *result_out_ptr = EDCS_DT_CLASSIFICATION;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_ATTRIBUTE") == 0)
    {
        *result_out_ptr = EDCS_DT_ATTRIBUTE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_ATTRIBUTE_VALUE_CHARACTERISTIC") == 0)
    {
        *result_out_ptr = EDCS_DT_ATTRIBUTE_VALUE_CHARACTERISTIC;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_ATTRIBUTE_ENUMERANT") == 0)
    {
        *result_out_ptr = EDCS_DT_ATTRIBUTE_ENUMERANT;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_UNIT") == 0)
    {
        *result_out_ptr = EDCS_DT_UNIT;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_UNIT_SCALE") == 0)
    {
        *result_out_ptr = EDCS_DT_UNIT_SCALE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_UNIT_EQUIVALENCE_CLASS") == 0)
    {
        *result_out_ptr = EDCS_DT_UNIT_EQUIVALENCE_CLASS;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_ORGANIZATION_SCHEMA") == 0)
    {
        *result_out_ptr = EDCS_DT_ORGANIZATION_SCHEMA;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_DT_GROUP") == 0)
    {
        *result_out_ptr = EDCS_DT_GROUP;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToDictionaryType */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToNull
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToNull
(
    const char *enum_name_in_ptr,
          EDCS_Null *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NULL") == 0)
    {
        *result_out_ptr = EDCS_NULL;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToNull */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToNumericValueType
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToNumericValueType
(
    const char *enum_name_in_ptr,
          EDCS_Numeric_Value_Type *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_NVT_", 9) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_SINGLE_VALUE") == 0)
    {
        *result_out_ptr = EDCS_NVT_SINGLE_VALUE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_OPEN_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_OPEN_INTERVAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_GE_LT_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_GE_LT_INTERVAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_GT_LE_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_GT_LE_INTERVAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_CLOSED_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_CLOSED_INTERVAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_GT_SEMI_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_GT_SEMI_INTERVAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_GE_SEMI_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_GE_SEMI_INTERVAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_LT_SEMI_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_LT_SEMI_INTERVAL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_NVT_LE_SEMI_INTERVAL") == 0)
    {
        *result_out_ptr = EDCS_NVT_LE_SEMI_INTERVAL;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToNumericValueType */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToReferenceType
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToReferenceType
(
    const char *enum_name_in_ptr,
          EDCS_Reference_Type *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_REF_TYP_", 13) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_REF_TYP_PRESCRIPTIVE") == 0)
    {
        *result_out_ptr = EDCS_REF_TYP_PRESCRIPTIVE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_REF_TYP_AUTHORITATIVE") == 0)
    {
        *result_out_ptr = EDCS_REF_TYP_AUTHORITATIVE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_REF_TYP_INFORMATIVE") == 0)
    {
        *result_out_ptr = EDCS_REF_TYP_INFORMATIVE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_REF_TYP_NOT_APPLICABLE") == 0)
    {
        *result_out_ptr = EDCS_REF_TYP_NOT_APPLICABLE;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToReferenceType */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToStatusCode
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToStatusCode
(
    const char *enum_name_in_ptr,
          EDCS_Status_Code *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_SC_", 8) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_LABEL") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_LABEL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_CODE") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_CODE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_NULL_REQUIRED_PARAMETER") == 0)
    {
        *result_out_ptr = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_SUCCESS") == 0)
    {
        *result_out_ptr = EDCS_SC_SUCCESS;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_UNIT") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_UNIT;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_OUTPUT_UNIT") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_OUTPUT_UNIT;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_UNIT_SCALE") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_UNIT_SCALE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_OUTPUT_UNIT_SCALE") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_OUTPUT_UNIT_SCALE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_UNITS_NOT_EQUIVALENT") == 0)
    {
        *result_out_ptr = EDCS_SC_UNITS_NOT_EQUIVALENT;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_ENUMERATED_ATTRIBUTE") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_ENUMERATED_ATTRIBUTE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_GROUP") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_GROUP;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_INVALID_INPUT_DICTIONARY") == 0)
    {
        *result_out_ptr = EDCS_SC_INVALID_INPUT_DICTIONARY;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_SC_OTHER_FAILURE") == 0)
    {
        *result_out_ptr = EDCS_SC_OTHER_FAILURE;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToStatusCode */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToUnitStatus
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToUnitStatus
(
    const char *enum_name_in_ptr,
          EDCS_Unit_Status *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_UNIT_STAT_", 15) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_UNIT_STAT_RECOMMENDED") == 0)
    {
        *result_out_ptr = EDCS_UNIT_STAT_RECOMMENDED;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_UNIT_STAT_ACCEPTED") == 0)
    {
        *result_out_ptr = EDCS_UNIT_STAT_ACCEPTED;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_UNIT_STAT_DEPRECATED") == 0)
    {
        *result_out_ptr = EDCS_UNIT_STAT_DEPRECATED;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_UNIT_STAT_NOT_SI") == 0)
    {
        *result_out_ptr = EDCS_UNIT_STAT_NOT_SI;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToUnitStatus */


/*
 *------------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_EnumNameToValueCharacteristicApplicability
 *
 *------------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_EnumNameToValueCharacteristicApplicability
(
    const char *enum_name_in_ptr,
          EDCS_Value_Characteristic_Applicability *result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!enum_name_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if (strncmp(enum_name_in_ptr,
             "EDCS_ATTR_VAL_CHAR_APPLICABILITY_", 33) != 0)
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL") == 0)
    {
        *result_out_ptr = EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL;
    }
    else if (strcmp(enum_name_in_ptr,
             "EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC") == 0)
    {
        *result_out_ptr = EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC;
    }
    else
    {
        status = EDCS_SC_OTHER_FAILURE;
    }
    return status;
} /* end EDCS_EnumNameToValueCharacteristicApplicability */
