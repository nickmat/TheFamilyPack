/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        include/rec/recGalleryMedia.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage the SQLite3 GalleryMedia record header.
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

#ifndef RECGALLERYMEDIA_H
#define RECGALLERYMEDIA_H

#include <rec/recDatabase.h>
#include <rec/recMedia.h>

class recGalleryMedia : public recDbT<recGalleryMedia>
{
public:
    static constexpr const char* s_tablename = "GalleryMedia";
    static constexpr recTable s_table = recTable::GalleryMedia;

    recGalleryMedia() : f_gal_id(0), f_med_id(0), f_med_seq(0) {}
    recGalleryMedia( idt id, const wxString& dbname = "Main" ) : recDbT( id ) { Read( dbname ); }
    recGalleryMedia( const recGalleryMedia& name );
    recGalleryMedia( idt galID, idt medID, const wxString& dbname = "Main" ) {
        ReadGalleryMedia( galID, medID, dbname ); }

    void Clear();
    void Save( const wxString& dbname = "Main" );
    bool Read( const wxString& dbname = "Main" );
    bool Equivalent( const recGalleryMedia& r2 ) const;

    wxString FGetTitle() const { return f_title; }
    idt FGetGalID() const { return f_gal_id; }
    idt FGetMedID() const { return f_med_id; }
    int FGetMedSeq() const { return f_med_seq; }

    void FSetTitle( const wxString& title ) { f_title = title; }
    void FSetGalID( idt galID ) { f_gal_id = galID; }
    void FSetMedID( idt medID ) { f_med_id = medID; }
    void FSetMedSeq( int seq ) { f_med_seq = seq; }

    bool ReadGalleryMedia( idt galID, idt medID, const wxString& dbname = "Main" );

    void SetNextMedSequence( idt galID, const wxString& dbname = "Main" );

    static wxString GetTitle( idt galID, idt medID, const wxString& dbname = "Main" );

    static std::string CsvTitles();
    static void CsvWrite( std::ostream& out, idt id );
    bool CsvRead( std::istream& in );

private:
    wxString f_title;
    idt      f_gal_id;
    idt      f_med_id;
    int      f_med_seq;
};


using  recGalleryMediaVec = std::vector< recGalleryMedia >;

class recGalleryMediaMedia
{
public:
    recGalleryMediaMedia() : m_gm( 0 ), m_med( 0 ) {}
    recGalleryMediaMedia( idt galID, idt medID, const wxString& dbname = "Main" )
        : m_gm( galID, medID, dbname ), m_med( medID, dbname ) {}

    recGalleryMedia& GetGalleryMedia() { return m_gm; }
    recMedia& GetMedia() { return m_med; }

    idt GetMedID() const { return m_med.FGetID(); }
    wxString GetMedIdStr() const { return m_med.GetIdStr(); }
    wxString GetTitle() const;

private:
    recGalleryMedia m_gm;
    recMedia        m_med;
};

#endif // RECGALLERYMEDIA_H
