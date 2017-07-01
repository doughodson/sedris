
#ifndef __EDCS_VALUE_CHARACTERISTIC_DICT_H_INCLUDED__
#define __EDCS_VALUE_CHARACTERISTIC_DICT_H_INCLUDED__

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

#include "edcs_types.h"

#define EDCS_TOTAL_EV 20

/*
 * Allow C++ compilers to use this API without problems.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetEVDictionaryEntry
 *
 *   Retrieves dictionary information for the given EM.
 *
 * PARAMETERS:
 *
 *   ev_code_in -- The EV code for which information is requested.
 *
 *   result_out_ptr -- pointer to a variable in the user's memory into which
 *       a handle to the requested dictionary entry will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *result_out_ptr is set to the appropriate
 *     value, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REMUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_CODE - and no changes are made, if ev_code_in
 *     does not correspond to a valid EM.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_GetEVDictionaryEntry
(
    EDCS_Value_Characteristic_Code               ev_code_in,
    const EDCS_Value_Characteristic_Dictionary_Entry **result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_LabelToEVCode
 *
 *   Retrieves the EV code corresponding to the given label.
 *
 * PARAMETERS:
 *
 *   ev_label_in_ptr -- the label for which the corresponding EV code is
 *       requested; note that this is the abstract label (i.e., corresponds
 *       the abstract EDCS specification)
 *
 *   result_out_ptr -- pointer to a variable in the user's memory into which
 *       the output will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *result_out_ptr is set to the appropriate
 *     value, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REMUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_LABEL - and no changes are made, if *ev_label_in_ptr
 *     does not correspond to a valid EV.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_LabelToEVCode
(
    const EDCS_Character                  *ev_label_in_ptr,
          EDCS_Value_Characteristic_Code  *result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SymbolicConstantToEVCode
 *
 *   Retrieves the EV code corresponding to the given symbolic constant name.
 *
 * PARAMETERS:
 *
 *   ev_symbolic_constant_in_ptr -- the symbolic constant for which the
 *       corresponding EV code is requested; note that this is the
 *       language-binding symbolic constant, rather than the abstract label
 *       (i.e., corresponds to the C language binding standard rather than
 *       the abstract EDCS specification)
 *
 *   result_out_ptr -- pointer to a variable in the user's memory into which
 *       the output will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *result_out_ptr is set to the appropriate
 *     value, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REMUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT - and no changes are made, if
 *     *ev_symbolic_constant_in_ptr does not correspond to a valid EV.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_SymbolicConstantToEVCode
(
    const EDCS_Character      *ev_symbolic_constant_in_ptr,
          EDCS_Value_Characteristic_Code  *result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidValueCharacteristicCode
 *
 *   Indicates if the given EV code is a valid EDCS Value Characteristic Code.
 *
 * PARAMETERS:
 *
 *   ev_code_in -- The EV code whose validity is being checked.
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if a valid EV code was passed in.
 *
 *   EDCS_FALSE - if a non-valid EV code was passed in.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidValueCharacteristicCode
(
    EDCS_Value_Characteristic_Code ev_code_in
);

/*
 * Definition:
 *     The attribute value is positive infinity.
 *
 * Applicability: Numeric
 *
 * Quantitative: True
 */
#define EVC_POSITIVE_INFINITY ((EDCS_Value_Characteristic_Code)1)

/*
 * Definition:
 *     The attribute value is negative infinity.
 *
 * Applicability: Numeric
 *
 * Quantitative: True
 */
#define EVC_NEGATIVE_INFINITY ((EDCS_Value_Characteristic_Code)2)

/*
 * Definition:
 *     The attribute value is greater than any positive value that can be
 *     represented; positive overflow.
 *
 * Applicability: Numeric
 *
 * Quantitative: True
 */
#define EVC_POSITIVE_OVERFLOW ((EDCS_Value_Characteristic_Code)3)

/*
 * Definition:
 *     The attribute value is less than any negative value that can be
 *     represented; negative overflow.
 *
 * Applicability: Numeric
 *
 * Quantitative: True
 */
#define EVC_NEGATIVE_OVERFLOW ((EDCS_Value_Characteristic_Code)4)

/*
 * Definition:
 *     The value of the attribute value is positive and the absolute value of
 *     the attribute value is less than the absolute value of any positive
 *     value that can be represented in the implementation; positive
 *     underflow.
 *
 * Applicability: Numeric
 *
 * Quantitative: True
 */
#define EVC_POSITIVE_UNDERFLOW ((EDCS_Value_Characteristic_Code)5)

/*
 * Definition:
 *     The value of the attribute value is negative and the absolute value of
 *     the attribute value is less than the absolute value of any negative
 *     value that can be represented in the implementation; negative
 *     underflow.
 *
 * Applicability: Numeric
 *
 * Quantitative: True
 */
#define EVC_NEGATIVE_UNDERFLOW ((EDCS_Value_Characteristic_Code)6)

/*
 * Definition:
 *     The attribute value is missing.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_MISSING ((EDCS_Value_Characteristic_Code)7)

/*
 * Definition:
 *     The attribute has more than one possible value; multiple.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_MULTIPLE ((EDCS_Value_Characteristic_Code)8)

/*
 * Definition:
 *     No attribute value in the range of possible attribute values is
 *     applicable.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_NOT_APPLICABLE ((EDCS_Value_Characteristic_Code)9)

/*
 * Definition:
 *     The attribute value exists, but due to policy considerations it cannot
 *     be given; value withheld.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_VALUE_WITHHELD ((EDCS_Value_Characteristic_Code)10)

/*
 * Definition:
 *     The attribute value cannot be given for some reason other than it is
 *     one of: EVC_MISSING, EVC_MULTIPLE, EVC_NOT_APPLICABLE, or
 *     EVC_VALUE_WITHHELD; undesignated.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_UNDESIGNATED ((EDCS_Value_Characteristic_Code)11)

/*
 * Definition:
 *     The attribute value is specified.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_VALUE_SPECIFIED ((EDCS_Value_Characteristic_Code)12)

/*
 * Definition:
 *     This attribute value is the nominal and/or default value.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_NOMINAL_VALUE ((EDCS_Value_Characteristic_Code)13)

/*
 * Definition:
 *     The set of attribute values are constant at this value.
 *
 * Applicability: All
 *
 * Quantitative: False
 */
#define EVC_CONSTANT_VALUE ((EDCS_Value_Characteristic_Code)14)

/*
 * Definition:
 *     Each value in the set of attribute values is rounded to a multiple of
 *     this value; tolerance.
 *
 * Applicability: Numeric
 *
 * Quantitative: False
 */
#define EVC_TOLERANCE ((EDCS_Value_Characteristic_Code)15)

/*
 * Definition:
 *     This attribute value is the maximum valid attribute value.
 *
 * Applicability: Numeric
 *
 * Quantitative: False
 */
#define EVC_MAXIMUM_VALUE ((EDCS_Value_Characteristic_Code)16)

/*
 * Definition:
 *     This attribute value is the minimum valid attribute value.
 *
 * Applicability: Numeric
 *
 * Quantitative: False
 */
#define EVC_MINIMUM_VALUE ((EDCS_Value_Characteristic_Code)17)

/*
 * Definition:
 *     This attribute value bounds the set of attribute values from above,
 *     but does not necessarily equal the EVC_MAXIMUM_VALUE; upper bound.
 *
 * Applicability: Numeric
 *
 * Quantitative: False
 */
#define EVC_UPPER_BOUND ((EDCS_Value_Characteristic_Code)18)

/*
 * Definition:
 *     This attribute value bounds the set of attribute values from below,
 *     but does not necessarily equal the EVC_MINIMUM_VALUE; lower bound.
 *
 * Applicability: Numeric
 *
 * Quantitative: False
 */
#define EVC_LOWER_BOUND ((EDCS_Value_Characteristic_Code)19)

/*
 * Definition:
 *     The attribute value was measured or estimated with a standard error
 *     given by this value.
 *
 * Applicability: Numeric
 *
 * Quantitative: False
 */
#define EVC_MEASUREMENT_ERROR ((EDCS_Value_Characteristic_Code)20)

#ifdef __cplusplus
}
#endif

#endif
