
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

