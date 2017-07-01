
//
// PROGRAMMERS: Automatically generated from EDCS database
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

#include "edcs.h"
#include "edcs_internal.h"

#define EDCS_TOTAL_LABEL_ABBREV ((EDCS_Integer)287)

const char *
EDCS_Label_Abbrev[] =
{
    "ABS",
    "ABV",
    "ACCUM",
    "ADMIN",
    "ADRG",
    "AERO",
    "AGG",
    "AGL",
    "AGRI",
    "ALT",
    "ALTOCM",
    "AM",
    "AMASS",
    "AMB",
    "AMP",
    "AMT",
    "APAP",
    "APPROX",
    "ARCP",
    "ARIP",
    "ARTCC",
    "ATM",
    "ATNAV",
    "ATS",
    "ATZ",
    "AZ",
    "BHO",
    "BLOW",
    "BLW",
    "BOTU",
    "BRDF",
    "C",
    "C4I",
    "CD",
    "CHAR",
    "CHARCTR",
    "CHG",
    "CLD",
    "CLECT",
    "CLIM",
    "CLUST",
    "CM",
    "CMNIMB",
    "CMPH",
    "CNCRT",
    "CNTNTL",
    "COEFF",
    "COMNAVFE",
    "COMNAVPAC",
    "COMP",
    "CONC",
    "CONT",
    "CONUS",
    "CREX",
    "CRSTRAT",
    "CTR",
    "CTRY",
    "CUR",
    "CYCL",
    "CZ",
    "DANES",
    "DEC",
    "DECID",
    "DEF",
    "DELIB",
    "DEM",
    "DENS",
    "DEPR",
    "DEV",
    "DEVL",
    "DEW",
    "DHR",
    "DIFF",
    "DIR",
    "DME",
    "DRFT",
    "DRZL",
    "DSSS",
    "ELEC",
    "ELEV",
    "ELLPS",
    "EM",
    "EMBANK",
    "EMIT",
    "ENV",
    "EQUIV",
    "ERR",
    "ETRS",
    "EUR",
    "EV",
    "EVAP",
    "EXBI",
    "FAA",
    "FANM",
    "FLY",
    "FORACS",
    "FREQ",
    "FRZ",
    "GCA",
    "GCI",
    "GEN",
    "GEOPHY",
    "GIBI",
    "GPS",
    "GRAD",
    "GRAF",
    "GSE",
    "HF",
    "HI",
    "HMISPH",
    "HORIZ",
    "HRS",
    "HT",
    "HVY",
    "HYDRO",
    "HZ",
    "ID",
    "IDZ",
    "IED",
    "IFR",
    "ILS",
    "IMO",
    "IMPED",
    "INC",
    "INCID",
    "INDEP",
    "INFL",
    "INMIT",
    "INR",
    "INS",
    "INT",
    "INTEG",
    "INTERM",
    "INV",
    "INVIS",
    "INVRSN",
    "INZ",
    "IRREG",
    "ISO",
    "K",
    "KG",
    "KHZ",
    "KIBI",
    "KM",
    "LANG",
    "LEN",
    "LF",
    "LFLY",
    "LOC",
    "LQD",
    "LRG",
    "LVL",
    "M",
    "MAGMETER",
    "MAX",
    "MEBI",
    "MECH",
    "MET",
    "METOC",
    "MICRON",
    "MIN",
    "MISC",
    "MISS",
    "MLS",
    "MLTRY",
    "MMPH",
    "MOD",
    "MRCHNT",
    "MSL",
    "N",
    "NB",
    "NDB",
    "NE",
    "NF",
    "NW",
    "OBS",
    "OCA",
    "ODAS",
    "OIS",
    "PAR",
    "PCT",
    "PEBI",
    "PEOP",
    "PER",
    "PERP",
    "PLLT",
    "POL",
    "POS",
    "PPB",
    "PPM",
    "PPT",
    "PPTH",
    "PRECIP",
    "PREV",
    "PRHBT",
    "PRI",
    "PRIN",
    "PROP",
    "PROV",
    "PRSNT",
    "PRVL",
    "PVC",
    "PVU",
    "PWR",
    "RAD",
    "RCI",
    "RDCD",
    "RECOG",
    "REF",
    "REG",
    "REIL",
    "RF",
    "RFLCT",
    "RGB",
    "RNG",
    "ROT",
    "RSTRCT",
    "RTE",
    "S",
    "SAL",
    "SCINT",
    "SCND",
    "SCTR",
    "SDSTRM",
    "SE",
    "SEC",
    "SECT",
    "SEP",
    "SHWR",
    "SIGNI",
    "SIGNIF",
    "SL",
    "SLTN",
    "SML",
    "SNFLK",
    "SPC",
    "SPCT",
    "SQ",
    "SQD",
    "SR",
    "SRF",
    "SSALR",
    "SSNL",
    "ST",
    "STD",
    "STRATCM",
    "SUB",
    "SUBST",
    "SUPP",
    "SURV",
    "SVR",
    "SW",
    "TACT",
    "TAPPS",
    "TEBI",
    "TEL",
    "TELECOM",
    "TEMP",
    "THERMO",
    "THICK",
    "THIN",
    "THND",
    "TRANS",
    "TRNSHP",
    "TRNSP",
    "TROP",
    "TRRT",
    "TSS",
    "TZ",
    "UK",
    "UNESCO",
    "US",
    "UUID",
    "VAR",
    "VASI",
    "VEH",
    "VFR",
    "VIBRAT",
    "VIS",
    "VISIB",
    "VOR",
    "W",
    "WGS",
    "WRT",
    "WTR",
    "WW",
    "WX"
};

/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetHighestCodesUsed
 *
 *----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_GetHighestCodesUsed
(
    EDCS_Dictionary_Type  dictionary_name,
    EDCS_Integer         *standard_code_out_ptr,
    EDCS_Integer         *registered_code_out_ptr
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (EDCS_ValidDictionaryType(dictionary_name) != EDCS_SC_SUCCESS)
    {
        status = EDCS_SC_INVALID_INPUT_DICTIONARY;
    }
    else if (!standard_code_out_ptr || !registered_code_out_ptr)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else
    {
        switch (dictionary_name)
        {
            case EDCS_DT_CLASSIFICATION:
                *standard_code_out_ptr = EDCS_TOTAL_EC;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_ATTRIBUTE:
                *standard_code_out_ptr = EDCS_TOTAL_EA;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_ATTRIBUTE_VALUE_CHARACTERISTIC:
                *standard_code_out_ptr = EDCS_TOTAL_EV;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_ATTRIBUTE_ENUMERANT:
                *standard_code_out_ptr = EDCS_TOTAL_EE;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_UNIT:
                *standard_code_out_ptr = EDCS_TOTAL_EU;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_UNIT_SCALE:
                *standard_code_out_ptr = EDCS_TOTAL_ES;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_UNIT_EQUIVALENCE_CLASS:
                *standard_code_out_ptr = EDCS_TOTAL_EQ;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_ORGANIZATION_SCHEMA:
                *standard_code_out_ptr = EDCS_TOTAL_EO;
                *registered_code_out_ptr = 0;
                break;
            case EDCS_DT_GROUP:
                *standard_code_out_ptr = EDCS_TOTAL_EG;
                *registered_code_out_ptr = 0;
                break;
        } /* end switch */
    }
    return status;
} /* end EDCS_GetHighestCodesUsed */


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_PrettyPrintLabel
 *
 *----------------------------------------------------------------------------
 */
const char *
EDCS_PrettyPrintLabel
(
    const char * label_in_ptr
)
{
    static EDCS_Character buffer[100];
    EDCS_Count end_word_pos = 0, pos = 0, i;
    EDCS_Boolean word_start = EDCS_TRUE;

    buffer[0] = '\0';

    if (label_in_ptr == NULL)
    {
        return "NULL Label";
    }
    else if (strlen(label_in_ptr) == 0)
    {
        return "";
    }
    else
    {
        sprintf(buffer, "%s", label_in_ptr);

        while (pos < strlen(buffer))
        {
            /*
             * if we are at the start of the word, find the length of the word
             * and check the EDCS_Label_Abbrev array for matching values.  If
             * none are found then do simple smart capitalization
             */
            if (word_start)
            {
                word_start = EDCS_FALSE;

                end_word_pos = 0;

                for (i = pos; i < strlen(buffer) && !end_word_pos; i++)
                {
                    if (buffer[i] == '_')
                    {
                        end_word_pos = i;
                    }
                }

                if (end_word_pos < 1)
                {
                    end_word_pos = i;
                }

                for (i = 0; i < EDCS_TOTAL_LABEL_ABBREV; i++)
                {
                    if (!strncmp(&buffer[pos], EDCS_Label_Abbrev[i], strlen(EDCS_Label_Abbrev[i])))
                    {
                        if (((EDCS_Count)strlen(EDCS_Label_Abbrev[i])) == end_word_pos - pos)
                        {
                            break;
                        }
                    }
                }

                if (i != EDCS_TOTAL_LABEL_ABBREV)
                {
                    pos += (strlen(EDCS_Label_Abbrev[i]));
                }
                else
                {
                    pos++;
                }
            }
            else
            {
                buffer[pos] = tolower(buffer[pos]);
                pos++;
            }

            if (buffer[pos] == '_')
            {
                buffer[pos] = ' ';
                word_start = EDCS_TRUE;
                pos++;
            }
        }
    }
    return buffer;
} /* end EDCS_PrettyPrintLabel */


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetVersionInformation
 *
 *----------------------------------------------------------------------------
 */
EDCS_Status_Code
EDCS_GetVersionInformation
(
    EDCS_Count     *major_EDCS_version,
    EDCS_Count     *minor_EDCS_version,
    EDCS_Character *interim_EDCS_version
)
{
    EDCS_Status_Code status = EDCS_SC_SUCCESS;

    if (!major_EDCS_version || !minor_EDCS_version || !interim_EDCS_version)
    {
        status = EDCS_SC_NULL_REQUIRED_PARAMETER;
    }
    else
    {
        *major_EDCS_version   = EDCS_MAJOR_VERSION;
        *minor_EDCS_version   = EDCS_MINOR_VERSION;
        *interim_EDCS_version = EDCS_INTERIM_VERSION;
    }
    return status;
} /* end EDCS_GetVersionInformation */


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetImplVerInfo
 *
 *----------------------------------------------------------------------------
 */
const char *
EDCS_GetImplVerInfo(void)
{
    return "4.4.0";
} /* end EDCS_GetImplVerInfo */
