#include <sol.hpp>

#include "srf_all.hpp"

void register_structs(sol::state* lua)
{
	//-----------------------------------
   // SRM_SRFS_Info
	//-----------------------------------
	lua->new_usertype<SRM_SRFS_Info>("SRM_SRFS_Info",
		"orm_code", &SRM_SRFS_Info::orm_code,
		"srfs_code_info", &SRM_SRFS_Info::srfs_code_info
   );

}
