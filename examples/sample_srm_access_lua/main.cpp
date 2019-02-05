
#include <sol.hpp>

#include "srf_all.hpp"

#include <string>
#include <iostream>

void register_types(sol::state*);
void register_structs(sol::state*);

void print_results(const srm::Coord3D_TransverseMercator&,
                   const srm::Coord3D_Celestiodetic&,
                   const srm::Coord3D_Celestiocentric&);

int main()
{
   sol::state lua;
	lua.open_libraries(sol::lib::base);
   register_structs(&lua);
   register_types(&lua);

	// SRF containers, parameters, and coordinates
   SRM_Long_Float src_ord1{500000.0};
   SRM_Long_Float src_ord2{};
   SRM_Long_Float src_ord3{1000.0};

   SRM_SRF_Code cd_srf_code{SRM_SRFCOD_GEODETIC_WGS_1984};
   SRM_SRF_Code cc_srf_code{SRM_SRFCOD_GEOCENTRIC_WGS_1984};

   SRM_RT_Code  rt{SRM_RTCOD_WGS_1984_IDENTITY};

   // initialize SRFs and coordinates
   SRM_SRFS_Info utm12_srfs_params;
   utm12_srfs_params.srfs_code_info.srfs_code = SRM_SRFSCOD_UNIVERSAL_TRANSVERSE_MERCATOR;
   utm12_srfs_params.srfs_code_info.value.srfsm_utm = SRM_SRFSMUTMCOD_ZONE_12_NORTHERN_HEMISPHERE;
   utm12_srfs_params.orm_code = SRM_ORMCOD_WGS_1984;

   srm::SRF_TransverseMercator* utm12_srf{static_cast<srm::SRF_TransverseMercator*>(srm::BaseSRF::createSRFSetMember(utm12_srfs_params, rt))};
   srm::SRF_Celestiodetic* cd_srf{static_cast<srm::SRF_Celestiodetic*>(srm::BaseSRF::createStandardSRF(cd_srf_code, rt))};
   srm::SRF_Celestiocentric* cc_srf{static_cast<srm::SRF_Celestiocentric*>(srm::BaseSRF::createStandardSRF(cc_srf_code, rt))};

   srm::Coord3D_TransverseMercator  utm_coord(utm12_srf, src_ord1, src_ord2, src_ord3);
   srm::Coord3D_Celestiodetic       cd_coord(cd_srf);
   srm::Coord3D_Celestiocentric     cc_coord(cc_srf);

   // perform conversions and print results
   cd_srf->changeCoordinate3DSRF(utm_coord, cd_coord);
   cc_srf->changeCoordinate3DSRF(cd_coord, cc_coord);

   print_results(utm_coord, cd_coord, cc_coord);

   lua.set("utm_coord", &utm_coord);
	lua.set("cd_coord", &cd_coord);
	lua.set("cc_coord", &cc_coord);

	std::cout << "Leaving C++ land, off to Lua\n";
   lua.script_file("test.lua");
   std::cout << "Script done, back to C++\n";

}
