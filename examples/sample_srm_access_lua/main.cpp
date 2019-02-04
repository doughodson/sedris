
#include <sol.hpp>

#include "srf_all.hpp"

#include <string>
#include <iostream>

void register_types(sol::state*);

int main()
{
   sol::state lua;
	lua.open_libraries(sol::lib::base);
   register_types(&lua);

	std::cout << "Leaving C++ land, off to Lua\n";
   lua.script_file("test.lua");
   std::cout << "Script done, back to C++\n";

}
