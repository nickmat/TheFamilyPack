# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        test/tdb/CMakeLists.txt
# Project:     tdb: Create and Manage Test Database.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     10th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( TEST_TDB_FILES
    tdbMain.cpp
)

add_executable( tdb ${TEST_TDB_FILES} )

target_link_libraries( tdb PRIVATE reccl )
