# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        src/tfp/CMakeLists.txt
# Project:     The Family Pack: Genealogy data storage and display program.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( SRC_TFP_FILES
    tfpApp.cpp
    tfpExportGed.cpp
    tfpFrame.cpp
    tfpMemory.cpp
    tfpNote.cpp
    tfpRdGed.cpp
    tfpVersion.cpp
    tfpWr.cpp
    tfpWrAdmin.cpp
    tfpWrArchive.cpp
    tfpWrChart.cpp
    tfpWrEvent.cpp
    tfpWrEventa.cpp
    tfpWrEventaIndex.cpp
    tfpWrEventIndex.cpp
    tfpWrFamily.cpp
    tfpWrGallery.cpp
    tfpWrIndividual.cpp
    tfpWrMedia.cpp
    tfpWrName.cpp
    tfpWrNotes.cpp
    tfpWrPersona.cpp
    tfpWrReference.cpp
)

set( SRC_TFP_HEADERS
    tfpApp.h
    tfpExport.h
    tfpFrame.h
    tfpMemory.h
    tfpNote.h
    tfpRd.h
    tfpText.h
    tfpVersion.h
    tfpWr.h
)

set( SRC_TFP_RCS
    tfp.rc
)

include_directories( ../ )

add_executable( tfp WIN32 MACOSX_BUNDLE ${SRC_TFP_FILES} ${SRC_TFP_HEADERS} ${SRC_TFP_RCS} )

target_link_libraries( tfp PRIVATE recgui )
