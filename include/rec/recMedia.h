/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recMedia.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 Media record header.
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

#ifndef RECMEDIA_H
#define RECMEDIA_H

#include <rec/recDatabase.h>

class recMedia;
using  recMediaVec = std::vector< recMedia >;

class recMedia : public recDbT<recMedia>
{
public:
    static constexpr const char* s_tablename = "Media";

    recMedia() : f_data_id(0), f_ass_id(0), f_ref_id(0),
        f_ref_seq(0), f_privacy(0) {}
    recMedia( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recMedia( const recMedia& name );

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recMedia& r2 ) const;

    idt FGetDataID() const { return f_data_id; }
    idt FGetAssID() const { return f_ass_id; }
    idt FGetRefID() const { return f_ref_id; }
    int FGetRefSeq() const { return f_ref_seq; }
    int FGetPrivacy() const { return f_privacy; }
    wxString FGetTitle() const { return f_title; }
    wxString FGetNote() const { return f_note; }

    void FSetDataID( idt dataID ) { f_data_id = dataID; }
    void FSetAssID( idt assID ) { f_ass_id = assID; }
    void FSetRefID( idt refID ) { f_ref_id = refID; }
    void FSetRefSeq( int refseq ) { f_ref_seq = refseq; }
    void FSetPrivacy( int privacy ) { f_privacy = privacy; }
    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetNote( const wxString& note ) { f_note = note; }

    static wxString GetIdStr( idt medID ) { return wxString::Format( "M" ID, medID ); }
    wxString GetIdStr() const { return GetIdStr( f_id ); }

    wxString GetDataIdStr() const { return wxString::Format( "A" ID ":MD" ID, f_ass_id, f_data_id ); }
    static wxString GetDataIdStr( idt medID, const wxString& dbname = "Main" ) {
        recMedia med( medID, dbname ); return med.GetDataIdStr(); }

    static idt Create( idt mdID, idt assID, idt refID );
    static int GetNextRefSeq( idt refID );

    static wxString GetTitle( idt medID, const wxString& dbname = "Main" );

    static wxSQLite3Table GetMediaList( const wxString& dbname = "Main" );
    static wxSQLite3Table GetMediaList( idt offset, int limit, const wxString& dbname = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    idt      f_data_id;
    idt      f_ass_id;
    idt      f_ref_id;
    int      f_ref_seq;
    int      f_privacy;
    wxString f_title;
    wxString f_note;
};

#endif // RECMEDIA_H
