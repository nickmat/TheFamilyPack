/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recGallery.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Gallery record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018..2022, Nick Matthews.
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

class recGallery : public recDbT<recGallery>
{
public:
    static constexpr const char* s_tablename = "Gallery";

    recGallery() {}
    recGallery( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recGallery( const recGallery& source );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recGallery& r2 ) const;

    wxString FGetTitle() const { return f_title; }
    wxString FGetNote() const { return f_note; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt galID ) { return wxString::Format( "G" ID, galID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static recGalleryVec GetGalleries( const wxString& dbname = "Main" );

    static recMediaVec GetMediaVec( idt galID, const wxString& dbname = "Main" );
    recMediaVec GetMediaVec( const wxString& dbname = "Main" ) const {
        return GetMediaVec( f_id, dbname ); }

    static recGalleryMediaMediaVec GetGalleryMediaMediaVec(
        idt galID, const wxString& dbname = "Main" );
    recGalleryMediaMediaVec GetGalleryMediaMediaVec(
        const wxString& dbname = "Main" ) const {
        return GetGalleryMediaMediaVec( f_id, dbname ); }

private:
    wxString f_title;
    wxString f_note;
};


#endif // RECGALLERY_H
