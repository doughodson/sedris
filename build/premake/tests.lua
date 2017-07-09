
   --
   -- tests
   --

   -- test accuracy
   project "test_accuracy"
      targetname "test_accuracy"
      targetdir "../../examples/test_accuracy"
      debugdir "../../examples/test_accuracy"
      kind "ConsoleApp"
      language "C"
      if _ACTION ~= "gmake" then
         defines { "_CONSOLE" }
      end
      includedirs { EDCS_IncPath }
      libdirs { SEDRIS_LibPath }
      links { "lib_edcs" }
      files {
         "../../examples/test_accuracy/**.h*",
         "../../examples/test_accuracy/**.c*"
      }

   -- test timing
   project "test_timing"
      targetname "test_timing"
      targetdir "../../examples/test_timing"
      debugdir "../../examples/test_timing"
      kind "ConsoleApp"
      language "C++"
      if _ACTION ~= "gmake" then
         defines { "_CONSOLE" }
      end
      if _ACTION == "gmake" then
         buildoptions { "-std=c++11" }
      end
      includedirs { SRM_IncPath }
      libdirs { SEDRIS_LibPath }
      links { "lib_srm" }
      files {
         "../../examples/test_timing/**.h*",
         "../../examples/test_timing/**.cpp"
      }

