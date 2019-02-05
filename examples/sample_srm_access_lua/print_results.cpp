
#include <iostream>

#include "srf_all.hpp"

const double PI{3.14159265358979323846};
#define TO_DEGREES(__rad)   (__rad*(180/PI))

void print_results(const srm::Coord3D_TransverseMercator& utm_coord,
                   const srm::Coord3D_Celestiodetic& cd_coord,
                   const srm::Coord3D_Celestiocentric& cc_coord)
{
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
}
