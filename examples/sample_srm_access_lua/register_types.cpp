#include <sol.hpp>

#include "srf_all.hpp"

void register_types(sol::state* lua)
{
	//-----------------------------------
	// srm::SRF_TransverseMercator
	//-----------------------------------
	struct TransverseMercator_deleter {
		void operator()(srm::SRF_TransverseMercator* x) const { x->release(); }
	};

   lua->new_usertype<srm::SRF_TransverseMercator>("TransverseMercator",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::SRF_TransverseMercator, TransverseMercator_deleter>(); }
      ),
      sol::meta_function::garbage_collect, sol::destructor([](srm::SRF_TransverseMercator&){})
   );

   //-----------------------------------
	// srm::SRF_Celestiodetic
	//-----------------------------------
	struct Celestiodetic_deleter {
		void operator()(srm::SRF_Celestiodetic* x) const { x->release(); }
	};

   lua->new_usertype<srm::SRF_Celestiodetic>("Celestiodetic",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::SRF_Celestiodetic, Celestiodetic_deleter>(); }
      ),
      sol::meta_function::garbage_collect, sol::destructor([](srm::SRF_Celestiodetic&){})
   );

	//-----------------------------------
	// srm::SRF_Celestiocentric
	//-----------------------------------
   struct Celestiocentric_deleter {
		void operator()(srm::SRF_Celestiocentric* x) const { x->release(); }
	};

   lua->new_usertype<srm::SRF_Celestiocentric>("Celestiocentric",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::SRF_Celestiocentric, Celestiocentric_deleter>(); }
      ),
      sol::meta_function::garbage_collect, sol::destructor([](srm::SRF_Celestiocentric&){})
   );

	//-----------------------------------
   // srm::Coord3D_TransverseMercator
	//-----------------------------------
	lua->new_usertype<srm::Coord3D_TransverseMercator>("Coord3D_TransverseMercator",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::Coord3D_TransverseMercator>(); }
      ),
      "get_easting", &srm::Coord3D_TransverseMercator::get_easting,
      "get_northing", &srm::Coord3D_TransverseMercator::get_northing,
		"get_ellipsoidal_height", &srm::Coord3D_TransverseMercator::get_ellipsoidal_height
   );

	//-----------------------------------
   // srm::Coord3D_Celestiodetic
	//-----------------------------------
	lua->new_usertype<srm::Coord3D_Celestiodetic>("Coord3D_Celestiodetic",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::Coord3D_Celestiodetic>(); }
      ),
		"get_longitude", &srm::Coord3D_Celestiodetic::get_longitude,
      "get_latitude", &srm::Coord3D_Celestiodetic::get_latitude,
		"get_ellipsoidal_height", &srm::Coord3D_Celestiodetic::get_ellipsoidal_height
   );

	//-----------------------------------
   // srm::Coord3D_Celestiocentric
	//-----------------------------------
	lua->new_usertype<srm::Coord3D_Celestiocentric>("Coord3D_Celestiocentric",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::Coord3D_Celestiocentric>(); }
      ),
		"get_u", &srm::Coord3D_Celestiocentric::get_u,
      "get_v", &srm::Coord3D_Celestiocentric::get_v,
		"get_w", &srm::Coord3D_Celestiocentric::get_w
   );
}
