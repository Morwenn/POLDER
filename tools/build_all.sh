#!/build/sh

# Build all the debug and release libraries at once
# Under Linux

cd ..
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCOMPILE_MODE="Dynamic"
make
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCOMPILE_MODE="Static"
make
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCOMPILE_MODE="Dynamic"
make
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCOMPILE_MODE="Static"
make