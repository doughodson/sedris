
SEDRIS: The Source for Environmental Data Representation & Interchange
======================================================================

Website: [www.sedris.org][sedris].

This project aims to improve upon (i.e., modernize) the SEDRIS 4.1.4 codebase.

Libraries
---------

* Data Representation Model (DRM)
* Environmental Data Coding Specification (EDCS)
* Spatial Reference Model (SRM) C++
* Spatial Reference Model (SRM) C++ Wrapper for C

Examples
--------

* sample_edcs_access
* sample_srm_access (uses C++ SRM)
* sample_srm_access_c (uses C wrapper interface)

Compiling Codebase
------------------

* Run the appropriate batch/script file located in build/premake to create build files.  Load generated solution into Visual Studio or compile in Linux using make from command prompt. 

Progress - Steps to Improve Code
--------------------------------

* Reorganized SEDRIS libraries and examples into traditional open source C++ project structure (e.g., include, src, examples directories).
* Created build files for Visual Studio 2013/2015/2017 and Linux GCC/Clang make system using premake.
* Cleaned up include file paths in SRM library.
* Removed code (some very old) oriented at exporting various things to DLLs.
* Separated SRM library C wrapper code from C++ code and created a new wrapper library.
* Removed several 'using namespace' directives in C++ header files.
* Cleaned up many header files and removed RCS revision control generated tags - code slowly becoming readable.
* Create license file in root directory (as suggested by GitHub) to reduce clutter within code files.
* Renamed C++ public header for SRM library to be .hpp as opposed to .h.  Since SRM is a mixture of C and C++ code, this help keeps this distinction more clear.

To do/in-progress:

* Remove unnecessary includes and/or old C header files from C++ code (e.g., math.h, string.h, etc.).
* Make maximum use of forward references as possible.
* Remove legacy compiler/platform support - basically remove as many conditional compilation macros, etc, as possible.
* Update codebase to leverage more modern C++ features.
* Test to ensure code works as intended.

The libraries and examples above compile and appear to work.  We have dumped several of the old build tools used in the project and have moved to using premake.  This eases the creation of Visual Studio and gmake files with one consistent solution.

[sedris]: http://www.sedris.org
