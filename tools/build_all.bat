REM Build all the debug and release libraries at once
REM Under Windows using MinGW

cd ..
del CMakeCache.txt
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
make
del CMakeCache.txt
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
make