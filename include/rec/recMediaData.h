/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recMediaData.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 MediaData record header.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     19th September 2018
 * Copyright:   Copyright (c) 2018 ~ 2019, Nick Matthews.
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

#ifndef RECMEDIADATA_H
#define RECMEDIADATA_H

#include <rec/recDatabase.h>

class recMediaData : public recDb
{
public:
    enum class Mime { null_mime, image_png, image_jpeg, image_gif };

    recMediaData() {}
    recMediaData( idt id ) : recDb( id ) { Read(); }
    recMediaData( idt id, idt assID ) { ReadID( id, assID ); }
    recMediaData( const wxString dbname, idt id ) : recDb( id ) { Read( dbname ); }
    recMediaData( const recMediaData& md );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool ReadID( idt id, idt assID );
    TABLE_NAME_MEMBERS( "MediaData" );
    bool Equivalent( const recMediaData& r2 ) const;

    wxString FGetTitle() const { return f_title; }
    wxMemoryBuffer FGetData() const { return f_data; }
    Mime FGetType() const { return f_type; }
    int FGetPrivacy() const { return f_privacy; }
    wxString FGetCopyright() const { return f_copyright; }
    wxString FGetFile() const { return f_file; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetData( const wxMemoryBuffer& data ) { f_data = data; }
    void FSetType( Mime type ) { f_type = type; }
    void FSetPrivacy( int privacy ) { f_privacy = privacy; }
    void FSetCopyright( const wxString& copyright ) { f_copyright = copyright; }
    void FSetFile( const wxString& file ) { f_file = file; }

    static wxString GetIdStr( idt medID ) { return wxString::Format( "MD" ID, medID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    static wxString GetFileName( const wxString& assDb, idt mdID );

    static idt FindMedia( idt mdID, idt assID );
    idt FindMedia( idt assID ) const { return FindMedia( f_id, assID ); }

    bool ImportData( wxString& filename );

    static wxSQLite3Table GetMediaDataList( const wxString& dbname = "Main" );

private:
    wxString       f_title;
    wxMemoryBuffer f_data;
    Mime           f_type;
    int            f_privacy;
    wxString       f_copyright;
    wxString       f_file;
};

inline bool operator==( const recMediaData& r1, const recMediaData& r2 )
{
    return r1.Equivalent( r2 ) && r1.EqualID( r2 );
}

inline bool operator!=( const recMediaData& r1, const recMediaData& r2 )
{
    return !( r1 == r2 );
}

#endif // RECMEDIADATA_H
