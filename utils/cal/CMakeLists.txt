# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        utils/cal/CMakeLists.txt
# Project:     CalCalc: Program to test calendar (cal) library.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( UTILS_CAL_FILES
    calCalc.cpp
)

add_executable( calCalc ${UTILS_CAL_FILES} )

target_link_libraries( calCalc PRIVATE calendar )
