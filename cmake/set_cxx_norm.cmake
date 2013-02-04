# Version
cmake_minimum_required(VERSION 2.6.3)

set(CXX_NORM_CXX98 1)   # C++98
set(CXX_NORM_CXX03 2)   # C++03
set(CXX_NORM_CXX11 3)   # C++11

# - Set the wanted C++ norm
# Adds the good argument to the command line in function of the compiler
macro(set_cxx_norm NORM)

    if(CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        if(${NORM} EQUAL ${CXX_NORM_CXX98})
            add_definitions("-std=c++98")
        elseif(${NORM} EQUAL ${CXX_NORM_CXX03})
            add_definitions("-std=c++03")
        elseif(${NORM} EQUAL ${CXX_NORM_CXX11})
            add_definitions("-std=c++11")
        endif()
    endif()

endmacro()
