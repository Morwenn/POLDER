# Version
cmake_minimum_required(VERSION 2.6)

# .a output directory
set(LIBRARY_OUTPUT_PATH lib/)

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

# Check the build type
if (NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

	# Create the projects
	project(polder-d)
	project(polder-d-s)

	# polder-d.dll and libpolder-d.a
	add_library(
		polder-d SHARED
		${source_files}
	)
	set_target_properties(polder-d PROPERTIES PREFIX "")
	set_target_properties(polder-d PROPERTIES IMPORT_SUFFIX ".a")

	# libpolder-d-s.a
	add_library(
		polder-d-s STATIC
		${source_files}
	)
	
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

	# Create the projects
	project(polder)
	project(polder-s)
	
	### Create the libraries ###

	# polder.dll and libpolder.a
	add_library(
		polder SHARED
		${source_files}
	)
	set_target_properties(polder PROPERTIES PREFIX "")
	set_target_properties(polder PROPERTIES IMPORT_SUFFIX ".a")

	# libpolder-s.a
	add_library(
		polder-s STATIC
		${source_files}
	)
	
endif()

# Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++0x -pedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
