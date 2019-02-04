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
      )
   );

	//-----------------------------------
   // srm::Coord3D_Celestiodetic
	//-----------------------------------
	lua->new_usertype<srm::Coord3D_Celestiodetic>("Coord3D_Celestiodetic",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::Coord3D_Celestiodetic>(); }
      )
   );

	//-----------------------------------
   // srm::Coord3D_Celestiocentric
	//-----------------------------------
	lua->new_usertype<srm::Coord3D_Celestiocentric>("Coord3D_Celestiocentric",
      "new", sol::factories(
         [](){ return std::unique_ptr<srm::Coord3D_Celestiocentric>(); }
      )
   );
}
