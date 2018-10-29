/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recGallery.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Gallery record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
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

#ifndef RECGALLERY_H
#define RECGALLERY_H

#include <rec/recDatabase.h>
#include <rec/recMedia.h>

class recGallery;
using  recGalleryVec = std::vector< recGallery >;
class recGalleryMediaMedia;
using recGalleryMediaMediaVec = std::vector< recGalleryMediaMedia >;

class recGallery : public recDb
{
public:

    recGallery() {}
    recGallery( idt id ) : recDb( id ) { Read(); }
    recGallery( const recGallery& source );

    void Clear();
    void Save();
    bool Read();
    TABLE_NAME_MEMBERS( "Gallery" );
    bool Equivalent( const recGallery& r2 ) const;

    wxString FGetTitle() const { return f_title; }
    wxString FGetNote() const { return f_note; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt galID ) { return wxString::Format( "G" ID, galID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recGalleryVec GetGalleries();

    static recMediaVec GetMediaVec( idt galID );
    recMediaVec GetMediaVec() const { return GetMediaVec( f_id ); }

    static recGalleryMediaMediaVec GetGalleryMediaMediaVec( idt galID );
    recGalleryMediaMediaVec GetGalleryMediaMediaVec() const { return GetGalleryMediaMediaVec( f_id ); }

private:
    wxString f_title;
    wxString f_note;
};

inline bool operator==( const recGallery& r1, const recGallery& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recGallery& r1, const recGallery& r2 )
{
    return !( r1 == r2 );
}


#endif // RECGALLERY_H
