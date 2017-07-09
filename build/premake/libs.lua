
   --
   -- libraries
   --

   -- drm
   project "lib_drm"
      targetname "sedris_drm"
      targetdir ("../../lib/")
      kind "StaticLib"
      language "C"
      if _ACTION ~= "gmake" then
         defines { "_LIB" }
      end
      if _ACTION == "gmake" then
         defines { "gnu" }
      end
      includedirs { SRM_c_wrapper_IncPath, SRM_IncPath, EDCS_IncPath }
      files {
         "../../include/sedris/drm/**.h*",
         "../../src/drm/**.c*"
      }

   -- edcs
   project "lib_edcs"
      targetname "sedris_edcs"
      targetdir ("../../lib/")
      kind "StaticLib"
      language "C"
      if _ACTION ~= "gmake" then
        defines { "_LIB" }
      end
      if _ACTION == "gmake" then
         defines { "gnu" }
      end
      includedirs { EDCS_IncPath }
      files {
         "../../include/sedris/edcs/**.h*",
         "../../src/edcs/**.c*"
      }

   -- srm
   project "lib_srm"
      targetname "sedris_srm"
      targetdir ("../../lib/")
      kind "StaticLib"
      language "C++"
      if _ACTION == "gmake" then
         buildoptions { "-std=c++11" }
      end
      if _ACTION ~= "gmake" then
         defines { "_LIB" }
      end
      includedirs { SRM_IncPath }
      files {
         "../../include/sedris/srm/**.h*",
         "../../src/srm/**.h*",
         "../../src/srm/**.cpp"
      }

   -- srm-c-wrapper
   project "lib_srm_c_wrapper"
      targetname "sedris_srm_c_wrapper"
      targetdir ("../../lib/")
      kind "StaticLib"
      language "C++"
      if _ACTION == "gmake" then
         buildoptions { "-std=c++11" }
      end
      if _ACTION ~= "gmake" then
         defines { "_LIB" }
      end
      includedirs { SRM_c_wrapper_IncPath, SRM_IncPath }
      files {
         "../../include/sedris/srm-c-wrapper/**.h*",
         "../../src/srm-c-wrapper/**.h*",
         "../../src/srm-c-wrapper/**.cpp"
      }
