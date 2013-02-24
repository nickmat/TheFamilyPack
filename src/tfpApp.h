/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        tfpApp.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Program App class
 * Author:      Nick Matthews
 * Modified by:
 * Created:     24 September 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
 * Website:     http://thefamilypack.org
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

#ifndef TFPAPP_H
#define TFPAPP_H

class wxWebViewHandler;
class wxWebViewFSHandler;

//! The application class. As required by wxWidgets.
class TfpApp : public wxApp
{
private:
    wxSharedPtr<wxWebViewHandler> m_webviewFSHandler;

public:
    TfpApp() {}
    virtual bool OnInit();
    virtual int OnExit();

    wxSharedPtr<wxWebViewHandler> GetWebViewFSHandler() { return m_webviewFSHandler; }
};

wxDECLARE_APP( TfpApp );

extern wxSharedPtr<wxWebViewHandler> GetWebViewMemoryHandler();

#endif // TFPAPP_H

