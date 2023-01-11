# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        test/ru/CMakeLists.txt
# Project:     recUnit: Unit test program for the rec library.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     10th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( TEST_RECUNIT_FILES
    ruMain.cpp
    ruTables.cpp
    ruTransfer.cpp
)

set( TEST_RECUNIT_HEADERS
    ../../include/catch2/catch.hpp
    ruMain.h
)

add_executable( recunit ${TEST_RECUNIT_FILES} ${TEST_RECUNIT_HEADERS} )

target_link_libraries( recunit PRIVATE reccl )
