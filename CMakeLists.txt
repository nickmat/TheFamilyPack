# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        CMakeLists.txt
# Project:     The Family Pack: Genealogy data storage and display program.
# Purpose:     Primary CMake for The Family Pack
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# NOTE: This build system is still being tested,
# but seems to work well under Windows.
# Untested on other operating systems.

cmake_minimum_required( VERSION 3.25 )

project( tfp )

option( BUILD_SHARED_LIBS "Set static libs" OFF )
include_directories( include )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

add_subdirectory( 3rdparty/CppUnit/src/cppunit )
add_subdirectory( 3rdparty/pugixml )
add_subdirectory( 3rdparty/wxWidgets )
add_subdirectory( 3rdparty/wxsqlite3 )

add_subdirectory( src/cal )
add_subdirectory( src/rc )
add_subdirectory( src/rec )
add_subdirectory( src/rg )
add_subdirectory( src/tfp )

add_subdirectory( utils/cal )
add_subdirectory( utils/cdb )
add_subdirectory( utils/cdm )
add_subdirectory( utils/doccore )

add_subdirectory( tests )

add_subdirectory( test/ru )
add_subdirectory( test/tdb )
