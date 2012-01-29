REM Build all the debug and release libraries at once
REM Under Windows using MinGW

cd ..
del CMakeCache.txt
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCOMPILE_MODE=Dynamic
make
del CMakeCache.txt
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCOMPILE_MODE=Static
make
del CMakeCache.txt
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCOMPILE_MODE=Dynamic
make
del CMakeCache.txt
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCOMPILE_MODE=Static
make