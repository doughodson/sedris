
#ifndef __EDCS_ORG_SCHEMA_DICT_H_INCLUDED__
#define __EDCS_ORG_SCHEMA_DICT_H_INCLUDED__

//
// PROGRAMMERS: Automatically generated from EDCS database
//
// DESCRIPTION:
//      Provides dictionary information for all EOs.
//
//      *** IMPORTANT NOTE ***
//      This file is generated automatically from the EDCS database tables using
//      the EDCS Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
//      be made in the EDCS database and EDCS Code generator templates, and will be
//      reflected in this file when the system is rebuilt.
//

#include "edcs_types.h"

#define EDCS_TOTAL_EO 1

/*
 * Allow C++ compilers to use this API without problems.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetEODictionaryEntry
 *
 *   Retrieves dictionary information for the given EO.
 *
 * PARAMETERS:
 *
 *   eo_code_in -- handle to the EO code for which information is requested
 *
 *   result_out_ptr -- pointer to a variable in the user's memory into which
 *        a handle to the requested dictionary entry will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *result_out_ptr is set to the appropriate
 *       value, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REOUIRED_PARAMETER - and no changes are made, if any
 *       parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_CODE - and no changes are made, if eo_code_in
 *       does not correspond to a valid EO.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_GetEODictionaryEntry
(
          EDCS_Organization_Schema_Code               eo_code_in,
    const EDCS_Organization_Schema_Dictionary_Entry **result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_LabelToEOCode
 *
 *   Retrieves the EO code corresponding to the given label.
 *
 * PARAMETERS:
 *
 *   eo_label_in_ptr -- the label for which the corresponding EO code is
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
 *   EDCS_SC_NULL_REOUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_LABEL - and no changes are made, if *eo_label_in_ptr
 *     does not correspond to a valid EO.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_LabelToEOCode
(
    const EDCS_Character                *eo_label_in_ptr,
          EDCS_Organization_Schema_Code *result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SymbolicConstantToEOCode
 *
 *   Retrieves the EO code corresponding to the given symbolic constant name.
 *
 * PARAMETERS:
 *
 *   eo_symbolic_constant_in_ptr -- the symbolic constant for which the
 *       corresponding EO code is requested; note that this is the
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
 *   EDCS_SC_NULL_REOUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT - and no changes are made, if
 *     *eo_symbolic_constant_in_ptr does not correspond to a valid EO.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_SymbolicConstantToEOCode
(
    const EDCS_Character         *eo_symbolic_constant_in_ptr,
          EDCS_Organization_Schema_Code *result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidOrganizationSchemaCode
 *
 *   Indicates if the given EO code is a valid EDCS Organization Schema Code.
 *
 * PARAMETERS:
 *
 *   eo_code_in -- The EO code whose validity is being checked.
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if a valid EO code was passed in.
 *
 *   EDCS_FALSE - if a non-valid EO code was passed in.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidOrganizationSchemaCode
(
    EDCS_Organization_Schema_Code eo_code_in
);


/*
 * Definition:
 *     A schema based on natural and/or scientific principles.
 *
 * Group Membership:
 *    EGC_GEN_ABSTRACT_OBJECT
 *    EGC_GEN_ACOUSTIC_PHENOMENON
 *    EGC_GEN_ADMINISTRATION
 *    EGC_GEN_AGRICULTURE
 *    EGC_GEN_AIR_TRNSP
 *    EGC_GEN_AIRBORNE_PARTICLE
 *    EGC_GEN_ALGORITHM_RELATED
 *    EGC_GEN_ANGULAR_MEASURE
 *    EGC_GEN_ANIMAL
 *    EGC_GEN_ATMOSPHERE
 *    EGC_GEN_BUILDING_COMPONENT
 *    EGC_GEN_COLOUR
 *    EGC_GEN_COMMUNICATION
 *    EGC_GEN_DEMARCATION
 *    EGC_GEN_DEVICE_AND_EQUIPMENT
 *    EGC_GEN_DIMENSION
 *    EGC_GEN_EM_PHENOMENON
 *    EGC_GEN_FLUID_CONDITION
 *    EGC_GEN_HARBOUR_AND_PORT
 *    EGC_GEN_HYDROGRAPHIC_ARTEFACT
 *    EGC_GEN_HYDROGRAPHIC_INDUSTRY
 *    EGC_GEN_HYDROGRAPHIC_TRNSP
 *    EGC_GEN_HYDROLOGY
 *    EGC_GEN_ICE
 *    EGC_GEN_IDENTIFICATION
 *    EGC_GEN_INDUSTRY
 *    EGC_GEN_INFRASTRUCTURE
 *    EGC_GEN_LAND_INDUSTRY
 *    EGC_GEN_LAND_TRNSP
 *    EGC_GEN_LIGHTING_AND_VISIBILITY
 *    EGC_GEN_LITTORAL
 *    EGC_GEN_LIVING_ORGANISM
 *    EGC_GEN_LOCATION
 *    EGC_GEN_MATERIAL
 *    EGC_GEN_MILITARY_SCIENCE
 *    EGC_GEN_PHYSIOGRAPHY
 *    EGC_GEN_PLANT
 *    EGC_GEN_PROPERTY_SET
 *    EGC_GEN_RATE_OR_RATIO
 *    EGC_GEN_RECREATION
 *    EGC_GEN_RELIGION
 *    EGC_GEN_SHELTER
 *    EGC_GEN_SPACE
 *    EGC_GEN_SUPPORT_STRUCTURE
 *    EGC_GEN_SURFACE
 *    EGC_GEN_SURFACE_MATERIAL
 *    EGC_GEN_SURVEY
 *    EGC_GEN_TEMPERATURE
 *    EGC_GEN_TIME
 *    EGC_GEN_TRNSP
 *    EGC_GEN_USAGE_REGION
 *    EGC_GEN_VEHICLE
 *    EGC_GEN_WATERBODY_FLOOR
 *    EGC_GEN_WATERBODY_STATE
 *    EGC_GEN_WATERBODY_SURFACE
 */
#define EOC_GENERAL ((EDCS_Organization_Schema_Code)1)

#ifdef __cplusplus
}
#endif

#endif
