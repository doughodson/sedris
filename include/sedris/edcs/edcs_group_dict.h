
#ifndef __EDCS_GROUP_DICT_H_INCLUDED__
#define __EDCS_GROUP_DICT_H_INCLUDED__

//
// PROGRAMMERS: Automatically generated from EDCS database
//
// DESCRIPTION:
//      Provides dictionary information for all EGs.
//
//      *** IMPORTANT NOTE ***
//      This file is generated automatically from the EDCS database tables using
//      the EDCS Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
//      be made in the EDCS database and EDCS Code generator templates, and will be
//      reflected in this file when the system is rebuilt.
//

#include "edcs_types.h"

#define EDCS_TOTAL_EG 55

/*
 * Allow C++ compilers to use this API without problems.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_GetEGDictionaryEntry
 *
 *   Retrieves dictionary information for the given EG.
 *
 * PARAMETERS:
 *
 *   eo_code_in -- The EO code for the EG for which information is requested
 *
 *   eg_code_in -- The EG code for which information is requested
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
 *   EDCS_SC_INVALID_INPUT_CODE - and no changes are made, if eo_code_in
 *     does not correspond to a valid EO, or if eg_code_in does not
 *     correspond to a valid EG for that EO.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_GetEGDictionaryEntry
(
          EDCS_Organization_Schema_Code eo_code_in,
          EDCS_Group_Code               eg_code_in,
    const EDCS_Group_Dictionary_Entry **result_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_LabelToEGCode
 *
 *   Retrieves the {EO, EG} code pair corresponding to the given pair of EO and
 *   EG labels, where the EG is scoped by the given EO.
 *
 * PARAMETERS:
 *
 *   eo_label_in_ptr -- the label for the EO code that provides a scope for
 *       the EG label specified in eg_label_in_ptr; note that this is the
 *       abstract label (i.e., corresponds to the abstract EDCS specification)
 *
 *   eg_label_in_ptr -- the label for which the corresponding EG code is
 *       requested; note that this is the abstract label (i.e., corresponds
 *       to the abstract EDCS specification).  The EO scope this EG falls
 *       in is determined by the eo_label_in_ptr parameter.
 *
 *   eo_out_ptr -- pointer to a variable in the user's memory into which
 *       the output EOC will be copied
 *
 *   eg_out_ptr -- pointer to a variable in the user's memory into which
 *       the output EGC will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *eo_out_ptr, *eg_out_ptr are set to the
 *     appropriate values, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_LABEL - and no changes are made, if *eo_label_in_ptr
 *     does not correspond to a valid EO, or *eq_label_in_ptr does not correspond
 *     to a valid EG for the EO given in *eo_label_in_ptr.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_LabelToEGCode
(
    const EDCS_Character                *eo_label_in_ptr,
    const EDCS_Character                *eg_label_in_ptr,
          EDCS_Organization_Schema_Code *eo_out_ptr,
          EDCS_Group_Code               *eg_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_SymbolicConstantToEGCode
 *
 *   Retrieves the {EO, EG} code pair corresponding to the given symbolic constant name.
 *
 * PARAMETERS:
 *
 *   eg_symbolic_constant_in_ptr -- the symbolic constant for which the
 *       corresponding EG code is requested; note that this is the
 *       language-binding symbolic constant, rather than the abstract
 *       label (i.e., corresponds to the C language binding standard rather
 *       than the abstract EDCS specification)
 *
 *   eo_out_ptr -- pointer to a variable in the user's memory into which
 *       the output EOC will be copied
 *
 *   eg_out_ptr -- pointer to a variable in the user's memory into which
 *       the output EGC will be copied
 *
 * RETURNS:
 *
 *   EDCS_SC_SUCCESS - and *eo_out_ptr, *eg_out_ptr are set to the
 *     appropriate values, if valid parameters were passed in.
 *
 *   EDCS_SC_NULL_REQUIRED_PARAMETER - and no changes are made, if
 *     any parameter is NULL.
 *
 *   EDCS_SC_INVALID_INPUT_SYMBOLIC_CONSTANT - and no changes are made, if *eq_symbolic_constant_in_ptr
 *     does not correspond to a valid EG for some EO.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Status_Code
EDCS_SymbolicConstantToEGCode
(
    const EDCS_Character                *eg_symbolic_constant_in_ptr,
          EDCS_Organization_Schema_Code *eo_out_ptr,
          EDCS_Group_Code               *eg_out_ptr
);


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: EDCS_ValidGroupCode
 *
 *   Indicates if the given EG code is a valid EDCS Group Code.
 *
 * PARAMETERS:
 *
 *   eo_code_in -- The enumerated EO code to which the EG being checked is
 *       a member of.
 *
 *   eg_code_in -- The EG code whose validity is being checked.
 *
 * RETURNS:
 *
 *   EDCS_TRUE - if a valid EG code for the given EO was passed in.
 *
 *   EDCS_FALSE - if the EO code passed in is not an valid EO code
 *       or a non-valid EG code for the given EO was passed in.
 *
 *-----------------------------------------------------------------------------
 */
extern EDCS_Boolean
EDCS_ValidGroupCode
(
    EDCS_Organization_Schema_Code eo_code_in,
    EDCS_Group_Code eg_code_in
);

/*
 * Definition:
 *     ECs that either are or are related to abstract <OBJECT>s; EAs that
 *     specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ABSTRACT_OBJECT ((EOC_General)1)

/*
 * Definition:
 *     ECs that either are or are related to acoustic phenomena; EAs that
 *     specify the state of such concepts. For the purposes of this concept
 *     definition, an acoustic phenomenon is a phenomenon related to the
 *     production, propagation, reception, and processing of sound signals,
 *     signal characteristics and interfering noise, reverberation, and
 *     scattering.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ACOUSTIC_PHENOMENON ((EOC_General)2)

/*
 * Definition:
 *     ECs that either are or are related to administration; EAs that specify
 *     the state of such concepts. EXAMPLES Management, legal, government,
 *     financial activities.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ADMINISTRATION ((EOC_General)3)

/*
 * Definition:
 *     ECs that either are or are related to agriculture; EAs that specify
 *     the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_AGRICULTURE ((EOC_General)4)

/*
 * Definition:
 *     ECs that are members of the TRNSP and involve <AIRCRAFT>; EAs that
 *     specify the state of such ECs.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_AIR_TRNSP ((EOC_General)5)

/*
 * Definition:
 *     ECs that are or are related to airborne particles; EAs that specify
 *     the state of such concepts. For the purposes of this concept
 *     definition, airborne particles are unconsolidated fine <PARTICLE>s of
 *     solid and/or liquid <MATERIAL> that are suspended in <AIR>.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_AIRBORNE_PARTICLE ((EOC_General)6)

/*
 * Definition:
 *     ECs that are used by algorithms and/or are related to algorithms; EAs
 *     that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ALGORITHM_RELATED ((EOC_General)7)

/*
 * Definition:
 *     EAs that are measurements of either plane or solid angles.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ANGULAR_MEASURE ((EOC_General)8)

/*
 * Definition:
 *     ECs that either are or are related to <ANIMAL>s; EAs that specify the
 *     state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ANIMAL ((EOC_General)9)

/*
 * Definition:
 *     ECs that either are or are related to an <ATMOSPHERE> and/or a natural
 *     phenomenon that occurs in an <ATMOSPHERE>; EAs that specify the state
 *     of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ATMOSPHERE ((EOC_General)10)

/*
 * Definition:
 *     ECs that either are or are related to <BUILDING_COMPONENT>s; EAs that
 *     specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_BUILDING_COMPONENT ((EOC_General)11)

/*
 * Definition:
 *     ECs that are <OBJECT>s specified by their colour; EAs that specify
 *     and/or measure the colour or <<COLOURATION>> of <OBJECT>s.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_COLOUR ((EOC_General)12)

/*
 * Definition:
 *     ECs that either are or are related to communication; EAs that specify
 *     the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_COMMUNICATION ((EOC_General)13)

/*
 * Definition:
 *     ECs that either are or are related to demarcation; EAs that specify
 *     the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_DEMARCATION ((EOC_General)14)

/*
 * Definition:
 *     ECs that either are or are related to <DEVICE>s and/or <EQUIPMENT>;
 *     EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_DEVICE_AND_EQUIPMENT ((EOC_General)15)

/*
 * Definition:
 *     EAs that are measurements of size, capacity, and/or dimension.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_DIMENSION ((EOC_General)16)

/*
 * Definition:
 *     ECs that either are or are related to electric fields and/or
 *     <MAGNETIC_FIELD>s; EAs that specify the state of such concepts;
 *     electromagnetic phenomenon.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_EM_PHENOMENON ((EOC_General)17)

/*
 * Definition:
 *     ECs that either are or are related to fluids; EAs that specify the
 *     state of such concepts; fluid condition.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_FLUID_CONDITION ((EOC_General)18)

/*
 * Definition:
 *     ECs that either are or are related to <HARBOUR>s or <MARINE_PORT>s;
 *     EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_HARBOUR_AND_PORT ((EOC_General)19)

/*
 * Definition:
 *     ECs that either are or are related to artefacts involving a
 *     <WATERBODY>; EAs that specify the state of such concepts;
 *     hydrographic artefact.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_HYDROGRAPHIC_ARTEFACT ((EOC_General)20)

/*
 * Definition:
 *     ECs that are members of INDUSTRY and that involve a <WATERBODY>; EAs
 *     that specify the state of such ECs; hydrographic artefact.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_HYDROGRAPHIC_INDUSTRY ((EOC_General)21)

/*
 * Definition:
 *     ECs that are members of TRNSP and involve a <WATERBODY>; EAs that
 *     specify the state of such ECs; hydrographic transportation.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_HYDROGRAPHIC_TRNSP ((EOC_General)22)

/*
 * Definition:
 *     ECs that relate to hydrology; EAs that specify the state of such
 *     concepts. For the purposes of this concept definition, hydrology is
 *     the branch of science that deals with <WATERBODY>s found on and/or
 *     below a <PLANETARY_SURFACE> and in inland <REGION>s.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_HYDROLOGY ((EOC_General)23)

/*
 * Definition:
 *     ECs that are <OBJECT>s composed at least in part of <ICE>; EAs that
 *     specify the state of such <OBJECT>s.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_ICE ((EOC_General)24)

/*
 * Definition:
 *     EAs that uniquely identify <OBJECT>s.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_IDENTIFICATION ((EOC_General)25)

/*
 * Definition:
 *     ECs that either are or are related to industrial <OBJECT>s and/or
 *     industries; EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_INDUSTRY ((EOC_General)26)

/*
 * Definition:
 *     ECs that either are or are related to infrastructure <OBJECT>s; EAs
 *     that specify the state of such concepts. For the purposes of this
 *     concept definition, an infrastructure <OBJECT> is a basic supporting
 *     utility, <EQUIPMENT>, and/or <FACILITY>.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_INFRASTRUCTURE ((EOC_General)27)

/*
 * Definition:
 *     ECs that belong to INDUSTRY and involve a <REGION> of <LAND>; EAs that
 *     specify the state of such ECs.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_LAND_INDUSTRY ((EOC_General)28)

/*
 * Definition:
 *     ECs that belong to TRNSP and involve <LAND>; EAs that specify the
 *     state of such ECs.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_LAND_TRNSP ((EOC_General)29)

/*
 * Definition:
 *     ECs that are related to lighting and/or visibility; EAs that specify
 *     the state of lighting and/or visibility.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_LIGHTING_AND_VISIBILITY ((EOC_General)30)

/*
 * Definition:
 *     ECs that either are or are related to littoral <REGION>s; EAs that
 *     specify the state of such concepts. For the purposes of this concept
 *     definition, a littoral <REGION> is a <SHORE> where a normal cycle of
 *     exposure and submersion by <WATER> occurs.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_LITTORAL ((EOC_General)31)

/*
 * Definition:
 *     ECs that either are or are related to <LIVING_ORGANISM>s; EAs that
 *     specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_LIVING_ORGANISM ((EOC_General)32)

/*
 * Definition:
 *     ECs that either are or are related to the specification of
 *     <LOCATION>s; EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_LOCATION ((EOC_General)33)

/*
 * Definition:
 *     ECs that either are or are related to <MATERIAL>s; EAs that specify
 *     the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_MATERIAL ((EOC_General)34)

/*
 * Definition:
 *     ECs that either are or are related to military science; EAs that
 *     specify the state of such concepts. For the purposes of this concept
 *     definition, military science is the organization, operation,
 *     construction, installation, <EQUIPMENT>, and/or <MATERIAL> of a
 *     national armed force.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_MILITARY_SCIENCE ((EOC_General)35)

/*
 * Definition:
 *     ECs that either are or are related to physiographic <OBJECT>s; EAs
 *     that specify the state of such concepts. For the purposes of this
 *     concept definition, physiography is physical geography (the natural
 *     features and inanimate phenomena of a <PLANETARY_SURFACE>).
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_PHYSIOGRAPHY ((EOC_General)36)

/*
 * Definition:
 *     ECs that either are or are related to <PLANT>s; EAs that specify the
 *     state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_PLANT ((EOC_General)37)

/*
 * Definition:
 *     ECs that are <PROPERTY_SET>s; EAs that either describe or are members
 *     of <PROPERTY_SET>s.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_PROPERTY_SET ((EOC_General)38)

/*
 * Definition:
 *     EAs that are measurements expressed as a rate and/or ratio.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_RATE_OR_RATIO ((EOC_General)39)

/*
 * Definition:
 *     ECs that either are or are related to recreational <OBJECT>s; EAs that
 *     specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_RECREATION ((EOC_General)40)

/*
 * Definition:
 *     ECs that are <OBJECT>s related to a religion and/or system of belief;
 *     EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_RELIGION ((EOC_General)41)

/*
 * Definition:
 *     ECs that either are or are related to <SHELTER>s; EAs that specify the
 *     state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_SHELTER ((EOC_General)42)

/*
 * Definition:
 *     ECs that either are or are related to <SPACE>; EAs that specify the
 *     state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_SPACE ((EOC_General)43)

/*
 * Definition:
 *     ECs that either are or are related to <STRUCTURE>s other than
 *     <BUILDING>s; EAs that specify the state of such concepts; support
 *     structure.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_SUPPORT_STRUCTURE ((EOC_General)44)

/*
 * Definition:
 *     ECs that either are or are related to <SURFACE>s; EAs that specify the
 *     state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_SURFACE ((EOC_General)45)

/*
 * Definition:
 *     ECs that either are or are related to <MATERIAL>s at and/or on a
 *     <SURFACE>; EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_SURFACE_MATERIAL ((EOC_General)46)

/*
 * Definition:
 *     ECs that either are or are related to <LOCATION>s determined through
 *     the use of surveying techniques; EAs that specify the state of such
 *     concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_SURVEY ((EOC_General)47)

/*
 * Definition:
 *     ECs that either are or are related to <<TEMPERATURE>>; EAs that
 *     specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_TEMPERATURE ((EOC_General)48)

/*
 * Definition:
 *     ECs that are related to time; EAs that specify the state of such
 *     concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_TIME ((EOC_General)49)

/*
 * Definition:
 *     ECs that either are or are related to transportation or travel; EAs
 *     that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_TRNSP ((EOC_General)50)

/*
 * Definition:
 *     ECs that either or are related to <REGION>s and/or <OBJECT>s based on
 *     how they are used; EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_USAGE_REGION ((EOC_General)51)

/*
 * Definition:
 *     ECs that either are or are related to <VEHICLE>s; EAs that specify the
 *     state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_VEHICLE ((EOC_General)52)

/*
 * Definition:
 *     ECs that either are or are related to the characteristics of
 *     <WATERBODY_FLOOR>s; EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_WATERBODY_FLOOR ((EOC_General)53)

/*
 * Definition:
 *     ECs that either are or are related to particular modes, states, and/or
 *     circumstances of a <WATERBODY>; EAs that specify the state of such
 *     concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_WATERBODY_STATE ((EOC_General)54)

/*
 * Definition:
 *     ECs that either are or are related to characteristics of
 *     <WATERBODY_SURFACE>s; EAs that specify the state of such concepts.
 *
 * Group for Organization_Schema: GENERAL
 */
#define EGC_GEN_WATERBODY_SURFACE ((EOC_General)55)


#ifdef __cplusplus
}
#endif

#endif
