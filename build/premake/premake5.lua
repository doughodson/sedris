
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
SRM_IncPath            = "../../include/sedris/srm"
SRM_c_wrapper_IncPath  = "../../include/sedris/srm-c-wrapper"
EDCS_IncPath           = "../../include/sedris/edcs"
SEDRIS_LibPath         = "../../lib"

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
      optimize "On"
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

   -- libraries
   dofile "libs.lua"

   -- examples
   dofile "examples.lua"

   -- tests
   dofile "tests.lua"
