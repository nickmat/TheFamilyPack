# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        utils/docore/CMakeLists.txt
# Project:     doccore: Program to create webpage documenting common data.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( UTILS_DOCCORE_FILES
    dcMain.cpp
)

add_executable( doccore ${UTILS_DOCCORE_FILES} )

target_link_libraries( doccore PRIVATE reccl )
