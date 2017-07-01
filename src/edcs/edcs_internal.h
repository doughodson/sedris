
#ifndef __EDCS_INTERNAL_H_INCLUDED__
#define __EDCS_INTERNAL_H_INCLUDED__

//
// PROGRAMMERS: Automatically generated from EDCS database
//
// DESCRIPTION:
//      This file is an internal header file and should not be included
//      by external applications nor copied out to the top level include
//      directory.
//
//      *** IMPORTANT NOTE ***
//      This file is generated automatically from the EDCS database tables using
//      the EDCS Code Generator.  DO NOT MODIFY THIS FILE BY HAND.  Changes should
//      be made in the EDCS database and EDCS Code generator templates, and will be
//      reflected in this file when the system is rebuilt.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "edcs_types.h"

/*
 * STRUCT: EDCS_Enumerant_Label_Entry
 *
 *   Used to populate EE Label lookup tables.
 */
typedef struct
{
          EDCS_Attribute_Code  ea_code;
          EDCS_Enumerant_Code  ee_code;
    const EDCS_Character      *ee_symbolic_constant;
} EDCS_Enumerant_Label_Entry;

/*
 * This function solves the problem that the '_' character
 * is first in one sort order but last in the other.
 *
 * Since as far as I can tell we can't modify the sort
 * order of MS Access SQL results, I'm using a modified
 * strcmp for EDCS search operations that matches the MS
 * Access sort order.
 *
 * Additionally, MS Access sort order is independent of
 * case, so we have to capture that here as well.
 */
int edcs_strcmp( const char * s1, const char * s2 );


#endif
