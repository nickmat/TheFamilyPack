# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        src/rec/CMakeLists.txt
# Project:     rec: The Family Pack database handling library.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( SRC_REC_FILES
    recAssociate.cpp
    recCitation.cpp
    recContact.cpp
    recCsv.cpp
    recDatabase.cpp
    recDate.cpp
    recEvent.cpp
    recEventa.cpp
    recEventaPersona.cpp
    recEventEventa.cpp
    recEventType.cpp
    recEventTypeRole.cpp
    recFamEvent.cpp
    recFamEventa.cpp
    recFamily.cpp
    recFamilyIndividual.cpp
    recFamIndEventa.cpp
    recFilterEvent.cpp
    recGallery.cpp
    recGalleryMedia.cpp
    recGedExport.cpp
    recGedParse.cpp
    recHelper.cpp
    recIndEvent.cpp
    recIndividual.cpp
    recIndPersona.cpp
    recMedia.cpp
    recMediaData.cpp
    recName.cpp
    recPersona.cpp
    recPlace.cpp
    recReference.cpp
    recResearcher.cpp
    recSystem.cpp
    recUser.cpp
    recUpgrade.cpp
    recVersion.cpp
)

set( SRC_REC_HEADERS
    recDatabaseCreate.h
    ../../include/rec/recAssociate.h
    ../../include/rec/recCitation.h
    ../../include/rec/recContact.h
    ../../include/rec/recCsv.h
    ../../include/rec/recDatabase.h
    ../../include/rec/recDate.h
    ../../include/rec/recDb.h
    ../../include/rec/recDefs.h
    ../../include/rec/recEvent.h
    ../../include/rec/recEventa.h
    ../../include/rec/recEventaPersona.h
    ../../include/rec/recEventEventa.h
    ../../include/rec/recEventType.h
    ../../include/rec/recEventTypeRole.h
    ../../include/rec/recFamEvent.h
    ../../include/rec/recFamEventa.h
    ../../include/rec/recFamily.h
    ../../include/rec/recFamilyIndividual.h
    ../../include/rec/recFamIndEventa.h
    ../../include/rec/recFilterEvent.h
    ../../include/rec/recGallery.h
    ../../include/rec/recGalleryMedia.h
    ../../include/rec/recGedExport.h
    ../../include/rec/recGedParse.h
    ../../include/rec/recHelper.h
    ../../include/rec/recIndEvent.h
    ../../include/rec/recIndividual.h
    ../../include/rec/recInterface.h
    ../../include/rec/recIndPersona.h
    ../../include/rec/recMedia.h
    ../../include/rec/recMediaData.h
    ../../include/rec/recName.h
    ../../include/rec/recPersona.h
    ../../include/rec/recPlace.h
    ../../include/rec/recReference.h
    ../../include/rec/recResearcher.h
    ../../include/rec/recSystem.h
    ../../include/rec/recUser.h
    ../../include/rec/recVersion.h
)

add_library( rec ${SRC_REC_FILES} ${SRC_REC_HEADERS} ${INCLUDE_REC_HEADERS} )

target_link_libraries( rec PUBLIC calendar wxsqlite3 wx::core )
