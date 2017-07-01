
#ifndef __SRMsincos_h_Included__
#define __SRMsincos_h_Included__

//
// DESCRIPTION:
//     Internal arrays/constants and inline function prototypes for
//     SRM approximated sine/cosine functions.

//
//
// Usage:
//     srm_sin(), srm_cos(), srm_sincos()
//
// Options: none
//

#ifndef _USE_MATH_DEFINES
#  define _USE_MATH_DEFINES  // Enables M_PI, M_PI_2, etc., constants out of math.h
#endif
#include <math.h>

//
// These are not found on some platforms in math.h,
// so we define them here if not available.
//
#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif

#define TWO_PI (M_PI * 2.0)

// For SRM types, e.g., SRM_Long_Float
#include "srm_types.h"

//
// Macro for "inline"
//
#if defined(_WIN32) && (_MSC_VER >= 1300)    // 1300 = MS VCC 7.x
#  define INLINE  __forceinline
#else
#  define INLINE  inline
#endif

// #define USE_SYSTEM_SINCOS

#if defined (USE_SYSTEM_SINCOS)
#else
//
// Global variables used for defining the internal lattice.
//
// These are global because they are needed in srm_SetupSinCosLattice()
// as well as all the inline functions here.
// Alternatively, a class could be used, or srm_SetupSinCosLattice()
// could pass back a handle that is a structure hiding all of these
// as members, but access to these members could then increase the timing.
//
// N can only be one of (45, 210, 10000).
// It affects the optimization constants used in srm_SetupSinCosLattice().
//
static const unsigned int const_N = 10000;
static const unsigned int const_LATTICESIZE = 8 * const_N + 1;
extern double Coeff1[], Coeff2[], Coeff3[], Coeff4[], Coeff5[], Coeff6[];
extern double CON;
static bool Initialized = false;
#endif

// To be called only ONCE to set up the lattice prior to any
// calls to srm_sin(), srm_cos(), or srm_sincos() calls.
extern void srm_SetupSinCosLattice (void);

//
// These 3 inline functions are coded from Ralph Toms's writeup identified
// as approximated quadratic sine/cosine from "FINAL_FR_QUA45Dual_S_C.f"
// October 5, 2007.
//

INLINE
SRM_Long_Float srm_sin (const SRM_Long_Float& theta)
{
#if defined (USE_SYSTEM_SINCOS)
    return sin(theta);
#else
    if (!Initialized)
    {
        srm_SetupSinCosLattice();
        Initialized = true;
    }
   // Scale input theta to range [0, 4PI] so that XX is always positive
   double XX = theta + TWO_PI;
   int II = (int)(XX * CON);
   double sine = Coeff1[II] + XX * (Coeff2[II] + XX * Coeff3[II]);

   if (sine > 1.0)
      sine = 1.0;
   else if (sine < -1.0)
      sine = -1.0;
   return sine;
#endif
}

INLINE
SRM_Long_Float srm_cos (const SRM_Long_Float& theta)
{
#if defined (USE_SYSTEM_SINCOS)
    return cos(theta);
#else
    if (!Initialized)
    {
        srm_SetupSinCosLattice();
        Initialized = true;
    }

   // Scale input theta to range [0, 4PI] so that XX is always positive
   double XX = theta + TWO_PI;
   int II = (int)(XX * CON);
   double cosine = Coeff4[II] + XX * (Coeff5[II] + XX * Coeff6[II]);

   if (cosine > 1.0)
      cosine = 1.0;
   else if (cosine < -1.0)
      cosine = -1.0;
   return cosine;
#endif
}

// It may be preferable to use pointers for the last 2 output args here
// so that it is very visible in the calling routine when the address
// of each is passed in, i.e., srm_sincos(theta, &sine, &cosine) that
// these are getting modified.
INLINE
void srm_sincos
(
    const SRM_Long_Float& theta,
          SRM_Long_Float& SineVal,
          SRM_Long_Float& CosineVal
)
{
#if defined (USE_SYSTEM_SINCOS)
    SineVal   = sin(theta);
    CosineVal = cos(theta);
#else
    if (!Initialized)
    {
        srm_SetupSinCosLattice();
        Initialized = true;
    }

   // Scale input theta to range [0, 4PI] so that XX is always positive
   double XX = theta + TWO_PI;
   int II = (int)(XX * CON);

   SineVal   = Coeff1[II] + XX * (Coeff2[II] + XX * Coeff3[II]);
   CosineVal = Coeff4[II] + XX * (Coeff5[II] + XX * Coeff6[II]);

   if (SineVal > 1.0)
      SineVal = 1.0;
   else if (SineVal < -1.0)
      SineVal = -1.0;

   if (CosineVal > 1.0)
      CosineVal = 1.0;
   else if (CosineVal < -1.0)
      CosineVal = -1.0;
#endif
}
#endif // __SRMsincos_h_Included__
