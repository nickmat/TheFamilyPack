# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        utils/cdm/CMakeLists.txt
# Project:     cdManage: Common Data, Create and Management.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( UTILS_CDMANAGE_FILES
    cdmMain.cpp
)

add_executable( cdManage ${UTILS_CDMANAGE_FILES} )

target_link_libraries( cdManage PRIVATE reccl )
