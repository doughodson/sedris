rem
rem remove any generated build files
rem
rmdir /S /Q ..\gmake
rmdir /S /Q ..\vs2017
rmdir /S /Q ..\obj
rem
rem remove any compiled libraries
rem
del ..\..\lib\*.lib
rem
rem create new build files files
rem
premake5-alpha13.exe --os=windows --file=premake5.lua vs2017

