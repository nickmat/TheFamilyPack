/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rg/rgEdGallery.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Edit database Image Gallery dialog header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     24 October 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

*/

#ifndef SRC_RG_RGEDGALLERY_H
#define SRC_RG_RGEDGALLERY_H

#include "fb/fbRgEditGallery.h"

#include <rec/recGallery.h>
#include <rec/recGalleryMedia.h>

//============================================================================
//                 rgDlgEditGallery dialog
//============================================================================

class rgDlgEditGallery : public fbRgEditGallery
{
    enum Page {
        PAGE_Note, PAGE_Images
    };
    enum ImageColumns {
        IC_id, IC_title, IC_MAX
    };

public:
    rgDlgEditGallery( wxWindow* parent, idt galID );

    bool IsGalIdOk( idt galID );

private:
    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    void UpdateMediaList( idt medID = 0 );

    // Virtual event handlers, overide them in your derived class
    void OnMediaAddButton( wxCommandEvent& event ) override;
    void OnAddNewMedia( wxCommandEvent& event ) override;
    void OnAddExistingMedia( wxCommandEvent& event ) override;
    void OnMediaEditButton( wxCommandEvent& event ) override;
    void OnMediaRemoveButton( wxCommandEvent& event ) override;
    void OnMediaUpButton( wxCommandEvent& event ) override;
    void OnMediaDownButton( wxCommandEvent& event ) override;
    void OnViewImage( wxCommandEvent& event ) override;

    recGallery              m_gallery;
    recGalleryMediaMediaVec m_gmms;
};

#endif // SRC_RG_RGEDGALLERY_H
