
#ifndef _DRM_STDS_H_INCLUDED
#define _DRM_STDS_H_INCLUDED

//
// DESCRIPTION:
//
//   CHANGE THIS FILE, IF NEEDED, TO MATCH YOUR MACHINE!
//
//   This file:
//
//     - defines whether your machine is Big or Little Endian
//       (THIS MAY NEED TO BE CHANGED TO MATCH YOUR MACHINE)
//
//     - defines the 'base' SEDRIS types:
//       (THESE MAY NEED TO BE CHANGED TO MATCH YOUR MACHINE)
//              signed 8, 16, and 32 bit integers,
//            unsigned 8, 16, and 32 bit integers,
//                                32 and 64 bit floating point numbers
//
//     - defines a boolean type (SE_Boolean), along with true and false
//       values (SE_TRUE and SE_FALSE)
//
//     - defines constants that signify Positive and Negative Infinity within
//       SEDRIS (the constants used are the appropriate IEEE values)
//
//     - defines constants that signify min and max values for the 'base'
//       SEDRIS numeric types
//
//     - provides a convenient SE_EQUAL(a,b,epsilon) macro to test whether
//       two floating point numbers are within epsilon of each other
//       (to avoid the classic problem of using == to compare equality
//        among floating point numbers)
//
//   YOU WILL NEED TO CHANGE THIS FILE:
//     - IF YOUR MACHINE IS NOT BIG ENDIAN
//     - IF YOUR MACHINE USES INTs OR FLOATs WITH DIFFERENT SIZES
//       THAN THOSE USED IN THE PROVIDED DEFINITIONS
//
//   By 'default', this header file is designed for a Big Endian machine
//   with a 32 bit integer.  The 'default' type definitions are:
//
//      SEDRIS Base Type     | machine specific type
//  =========================+=======================
//     signed  8 bit integer | signed char
//     signed 16 bit integer | short
//     signed 32 bit integer | int
//   unsigned  8 bit integer | unsigned char
//   unsigned 16 bit integer | unsigned short
//   unsigned 32 bit integer | unsigned int
//   positive  8 bit integer | unsigned char
//   positive 16 bit integer | unsigned short
//   positive 32 bit integer | unsigned int
//            32 bit float   | float
//            64 bit float   | double
//
//
//   IF THESE "machine specific" TYPES ARE NOT CORRECT FOR YOUR MACHINE,
//   THEN CHANGE THE DEFINITIONS TO THE APPROPRIATE MACHINE SPECIFIC TYPES
//   USED IN THE "typedef" STATEMENTS TO BE CORRECT FOR YOUR MACHINE.
//
//   For example, if on your machine an int is 16 bits, and a long int is 32
//   bits, then you would probably change the integer declarations to read
//   as follows:
//
//      typedef signed char    SE_Byte;
//      typedef int            SE_Short_Integer;
//      typedef long int       SE_Integer;
//
//      typedef unsigned char  SE_Byte_Unsigned;
//      typedef unsigned int   SE_Short_Integer_Unsigned;
//      typedef unsigned long  SE_Integer_Unsigned;
//
//      typedef unsigned char  SE_Byte_Positive;
//      typedef unsigned int   SE_Short_Integer_Positive;
//      typedef unsigned long  SE_Integer_Positive;
//
//   IF YOUR MACHINE IS NOT DEFINED AS A LITTLE ENDIAN MACHINE, THEN ADD THE
//   APPROPRIATE #defined() TO THE LINE THAT READS
//   "#if defined(CPUARCH_i386)..."
//
//   This file is the only SEDRIS file that should need to be changed due
//   to machine (platform/OS) differences.
//

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CPUARCH_i386) || defined(CPUARCH_i486)  || defined(CPUARCH_i586)  || defined(CPUARCH_i686) || defined(CPUARCH_alpha) || defined (_WIN32)
#define SE_LITTLE_ENDIAN
#else
#define SE_BIG_ENDIAN
#endif

typedef signed char    SE_Byte;
typedef short          SE_Short_Integer;
typedef int            SE_Integer;

typedef unsigned char  SE_Byte_Unsigned;
typedef unsigned short SE_Short_Integer_Unsigned;
typedef unsigned int   SE_Integer_Unsigned;

typedef unsigned char  SE_Byte_Positive;
typedef unsigned short SE_Short_Integer_Positive;
typedef unsigned int   SE_Integer_Positive;

typedef float          SE_Float;
typedef double         SE_Long_Float;

/*
 * ENUM: SE_Boolean
 *
 *   Boolean.
 */
typedef enum
{
    SE_FALSE = 0,
    SE_TRUE  = 1
} SE_Boolean;

/*
 * Used to define the max/min values.
 */
#define SE_BYTE_MAX 127
#define SE_BYTE_MIN (-128)

#define SE_SHORT_INTEGER_MAX 32767
#define SE_SHORT_INTEGER_MIN (-32768)

#define SE_INTEGER_MAX 2147483647
#define SE_INTEGER_MIN (-2147483647-1)

#define SE_BYTE_UNSIGNED_MAX 255
#define SE_BYTE_UNSIGNED_MIN 0

#define SE_SHORT_INTEGER_UNSIGNED_MAX 65535
#define SE_SHORT_INTEGER_UNSIGNED_MIN 0

#define SE_INTEGER_UNSIGNED_MAX 4294967295U
#define SE_INTEGER_UNSIGNED_MIN 0

#define SE_BYTE_POSITIVE_MAX 255
#define SE_BYTE_POSITIVE_MIN 1

#define SE_SHORT_INTEGER_POSITIVE_MAX 65535
#define SE_SHORT_INTEGER_POSITIVE_MIN 1

#define SE_INTEGER_POSITIVE_MAX 4294967295U
#define SE_INTEGER_POSITIVE_MIN 1


/*
 * Used to define infinity values.
 */
extern const unsigned int
__se_32_pos_infinity[1];

extern const unsigned int
__se_32_neg_infinity[1];

extern const unsigned int
__se_64_pos_infinity[2];

extern const unsigned int
__se_64_neg_infinity[2];



/*
 * CONSTANTS: SE_POSITIVE_INFINITY_32, SE_NEGATIVE_INFINITY_32
 *            SE_POSITIVE_INFINITY,    SE_NEGATIVE_INFINITY
 *
 *   Infinity values.
 */
#define SE_POSITIVE_INFINITY_32 (*(SE_Float *)__se_32_pos_infinity)
#define SE_NEGATIVE_INFINITY_32 (*(SE_Float *)__se_32_neg_infinity)
#define SE_POSITIVE_INFINITY    (*(SE_Long_Float *)__se_64_pos_infinity)
#define SE_NEGATIVE_INFINITY    (*(SE_Long_Float *)__se_64_neg_infinity)

#define SE_EQUAL(a,b,delta) ( ((a) == (b)) || \
     ((a)-(delta) < (b) && (a)+(delta) > (b)) )


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_GetDRMImplVerInfo
 *
 *   This function returns the implementation version of the DRM component.
 *
 * PARAMETERS:
 *
 *   none
 *
 * RETURNS:
 *
 *   the appropriate string
 *
 *-----------------------------------------------------------------------------
 */
extern const char *
SE_GetDRMImplVerInfo(void);

#ifdef __cplusplus
}
#endif

#endif
