# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        src/rc/CMakeLists.txt
# Project:     reccl: Manage the rec lib command line interface functions.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( SRC_RECCL_FILES
    reccl.cpp
)

add_library( reccl ${SRC_RECCL_FILES} )

target_link_libraries( reccl PUBLIC rec )
