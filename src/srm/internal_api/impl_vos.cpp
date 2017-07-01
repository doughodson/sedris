
#include "impl_alloc.h"
#include "impl_change.h"
#include "../srf_impl/orm_rd_struct.h"
#include "impl_vos.h"

extern Impl_Status Impl_GetWGS84GeoidalSeparation
(
    const SRM_Long_Float  coord_org_wgs84_cd[3],
          SRM_Long_Float *GeoidalSeparation_ptr
);

Impl_Status Impl_calcDSS_EGM84_GEOID
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    Impl_Status status=IMPL_UNIMPLEM;

#if 0
    Impl_SRF_ptr my_srf_cd=NULL;
    SRM_Long_Float my_coord_org[3]={wgs84_cd_coord[0],wgs84_cd_coord[1],0.0};
    SRM_Long_Float coord_cd[3]={IMPL_NAN,IMPL_NAN,IMPL_NAN};

    status=Impl_createSRFFromParams(SRM_SRFTCOD_CELESTIODETIC,
                                    SRM_ORMCOD_WGS_1984,
                                    SRM_RTCOD_WGS_1984_IDENTITY,
                                    0,
                                    (void**)&my_srf_cd);

    if(status!=IMPL_VALID)
    {
        Impl_releaseSRF((void**)&my_srf_cd);
        SIMPLIFY_STATUS(status);
        return status;
    }
    status=Impl_changeCoord3DSRF(srf_org,
                                 my_coord_org,
                                 (void*)my_srf_cd,
                                 coord_cd);

    if(status&IMPL_BADSTAT)
    {
        Impl_releaseSRF((void**)&my_srf_cd);
        SIMPLIFY_STATUS(status);
        return status;
    }
    status|=Impl_GetWGS84GeoidalSeparation(coord_cd,retval);
    status|= Impl_releaseSRF((void**)&my_srf_cd);

    Impl_releaseSRF((void**)&my_srf_cd);
    SIMPLIFY_STATUS(status);
#endif

    return status;
}

Impl_Status Impl_calcDSS_IGLD_1955
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    return IMPL_UNIMPLEM;
}
Impl_Status Impl_calcDSS_IGLD_1985
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    return IMPL_UNIMPLEM;
}
Impl_Status Impl_calcDSS_MSL
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    return IMPL_UNIMPLEM;
}
Impl_Status Impl_calcDSS_NAVD_1988
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    return IMPL_UNIMPLEM;
}
Impl_Status Impl_calcDSS_NGVD_1929
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    return IMPL_UNIMPLEM;
}
Impl_Status Impl_calcDSS_OSGM_2002
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    return IMPL_UNIMPLEM;
}
Impl_Status Impl_calcDSS_WGS84_ELLIPSOID
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    // This is always 0.0
    *retval = 0.0;

    return IMPL_VALID;
}


Impl_Status Impl_calcDSS_EGM96_GEOID
(
    Impl_SRF_ptr    srf_org,
    SRM_Long_Float  wgs84_cd_coord[3],
    SRM_Long_Float *retval
)
{
    Impl_Status status=0;
    Impl_SRF_ptr my_srf_cd=NULL;
    SRM_Long_Float my_coord_org[3]={wgs84_cd_coord[0],wgs84_cd_coord[1],0.0};
    SRM_Long_Float coord_cd[3]={IMPL_NAN,IMPL_NAN,IMPL_NAN};

    status=Impl_createSRFFromParams(SRM_SRFTCOD_CELESTIODETIC,
                                    SRM_ORMCOD_WGS_1984,
                                    SRM_RTCOD_WGS_1984_IDENTITY,
                                    0,
                                    (void**)&my_srf_cd);

    if(status!=IMPL_VALID)
    {
        Impl_releaseSRF((void**)&my_srf_cd);
        SIMPLIFY_STATUS(status);
        return status;
    }
    status=Impl_changeCoord3DSRF(srf_org,my_coord_org,(void*)my_srf_cd,coord_cd);

    if(status&IMPL_BADSTAT)
    {
        Impl_releaseSRF((void**)&my_srf_cd);
        SIMPLIFY_STATUS(status);
        return status;
    }
    status|=Impl_GetWGS84GeoidalSeparation(my_coord_org,retval);
    status|= Impl_releaseSRF((void**)&my_srf_cd);

    Impl_releaseSRF((void**)&my_srf_cd);
    SIMPLIFY_STATUS(status);

    return status;
}


/*
 *----------------------------------------------------------------------------
 *
 * FUNCTION: Impl_GetWGS84GeoidalSeparation
 *
 *   Returns the height of the WGS84 geoid above or below the WGS84
 *   ellipsoid, at the specified geodetic coordinates, using a grid
 *   of height adjustments from the WGS84 EGM 96 gravity model 15 minute
 *   increment geoid offset table.
 *   ftp://164.214.2.65/pub/gig/gravity3/WW15MGH.Z
 *
 *----------------------------------------------------------------------------
 */
Impl_Status
Impl_GetWGS84GeoidalSeparation
(
    const SRM_Long_Float  coord_org_wgs84_cd[3],
          SRM_Long_Float *GeoidalSeparation_ptr
)
{
    SRM_Integer_Unsigned  Index,ScaleFactor,NumbGeoidCols,NumbGeoidRows;
    SRM_Long_Float DeltaX, DeltaY,
               ElevationSE, ElevationSW, ElevationNE, ElevationNW,
               OffsetX, OffsetY, PostX, PostY, UpperY, LowerY;
    Impl_Status status = IMPL_VALID;

    ScaleFactor = 4;
    NumbGeoidCols = 1441;
    NumbGeoidRows = 721;

    const SRM_Integer_Unsigned MaxTableIndex = (SRM_Integer_Unsigned)(sizeof(WGS84_GeoidSeparationTable)/sizeof(float)-1);

   /*
    *  Compute X and Y Offsets into Geoid Height Array.
    */
    if (coord_org_wgs84_cd[0] < 0.0)
    {
        OffsetX = (coord_org_wgs84_cd[0]*SRM_DEGREES_PER_RADIAN + 360.0)
                  * ScaleFactor;
    }
    else
    {
        OffsetX = coord_org_wgs84_cd[0]*SRM_DEGREES_PER_RADIAN* ScaleFactor;
    }

    OffsetY = (90.0 - coord_org_wgs84_cd[1]*SRM_DEGREES_PER_RADIAN)
              * ScaleFactor;

   /*
    *  Find Four Nearest Geoid Height Cells for specified Latitude, Longitude;
    *  Assumes that (0,0) of Geoid Height Array is at Northwest corner.
    */
    PostX = floor( OffsetX );
    if ((PostX + 1) == NumbGeoidCols)
        PostX--;
    PostY = floor( OffsetY );
    if ((PostY + 1) == NumbGeoidRows)
        PostY--;

    // compute NW and NE elevations
    Index = (SRM_Integer_Unsigned)(PostY * NumbGeoidCols + PostX);
    if( (Index > MaxTableIndex ) || (Index < 0 ) )
    {
      status= IMPL_INACTBLE;
      *GeoidalSeparation_ptr=IMPL_NAN;
      return status;
    }
    ElevationNW = WGS84_GeoidSeparationTable[Index];
    ElevationNE = WGS84_GeoidSeparationTable[Index+ 1];

    // compute SW and SE elevations
    Index = (SRM_Integer_Unsigned)((PostY + 1) * NumbGeoidCols + PostX);
    if( (Index > MaxTableIndex ) || (Index < 0 ) )
    {
      status= IMPL_INACTBLE;
      *GeoidalSeparation_ptr=IMPL_NAN;
      return status;
    }
    ElevationSW = WGS84_GeoidSeparationTable[Index];
    ElevationSE = WGS84_GeoidSeparationTable[ Index + 1 ];

   /*
    *  Perform Bi-Linear Interpolation to compute Height above Ellipsoid
    */
    DeltaX = OffsetX - PostX;
    DeltaY = OffsetY - PostY;

    UpperY = ElevationNW + DeltaX * ( ElevationNE - ElevationNW );
    LowerY = ElevationSW + DeltaX * ( ElevationSE - ElevationSW );

   *GeoidalSeparation_ptr = UpperY + DeltaY * ( LowerY - UpperY );

    return status;
} /* end SRM_GetWGS84GeoidalSeparation */



Impl_Status(*Impl_calcDSS[SRM_DSS_CODE_UBOUND+1])(Impl_SRF_ptr srf, SRM_Long_Float coord[3], SRM_Long_Float* retval)=
{
  0,
  Impl_calcDSS_EGM96_GEOID,
  Impl_calcDSS_IGLD_1955,
  Impl_calcDSS_IGLD_1985,
  Impl_calcDSS_MSL,
  Impl_calcDSS_NAVD_1988,
  Impl_calcDSS_NGVD_1929,
  Impl_calcDSS_OSGM_2002,
  Impl_calcDSS_WGS84_ELLIPSOID,
  Impl_calcDSS_EGM84_GEOID
};
