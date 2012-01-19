# Version
cmake_minimum_required(VERSION 2.6)

# The projects
project(polder)
project(polder-s)
# project(polder-d) # TODO
# project(polder-d-s) # TODO

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

# Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++0x -pedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()


### Create the libraries ###

# polder.dll and libpolder.a
add_library(
	polder SHARED
	${source_files}
)
set_target_properties(polder PROPERTIES PREFIX "")				# libpolder.dll 	--> polder.dll
set_target_properties(polder PROPERTIES IMPORT_SUFFIX ".a")		# libpolder.dll.a 	--> libpolder.a

# libpolder-s.a
add_library(
	polder-s STATIC
	${source_files}
)
