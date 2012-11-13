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
	src/*
	include/*
)

# Check the build type
if (NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

	if(COMPILE_MODE STREQUAL "Dynamic") # Build a dll
		
		project(polder-d)
		
		# Define POLDER_DYNAMIC and POLDER_EXPORTS
		add_definitions(-DPOLDER_DYNAMIC -DPOLDER_EXPORTS)
		
		# polder-d.dll and libpolder-d.a
		add_library(
			polder-d SHARED
			${source_files}
		)
		set_target_properties(polder-d PROPERTIES PREFIX "")
		set_target_properties(polder-d PROPERTIES IMPORT_SUFFIX ".a")
		
	elseif(COMPILE_MODE STREQUAL "Static") # Build a static library
	
		project(polder-d-s)
		
		# libpolder-d-s.a
		add_library(
			polder-d-s STATIC
			${source_files}
		)
	
	endif()
	
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

	if(COMPILE_MODE STREQUAL "Dynamic") # Build a dll
		
		project(polder)
		
		# Define POLDER_DYNAMIC and POLDER_EXPORTS
		add_definitions(-DPOLDER_DYNAMIC -DPOLDER_EXPORTS)
		
		# polder.dll and libpolder.a
		add_library(
			polder SHARED
			${source_files}
		)
		set_target_properties(polder PROPERTIES PREFIX "")
		set_target_properties(polder PROPERTIES IMPORT_SUFFIX ".a")
		
	elseif(COMPILE_MODE STREQUAL "Static") # Build a static library
	
		project(polder-s)
		
		# libpolder-s.a
		add_library(
			polder-s STATIC
			${source_files}
		)
	
	endif()
	
endif()

# Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic -Wall")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
