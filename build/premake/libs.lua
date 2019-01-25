
--
-- libraries
--

-- SRM library
project "libsrm"
   targetname "srm"
   targetdir(LibPathSEDRIS)
   kind "StaticLib"
   language "C++"
   if _ACTION == "gmake" then
      buildoptions { "-std=c++11" }
   end
   if _ACTION ~= "gmake" then
      defines { "_LIB" }
   end
   includedirs { IncPathSRM }
   files {
      "../../src/srm/**.h*",
      "../../src/srm/**.cpp"
   }

-- SRM C wrapper library
project "libsrm_c_wrapper"
   targetname "srm_c_wrapper"
   targetdir(LibPathSEDRIS)
   kind "StaticLib"
   language "C++"
   if _ACTION == "gmake" then
      buildoptions { "-std=c++11" }
   end
   if _ACTION ~= "gmake" then
      defines { "_LIB" }
   end
   includedirs { IncPathSRM }
   files {
      "../../src/srm_c_wrapper/**.h*",
      "../../src/srm_c_wrapper/**.cpp"
   }

-- lua library
project "liblua"
   targetname "lua"
   targetdir(LibPathDeps)
   kind "StaticLib"
   language "C"
   files {
      "../../deps/src/lua-5.3.5/src/**.h",
      "../../deps/src/lua-5.3.5/src/**.hpp",
      "../../deps/src/lua-5.3.5/src/**.c"
   }
   excludes {
      "../../deps/src/lua-5.3.5/src/lua.c",
      "../../deps/src/lua-5.3.5/src/luac.c"
   }
   if os.ishost("linux") then
      defines { "LUA_COMPAT_MODULE_5_2", "LUA_USE_LINUX" }
   end

