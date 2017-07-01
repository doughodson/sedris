
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

#include "edcs_internal.h"

/*
 * This function may bear further improvements. If case sensitivity were
 * desired, strcmp() would be adequate. If case insensitivity is
 * desired, this function is being used in place of strcasecmp() to
 * avoid portability issues.
 */
int edcs_strcmp( register const char * s1, register const char * s2 )
{
	while (toupper(*s1) == toupper(*s2++))
	{
		if (!*s1++) return 0;	
	}
	
	if (s2[-1] == '\0')
		return 1;
	else if (s1[0] == '\0')
		return -1;
	else if (s1[0] == '_') 
		return -1;
	else if (s2[-1] == '_')
		return 1;

	return toupper(s1[0]) - toupper(s2[-1]);
}
