//
// test program to exercise the creation and destruction of objects
//

#include <iostream>

#include "srf_all.hpp"

#ifndef PI
#define PI 3.14159265358979323846
#endif

#define TO_DEGREES(__rad)   (__rad*(180/PI))

int main()
{
   // SRF containers, parameters, and coordinates
   srm::SRF_TransverseMercator* utm12_srf{};
   srm::SRF_Celestiodetic*      cd_srf{};
   srm::SRF_Celestiocentric*    cc_srf{};
   SRM_SRFS_Info utm12_srfs_params;

   SRM_Long_Float src_ord1{500000.0};
   SRM_Long_Float src_ord2{0.0};
   SRM_Long_Float src_ord3{1000.0};

   SRM_SRFS_Code utm_srf_code{SRM_SRFSCOD_UNIVERSAL_TRANSVERSE_MERCATOR};
   SRM_SRF_Code  cd_srf_code{SRM_SRFCOD_GEODETIC_WGS_1984};
   SRM_SRF_Code  cc_srf_code{SRM_SRFCOD_GEOCENTRIC_WGS_1984};
   SRM_ORM_Code  orm{SRM_ORMCOD_WGS_1984};
   SRM_RT_Code   rt{SRM_RTCOD_WGS_1984_IDENTITY};

   try {
      // Initialize SRFs and coordinates
      utm12_srfs_params.srfs_code_info.srfs_code = utm_srf_code;
      utm12_srfs_params.srfs_code_info.value.srfsm_utm = SRM_SRFSMUTMCOD_ZONE_12_NORTHERN_HEMISPHERE;
      utm12_srfs_params.orm_code = orm;

      utm12_srf = static_cast<srm::SRF_TransverseMercator*>(srm::BaseSRF::createSRFSetMember(utm12_srfs_params, rt));

      utm12_srf->release();

    } catch (srm::Exception(ex)) {
       std::cout << "Caught exception: " << ex.getWhat() << std::endl;
    }
}
