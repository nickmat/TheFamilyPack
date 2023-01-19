# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Name:        src/rg/CMakeLists.txt
# Project:     recgui: Manage the rec lib wxWigets GUI functions and dialogs.
# Author:      Nick Matthews
# Website:     http://thefamilypack.org
# Created:     9th January 2023
# Copyright:   Copyright (c) 2023, Nick Matthews.
# Licence:     GNU GPLv3
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( SRC_RG_FILES
    fb/fbRgEditAssociate.cpp
    fb/fbRgEditCitation.cpp
    fb/fbRgEditContact.cpp
    fb/fbRgEditDate.cpp
    fb/fbRgEditEventa.cpp
    fb/fbRgEditEventRole.cpp
    fb/fbRgEditGallery.cpp
    fb/fbRgEditMedia.cpp
    fb/fbRgEditName.cpp
    fb/fbRgEditPersona.cpp
    fb/fbRgEditPlace.cpp
    fb/fbRgEditReference.cpp
    fb/fbRgEditResearcher.cpp
    fb/fbRgSelect.cpp
    fb/fbRgSetupDatabase.cpp
    fb/fbRgSetupReference.cpp
    fb/fbRgViewMedia.cpp
    fbRgDialog.cpp
    recgui.cpp
    rgAssociate.cpp
    rgCompareEvent.cpp
    rgCrIndividual.cpp
    rgCrName.cpp
    rgEdCitation.cpp
    rgEdCitPart.cpp
    rgEdCitPartType.cpp
    rgEdContact.cpp
    rgEdDate.cpp
    rgEdEvent.cpp
    rgEdEventa.cpp
    rgEdEventEventa.cpp
    rgEdEventType.cpp
    rgEdFamily.cpp
    rgEdGallery.cpp
    rgEdIndividual.cpp
    rgEdMedia.cpp
    rgEdName.cpp
    rgEdNamePart.cpp
    rgEdNamePartType.cpp
    rgEdNameStyle.cpp
    rgEdPerIndEvent.cpp
    rgEdPersona.cpp
    rgEdPlace.cpp
    rgEdReference.cpp
    rgEdRelDate.cpp
    rgEdRepository.cpp
    rgEdResearcher.cpp
    rgEdRole.cpp
    rgEdSystem.cpp
    rgEdUser.cpp
    rgImagePanel.cpp
    rgIndividual.cpp
    rgRefTemplate.cpp
    rgSelect.cpp
    rgSelEvent.cpp
    rgSetupDatabase.cpp
    rgSetupReference.cpp
    rgTableCtrl.cpp
    rgTransfer.cpp
    rgViewMedia.cpp
)

set( SRC_RG_HEADERS
    ../../include/rg/rgCompareEvent.h
    ../../include/rg/rgDialogs.h
    ../../include/rg/rgImagePanel.h

    fb/fbRgEditAssociate.h
    fb/fbRgEditCitation.h
    fb/fbRgEditContact.h
    fb/fbRgEditDate.h
    fb/fbRgEditEventa.h
    fb/fbRgEditEventRole.h
    fb/fbRgEditGallery.h
    fb/fbRgEditMedia.h
    fb/fbRgEditName.h
    fb/fbRgEditPersona.h
    fb/fbRgEditPlace.h
    fb/fbRgEditReference.h
    fb/fbRgEditResearcher.h
    fb/fbRgSelect.h
    fb/fbRgSetupDatabase.h
    fb/fbRgSetupReference.h
    fb/fbRgViewMedia.h

    fbRgDialog.h
    rgAssociate.h
    rgCrIndividual.h
    rgCrName.h
    rgEdCitation.h
    rgEdCitPart.h
    rgEdCitPartType.h
    rgEdContact.h
    rgEdDate.h
    rgEdEvent.h
    rgEdEventa.h
    rgEdEventEventa.h
    rgEdEventType.h
    rgEdFamily.h
    rgEdGallery.h
    rgEdIndividual.h
    rgEdMedia.h
    rgEdName.h
    rgEdNamePart.h
    rgEdNamePartType.h
    rgEdNameStyle.h
    rgEdPerIndEvent.h
    rgEdPersona.h
    rgEdPlace.h
    rgEdReference.h
    rgEdRelDate.h
    rgEdRepository.h
    rgEdResearcher.h
    rgEdRole.h
    rgEdSystem.h
    rgEdUser.h
    rgRefTemplate.h
    rgSelect.h
    rgSelEvent.h
    rgSetupDatabase.h
    rgSetupReference.h
    rgTableCtrl.h
    rgViewMedia.h
)

add_library( recgui ${SRC_RG_FILES} ${SRC_RG_HEADERS} )

target_link_libraries( recgui PUBLIC pugixml rec wx::webview )
