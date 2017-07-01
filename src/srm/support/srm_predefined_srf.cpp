
#include <math.h>
#include <signal.h>

#include "../internal_api/impl_private.h"
#include "../internal_api/impl_alloc.h"
#include "../internal_api/impl_change.h"
#include "../internal_api/impl_vos.h"

#include "srm_internal.h"
#include "srm_validcoord.h"
#include "srm_srfp.h"

/*The following functions allocate standard (predefined SRFs).*/

void* Impl_allocsrfNULL_SRF( SRM_RT_Code rt_code )
{
    /*This is a placeholder that shouldn't get called*/
    return NULL;
}

void* Impl_allocsrfBRITISH_NAT_GRID( SRM_RT_Code rt_code )
{
    SRM_TM_Parameters api_srf;
    SRM_ORM_Code orm=SRM_ORMCOD_OSGB_1936;

    api_srf.origin_longitude=-2.0*SRM_RADIANS_PER_DEGREE;
    api_srf.origin_latitude= 49.0*SRM_RADIANS_PER_DEGREE;
    api_srf.central_scale=      0.9996012717;
    api_srf.false_easting= 400000;  /*Checked against OSGB.gov.uk*/
    api_srf.false_northing=-100000;

    return Impl_allocsrfTRANSVERSE_MERCATOR(orm,rt_code,&api_srf);
}

void* Impl_allocsrfBRITISH_OSGRS80_GRID( SRM_RT_Code rt_code )
{
    SRM_TM_Parameters api_srf;
    SRM_ORM_Code orm=SRM_ORMCOD_ETRS_1989;

    api_srf.origin_longitude=-2.0*SRM_RADIANS_PER_DEGREE;
    api_srf.origin_latitude= 49.0*SRM_RADIANS_PER_DEGREE;
    api_srf.central_scale=      0.9996012717;
    api_srf.false_easting= 400000;  /*Checked against OSGB.gov.uk*/
    api_srf.false_northing=-100000;

    return Impl_allocsrfTRANSVERSE_MERCATOR(orm,rt_code,&api_srf);
}

void* Impl_allocsrfDELAWARE_SPCS( SRM_RT_Code rt_code )
{
    SRM_TM_Parameters api_srf;

    SRM_ORM_Code orm=SRM_ORMCOD_N_AM_1983;

    api_srf.origin_longitude=(-75.0-(25.0/60.0))*SRM_RADIANS_PER_DEGREE;/*-75 degrees 25 minutes*/
    api_srf.origin_latitude=  38.0*SRM_RADIANS_PER_DEGREE;
    api_srf.central_scale=   (1.0- (1.0/200000.0));
    api_srf.false_easting=    200000.0;
    api_srf.false_northing=   0.0;

    return Impl_allocsrfTRANSVERSE_MERCATOR(orm, rt_code,&api_srf);
}

void* Impl_allocsrfGC_WGS_1984( SRM_RT_Code rt_code )
{
    SRM_ORM_Code orm=SRM_ORMCOD_WGS_1984;
    return Impl_allocsrfCELESTIOCENTRIC(orm,rt_code,0);
}

void* Impl_allocsrfGD_AUSTRALIA_1984( SRM_RT_Code rt_code )
{
    SRM_ORM_Code orm=SRM_ORMCOD_AUSTRALIAN_GEOD_1984;

    return Impl_allocsrfCELESTIODETIC(orm,rt_code,0);
}

void* Impl_allocsrfGD_WGS_1984( SRM_RT_Code rt_code )
{
    SRM_ORM_Code orm=SRM_ORMCOD_WGS_1984;

    return Impl_allocsrfCELESTIODETIC(orm,rt_code,0);
}

void* Impl_allocsrfGD_N_AMERICAN_1983( SRM_RT_Code rt_code )
{
    SRM_ORM_Code orm=SRM_ORMCOD_N_AM_1983;

    return Impl_allocsrfCELESTIODETIC(orm,rt_code,0);
}

void* Impl_allocsrfIRISH_GRID( SRM_RT_Code rt_code )
{
    SRM_TM_Parameters api_srf;

    SRM_ORM_Code orm=SRM_ORMCOD_IRELAND_1965;

    api_srf.origin_longitude=-8.0*SRM_RADIANS_PER_DEGREE;
    api_srf.origin_latitude= (53.0+30.0/60.0)*SRM_RADIANS_PER_DEGREE;
    api_srf.central_scale= 1.000035    ;
    api_srf.false_easting= 200000.0;
    api_srf.false_northing=250000.0;

    return Impl_allocsrfTRANSVERSE_MERCATOR(orm,rt_code,&api_srf);
}


void* Impl_allocsrfIRISH_TRANS_MERCATOR( SRM_RT_Code rt_code )
{
    SRM_TM_Parameters api_srf;

    SRM_ORM_Code orm=SRM_ORMCOD_ETRS_1989;
    api_srf.origin_longitude=-8.0*SRM_RADIANS_PER_DEGREE;
    api_srf.origin_latitude= (53.0+ (30.0/60.0) )*SRM_RADIANS_PER_DEGREE;
    api_srf.central_scale= 0.999820;
    api_srf.false_easting= 600000.0;
    api_srf.false_northing=750000.0;

    return Impl_allocsrfTRANSVERSE_MERCATOR(orm,rt_code,&api_srf);
}

void* Impl_allocsrfLAMBERT_93( SRM_RT_Code rt_code )
{
    SRM_LCC_Parameters api_srf;

    SRM_ORM_Code orm=SRM_ORMCOD_RGF_1993;

    api_srf.origin_longitude=3.0*SRM_RADIANS_PER_DEGREE;
    api_srf.origin_latitude=(46.0+(30.0/60.0))*SRM_RADIANS_PER_DEGREE;
    api_srf.latitude1=44.0*SRM_RADIANS_PER_DEGREE;
    api_srf.latitude2=49.0*SRM_RADIANS_PER_DEGREE;
    api_srf.false_easting=700000.0;
    api_srf.false_northing=6600000.0;

    return Impl_allocsrfLAMBERT_CONF_CONIC(orm,rt_code,&api_srf);
}

void* Impl_allocsrfLAMBERT_II_WIDE( SRM_RT_Code rt_code )
{
    SRM_LCC_Parameters api_srf;

    SRM_ORM_Code orm=SRM_ORMCOD_NTF_1896_PM_PARIS;
    api_srf.origin_longitude=0.0*SRM_RADIANS_PER_DEGREE;
    api_srf.origin_latitude=(46.0+(48.0/60.0))*SRM_RADIANS_PER_DEGREE;
    api_srf.latitude1=(45.0+(53.0/60.0)+(56.108/3600.0))*SRM_RADIANS_PER_DEGREE;
    api_srf.latitude2=(47.0+(41.0/60.0)+(45.652/3600.0))*SRM_RADIANS_PER_DEGREE;
    api_srf.false_easting=600000.0;
    api_srf.false_northing=2200000.0;

    return Impl_allocsrfLAMBERT_CONF_CONIC(orm,rt_code,&api_srf);
}

void* Impl_allocsrfMARYLAND_SPCS( SRM_RT_Code rt_code )
{
    SRM_LCC_Parameters api_srf;
    SRM_ORM_Code orm=SRM_ORMCOD_N_AM_1983;
    api_srf.origin_longitude=-77.0*SRM_RADIANS_PER_DEGREE;
    api_srf.origin_latitude=(37.0+(40.0/60.0))*SRM_RADIANS_PER_DEGREE;
    api_srf.latitude1=(38.0+18.0/60)*SRM_RADIANS_PER_DEGREE;
    api_srf.latitude2=(39.0+(27.0/60.0))*SRM_RADIANS_PER_DEGREE;
    api_srf.false_easting=400000.0;
    api_srf.false_northing=0.0;

    return Impl_allocsrfLAMBERT_CONF_CONIC(orm,rt_code,&api_srf);
}


void* Impl_allocsrfMARS_PLANETOCENTRIC_2000( SRM_RT_Code rt_code )
{
    SRM_ORM_Code orm=SRM_ORMCOD_MARS_SPHERE_2000;

    return Impl_allocsrfCELESTIODETIC(orm,rt_code,0);
}

void* Impl_allocsrfMARS_PLANETOGRAPHIC_2000( SRM_RT_Code rt_code )
{
    SRM_ORM_Code orm=SRM_ORMCOD_MARS_2000;

    return Impl_allocsrfPLANETODETIC(orm,rt_code,0);
}

/*The following group of functions returns the SRFT code for a given
  predefined standard SRF
*/

SRM_SRFT_Code Impl_templcodeNULL_SRF()
{
    return 0;
    /*placehoulder that shouldn't get called*/
}

SRM_SRFT_Code Impl_templcodeBRITISH_NAT_GRID()
{
    return SRM_SRFTCOD_TRANSVERSE_MERCATOR;
}

SRM_SRFT_Code Impl_templcodeBRITISH_OSGRS80_GRID()
{
    return SRM_SRFTCOD_TRANSVERSE_MERCATOR;
}

SRM_SRFT_Code Impl_templcodeDELAWARE_SPCS()
{
    return SRM_SRFTCOD_TRANSVERSE_MERCATOR;
}

SRM_SRFT_Code Impl_templcodeGC_WGS_1984()
{
    return SRM_SRFTCOD_CELESTIOCENTRIC;
}

SRM_SRFT_Code Impl_templcodeGD_AUSTRALIA_1984()
{
    return SRM_SRFTCOD_CELESTIODETIC;
}

SRM_SRFT_Code Impl_templcodeGD_WGS_1984()
{
    return SRM_SRFTCOD_CELESTIODETIC;
}
SRM_SRFT_Code Impl_templcodeGD_N_AMERICAN_1983()
{
    return SRM_SRFTCOD_CELESTIODETIC;
}
SRM_SRFT_Code Impl_templcodeIRISH_GRID()
{
    return SRM_SRFTCOD_TRANSVERSE_MERCATOR;
}
SRM_SRFT_Code Impl_templcodeIRISH_TRANS_MERCATOR()
{
    return SRM_SRFTCOD_TRANSVERSE_MERCATOR;
}
SRM_SRFT_Code Impl_templcodeLAMBERT_93()
{
    return SRM_SRFTCOD_LAMBERT_CONFORMAL_CONIC;
}
SRM_SRFT_Code Impl_templcodeLAMBERT_II_WIDE()
{
    return SRM_SRFTCOD_LAMBERT_CONFORMAL_CONIC;
}
SRM_SRFT_Code Impl_templcodeMARYLAND_SPCS()
{
    return SRM_SRFTCOD_LAMBERT_CONFORMAL_CONIC;
}

SRM_SRFT_Code Impl_templcodeMARS_PLANETOCENTRIC_2000()
{
    return SRM_SRFTCOD_CELESTIODETIC;
}

SRM_SRFT_Code Impl_templcodeMARS_PLANETOGRAPHIC_2000()
{
    return SRM_SRFTCOD_PLANETODETIC;
}
