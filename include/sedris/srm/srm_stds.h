
#ifndef __SRM_STDS_H_INCLUDED__
#define __SRM_STDS_H_INCLUDED__

/** @file   srm_stds.h
    @author Bill Horan (SAIC)
    @brief  Defines the 'base' SRM types.

    CHANGE THIS FILE, IF NEEDED, TO MATCH YOUR MACHINE!

    This file:

      - defines whether your machine is Big or Little Endian
        (THIS MAY NEED TO BE CHANGED TO MATCH YOUR MACHINE)

      - defines the 'base' SRM types:
        (THESE MAY NEED TO BE CHANGED TO MATCH YOUR MACHINE)
               signed 8, 16, and 32 bit integers,
             unsigned 8, 16, and 32 bit integers,
                                 32 and 64 bit floating point numbers

      - defines a boolean type (SRM_Boolean), along with true and false
        values (SRM_TRUE and SRM_FALSE)

      - defines constants that signify Positive and Negative Infinity within
        SRM (the constants used are the appropriate IEEE values)

      - defines constants that signify min and max values for the 'base'
        SRM numeric types

    YOU WILL NEED TO CHANGE THIS FILE:
      - IF YOUR MACHINE IS NOT BIG ENDIAN
      - IF YOUR MACHINE USES INTs OR FLOATs WITH DIFFERENT SIZES
        THAN THOSE USED IN THE PROVIDED DEFINITIONS

    By 'default', this header file is designed for a Big Endian machine
    with a 32 bit integer.  The 'default' type definitions are:

    (SRM Base Type  -- machine specific type)

      - signed  8 bit integer   -- signed char
      - signed 16 bit integer   -- short
      - signed 32 bit integer   -- int
      - unsigned  8 bit integer -- unsigned char
      - unsigned 16 bit integer -- unsigned short
      - unsigned 32 bit integer -- unsigned int
      - positive  8 bit integer -- unsigned char
      - positive 16 bit integer -- unsigned short
      - positive 32 bit integer -- unsigned int
      - 32 bit float            -- float
      - 64 bit float            -- double


    IF THESE "machine specific" TYPES ARE NOT CORRECT FOR YOUR MACHINE,
    THEN CHANGE THE DEFINITIONS TO THE APPROPRIATE MACHINE SPECIFIC TYPES
    USED IN THE "typedef" STATEMENTS TO BE CORRECT FOR YOUR MACHINE.

    For example, if on your machine an int is 16 bits, and a long int is 32
    bits, then you would probably change the integer declarations to read
    as follows:

       - typedef long int       SRM_Integer;

       - typedef unsigned long  SRM_Integer_Unsigned;

       - typedef unsigned long  SRM_Integer_Positive;

    IF YOUR MACHINE IS NOT DEFINED AS A LITTLE ENDIAN MACHINE, THEN ADD THE
    APPROPRIATE #defined() TO THE LINE THAT READS

       - "#if defined(CPUARCH_i386)..."

    This file is the only SRM file that should need to be changed due
    to machine (platform/OS) differences.

    For other release dates/detailed changes, contact SAIC.
 */

#ifdef __cplusplus
extern "C" {
#endif


#if defined(CPUARCH_i386) || defined(CPUARCH_i486)  || defined(CPUARCH_i586)  || defined(CPUARCH_i686) || defined(CPUARCH_alpha) || defined (_WIN32)
#define SRM_LITTLE_ENDIAN
#else
#define SRM_BIG_ENDIAN
#endif

#if defined(_WIN32)
#pragma warning(disable : 4996)
#endif

/*! SRM's integer */
typedef int            SRM_Integer;

/*! SRM's integer unsigned */
typedef unsigned int   SRM_Integer_Unsigned;

/*! SRM's integer positive */
typedef unsigned int SRM_Integer_Positive;


/*! SRM's long float */
typedef double         SRM_Long_Float;

/*!
 * ENUM: SRM_Boolean
 *
 *   Boolean.
 */
typedef enum
{
  SRM_FALSE = 0,  /*!< False value */
  SRM_TRUE  = 1   /*!< True value  */
} SRM_Boolean;

/*!
 * Used to define the max integer value.
 */
#define SRM_INTEGER_MAX 2147483647
/*!
 * Used to define the min integer value.
 */
#define SRM_INTEGER_MIN (-2147483647-1)
/*!
 * Used to define the max integer unsigned value.
 */
#define SRM_INTEGER_UNSIGNED_MAX 4294967295U
/*!
 * Used to define the min integer unsigned value.
 */
#define SRM_INTEGER_UNSIGNED_MIN 0
/*!
 * Used to define the max integer positive value.
 */
#define SRM_INTEGER_POSITIVE_MAX 4294967295U
/*!
 * Used to define the min integer positive value.
 */
#define SRM_INTEGER_POSITIVE_MIN 1


/*!
 * Used to define the positive 64 infinity value.
 */
extern
const unsigned int
__srm_64_pos_infinity[2];

/*!
 * Used to define the negative 64 infinity value.
 */
extern
const unsigned int
__srm_64_neg_infinity[2];


/*!
 * The constant positive 64 infinity value.
 */
#define SRM_POSITIVE_INFINITY    (*(SRM_Long_Float *)__srm_64_pos_infinity)
/*!
 * The constant negative 64 infinity value.
 */
#define SRM_NEGATIVE_INFINITY    (*(SRM_Long_Float *)__srm_64_neg_infinity)

/*!
 * Specifies the major version number of the release of the
 * SRM implementation.
 */
#define SRM_MAJOR_VERSION ((SRM_Integer_Positive)4)

/*!
 * Specifies the minor version number of the release of the
 * SRM implementation.
 */
#define SRM_MINOR_VERSION ((SRM_Integer_Unsigned)1)

/*!
 * Specifies the interim version letter of the release of the
 * SRM implementation. This shall be '\0' for none; between
 * 'a' and 'z' inclusive, for an unofficial interim version.
 */
#define SRM_INTERIM_VERSION '\0'

/*!
 * MACRO: SRM_EQUAL
 *
 *   A convenient macro to test whether two floating point numbers are
 *   within delta of each other (to avoid the classic problem of using
 *   == to compare equality among floating point numbers)
 */
#define SRM_EQUAL(a,b,delta) ( ((a) == (b)) || \
     ((a)-(delta) < (b) && (a)+(delta) > (b)) )

/*-----------------------------------------------------------------------------*/
/** This function returns the implementation version of the SRM component.
    @return the appropriate version string
 */
/*-----------------------------------------------------------------------------*/
extern
const char *
SRM_GetImplVerInfo(void);

#ifdef __cplusplus
}
#endif

#endif
