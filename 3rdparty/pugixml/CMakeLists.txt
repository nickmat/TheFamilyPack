# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        3rdparty/pugixml/CMakeLists.txt
# Project:     pugixml: C++ XML processing library.
# Author:      Nick Matthews (This file only)
# Website:     https://pugixml.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     MIT
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( PUGIXML_FILES
    pugixml.cpp
)

set( PUGIXML_HEADERS
    ../../include/pugixml/pugiconfig.hpp
    ../../include/pugixml/pugixml.hpp
)

include_directories( ../../include/pugixml )

add_library( pugixml ${PUGIXML_FILES} ${PUGIXML_HEADERS} )
