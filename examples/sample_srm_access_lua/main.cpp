
#include <sol.hpp>
#include <string>
#include <iostream>

std::string my_function(std::string a, std::string b)
{
   return a + b;
}

int main()
{
   sol::state lua;

   lua["my_func"] = my_function; // way 1
// lua.set("my_func", my_function); // way 2
// lua.set_function("my_func", my_function); // way 3

   // This function is now accessible as 'my_func' in
   // lua scripts / code run on this state:
   lua.script("some_str = my_func('Hello ', 'World')");

   // Read out the global variable we stored in 'some_str' in the
   // quick lua code we just executed
   std::string some_str = lua["some_str"];

   // print returned result, directly
   std::cout << some_str << std::endl;

   // open libraries which makes them available to script
   lua.open_libraries(sol::lib::base, sol::lib::package);
   lua.script_file("test.lua");


}
