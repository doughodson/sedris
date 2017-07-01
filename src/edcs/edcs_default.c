
//
// PROGRAMMERS: Automatically generated file
//
// DESCRIPTION:
//   Provides pre-initialized global variables containing complete, default
//   field structures for the EDCS API.
//

#include "edcs.h"

/*
 * GLOBAL VARIABLE: edcs_empty_string
 *
 */
const char edcs_empty_string = '\0';



/*
 * GLOBAL VARIABLE: EDCS_ATTRIBUTE_VALUE_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Attribute_Value variable.
 */
const EDCS_Attribute_Value
EDCS_ATTRIBUTE_VALUE_DEFAULT =
{
    EDCS_AVT_REAL, /* attribute_value_type */
    {{EDCS_NVT_SINGLE_VALUE, EUC_UNITLESS, ESC_UNI, {0.0}}} /* value */
};


/*
 * GLOBAL VARIABLE: EDCS_COUNT_INTERVAL_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Count_Interval variable.
 */
const EDCS_Count_Interval
EDCS_COUNT_INTERVAL_DEFAULT =
{
    0, /* lower_bound */
    0 /* upper_bound */
};


/*
 * GLOBAL VARIABLE: EDCS_COUNT_VALUE_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Count_Value variable.
 */
const EDCS_Count_Value
EDCS_COUNT_VALUE_DEFAULT =
{
    EDCS_NVT_SINGLE_VALUE, /* numeric_value_type */
    {0} /* value */
};


/*
 * GLOBAL VARIABLE: EDCS_INTEGER_INTERVAL_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Integer_Interval variable.
 */
const EDCS_Integer_Interval
EDCS_INTEGER_INTERVAL_DEFAULT =
{
    0, /* lower_bound */
    0 /* upper_bound */
};


/*
 * GLOBAL VARIABLE: EDCS_INTEGER_VALUE_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Integer_Value variable.
 */
const EDCS_Integer_Value
EDCS_INTEGER_VALUE_DEFAULT =
{
    EDCS_NVT_SINGLE_VALUE, /* numeric_value_type */
    {0} /* value */
};


/*
 * GLOBAL VARIABLE: EDCS_LOCALE_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Locale variable.
 */
const EDCS_Locale
EDCS_LOCALE_DEFAULT =
{
    {'e', 'n'}, /* language */
    {'u', 's', 'a'} /* country */
};


/*
 * GLOBAL VARIABLE: EDCS_LONG_FLOAT_INTERVAL_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Long_Float_Interval variable.
 */
const EDCS_Long_Float_Interval
EDCS_LONG_FLOAT_INTERVAL_DEFAULT =
{
    0.0, /* lower_bound */
    0.0 /* upper_bound */
};


/*
 * GLOBAL VARIABLE: EDCS_LONG_FLOAT_VALUE_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Long_Float_Value variable.
 */
const EDCS_Long_Float_Value
EDCS_LONG_FLOAT_VALUE_DEFAULT =
{
    EDCS_NVT_SINGLE_VALUE, /* numeric_value_type */
    EUC_UNITLESS, /* unit */
    ESC_UNI, /* unit_scale */
    {0.0} /* value */
};


/*
 * GLOBAL VARIABLE: EDCS_REAL_VALUE_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_Real_Value variable.
 */
const EDCS_Real_Value
EDCS_REAL_VALUE_DEFAULT =
{
    EUC_UNITLESS, /* unit */
    ESC_UNI, /* unit_scale */
    0.0 /* value */
};


/*
 * GLOBAL VARIABLE: EDCS_STRING_DEFAULT
 *
 *   Pre-initialized global variable containing the default values for an
 *   EDCS_String variable.
 */
const EDCS_String
EDCS_STRING_DEFAULT =
{
    {{'e', 'n'}, {'u', 's', 'a'}}, /* locale */
    0, /* length */
    (EDCS_Character *)&edcs_empty_string /* characters */
};
