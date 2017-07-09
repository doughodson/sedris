
SEDRIS: The Source for Environmental Data Representation & Interchange
======================================================================

Website: [www.sedris.org][sedris].

This project aims to improve upon (i.e., modernize) the SEDRIS 4.1.4 release.

Libraries
---------

* Data Representation Model (DRM)
* Environmental Data Coding Specification (EDCS)
* Spatial Reference Model (SRM) C++
* Spatial Reference Model (SRM) C Wrapper for C++ (new)

Examples
--------

* sample_edcs_access
* sample_srm_access (uses C++ SRM)
* sample_srm_access_c (uses C wrapper interface functions)

Compiling Codebase
------------------

* Run the appropriate batch/script file located in build/premake to create build files.  Load generated solution into Visual Studio or compile in Linux using make from command prompt. 

Progress - Steps to Improve Code
--------------------------------

* Reorganized SEDRIS libraries and examples into traditional C++ project structure (e.g., include, src, examples directories).
* Created build files for Visual Studio 2013/2015/2017 and Linux GCC/Clang make system using premake.
* Cleaned up include file paths in SRM library. (Several relative 'within library' paths were not specified, forcing the build system to define every possible include file search directory.)
* Removed code (some very old) oriented at exporting various things to DLLs. (These libraries are small, therefore, the appeal and simplicity of simply linking them into a final executable reduces the overall complexity of the codebase.)
* Separated SRM library C wrapper code from main SRM C++ code.  This interface code was moved into a new 'wrapper' library.
* Removed several 'using namespace' directives in C++ header files. (This should never have existed - it has been corrected.)
* Cleaned up many header files and removed RCS revision control generated tags.  These are old RCS 'indicators' left over from this ancient revision control system.  Code moved to GitHub, therefore, this is an easy cleanup that improves readable.
* Create license file in root directory (as suggested by GitHub) to reduce duplication and clutter within code files.
* Renamed SRM library C++ public header extensions from .h to .hpp to make obvious the nature of this codebase (C++).

To do/in-progress:

* Add two SRM tests (timing and accuracy) to repo - update code.
* Remove unnecessary includes and/or old C header files from C++ code (e.g., math.h, string.h, etc.).
* Make maximum use of forward references were possible.
* Remove legacy compiler/platform support - basically remove as many conditional compilation macros, etc, as possible.
* Dump inclusion of Windows.h and any other platform specific references as much as possible.
* Update codebase to leverage more modern C++ features.

The libraries and examples above compile and appear to work.  We have dumped several of the old build tools used in the project and have moved to using premake.  This eases the creation of Visual Studio and gmake files with one consistent solution.

[sedris]: http://www.sedris.org
