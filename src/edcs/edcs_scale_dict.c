
//
// PROGRAMMERS: Automatically generated from EDCS database
//
// DESCRIPTION:
//      Provides dictionary information for all ESs.
//
//      *** IMPORTANT NOTE ***
//      This file is generated automatically from the EDCS database tables using
//      the EDCS Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
//      be made in the EDCS database and EDCS Code generator templates, and will be
//      reflected in this file when the system is rebuilt.
//

#include "edcs_scale_dict.h"
#include "edcs_internal.h"

static const EDCS_Unit_Scale_Dictionary_Entry
EDCS_Unit_Scale_Dictionary[] =
{
    {ESC_YOTTA,
    "YOTTA", "ESC_YOTTA",
    "Y", "10^(24)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_ZETTA,
    "ZETTA", "ESC_ZETTA",
    "Z", "10^(21)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_EXA,
    "EXA", "ESC_EXA",
    "E", "10^(18)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_PETA,
    "PETA", "ESC_PETA",
    "P", "10^(15)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_TERA,
    "TERA", "ESC_TERA",
    "T", "10^(12)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_GIGA,
    "GIGA", "ESC_GIGA",
    "G", "10^(9)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_MEGA,
    "MEGA", "ESC_MEGA",
    "M", "10^(6)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_KILO,
    "KILO", "ESC_KILO",
    "k", "10^(3)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_HECTO,
    "HECTO", "ESC_HECTO",
    "h", "10^(2)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_DECA,
    "DECA", "ESC_DECA",
    "da", "10^(1)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_UNI,
    "UNI", "ESC_UNI",
    "1", "10^(0)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_DECI,
    "DECI", "ESC_DECI",
    "d", "10^(-1)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_CENTI,
    "CENTI", "ESC_CENTI",
    "c", "10^(-2)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_MILLI,
    "MILLI", "ESC_MILLI",
    "m", "10^(-3)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_MICRO,
    "MICRO", "ESC_MICRO",
    "(mu)", "10^(-6)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_NANO,
    "NANO", "ESC_NANO",
    "n", "10^(-9)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_PICO,
    "PICO", "ESC_PICO",
    "p", "10^(-12)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_FEMTO,
    "FEMTO", "ESC_FEMTO",
    "f", "10^(-15)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_ATTO,
    "ATTO", "ESC_ATTO",
    "a", "10^(-18)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_ZEPTO,
    "ZEPTO", "ESC_ZEPTO",
    "z", "10^(-21)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_YOCTO,
    "YOCTO", "ESC_YOCTO",
    "y", "10^(-24)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_KIBI,
    "KIBI", "ESC_KIBI",
    "Ki", "2^(10)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_MEBI,
    "MEBI", "ESC_MEBI",
    "Mi", "2^(20)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_GIBI,
    "GIBI", "ESC_GIBI",
    "Gi", "2^(30)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_TEBI,
    "TEBI", "ESC_TEBI",
    "Ti", "2^(40)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_PEBI,
    "PEBI", "ESC_PEBI",
    "Pi", "2^(50)",
    EDCS_CONCEPT_STAT_ISO },

    {ESC_EXBI,
    "EXBI", "ESC_EXBI",
    "Ei", "2^(60)",
    EDCS_CONCEPT_STAT_ISO }

}; /* EDCS_Unit_Scale_Dictionary */

/*
 * STRUCT: EDCS_Unit_Scale_Label_Entry
 *
 *  Used within this file for the label lookup table.
 */
typedef struct
{
    EDCS_Unit_Scale_Code  code;
    EDCS_Unit_Scale_Label label;
} EDCS_Unit_Scale_Label_Entry;

static const EDCS_Unit_Scale_Label_Entry
EDCS_Unit_Scale_Labels[] =
{
    {ESC_ATTO, "ATTO"},
    {ESC_CENTI, "CENTI"},
    {ESC_DECA, "DECA"},
    {ESC_DECI, "DECI"},
    {ESC_EXA, "EXA"},
    {ESC_EXBI, "EXBI"},
    {ESC_FEMTO, "FEMTO"},
    {ESC_GIBI, "GIBI"},
    {ESC_GIGA, "GIGA"},
    {ESC_HECTO, "HECTO"},
    {ESC_KIBI, "KIBI"},
    {ESC_KILO, "KILO"},
    {ESC_MEBI, "MEBI"},
    {ESC_MEGA, "MEGA"},
    {ESC_MICRO, "MICRO"},
    {ESC_MILLI, "MILLI"},
    {ESC_NANO, "NANO"},
    {ESC_PEBI, "PEBI"},
    {ESC_PETA, "PETA"},
    {ESC_PICO, "PICO"},
    {ESC_TEBI, "TEBI"},
    {ESC_TERA, "TERA"},
    {ESC_UNI, "UNI"},
    {ESC_YOCTO, "YOCTO"},
    {ESC_YOTTA, "YOTTA"},
    {ESC_ZEPTO, "ZEPTO"},
    {ESC_ZETTA, "ZETTA"}
}; /* EDCS_Unit_Scale_Labels */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: local_CompareESLabel
 *
 *-----------------------------------------------------------------------------
 */
static int
local_CompareESLabel
(
    const EDCS_Unit_Scale_Label_Entry *a_ptr,
    const EDCS_Unit_Scale_Label_Entry *b_ptr
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
} /* end local_CompareESLabel */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetESDictionaryEntry
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_GetESDictionaryEntry
(
          EDCS_Unit_Scale_Code               es_code_in,
    const EDCS_Unit_Scale_Dictionary_Entry **result_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (result_out_ptr == NULL)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else if(!EDCS_ValidUnitScaleCode(es_code_in))
    {
        status = EDCS_SC_INVALID_INPUT_CODE;
    }
    else
    {
        *result_out_ptr = &(EDCS_Unit_Scale_Dictionary[es_code_in-1]);
    }
    return status;
} /* end EDCS_GetESDictionaryEntry */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_LabelToESCode
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_LabelToESCode
(
    const EDCS_Character       *label_in_ptr,
          EDCS_Unit_Scale_Code *result_out_ptr
)
{
    EDCS_Status_Code             status = EDCS_SC_SUCCESS;
    EDCS_Unit_Scale_Label_Entry *search_result_ptr = NULL, target;

    if (!label_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else
    {
       *result_out_ptr    = (EDCS_Unit_Scale_Code)0;
        target.label      = label_in_ptr;
        search_result_ptr = (EDCS_Unit_Scale_Label_Entry *)
                            bsearch
                            (
                               &target,
                               EDCS_Unit_Scale_Labels,
                               EDCS_TOTAL_ES,
                               sizeof(EDCS_Unit_Scale_Label_Entry),
                               (int(*)(const void*,const void *))
                                      local_CompareESLabel
                            );
        if (search_result_ptr)
            *result_out_ptr = search_result_ptr->code;
        else
            status = EDCS_SC_INVALID_INPUT_LABEL;
    }
    return status;
} /* end EDCS_LabelToESCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_PrintUnitScaleCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
EDCS_PrintUnitScaleCode
(
    EDCS_Unit_Scale_Code es_code_in
)
{
    if (!EDCS_ValidUnitScaleCode(es_code_in))
    {
        static char buffer[256];

        sprintf(buffer, "ERROR - ILLEGAL EDCS_Unit_Scale_Code VALUE (%i)",
               (int) es_code_in);
        return buffer;
    }
    else
    {
        return EDCS_Unit_Scale_Dictionary[es_code_in-1].symbolic_constant;
    }
} /* end EDCS_PrintUnitScaleCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SymbolicConstantToESCode
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_SymbolicConstantToESCode
(
    const EDCS_Character       *symbolic_in_ptr,
          EDCS_Unit_Scale_Code *result_out_ptr
)
{
          EDCS_Status_Code  status = EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT;
    const EDCS_Character   *label;

    if (!symbolic_in_ptr || !result_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else
    {
       /*
        * Symbolic Constants should always be of the form ESC_<ES_Label>, so
        * we strip off the ESC_ and use the EDCS_LabelToESCode function
        */
        if (strstr(symbolic_in_ptr, "ESC_") == symbolic_in_ptr)
        {
            label = strchr(symbolic_in_ptr, '_');

            if (label != NULL)
            {
                label++;
                status = EDCS_LabelToESCode( label, result_out_ptr );

               /*
                * Hand back the correct error code if the label couldn't
                * be found
                */
                if (status == EDCS_SC_INVALID_INPUT_LABEL)
                {
                    status = EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT;
                }
            }
        }
    }
    return status;
} /* end EDCS_SymbolicConstantToESCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidUnitScaleCode
 *
 *-----------------------------------------------------------------------------
 */
EDCS_Boolean
EDCS_ValidUnitScaleCode
(
    EDCS_Unit_Scale_Code es_code_in
)
{
    EDCS_Boolean result = EDCS_TRUE;

    if ((es_code_in < 1) || (es_code_in > EDCS_TOTAL_ES))
    {
        result = EDCS_FALSE;
    }
    else if (EDCS_Unit_Scale_Dictionary[es_code_in-1].code != es_code_in)
    {
        result = EDCS_FALSE;
    }
    return result;
} /* end EDCS_ValidUnitScaleCode */
