# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        src/cal/CMakeLists.txt
# Project:     calendar: A general purpose calendar library.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( SRC_CALENDAR_FILES
    calAstro.cpp
    calendar.cpp
    calFrench.cpp
    calGregorian.cpp
    calHebrew.cpp
    calIslamic.cpp
    calJulian.cpp
    calMath.cpp
    calParse.cpp
    calRecord.cpp
)

set( HDR_CALENDAR_FILES
    calAstro.h
    ../../include/cal/calendar.h
    calCommon.h
    calFrench.h
    calGregorian.h
    calHebrew.h
    calIslamic.h
    calJulian.h
    calMath.h
    calParse.h
    calRecord.h
)

add_library( calendar ${SRC_CALENDAR_FILES} ${HDR_CALENDAR_FILES} )

target_link_libraries( calendar PUBLIC wx::base )
