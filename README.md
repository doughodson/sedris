
SEDRIS: The Source for Environmental Data Representation & Interchange
======================================================================

Website: [www.sedris.org][sedris].

This project aims to improve upon (i.e., modernize) the SEDRIS 4.1.4 codebase.

Libraries
---------

* Data Representation Model (DRM)
* Environmental Data Coding Specification (EDCS)
* Spatial Reference Model (SRM)

Examples
--------

* sample_edcs_access
* sample_srm_access

Compiling Codebase
------------------

* Run the appropriate batch/script file located in build/premake to create build files.  Load generated solution into Visual Studio or compile in Linux using make from command prompt. 

Progress - Steps to Improve Code
--------------------------------

* Reorganized SEDRIS libraries and examples into traditional open source C++ project structure (e.g., include, src, examples directories).
* Created build files for Visual Studio 2013/2015/2017 and Linux GCC/Clang make system using premake.
* Cleaned up include file paths in SRM library.
* Removed code (some very old) oriented at exporting various things to DLLs.
* Removed several 'using namespace' directives in header files.
* Cleaned up many header files and removed RCS revision control generated tags - code slowly becoming readable.

To do/in-progress:

* Remove unnecessary includes and/or old C header files. 
* Remove as many include files from headers as possible.  This means make maximum use of forward references as possible.
* Rename, if sensible C++ header files to .hpp - because SEDRIS is a mixture of C and C++ code, this help ensure the distinction is clear.
* Remove legacy compiler/platform support - basically remove as many conditional compilation macros, etc, as possible.
* Update codebase to leverage more modern C++ features.
* Test to ensure code works as intended.

The libraries and examples above compile and appear to work.  We have dumped several of the old build tools used in the project and have moved to using premake.  This eases the creation of Visual Studio and gmake files with one consistent solution.

[sedris]: http://www.sedris.org
