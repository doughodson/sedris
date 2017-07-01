
#ifndef __EDCS_SCALE_DICT_H_INCLUDED__
#define __EDCS_SCALE_DICT_H_INCLUDED__

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

#include "edcs_types.h"

#define EDCS_TOTAL_ES 27

/*
 * Allow C++ compilers to use this API without problems.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetESDictionaryEntry
 *
 *   Retrieves dictionary information for the given ES.
 *
 * PARAMETERS:
 *
 *   es_code_in -- The ES code for which information is requested
 *
 *   result_out_ptr -- pointer to a variable in the user's memory into which
 *       a handle to the requested dictionary entry will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *result_out_ptr is set to the appropriate
 *     value, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_CODE - and no changes are made, if es_code_in
 *     does not correspond to a valid ES.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_GetESDictionaryEntry
(
          EDCS_Unit_Scale_Code              es_code_in,
    const EDCS_Unit_Scale_Dictionary_Entry **result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_LabelToESCode
 *
 *   Retrieves the ES code corresponding to the given label.
 *
 * PARAMETERS:
 *
 *   es_label_in_ptr -- the label for which the corresponding ES code is
 *       requested; note that this is the abstract label (i.e., corresponds
 *       to the abstract EDCS specification)
 *
 *   result_out_ptr -- pointer to a variable in the user's memory into which
 *       the output will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *result_out_ptr is set to the appropriate
 *     value, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_LABEL - and no changes are made, if *es_label_in_ptr
 *     does not correspond to a valid ES.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_LabelToESCode
(
    const EDCS_Character       *es_label_in_ptr,
          EDCS_Unit_Scale_Code *result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SymbolicConstantToESCode
 *
 *   Retrieves the ES code corresponding to the given symbolic constant name.
 *
 * PARAMETERS:
 *
 *   es_symbolic_constant_in_ptr -- the symbolic constant for which the
 *     corresponding ES code is requested; note that this is the
 *     language-binding symbolic constant, rather than the abstract label
 *     (i.e., *       corresponds to the C language binding standard rather
 *     than the abstract EDCS specification)
 *
 *   result_out_ptr -- pointer to a variable in the user's memory into which
 *       the output will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *result_out_ptr is set to the appropriate
 *     value, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT - and no changes are made, if
 *     *es_symbolic_constant_in_ptr does not correspond to a valid ES.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_SymbolicConstantToESCode
(
    const EDCS_Character       *es_symbolic_constant_in_ptr,
          EDCS_Unit_Scale_Code *result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidUnitScaleCode
 *
 *   Indicates if the given ES code is a valid EDCS Unit Scale Code.
 *
 * PARAMETERS:
 *
 *   es_code_in -- The ES code whose validity is being checked.
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if a valid ES code was passed in.
 *
 *   EDCS_FALSE - if a non-valid ES code was passed in.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidUnitScaleCode
(
    EDCS_Unit_Scale_Code es_code_in
);

/*
 * Definition:
 *     10^(24)
 *
 * Symbol:
 *     Y
 */
#define ESC_YOTTA ((EDCS_Unit_Scale_Code)1)

/*
 * Definition:
 *     10^(21)
 *
 * Symbol:
 *     Z
 */
#define ESC_ZETTA ((EDCS_Unit_Scale_Code)2)

/*
 * Definition:
 *     10^(18)
 *
 * Symbol:
 *     E
 */
#define ESC_EXA ((EDCS_Unit_Scale_Code)3)

/*
 * Definition:
 *     10^(15)
 *
 * Symbol:
 *     P
 */
#define ESC_PETA ((EDCS_Unit_Scale_Code)4)

/*
 * Definition:
 *     10^(12)
 *
 * Symbol:
 *     T
 */
#define ESC_TERA ((EDCS_Unit_Scale_Code)5)

/*
 * Definition:
 *     10^(9)
 *
 * Symbol:
 *     G
 */
#define ESC_GIGA ((EDCS_Unit_Scale_Code)6)

/*
 * Definition:
 *     10^(6)
 *
 * Symbol:
 *     M
 */
#define ESC_MEGA ((EDCS_Unit_Scale_Code)7)

/*
 * Definition:
 *     10^(3)
 *
 * Symbol:
 *     k
 */
#define ESC_KILO ((EDCS_Unit_Scale_Code)8)

/*
 * Definition:
 *     10^(2)
 *
 * Symbol:
 *     h
 */
#define ESC_HECTO ((EDCS_Unit_Scale_Code)9)

/*
 * Definition:
 *     10^(1)
 *
 * Symbol:
 *     da
 */
#define ESC_DECA ((EDCS_Unit_Scale_Code)10)

/*
 * Definition:
 *     10^(0)
 *
 * Symbol:
 *     1
 */
#define ESC_UNI ((EDCS_Unit_Scale_Code)11)

/*
 * Definition:
 *     10^(-1)
 *
 * Symbol:
 *     d
 */
#define ESC_DECI ((EDCS_Unit_Scale_Code)12)

/*
 * Definition:
 *     10^(-2)
 *
 * Symbol:
 *     c
 */
#define ESC_CENTI ((EDCS_Unit_Scale_Code)13)

/*
 * Definition:
 *     10^(-3)
 *
 * Symbol:
 *     m
 */
#define ESC_MILLI ((EDCS_Unit_Scale_Code)14)

/*
 * Definition:
 *     10^(-6)
 *
 * Symbol:
 *     (mu)
 */
#define ESC_MICRO ((EDCS_Unit_Scale_Code)15)

/*
 * Definition:
 *     10^(-9)
 *
 * Symbol:
 *     n
 */
#define ESC_NANO ((EDCS_Unit_Scale_Code)16)

/*
 * Definition:
 *     10^(-12)
 *
 * Symbol:
 *     p
 */
#define ESC_PICO ((EDCS_Unit_Scale_Code)17)

/*
 * Definition:
 *     10^(-15)
 *
 * Symbol:
 *     f
 */
#define ESC_FEMTO ((EDCS_Unit_Scale_Code)18)

/*
 * Definition:
 *     10^(-18)
 *
 * Symbol:
 *     a
 */
#define ESC_ATTO ((EDCS_Unit_Scale_Code)19)

/*
 * Definition:
 *     10^(-21)
 *
 * Symbol:
 *     z
 */
#define ESC_ZEPTO ((EDCS_Unit_Scale_Code)20)

/*
 * Definition:
 *     10^(-24)
 *
 * Symbol:
 *     y
 */
#define ESC_YOCTO ((EDCS_Unit_Scale_Code)21)

/*
 * Definition:
 *     2^(10)
 *
 * Symbol:
 *     Ki
 */
#define ESC_KIBI ((EDCS_Unit_Scale_Code)22)

/*
 * Definition:
 *     2^(20)
 *
 * Symbol:
 *     Mi
 */
#define ESC_MEBI ((EDCS_Unit_Scale_Code)23)

/*
 * Definition:
 *     2^(30)
 *
 * Symbol:
 *     Gi
 */
#define ESC_GIBI ((EDCS_Unit_Scale_Code)24)

/*
 * Definition:
 *     2^(40)
 *
 * Symbol:
 *     Ti
 */
#define ESC_TEBI ((EDCS_Unit_Scale_Code)25)

/*
 * Definition:
 *     2^(50)
 *
 * Symbol:
 *     Pi
 */
#define ESC_PEBI ((EDCS_Unit_Scale_Code)26)

/*
 * Definition:
 *     2^(60)
 *
 * Symbol:
 *     Ei
 */
#define ESC_EXBI ((EDCS_Unit_Scale_Code)27)

#ifdef __cplusplus
}
#endif

#endif
