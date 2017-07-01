
--
-- If premake command is not supplied an action (target compiler), exit!
--
-- Targets of interest:
--     vs2013     (Visual Studio 2013)
--     vs2015     (Visual Studio 2015)
--     vs2017     (Visual Studio 2017)
--     gmake      (Linux make)
--
if (_ACTION == nil) then
    return
end

--
-- To print out complete compile command
-- make verbose=1
--

--
-- set include and library paths
--
SRM_IncPath     = "../../include/sedris/srm"
EDCS_IncPath     = "../../include/sedris/edcs"
SEDRIS_LibPath  = "../../lib"

workspace "sedris"

   -- destination directory for generated solution/project files
   location ("../" .. _ACTION)

   --
   -- Build (solution) configuration options:
   --     Release        (Runtime library is Multi-threaded DLL)
   --     Debug          (Runtime library is Multi-threaded Debug DLL)
   --
   configurations { "Release", "Debug" }

   -- visual studio options and warnings
   -- /wd4351 (C4351 warning) - disable warning associated with array brace initialization
   -- /wd4996 (C4996 warning) - disable deprecated declarations
   -- /wd4005 (C4005 warning) - disable macro redefinition
   -- /wd4100 (C4100 warning) - disable unreferenced formal parameter
   -- /Oi - generate intrinsic functions
   -- buildoptions( { "/wd4351", "/wd4996", "/wd4005", "/wd4100", "/Oi" } )

   -- common release configuration flags and symbols
   filter { "Release" }
      flags { "Optimize" }
      if _ACTION ~= "gmake" then
         -- favor speed over size
         buildoptions { "/Ot" }
         defines { "WIN32", "NDEBUG" }
      end

   -- common debug configuration flags and symbols
   filter { "Debug" }
      symbols "On"
      targetsuffix "_d"
      if _ACTION ~= "gmake" then
         defines { "WIN32", "_DEBUG" }
      end

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
      includedirs { EDCS_IncPath, SRM_IncPath }
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
   project "lib_srm-c-wrapper"
      targetname "sedris_srm-c-wrapper"
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
         "../../include/sedris/srm-c-wrapper/**.h*",
         "../../src/srm-c-wrapper/**.h*",
         "../../src/srm-c-wrapper/**.cpp"
      }

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
      language "C"
      if _ACTION ~= "gmake" then
         defines { "_CONSOLE" }
      end
      includedirs { SRM_IncPath }
      libdirs { SEDRIS_LibPath }
      links { "lib_srm", "lib_srm-c-wrapper" }
      files {
         "../../examples/sample_srm_access_c/**.h*",
         "../../examples/sample_srm_access_c/**.c*"
      }
