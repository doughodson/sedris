
--
-- tests
--

-- test the creation of objects
project "test_creation"
   targetname "test_creation"
   targetdir "../../examples/test_creation"
   debugdir "../../examples/test_creation"
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
      "../../examples/test_creation/**.h*",
      "../../examples/test_creation/**.c*"
   }

-- test SRM accuracy
project "test_srm_accuracy"
   targetname "test_srm_accuracy"
   targetdir "../../examples/test_srm_accuracy"
   debugdir "../../examples/test_srm_accuracy"
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
      "../../examples/test_srm_accuracy/**.h*",
      "../../examples/test_srm_accuracy/**.c*"
   }

-- test SRM timing
project "test_srm_timing"
   targetname "test_srm_timing"
   targetdir "../../examples/test_srm_timing"
   debugdir "../../examples/test_srm_timing"
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
      "../../examples/test_srm_timing/**.h*",
      "../../examples/test_srm_timing/**.cpp"
   }

