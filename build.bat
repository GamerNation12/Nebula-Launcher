@echo off
set PATH=C:\Qt\Tools\mingw1310_64\bin;%PATH%
cd cpp-core
rmdir /s /q build
C:\Qt\Tools\CMake_64\bin\cmake.exe . -B build\Desktop_Qt_6_11_0_MinGW_64_bit-Debug -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.11.0/mingw_64" -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" -DCMAKE_C_COMPILER="C:/Qt/Tools/mingw1310_64/bin/gcc.exe"
C:\Qt\Tools\CMake_64\bin\cmake.exe --build build\Desktop_Qt_6_11_0_MinGW_64_bit-Debug
C:\Qt\6.11.0\mingw_64\bin\windeployqt.exe --compiler-runtime build\Desktop_Qt_6_11_0_MinGW_64_bit-Debug\LuminaCore.exe
