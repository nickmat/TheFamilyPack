# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        tests/CMakeLists.txt
# Project:     cdBuild: Common Data, Build Database files.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( TESTS_FILES
    test.cpp
    cal/testCalendar.cpp
    rec/testDatabase.cpp
)

set( TESTS_HEADERS
    cppunit.h
    testprec.h
)

include_directories( ./ )
include_directories( ../3rdparty/CppUnit/include )

add_executable( tests ${TESTS_FILES} ${TESTS_HEADERS} )
target_compile_options( tests PRIVATE "-DWITH_CMAKE" )

target_link_libraries( tests PRIVATE cppunit reccl wx::net )
