# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        utils/cdb/CMakeLists.txt
# Project:     cdBuild: Common Data, Build Database files.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( UTILS_CDBUILD_FILES
    cdbMain.cpp
)

add_executable( cdBuild ${UTILS_CDBUILD_FILES} )

target_link_libraries( cdBuild PRIVATE reccl )
