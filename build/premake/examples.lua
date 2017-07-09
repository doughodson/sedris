
   --
   -- examples
   --

   -- sample_edcs_access
   project "sample_edcs_access"
      targetname "sample_edcs_access"
      targetdir "../../examples/sample_edcs_access"
      debugdir "../../examples/sample_edcs_access"
      kind "ConsoleApp"
      language "C"
      if _ACTION ~= "gmake" then
         defines { "_CONSOLE" }
      end
      includedirs { EDCS_IncPath }
      libdirs { SEDRIS_LibPath }
      links { "lib_edcs" }
      files {
         "../../examples/sample_edcs_access/**.h*",
         "../../examples/sample_edcs_access/**.c*"
      }

   -- sample_srm_access
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
      includedirs { SRM_IncPath }
      libdirs { SEDRIS_LibPath }
      links { "lib_srm" }
      files {
         "../../examples/sample_srm_access/**.h*",
         "../../examples/sample_srm_access/**.cpp"
      }

   -- sample_srm_access_c
   project "sample_srm_access_c"
      targetname "sample_srm_access_c"
      targetdir "../../examples/sample_srm_access_c"
      debugdir "../../examples/sample_srm_access_c"
      kind "ConsoleApp"
      language "C++"
      if _ACTION ~= "gmake" then
         defines { "_CONSOLE" }
      end
      --buildoptions { "-lm" "-lstdc++"}
      includedirs { SRM_c_wrapper_IncPath, SRM_IncPath }
      libdirs { SEDRIS_LibPath }
      links { "lib_srm_c_wrapper", "lib_srm" }
      files {
         "../../examples/sample_srm_access_c/**.h*",
         "../../examples/sample_srm_access_c/**.c*"
      }

