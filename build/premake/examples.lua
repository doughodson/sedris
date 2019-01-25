
--
-- examples
--

-- accessing SRM native functionality from using C++
project "sample_srm_access"
   targetname "sample_srm_access"
   targetdir "../../examples/sample_srm_access"
   debugdir "../../examples/sample_srm_access"
   kind "ConsoleApp"
   language "C++"
   if _ACTION ~= "gmake" then
      defines { "_CONSOLE" }
   end
   if _ACTION == "gmake" then
      buildoptions { "-std=c++11" }
   end
   includedirs { IncPathSRM }
   libdirs { LibPathSEDRIS }
   links { "libsrm" }
   files {
      "../../examples/sample_srm_access/**.h*",
      "../../examples/sample_srm_access/**.cpp"
   }

-- accessing SRM functionality from C
project "sample_srm_access_c"
   targetname "sample_srm_access_c"
   targetdir "../../examples/sample_srm_access_c"
   debugdir "../../examples/sample_srm_access_c"
   kind "ConsoleApp"
   language "C++"
   if _ACTION ~= "gmake" then
      defines { "_CONSOLE" }
   end
   --buildoptions { "-lm", "-lstdc++"}
   includedirs { IncPathSRM_c_wrapper, IncPathSRM }
   libdirs { LibPathSEDRIS }
   links { "libsrm_c_wrapper", "libsrm" }
   files {
      "../../examples/sample_srm_access_c/**.h*",
      "../../examples/sample_srm_access_c/**.c*"
   }

-- accessing SRM functionality from Lua
project "sample_srm_access_lua"
   targetname "sample_srm_access_lua"
   targetdir "../../examples/sample_srm_access_lua"
   debugdir "../../examples/sample_srm_access_lua"
   kind "ConsoleApp"
   language "C++"
   if os.ishost("linux") then
      links { "dl", "readline" }
   else
      defines { "_CONSOLE" }
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   end
   if _ACTION ~= "gmake" then
      defines { "_CONSOLE" }
   end
   if _ACTION == "gmake" then
      buildoptions { "-std=c++14" }
   end
   includedirs { IncPathSRM, IncPathSol2, IncPathLua }
   libdirs { LibPathSEDRIS, LibPathDeps }
   links { "libsrm", "liblua" }
   files {
      "../../examples/sample_srm_access_lua/**.h*",
      "../../examples/sample_srm_access_lua/**.cpp"
   }
