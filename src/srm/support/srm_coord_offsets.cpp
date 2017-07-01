
#include <string.h>

#include "srm_internal.h"

static SRM_Long_Float no_offset[3]={0.0,0.0,0.0};

/*This is a rather verbose way to add the false easting and
  northing offsets when projecting to a map proejection
  and subtracting the offsets when coming from a map projection.
  It has the advantage that it doesn't require a test in the
  virtual machine to figure out what to do and it is also unambiguous
  what was done.
*/

/*It should be noted that the named functions that copy no_offset
  to the offset values are redundant with getOffsetNone and that
  get offset_none is used in srm_conversions.cpp
  --cdk 5/28/2004
*/

Impl_Status Impl_getOffsetNone(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}


/*Beginning Of Offsets to SRF's*/

Impl_Status Impl_getOffsetToCELESTIOCENTRIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToLOC_SPACE_RECT_3D(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToLOC_SPACE_RECT_2D(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToCELESTIODETIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToLOC_TAN_EUCLIDEAN(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_LOC_TAN_EUCLIDEAN_SRFP* my_srfp = (IMPL_LOC_TAN_EUCLIDEAN_SRFP*) input_srfp;
  offset[0]=my_srfp->x_false_origin;
  offset[1]=my_srfp->y_false_origin;
  offset[2]=0.0;  /*Not actually used*/
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToLOC_TAN_AZ_SPHER(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToAZIMUTHAL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToLOC_TAN_CYL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToPOLAR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToCELESTIOMAGNETIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToEQUATORIAL_INERTIAL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToSOLAR_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToSOLAR_EQUATORIAL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToSOLAR_MAGNETIC_DIPOLE(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToSOLAR_MAGNETIC_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToHELIO_ARIES_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToHELIO_EARTH_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToHELIO_EARTH_EQUAT(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToMERCATOR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_MERCATOR_SRFP* my_srfp= (IMPL_MERCATOR_SRFP*)input_srfp;
  offset[0]=my_srfp->false_easting;
  offset[1]=my_srfp->false_northing;
  offset[2]=0.0;

  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToOBLIQUE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_OBLIQUE_MERCATOR_SRFP* my_srfp=(IMPL_OBLIQUE_MERCATOR_SRFP*) input_srfp;
  offset[0]=my_srfp->false_easting;
  offset[1]=my_srfp->false_northing;
  offset[2]=0.0;
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToTRANSVERSE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_TRANSVERSE_MERCATOR_SRFP* my_srfp=(IMPL_TRANSVERSE_MERCATOR_SRFP*) input_srfp;
  offset[0]=my_srfp->false_easting;
  offset[1]=my_srfp->false_northing;
  offset[2]=0.0;
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToLAMBERT_CONF_CONIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_LAMBERT_CONF_CONIC_SRFP* my_srfp= (IMPL_LAMBERT_CONF_CONIC_SRFP*) input_srfp;
  offset[0]=my_srfp->false_easting;
  offset[1]=my_srfp->false_northing;
  offset[2]=0.0;
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToPOLAR_STEREOGRAPHIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_POLAR_STEREOGRAPHIC_SRFP* my_srfp=(IMPL_POLAR_STEREOGRAPHIC_SRFP*) input_srfp;
  offset[0]=my_srfp->false_easting;
  offset[1]=my_srfp->false_northing;
  offset[2]=0.0;
  // Commented out for consistency.  Need reason why
  // memcpy(offset,no_offset,3*sizeof(SRM_Long_Float));
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetToEQUIDISTANT_CYL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_EQUIDISTANT_CYL_SRFP* my_srfp=(IMPL_EQUIDISTANT_CYL_SRFP*) input_srfp;
  offset[0]=my_srfp->false_easting;
  offset[1]=my_srfp->false_northing;
  offset[2]=0.0;

  return IMPL_VALID;
}

/*Beginning of offsets from SRF's*/


Impl_Status Impl_getOffsetFromCELESTIOCENTRIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromLOC_SPACE_RECT_3D(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromLOC_SPACE_RECT_2D(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromCELESTIODETIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromLOC_TAN_EUCLIDEAN(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_LOC_TAN_EUCLIDEAN_SRFP* my_srfp = (IMPL_LOC_TAN_EUCLIDEAN_SRFP*) input_srfp;
  offset[0]=-my_srfp->x_false_origin;
  offset[1]=-my_srfp->y_false_origin;
  offset[2]=0.0;  /*Not actually used*/
  return IMPL_VALID;

}
Impl_Status Impl_getOffsetFromLOC_TAN_AZ_SPHER(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromAZIMUTHAL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromLOC_TAN_CYL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromPOLAR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromCELESTIOMAGNETIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromEQUATORIAL_INERTIAL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromSOLAR_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromSOLAR_EQUATORIAL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromSOLAR_MAGNETIC_DIPOLE(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromSOLAR_MAGNETIC_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromHELIO_ARIES_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromHELIO_EARTH_ECLIPTIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromHELIO_EARTH_EQUAT(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_COPYCOORD(offset,no_offset);
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromMERCATOR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_MERCATOR_SRFP* my_srfp= (IMPL_MERCATOR_SRFP*)input_srfp;
  offset[0]=-my_srfp->false_easting;
  offset[1]=-my_srfp->false_northing;
  offset[2]=0.0;

  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromOBLIQUE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_OBLIQUE_MERCATOR_SRFP* my_srfp=(IMPL_OBLIQUE_MERCATOR_SRFP*) input_srfp;
  offset[0]=-my_srfp->false_easting;
  offset[1]=-my_srfp->false_northing;
  offset[2]=0.0;
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromTRANSVERSE_MERCATOR(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_TRANSVERSE_MERCATOR_SRFP* my_srfp=(IMPL_TRANSVERSE_MERCATOR_SRFP*) input_srfp;
  offset[0]=-my_srfp->false_easting;
  offset[1]=-my_srfp->false_northing;
  offset[2]=0.0;
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromLAMBERT_CONF_CONIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_LAMBERT_CONF_CONIC_SRFP* my_srfp= (IMPL_LAMBERT_CONF_CONIC_SRFP*) input_srfp;
  offset[0]=-my_srfp->false_easting;
  offset[1]=-my_srfp->false_northing;
  offset[2]=0.0;
  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromPOLAR_STEREOGRAPHIC(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_POLAR_STEREOGRAPHIC_SRFP* my_srfp=(IMPL_POLAR_STEREOGRAPHIC_SRFP*) input_srfp;
  offset[0]=-my_srfp->false_easting;
  offset[1]=-my_srfp->false_northing;
  offset[2]=0.0;

  return IMPL_VALID;
}
Impl_Status Impl_getOffsetFromEQUIDISTANT_CYL(void* input_srfp, SRM_Long_Float offset[3])
{
  IMPL_EQUIDISTANT_CYL_SRFP* my_srfp=(IMPL_EQUIDISTANT_CYL_SRFP*) input_srfp;
  offset[0]=-my_srfp->false_easting;
  offset[1]=-my_srfp->false_northing;
  offset[2]=0.0;

  return IMPL_VALID;
}

