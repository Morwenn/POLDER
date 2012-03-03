@echo off

REM Build all the debug and release libraries at once
REM Under Windows using MinGW

cd ..

echo Compiling the dynamic debug library...
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE="Debug" -DCOMPILE_MODE="Dynamic"
make

echo Compiling the static debug library...
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE="Debug" -DCOMPILE_MODE="Static"
make

echo Compiling the dynamic release library...
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCOMPILE_MODE="Dynamic"
make

echo Compiling the static release library...
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCOMPILE_MODE="Static"
make

echo Done
