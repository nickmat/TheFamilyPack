# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        3rdparty/wxsqlite3/CMakeLists.txt
# Project:     wxsqlite3: C++ wrapper around the SQLite3 C library.
# Author:      Nick Matthews (This file only)
# Website:     https://github.com/utelle/wxsqlite3
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     wxSQLite3: LGPL-3.0+ WITH WxWindows-exception-3.1
#              SQLite3: Public Domain
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( 3RDPARTY_WXSQLITE3_FILES
    sqlite3mc_amalgamation.c
    wxsqlite3.cpp
)

set( 3RDPARTY_WXSQLITE3_HEADERS
    sqlite3mc_amalgamation.h
    sqlite3mc_config.h
    ../../include/wx/wxsqlite3.h
    ../../include/wx/wxsqlite3_version.h
    ../../include/wx/wxsqlite3def.h
    ../../include/wx/wxsqlite3opt.h
)

add_library( wxsqlite3 ${3RDPARTY_WXSQLITE3_FILES} ${3RDPARTY_WXSQLITE3_HEADERS} )

target_link_libraries( wxsqlite3 PUBLIC wx::base )
