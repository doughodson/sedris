//
// DESCRIPTION:
//    This program create CC, CD and UTM SRFs and Coordinates and then
//    converts sequentially between them.
//

#include <iostream>

#include "srf_all.hpp"

#ifndef PI
#define PI 3.14159265358979323846
#endif

#define TO_DEGREES(__rad)   (__rad*(180/PI))

int main(int, char**)
{
   // SRF containers, parameters, and coordinates
   srm::SRF_TransverseMercator* utm12_srf{};
   srm::SRF_Celestiodetic*      cd_srf{};
   srm::SRF_Celestiocentric*    cc_srf{};
   SRM_SRFS_Info           utm12_srfs_params;

   SRM_Long_Float          src_ord1 = 500000.0,
                           src_ord2 = 0.0,
                           src_ord3 = 1000.0;
   SRM_SRFS_Code           utm_srf_code = SRM_SRFSCOD_UNIVERSAL_TRANSVERSE_MERCATOR;
   SRM_SRF_Code            cd_srf_code = SRM_SRFCOD_GEODETIC_WGS_1984,
                           cc_srf_code = SRM_SRFCOD_GEOCENTRIC_WGS_1984;
   SRM_ORM_Code            orm = SRM_ORMCOD_WGS_1984;
   SRM_RT_Code             rt = SRM_RTCOD_WGS_1984_IDENTITY;

   try {

      // Initialize SRFs and coordinates
      utm12_srfs_params.srfs_code_info.srfs_code = utm_srf_code;
      utm12_srfs_params.srfs_code_info.value.srfsm_utm = SRM_SRFSMUTMCOD_ZONE_12_NORTHERN_HEMISPHERE;
      utm12_srfs_params.orm_code = orm;

      utm12_srf = (srm::SRF_TransverseMercator*)
                  srm::BaseSRF::createSRFSetMember(utm12_srfs_params, rt);
      cd_srf = (srm::SRF_Celestiodetic*)
               srm::BaseSRF::createStandardSRF(cd_srf_code, rt);
      cc_srf = (srm::SRF_Celestiocentric*)
               srm::BaseSRF::createStandardSRF(cc_srf_code, rt);

      srm::Coord3D_TransverseMercator  utm_coord(utm12_srf, src_ord1, src_ord2, src_ord3);
      srm::Coord3D_Celestiodetic       cd_coord(cd_srf);
      srm::Coord3D_Celestiocentric     cc_coord(cc_srf);

      // Perform conversions and print results
      cd_srf->changeCoordinate3DSRF(utm_coord, cd_coord);
      cc_srf->changeCoordinate3DSRF(cd_coord, cc_coord);

      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      std::cout.precision(6);
      std::cout << "UTM (Zone N12) "
                << "[ " << utm_coord.get_easting() << ", " << utm_coord.get_northing()
                << ", " << utm_coord.get_ellipsoidal_height() << " ]" << std::endl;
      std::cout << "  => CD "
                << "[ " << TO_DEGREES(cd_coord.get_longitude())
                << ", " << TO_DEGREES(cd_coord.get_latitude())
                << ", " << cd_coord.get_ellipsoidal_height()
                << " ]" << std::endl << std::endl;

      std::cout << "CD "
                << "[ " << TO_DEGREES(cd_coord.get_longitude())
                << ", " << TO_DEGREES(cd_coord.get_latitude())
                << ", " << cd_coord.get_ellipsoidal_height()
                << " ]" << std::endl;
      std::cout << "  => CC "
                << "[ " << cc_coord.get_u() << ", " << cc_coord.get_v()
                << ", " << cc_coord.get_w() << " ]" << std::endl << std::endl;

    } catch (srm::Exception(ex)) {
       std::cout << "Caught exception: " << ex.getWhat() << std::endl;
    }
    return 0;
}
