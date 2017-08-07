rem
rem remove any generated build files
rem
rmdir /S /Q ..\gmake
rmdir /S /Q ..\vs2013
rmdir /S /Q ..\vs2015
rmdir /S /Q ..\vs2017
rmdir /S /Q ..\obj
rem
rem remove any compiled libraries
rem
del ..\..\lib\*.lib
rem
rem create new build files files
rem
premake5_v2017_0807.exe --os=windows --file=premake5.lua vs2013
premake5_v2017_0807.exe --os=windows --file=premake5.lua vs2015
premake5_v2017_0807.exe --os=windows --file=premake5.lua vs2017

