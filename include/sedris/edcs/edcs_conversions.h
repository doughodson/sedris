
#ifndef __EDCS_CONVERSIONS_H_INCLUDED__
#define __EDCS_CONVERSIONS_H_INCLUDED__

//
// PROGRAMMERS: Automatically generated from EDCS database
//
// DESCRIPTION:
//      Provides all unit and scale conversion information for EDCS.
//
//      *** IMPORTANT NOTE ***
//      This file is generated automatically from the EDCS database tables using
//      the EDCS Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
//      be made in the EDCS database and EDCS Code generator templates, and will be
//      reflected in this file when the system is rebuilt.
//

#include "edcs_types.h"

/*
 * Allow C++ compilers to use this API without problems.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ConvertQuantityLongFloatValue
 *
 *   Given a physical quantity with a given unit and scale specified in the
 *     from_value structure, convert that quantity to the unit and scale
 *     specified within the to_value structure.
 *
 * PARAMETERS:
 *
 *    from_value_in_ptr -- The value to be converted
 *
 *    to_value_in_out_ptr -- Pointer to a user space EDCS_Long_Float_Value
 *      that already has the unit and scale set to the desired conversion.  The
 *      float_value structure will be populated by this function.
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *to_value is set to the result of the
 *     specified conversion, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and *to_value_in_ptr is left
 *     unchanged, if either from_value_in_ptr or to_value_in_out_ptr were
 *      NULL.
 *
 *   EDCS_SC_INVALID_INPUT_UNIT - and *to_value_in_out_ptr is unchanged,
 *      if the unit specified in the from_value_in_ptr structure is not a
 *      valid EU code.
 *
 *   EDCS_SC_INVALID_OUTPUT_UNIT - and *to_value_in_out_ptr is unchanged,
 *      if the unit specified in the to_value_in_out_ptr structure is not
 *      a valid EU code.
 *
 *   EDCS_SC_INVALID_INPUT_UNIT_SCALE - and *to_value_in_out_ptr is unchanged,
 *      if the scale specified in the from_value_in_ptr structure is not a
 *      valid ES code.
 *
 *   EDCS_SC_INVALID_OUTPUT_UNIT_SCALE - and *to_value_in_out_ptr is unchanged,
 *      if the scale specified in the to_value_in_out_ptr structure is not a
 *      valid ES code.
 *
 *   EDCS_SC_UNITS_NOT_EQUIVALENT and *to_value_in_out_ptr is unchanged,
 *     if the units specified in the from_value_in_ptr and to_value_in_out_ptr
 *     structures do not belong to the same EQ class.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_ConvertQuantityLongFloatValue
(
    const EDCS_Long_Float_Value *from_value_in_ptr,
          EDCS_Long_Float_Value *to_value_in_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ConvertQuantityValue
 *
 *   Given a physical quantity with a given unit and scale specified in the
 *     from_value structure, convert that quantity to the unit and scale
 *     specified within the to_value structure.
 *
 * PARAMETERS:
 *
 *    from_value_in_ptr -- The value to be converted
 *
 *    to_value_in_out_ptr -- Pointer to a user space EDCS_Real_Value that
 *      already has the unit and scale set to the desired conversion.  The
 *      float_value structure will be populated by this function.
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *to_value is set to the result of the
 *     specified conversion, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and *to_value_in_ptr is left
 *     unchanged, if either from_value_in_ptr or to_value_in_out_ptr were
 *      NULL.
 *
 *   EDCS_SC_INVALID_INPUT_UNIT - and *to_value_in_out_ptr is unchanged,
 *      if the unit specified in the from_value_in_ptr structure is not a
 *      valid EU code.
 *
 *   EDCS_SC_INVALID_OUTPUT_UNIT - and *to_value_in_out_ptr is unchanged,
 *      if the unit specified in the to_value_in_out_ptr structure is not
 *      a valid EU code.
 *
 *   EDCS_SC_INVALID_INPUT_UNIT_SCALE - and *to_value_in_out_ptr is unchanged,
 *      if the scale specified in the from_value_in_ptr structure is not a
 *      valid ES code.
 *
 *   EDCS_SC_INVALID_OUTPUT_UNIT_SCALE - and *to_value_in_out_ptr is unchanged,
 *      if the scale specified in the to_value_in_out_ptr structure is not a
 *      valid ES code.
 *
 *   EDCS_SC_UNITS_NOT_EQUIVALENT and *to_value_in_out_ptr is unchanged,
 *     if the units specified in the from_value_in_ptr and to_value_in_out_ptr
 *     structures do not belong to the same EQ class.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_ConvertQuantityValue
(
    const EDCS_Real_Value *from_value_in_ptr,
          EDCS_Real_Value *to_value_in_out_ptr
);


/* Begin Unit Conversion Constant Definitions */
#define EDCS_LF_ANGSTROM_TO_METRE ((EDCS_Long_Float)1.0E-10)

#define EDCS_LF_ARE_TO_SQ_METRE ((EDCS_Long_Float)1.0E2)

#define EDCS_LF_ASTRONOMICAL_UNIT_TO_METRE ((EDCS_Long_Float)1.4959787E11)

#define EDCS_LF_BAR_TO_PASCAL ((EDCS_Long_Float)1.0E5)

#define EDCS_LF_BARN_TO_SQ_METRE ((EDCS_Long_Float)1.0E-28)

#define EDCS_LF_BEL_TO_NEPER ((EDCS_Long_Float)1.151293E0)

#define EDCS_LF_CURIE_TO_BECQUEREL ((EDCS_Long_Float)3.7E10)

#define EDCS_LF_DAY_TO_SECOND ((EDCS_Long_Float)8.64E4)

#define EDCS_LF_DB_TO_BEL ((EDCS_Long_Float)1.0E-1)

#define EDCS_LF_DB_TO_NEPER ((EDCS_Long_Float)1.151293E-1)

#define EDCS_LF_DECAY_RATE_TO_MINUTE_PER_CUBIC_METRE ((EDCS_Long_Float)1.6666667E-4)

#define EDCS_LF_DEGREE_ARC_TO_RADIAN ((EDCS_Long_Float)1.745329251994329576924E-2)

#define EDCS_LF_DEGREE_C_OFFSET_TO_KELVIN ((EDCS_Long_Float)2.7315E2)

#define EDCS_LF_DEGREE_C_PER_HOUR_TO_KELVIN_PER_SEC ((EDCS_Long_Float)2.777777777777777777778E-4)

#define EDCS_LF_DEGREE_C_PER_METRE_TO_KELVIN_PER_METRE ((EDCS_Long_Float)1.0E0)

#define EDCS_LF_DEGREE_C_PER_SEC_TO_KELVIN_PER_SEC ((EDCS_Long_Float)1.0E0)

#define EDCS_LF_ELECTRONVOLT_TO_JOULE ((EDCS_Long_Float)1.602177E-19)

#define EDCS_LF_ELECTRONVOLT_M_SQD_TO_JOULE_METRE_SQD ((EDCS_Long_Float)1.60217733E-19)

#define EDCS_LF_ELECTRONVOLT_M_SQD_PER_KG_TO_JOULE_METRE_SQD_PER_KG ((EDCS_Long_Float)1.60217733E-19)

#define EDCS_LF_FOOT_TO_METRE ((EDCS_Long_Float)3.048E-1)

#define EDCS_LF_GAL_TO_METRE_PER_SEC_SQD ((EDCS_Long_Float)1.0E-2)

#define EDCS_LF_GON_TO_RADIAN ((EDCS_Long_Float)1.570796326794896619231E-2)

#define EDCS_LF_GRAM_TO_KILOGRAM ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_GRAM_PER_CUBIC_CM_TO_KG_PER_CUBIC_METRE ((EDCS_Long_Float)1.0E3)

#define EDCS_LF_GRAM_PER_CUBIC_M_TO_KG_PER_CUBIC_METRE ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_GRAM_PER_GRAM_TO_KG_PER_KG ((EDCS_Long_Float)1.0E0)

#define EDCS_LF_GRAM_PER_KILOGRAM_TO_KG_PER_KG ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_HECTARE_TO_SQ_METRE ((EDCS_Long_Float)1.0E4)

#define EDCS_LF_HOUR_TO_SECOND ((EDCS_Long_Float)3.6E3)

#define EDCS_LF_INT_SOLAR_FLUX_UNIT_TO_JANSKY ((EDCS_Long_Float)1.0E4)

#define EDCS_LF_INT_SOLAR_FLUX_UNIT_TO_WATT_PER_SQ_M_HZ ((EDCS_Long_Float)1.0E-22)

#define EDCS_LF_INV_CUBIC_CM_TO_INV_CUBIC_METRE ((EDCS_Long_Float)1.0E-6)

#define EDCS_LF_INV_CUBIC_CM_SEC_TO_INV_CUBIC_METRE_SEC ((EDCS_Long_Float)1.0E-6)

#define EDCS_LF_INV_CUBIC_METRE_EV_TO_INV_CUBIC_METRE_JOULE ((EDCS_Long_Float)6.24150614E18)

#define EDCS_LF_INV_MICRON_TO_INV_METRE ((EDCS_Long_Float)1.0E6)

#define EDCS_LF_INV_SQ_CM_SEC_SR_EV_TO_INV_SQ_M_SEC_SR_EV ((EDCS_Long_Float)1.0E-6)

#define EDCS_LF_INV_SQ_CM_SEC_SR_KEV_TO_INV_SQ_M_SEC_SR_EV ((EDCS_Long_Float)1.0E-9)

#define EDCS_LF_INV_SQ_CM_SEC_SR_MEV_TO_INV_SQ_M_SEC_SR_EV ((EDCS_Long_Float)1.0E-12)

#define EDCS_LF_INV_SQ_CM_SEC_STERADIAN_TO_INV_SQ_M_SEC_STERADIAN ((EDCS_Long_Float)1.0E-4)

#define EDCS_LF_INV_STERADIAN_MICRON_TO_INV_STERADIAN_METRE ((EDCS_Long_Float)1.0E6)

#define EDCS_LF_JANSKY_TO_WATT_PER_SQ_M_HZ ((EDCS_Long_Float)1.0E-26)

#define EDCS_LF_JOULE_PER_GRAM_K_TO_JOULE_PER_KG_KELVIN ((EDCS_Long_Float)1.0E3)

#define EDCS_LF_JOULE_PER_KM_TO_JOULE_PER_METRE ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_KELVIN_PER_KM_TO_KELVIN_PER_METRE ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_KG_PER_LITRE_TO_KG_PER_CUBIC_METRE ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_KILOPOUND_TO_KILOGRAM ((EDCS_Long_Float)4.5359237E2)

#define EDCS_LF_KM_PER_HOUR_TO_METRE_PER_SEC ((EDCS_Long_Float)2.777777777777777777778E-1)

#define EDCS_LF_KNOT_TO_METRE_PER_SEC ((EDCS_Long_Float)5.14444E-1)

#define EDCS_LF_LIGHT_YEAR_TO_METRE ((EDCS_Long_Float)9.460730E15)

#define EDCS_LF_LITRE_TO_CUBIC_METRE ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_LITRE_PER_HOUR_TO_CUBIC_METRE_PER_SEC ((EDCS_Long_Float)2.777777777777777777778E-7)

#define EDCS_LF_LITRE_PER_SECOND_TO_CUBIC_METRE_PER_SEC ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_LONG_TON_TO_KILOGRAM ((EDCS_Long_Float)1.016047E3)

#define EDCS_LF_LUMEN_HOUR_TO_LUMEN_SECOND ((EDCS_Long_Float)3.6E3)

#define EDCS_LF_LUX_HOUR_TO_LUX_SECOND ((EDCS_Long_Float)3.6E3)

#define EDCS_LF_METRE_PER_HOUR_TO_METRE_PER_SEC ((EDCS_Long_Float)2.777777777777777777778E-4)

#define EDCS_LF_MILE_TO_METRE ((EDCS_Long_Float)1.609344E3)

#define EDCS_LF_MILE_PER_HOUR_TO_METRE_PER_SEC ((EDCS_Long_Float)4.4704E-1)

#define EDCS_LF_MINUTE_TO_SECOND ((EDCS_Long_Float)6.0E1)

#define EDCS_LF_MINUTE_ARC_TO_DEGREE_ARC ((EDCS_Long_Float)1.666666666666666666667E-2)

#define EDCS_LF_MINUTE_ARC_TO_RADIAN ((EDCS_Long_Float)2.908882086657215961539E-4)

#define EDCS_LF_MOLE_PER_LITRE_TO_MOLE_PER_CUBIC_M ((EDCS_Long_Float)1.0E3)

#define EDCS_LF_NAUTICAL_MILE_TO_METRE ((EDCS_Long_Float)1.852E3)

#define EDCS_LF_NEWTON_PER_SQ_M_TO_PASCAL ((EDCS_Long_Float)1.0E0)

#define EDCS_LF_PARSEC_TO_ASTRONOMICAL_UNIT ((EDCS_Long_Float)2.062648E5)

#define EDCS_LF_PARSEC_TO_METRE ((EDCS_Long_Float)3.085678E16)

#define EDCS_LF_PERCENT_TO_UNITLESS ((EDCS_Long_Float)1.0E-2)

#define EDCS_LF_PPB_MASS_FRACTION_TO_KG_PER_KG ((EDCS_Long_Float)1.0E-9)

#define EDCS_LF_PPM_MASS_FRACTION_TO_KG_PER_KG ((EDCS_Long_Float)1.0E-6)

#define EDCS_LF_PPT_MASS_FRACTION_TO_KG_PER_KG ((EDCS_Long_Float)1.0E-12)

#define EDCS_LF_PPTH_MASS_FRACTION_TO_KG_PER_KG ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_RAD_TO_GRAY ((EDCS_Long_Float)1.0E-2)

#define EDCS_LF_REM_TO_SIEVERT ((EDCS_Long_Float)1.0E-2)

#define EDCS_LF_ROENTGEN_TO_COULOMB_PER_KG ((EDCS_Long_Float)2.58E4)

#define EDCS_LF_SECOND_ARC_TO_DEGREE_ARC ((EDCS_Long_Float)2.777777777777777777778E-4)

#define EDCS_LF_SECOND_ARC_TO_RADIAN ((EDCS_Long_Float)4.848136811095359935899E-6)

#define EDCS_LF_TEC_TO_INV_SQ_METRE ((EDCS_Long_Float)1.0E16)

#define EDCS_LF_TON_TO_KILOGRAM ((EDCS_Long_Float)9.071847E2)

#define EDCS_LF_TONNE_TO_KILOGRAM ((EDCS_Long_Float)1.0E3)

#define EDCS_LF_TONNE_PER_CUBIC_METRE_TO_KG_PER_CUBIC_METRE ((EDCS_Long_Float)1.0E3)

#define EDCS_LF_UNIFIED_AMASS_UNIT_TO_KILOGRAM ((EDCS_Long_Float)1.660540E-27)

#define EDCS_LF_WATT_HOUR_TO_JOULE ((EDCS_Long_Float)3.6E3)

#define EDCS_LF_WATT_PER_SQ_CM_SEC_TO_WATT_PER_SQ_METRE_SEC ((EDCS_Long_Float)1.0E-4)

#define EDCS_LF_WATT_SECOND_TO_JOULE ((EDCS_Long_Float)1.0E0)

#define EDCS_LF_YEAR_TO_DAY ((EDCS_Long_Float)3.6524220E2)

#define EDCS_LF_YEAR_TO_SECOND ((EDCS_Long_Float)3.1556926E7)

/* Begin PI Definition */

#define EDCS_LF_PI ((EDCS_Long_Float)3.141592653589793238463E0)


/* Begin Scale Conversion Constant Definitions */

#define EDCS_LF_ATTO_TO_ONE ((EDCS_Long_Float)1.0E-18)

#define EDCS_LF_CENTI_TO_ONE ((EDCS_Long_Float)1.0E-2)

#define EDCS_LF_DECA_TO_ONE ((EDCS_Long_Float)1.0E1)

#define EDCS_LF_DECI_TO_ONE ((EDCS_Long_Float)1.0E-1)

#define EDCS_LF_EXA_TO_ONE ((EDCS_Long_Float)1.0E18)

#define EDCS_LF_EXBI_TO_ONE ((EDCS_Long_Float)1152921504606846976.0E0)

#define EDCS_LF_FEMTO_TO_ONE ((EDCS_Long_Float)1.0E-15)

#define EDCS_LF_GIBI_TO_ONE ((EDCS_Long_Float)1073741824.0E0)

#define EDCS_LF_GIGA_TO_ONE ((EDCS_Long_Float)1.0E9)

#define EDCS_LF_HECTO_TO_ONE ((EDCS_Long_Float)1.0E2)

#define EDCS_LF_KIBI_TO_ONE ((EDCS_Long_Float)1024.0E0)

#define EDCS_LF_KILO_TO_ONE ((EDCS_Long_Float)1.0E3)

#define EDCS_LF_MEBI_TO_ONE ((EDCS_Long_Float)1048576.0E0)

#define EDCS_LF_MEGA_TO_ONE ((EDCS_Long_Float)1.0E6)

#define EDCS_LF_MICRO_TO_ONE ((EDCS_Long_Float)1.0E-6)

#define EDCS_LF_MILLI_TO_ONE ((EDCS_Long_Float)1.0E-3)

#define EDCS_LF_NANO_TO_ONE ((EDCS_Long_Float)1.0E-9)

#define EDCS_LF_ONE_TO_ONE ((EDCS_Long_Float)1.0E0)

#define EDCS_LF_PEBI_TO_ONE ((EDCS_Long_Float)1125899906842624.0E0)

#define EDCS_LF_PETA_TO_ONE ((EDCS_Long_Float)1.0E15)

#define EDCS_LF_PICO_TO_ONE ((EDCS_Long_Float)1.0E-12)

#define EDCS_LF_TEBI_TO_ONE ((EDCS_Long_Float)1099511627776.0E0)

#define EDCS_LF_TERA_TO_ONE ((EDCS_Long_Float)1.0E12)

#define EDCS_LF_YOCTO_TO_ONE ((EDCS_Long_Float)1.0E-24)

#define EDCS_LF_YOTTA_TO_ONE ((EDCS_Long_Float)1.0E24)

#define EDCS_LF_ZEPTO_TO_ONE ((EDCS_Long_Float)1.0E-21)

#define EDCS_LF_ZETTA_TO_ONE ((EDCS_Long_Float)1.0E21)

#ifdef __cplusplus
}
#endif

#endif
