
/*
 * DESCRIPTION:
 *     This program takes an EDCS classification code (or label)
 *     and an EDCS attribute code (or label) and displays their
 *     information.
 *
 * Usage:
 *   sample_edcs_access ECC_label EAC_label
 *   or
 *   sample_edcs_access ECC_label EAC_code
 *   or
 *   sample_edcs_access ECC_code EAC_label
 *   or
 *   sample_edcs_access ECC_code EAC_code
 *
 * Options: none
 *
 * Examples:
 *
 *   sample_edcs_access WALL WALL_CONSTRUCTION_TYPE
 *   sample_edcs_access 101 200
 */

#include <stdio.h>
#include <stdlib.h>

#include "edcs.h"

const char *const EdcsVersionString = "4.4.x";
const char *const ToolName = "sample_edcs_access";
const char *const ToolVersionString = "4.4.0.0";
const char *const BaseToolString = "%s v%s\n    (compatible with EDCS SDK %s)\n\n\n";

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: print_usage_and_exit
 *
 *-----------------------------------------------------------------------------
 */
static void
print_usage_and_exit
(
    const char *err_msg
)
{
    fprintf(stderr, "%s\n\n", err_msg);

    fprintf(stderr,
"sample_edcs_access takes an EDCS classification code (or label) "\
"and an EDCS attribute code (or label) and displays their "\
"information.\n"\
"\n"\
"Usage: sample_edcs_access ECC_label EAC_label\n"\
"    or\n"\
"       sample_edcs_access ECC_label EAC_code\n"\
"    or\n"\
"       sample_edcs_access ECC_code EAC_label\n"\
"    or\n"\
"       sample_edcs_access ECC_code EAC_code\n"\
"\n"\
" Options:\n" \
"\n" \
"  None\n" \
"\n" \
"Examples:\n" \
"  To find mapping information for ECC_BUILDING and EAC_BUILDING_FUNCTION:\n"\
"    sample_edcs_access BUILDING BUILDING_FUNCTION\n"\
"    or\n"\
"    sample_edcs_access BUILDING 208\n\n"\
"    or\n"\
"    sample_edcs_access 173 BUILDING_FUNCTION\n\n"\
"    or\n"\
"    sample_edcs_access 173 208\n\n");
    fflush(stderr);
    exit(-1);
} /* end print_usage_and_exit */

int main( int argc, char * argv[] )
{
    printf(BaseToolString, ToolName, ToolVersionString,
           EdcsVersionString);

    if (argc < 3)
    {
        print_usage_and_exit("Not enough parameters.");
    }
    else
    {
        const EDCS_Classification_Dictionary_Entry *ecd = NULL;
        const EDCS_Attribute_Dictionary_Entry *ead = NULL;
        EDCS_Classification_Code ec_code = 0;
        EDCS_Attribute_Code      ea_code = 0;

        ec_code = atoi(argv[1]);
        if (EDCS_GetECDictionaryEntry(ec_code, &ecd) != EDCS_SC_SUCCESS)
        {
            if (EDCS_LabelToECCode(argv[1], &ec_code) == EDCS_SC_SUCCESS)
            {
                if (EDCS_GetECDictionaryEntry(ec_code, &ecd) != EDCS_SC_SUCCESS)
                {
                    ec_code = 0;
                    ecd     = NULL;
                }
            }
            else
            {
                ec_code = 0;
                ecd     = NULL;
            }
        }

        if (ecd != NULL)
        {
            printf("ECC (%i) - %s:\n\t%s\n",
                   ecd->code, ecd->label, ecd->definition);
        }
        else
        {
            fprintf(stderr,
                    "Error in call to EDCS_GetECDictionaryEntry() - "\
                    " requires integer code or label of a valid EC\n");
        }
        printf("\n");

        ea_code = atoi(argv[2]);
        if (EDCS_GetEADictionaryEntry(ea_code, &ead) != EDCS_SC_SUCCESS)
        {
            if (EDCS_LabelToEACode(argv[2], &ea_code) == EDCS_SC_SUCCESS)
            {
                if (EDCS_GetEADictionaryEntry(ea_code, &ead) != EDCS_SC_SUCCESS)
                {
                    ea_code = 0;
                    ead     = NULL;
                }
            }
            else
            {
                ea_code = 0;
                ead     = NULL;
            }
        }

        if (ead != NULL)
        {
            printf("EAC (%i) - %s:\n\t%s\n",
                   ead->code, ead->label, ead->definition);
        }
        else
        {
            fprintf(stderr,
                    "Error in call to EDCS_GetEADictionaryEntry() - "\
                    " requires integer code or label of a valid EA\n");
        }
    }
    return 0;
} /* end main */
