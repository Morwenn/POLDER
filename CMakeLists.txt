# Version
cmake_minimum_required(VERSION 2.6)

# The project
project(POLDER)

# .a output directory
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# Headers
include_directories(
	include
)

# Source files
file(
	GLOB_RECURSE
	source_files
	src/POLDER/*
	src/POLDER/geometry/*
	include/POLDER/*
	include/POLDER/geometry/*
)

# Library
add_library(
	POLDER STATIC
	${source_files}
)

# Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++0x -pedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
