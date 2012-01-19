#!/build/sh

# Build all the debug and release libraries at once
# Under Linux

cd ..
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
make
rm -f CMakeCache.txt
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make