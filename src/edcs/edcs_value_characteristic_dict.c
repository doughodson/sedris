
//
// PROGRAMMERS: Automatically generated from EDCS database
//
// DESCRIPTION:
//      Provides dictionary information for all EVs.
//
//      *** IMPORTANT NOTE ***
//      This file is generated automatically from the EDCS database tables using
//      the EDCS Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
//      be made in the EDCS database and EDCS Code generator templates, and will be
//      reflected in this file when the system is rebuilt.
//

#include "edcs_value_characteristic_dict.h"
#include "edcs_internal.h"

static const EDCS_Value_Characteristic_Dictionary_Entry
EDCS_Value_Characteristic_Dictionary[] =
{
    {EVC_POSITIVE_INFINITY,
    "POSITIVE_INFINITY", "EVC_POSITIVE_INFINITY",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_TRUE,
    "The attribute value is positive infinity.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_NEGATIVE_INFINITY,
    "NEGATIVE_INFINITY", "EVC_NEGATIVE_INFINITY",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_TRUE,
    "The attribute value is negative infinity.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_POSITIVE_OVERFLOW,
    "POSITIVE_OVERFLOW", "EVC_POSITIVE_OVERFLOW",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_TRUE,
    "The attribute value is greater than any positive value that can be"
    " represented; positive overflow.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_NEGATIVE_OVERFLOW,
    "NEGATIVE_OVERFLOW", "EVC_NEGATIVE_OVERFLOW",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_TRUE,
    "The attribute value is less than any negative value that can be"
    " represented; negative overflow.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_POSITIVE_UNDERFLOW,
    "POSITIVE_UNDERFLOW", "EVC_POSITIVE_UNDERFLOW",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_TRUE,
    "The value of the attribute value is positive and the absolute value of"
    " the attribute value is less than the absolute value of any positive"
    " value that can be represented in the implementation; positive"
    " underflow.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_NEGATIVE_UNDERFLOW,
    "NEGATIVE_UNDERFLOW", "EVC_NEGATIVE_UNDERFLOW",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_TRUE,
    "The value of the attribute value is negative and the absolute value of"
    " the attribute value is less than the absolute value of any negative"
    " value that can be represented in the implementation; negative"
    " underflow.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_MISSING,
    "MISSING", "EVC_MISSING",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "The attribute value is missing.",
    EDCS_REF_TYP_INFORMATIVE, "[FACC, 5.2.2.2, \"unknown\"]",
    "", EDCS_CONCEPT_STAT_ISO  },

    {EVC_MULTIPLE,
    "MULTIPLE", "EVC_MULTIPLE",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "The attribute has more than one possible value; multiple.",
    EDCS_REF_TYP_INFORMATIVE, "[FACC, 5.2.2.2, \"multiple\"]",
    "", EDCS_CONCEPT_STAT_ISO  },

    {EVC_NOT_APPLICABLE,
    "NOT_APPLICABLE", "EVC_NOT_APPLICABLE",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "No attribute value in the range of possible attribute values is"
    " applicable.",
    EDCS_REF_TYP_INFORMATIVE, "[FACC, 5.2.2.2, \"not applicable\"]",
    "", EDCS_CONCEPT_STAT_ISO  },

    {EVC_VALUE_WITHHELD,
    "VALUE_WITHHELD", "EVC_VALUE_WITHHELD",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "The attribute value exists, but due to policy considerations it cannot"
    " be given; value withheld.",
    EDCS_REF_TYP_INFORMATIVE, "[FACC, 5.2.2.2, \"unpopulated\"]",
    "", EDCS_CONCEPT_STAT_ISO  },

    {EVC_UNDESIGNATED,
    "UNDESIGNATED", "EVC_UNDESIGNATED",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "The attribute value cannot be given for some reason other than it is"
    " one of: EVC_MISSING, EVC_MULTIPLE, EVC_NOT_APPLICABLE, or"
    " EVC_VALUE_WITHHELD; undesignated.",
    EDCS_REF_TYP_INFORMATIVE, "[FACC, 5.2.2.2, \"other\"]",
    "", EDCS_CONCEPT_STAT_ISO  },

    {EVC_VALUE_SPECIFIED,
    "VALUE_SPECIFIED", "EVC_VALUE_SPECIFIED",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "The attribute value is specified.",
    EDCS_REF_TYP_INFORMATIVE, "[FACC, 5.2.2.2]",
    "", EDCS_CONCEPT_STAT_ISO  },

    {EVC_NOMINAL_VALUE,
    "NOMINAL_VALUE", "EVC_NOMINAL_VALUE",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "This attribute value is the nominal and/or default value.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "", EDCS_CONCEPT_STAT_ISO  },

    {EVC_CONSTANT_VALUE,
    "CONSTANT_VALUE", "EVC_CONSTANT_VALUE",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_ALL, EDCS_FALSE,
    "The set of attribute values are constant at this value.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_TOLERANCE,
    "TOLERANCE", "EVC_TOLERANCE",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_FALSE,
    "Each value in the set of attribute values is rounded to a multiple of"
    " this value; tolerance.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_MAXIMUM_VALUE,
    "MAXIMUM_VALUE", "EVC_MAXIMUM_VALUE",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_FALSE,
    "This attribute value is the maximum valid attribute value.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_MINIMUM_VALUE,
    "MINIMUM_VALUE", "EVC_MINIMUM_VALUE",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_FALSE,
    "This attribute value is the minimum valid attribute value.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_UPPER_BOUND,
    "UPPER_BOUND", "EVC_UPPER_BOUND",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_FALSE,
    "This attribute value bounds the set of attribute values from above,"
    " but does not necessarily equal the EVC_MAXIMUM_VALUE; upper bound.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_LOWER_BOUND,
    "LOWER_BOUND", "EVC_LOWER_BOUND",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_FALSE,
    "This attribute value bounds the set of attribute values from below,"
    " but does not necessarily equal the EVC_MINIMUM_VALUE; lower bound.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  },

    {EVC_MEASUREMENT_ERROR,
    "MEASUREMENT_ERROR", "EVC_MEASUREMENT_ERROR",
    EDCS_ATTR_VAL_CHAR_APPLICABILITY_NUMERIC, EDCS_FALSE,
    "The attribute value was measured or estimated with a standard error"
    " given by this value.",
    EDCS_REF_TYP_NOT_APPLICABLE, "",
    "[ECS]", EDCS_CONCEPT_STAT_ISO  }

}; /* EDCS_Value_Characteristic_Dictionary */

/*
 * STRUCT: EDCS_Value_Characteristic_Label_Entry
 *
 *  Used within this file for the label lookup table.
 */
typedef struct
{
    EDCS_Value_Characteristic_Code  code;
    EDCS_Value_Characteristic_Label label;
} EDCS_Value_Characteristic_Label_Entry;

static const EDCS_Value_Characteristic_Label_Entry
EDCS_Value_Characteristic_Labels[] =
{
    {EVC_CONSTANT_VALUE, "CONSTANT_VALUE"},
    {EVC_LOWER_BOUND, "LOWER_BOUND"},
    {EVC_MAXIMUM_VALUE, "MAXIMUM_VALUE"},
    {EVC_MEASUREMENT_ERROR, "MEASUREMENT_ERROR"},
    {EVC_MINIMUM_VALUE, "MINIMUM_VALUE"},
    {EVC_MISSING, "MISSING"},
    {EVC_MULTIPLE, "MULTIPLE"},
    {EVC_NEGATIVE_INFINITY, "NEGATIVE_INFINITY"},
    {EVC_NEGATIVE_OVERFLOW, "NEGATIVE_OVERFLOW"},
    {EVC_NEGATIVE_UNDERFLOW, "NEGATIVE_UNDERFLOW"},
    {EVC_NOMINAL_VALUE, "NOMINAL_VALUE"},
    {EVC_NOT_APPLICABLE, "NOT_APPLICABLE"},
    {EVC_POSITIVE_INFINITY, "POSITIVE_INFINITY"},
    {EVC_POSITIVE_OVERFLOW, "POSITIVE_OVERFLOW"},
    {EVC_POSITIVE_UNDERFLOW, "POSITIVE_UNDERFLOW"},
    {EVC_TOLERANCE, "TOLERANCE"},
    {EVC_UNDESIGNATED, "UNDESIGNATED"},
    {EVC_UPPER_BOUND, "UPPER_BOUND"},
    {EVC_VALUE_SPECIFIED, "VALUE_SPECIFIED"},
    {EVC_VALUE_WITHHELD, "VALUE_WITHHELD"}
}; /* EDCS_Value_Characteristic_Labels */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidValueCharacteristicCode
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Boolean
EDCS_ValidValueCharacteristicCode
(
    EDCS_Value_Characteristic_Code ev_code_in
)
{
    if( (ev_code_in < 1) || (ev_code_in > EDCS_TOTAL_EV))
    {
        return EDCS_FALSE;
    }
    else if(EDCS_Value_Characteristic_Dictionary[ev_code_in-1].code != ev_code_in)
    {
        return EDCS_FALSE;
    }
    else
    {
        return EDCS_TRUE;
    }
}


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_PrintValueCharacteristicCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
EDCS_PrintValueCharacteristicCode
(
    EDCS_Value_Characteristic_Code ev_code_in
)
{
    static char buffer[256];

    if(!EDCS_ValidValueCharacteristicCode(ev_code_in))
    {
        sprintf(buffer, "ERROR - ILLEGAL EDCS_Value_Characteristic_Code VALUE (%i)",
               (int) ev_code_in);
                return buffer;
    }
    else
    {
        return EDCS_Value_Characteristic_Dictionary[ev_code_in-1].symbolic_constant;
    }
}


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetEVDictionaryEntry
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_GetEVDictionaryEntry
(
    EDCS_Value_Characteristic_Code              ev_code_in,
    const EDCS_Value_Characteristic_Dictionary_Entry **result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (result_out_ptr == NULL)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if(!EDCS_ValidValueCharacteristicCode(ev_code_in))
    {
        status = EDCS_SC_INVALID_INPUT_CODE;
    }
    else
    {
        *result_out_ptr = &(EDCS_Value_Characteristic_Dictionary[ev_code_in-1]);
    }
    return status;
} /* end EDCS_GetEVDictionaryEntry */

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: local_CompareEVLabel
 *
 *-----------------------------------------------------------------------------
 */
static int
local_CompareEVLabel
(
    const EDCS_Value_Characteristic_Label_Entry *a_ptr,
    const EDCS_Value_Characteristic_Label_Entry *b_ptr
)
{
    int result = 0;

    if (!a_ptr && b_ptr)
        return -1;
    else if (!a_ptr && !b_ptr)
        return 0;
    else if (a_ptr && !b_ptr)
        return 1;

    result = edcs_strcmp(a_ptr->label, b_ptr->label);
    return result;
} /* end local_CompareEVLabel */

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_LabelToEVCode
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_LabelToEVCode
(
    const EDCS_Character                  *label_in_ptr,
          EDCS_Value_Characteristic_Code  *result_out_ptr
)
{
    EDCS_Status_Code        status = EDCS_SC_SUCCESS;
    EDCS_Value_Characteristic_Label_Entry *search_result_ptr = NULL, target;

    if (!label_in_ptr || !result_out_ptr)
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    else
    {
       *result_out_ptr    = (EDCS_Value_Characteristic_Code)0;
        target.label   = label_in_ptr;
        search_result_ptr = (EDCS_Value_Characteristic_Label_Entry *)
                            bsearch
                            (
                               &target,
                               EDCS_Value_Characteristic_Labels,
                               EDCS_TOTAL_EV,
                               sizeof(EDCS_Value_Characteristic_Label_Entry),
                               (int(*)(const void*,const void *))
                                      local_CompareEVLabel
                            );
        if (search_result_ptr)
            *result_out_ptr = search_result_ptr->code;
        else
            status = EDCS_SC_INVALID_INPUT_LABEL;
    }
    return status;
} /* end EDCS_LabelToEVCode */

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SymbolicConstantToEVCode
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_SymbolicConstantToEVCode
(
    const EDCS_Character     *symbolic_in_ptr,
          EDCS_Value_Characteristic_Code *result_out_ptr
)
{
          EDCS_Status_Code  status = EDCS_SC_SUCCESS;
    const EDCS_Character   *label;

    if (!symbolic_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else
    {
        /* Symbolic Constants should always be of the form EVC_<EV_Label>, so
         * we strip off the EVC_ and use the EDCS_LabelToEVCode function
         */
        label = strchr( symbolic_in_ptr, '_' );

        if (label == NULL)
        {
            status = EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT;
        }
        else
        {
            label++;
            status = EDCS_LabelToEVCode( label, result_out_ptr );

            /* Hand back the correct error code if the label couldn't be found */
            if(status == EDCS_SC_INVALID_INPUT_LABEL)
            {
                status = EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT;
            }
        }
    }
    return status;
} /* end EDCS_SymbolicConstantToEVCode */
