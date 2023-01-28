/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/recHelper.cpp
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     General helper classes and functions
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     30th April 2013
 * Copyright:   Copyright (c) 2013..2023, Nick Matthews.
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <rec/recHelper.h>

#include <wx/tokenzr.h>

#include <fstream>
#include <random>
#include <sstream>
#include <iomanip>

idt recGetID( const wxString& str )
{
    idt id = 0;
    str.ToLongLong( &id );
    return id;
}

idt recGetID( const std::string& str )
{
    if( str.empty() ) {
        return 0;
    }
    return strtoll( str.c_str(), nullptr, 10 );
}

idt recGetID( const char* str )
{
    return strtoll( str, nullptr, 10 );
}

bool recGetID( const std::string& str, idt* id )
{
    if( id == nullptr ) {
        return false;
    }
    if( !str.empty() ) {
        char ch = *str.begin();
        if( isdigit( ch ) || ch == '-' ) {
            *id = strtoll( str.c_str(), nullptr, 10 );
            return true;
        }
    }
    *id = 0;
    return false;
}

std::string stdStr_tolower( const std::string& str )
{
    std::string s( str );
    std::transform(
        s.begin(), s.end(), s.begin(),
        []( unsigned char c ) { return std::tolower( c ); }
    );
    return s;
}

std::string stdStr_toupper( const std::string& str )
{
    std::string s( str );
    std::transform(
        s.begin(), s.end(), s.begin(),
        []( unsigned char c ) { return std::toupper( c ); }
    );
    return s;
}

bool recGetIDs( const wxString& str, idt* id1, idt* id2, idt* id3 )
{
    if( id1 == nullptr || id2 == nullptr ) return false;
    *id1 = recGetID( str );
    size_t pos = str.find( ',' );
    if( pos == wxString::npos ) {
        *id2 = 0;
        if( id3 ) {
            *id3 = 0;
        }
    } else {
        *id2 = recGetID( str.substr( pos + 1 ) );
        if( id3 ) {
            pos = str.find( ',', pos + 1 );
            if( pos != wxString::npos ) {
                *id3 = recGetID( str.substr( pos + 1 ) );
            } else {
                *id3 = 0;
            }
        }
    }
    return true;
}

// The string can be formatted in one of 3 ways,
// 1)  nnn,nnn   Number followed by number, meaning depends on context. recSplitStrRet::number
// 2)  nnn:Ann   Number follows by Associate id number.                 recSplitStrRet::associate                   
// 3)  nnn,aaaa  Number folloed by text name of attached database       recSplitStrRet::text
recSplitStrRet recSplitStr( const wxString& str, idt* id1, idt* id2, wxString* dbname )
{
    *id1 = recGetID( str );
    size_t pos = str.find( ":A" );
    if( pos != wxString::npos ) {
        *id2 = recGetID( str.substr( pos + 2 ) );
        return recSplitStrRet::associate;
    }
    pos = str.find( "," );
    if( pos != wxString::npos ) {
        *id2 = recGetID( str.substr( pos + 1 ) );
        if( *id2 != 0 ) {
            return recSplitStrRet::number;
        }
        *dbname = str.substr( pos + 1 );
        return recSplitStrRet::text;
    }
    if( *id1 != 0 ) {
        *id2 = 0;
        *dbname = "main";
        return recSplitStrRet::text;
    }
    return recSplitStrRet::none;
}

wxString recGetSexStr( Sex sex )
{
    static wxString sexarray[] = {
        _( "Unstated" ), _( "Male" ), _( "Female" ), _( "Unknown" )
    };
    return sexarray[static_cast<size_t>(sex)];
}

wxString recGetTextStyleName( recTextStyle style )
{
    static wxString stylearray[] = {
        _( "Normal" ), _( "Bold" ), _( "Italic" ), _( "Bold Italic" )
    };
    return stylearray[static_cast<size_t>(style)];
}

std::string recStyleHTMLifyStr( const wxString& str, recTextStyle style )
{
    std::string htm = recHTMLifyStr( str );
    switch( style )
    {
    case recTextStyle::bold:
        return "<b>" + htm + "</b>";
    case recTextStyle::italic:
        return "<i>" + htm + "</i>";
    case recTextStyle::bolditalic:
        return "<b><i>" + htm + "</i></b>";
    }
    return htm;
}

std::string recHTMLifyStr( const wxString& str )
{
    std::string htm;
    for( auto it = str.begin() ; it != str.end() ; it++ ) {
        switch( (*it).GetValue() )
        {
        case '\n':
            htm += "<br>";
            break;
        case '&':
            htm += "&amp;";
            break;
        case '<':
            htm += "&lt;";
            break;
        case '>':
            htm += "&gt;";
            break;
        default:
            htm += *it;
        }
    }
    return htm;
}

bool recCheckIDsAreEqual( const recCheckIdVec& ids )
{
    for( size_t i = 0 ; i < ids.size() ; i++ ) {
        if( ids[i].GetFirstID() == 0 || ids[i].GetSecondID() == 0 ) {
            return false;
        }
    }
    return true;
}

bool recCheckIDsHaveAdditionalFirst( const recCheckIdVec& ids )
{
    for( size_t i = 0 ; i < ids.size() ; i++ ) {
        if( ids[i].GetSecondID() == 0 ) {
            return true;
        }
    }
    return false;
}

bool recCheckIDsHaveAdditionalSecond( const recCheckIdVec& ids )
{
    for( size_t i = 0 ; i < ids.size() ; i++ ) {
        if( ids[i].GetFirstID() == 0 ) {
            return true;
        }
    }
    return false;
}

idt recIdFromStr( const wxString& prefix, const wxString idStr )
{
    size_t psize = prefix.size();
    if( idStr.size() <= psize ) {
        return 0;
    }
    if( idStr.compare( 0, psize, prefix ) != 0 ) {
        return 0;
    }
    return recGetID( idStr.substr( psize ) );
}

std::string recConfToStr( double conf )
{
    std::stringstream ss, ss2;
    double d = conf * 100.0;
    ss2 << d;
    ss << std::setprecision(4) << d << "%";
    return ss.str();
}

double recConfFromStr( const std::string& str )
{
    double conf = std::stod( str );
    return conf / 100;
}

recIdVec recIdVecFromStr( const wxString& prefix, const wxString list )
{
    recIdVec vec;
    wxStringTokenizer tk( list, ", ", wxTOKEN_STRTOK );

    while ( tk.HasMoreTokens() ) {
        wxString idStr = tk.GetNextToken();
        idt id = recIdFromStr( prefix, idStr );
        if( id ) {
            vec.push_back( id );
        }
    }
    return vec;
}

void recIdVecAddIfUnique( recIdVec& vec, idt id )
{
    if( id == 0 ) {
        return;
    }
    for( size_t i = 0 ; i < vec.size() ; i++ ) {
        if( vec[i] == id ) {
            return;
        }
    }
    vec.push_back( id );
}

wxString GetBlobFormatStr( const wxMemoryBuffer& buf )
{
    static const char* const lut = "0123456789ABCDEF";
    unsigned char* cp = static_cast<unsigned char*>( buf.GetData() );
    wxString str;
    str.reserve( buf.GetDataLen() * 2 + 1 );
    for ( size_t i = 0; i < buf.GetDataLen(); i++ ) {
        str += lut[cp[i] >> 4];
        str += lut[cp[i] & 15];
    }
    return str;
}

std::string recTextFileRead( const std::string& filename )
{
    std::ifstream file( filename );
    std::string str;
    if( file ) {
        std::ostringstream ss;
        ss << file.rdbuf();
        str = ss.str();
    }
    return str;
}

bool recTextFileWrite( const std::string& filename, std::string& content )
{
    std::ofstream ofile( filename, std::ios::trunc );
    if( !ofile ) {
        return false;
    }
    ofile << content;
    return true;
}

std::istream& recCsvRead( std::istream& in, std::string& str )
{
    str.clear();
    char ch;
    in.get( ch );
    if( ch != '"' ) {
        // All strings must be quoted.
        in.setstate( std::ios::failbit );
        return in;
    }
    bool inquotes = true;
    for( ;;) {
        in.get( ch );
        if( ch == '"' ) {
            in.get( ch );
            if( ch != '"' ) {
                break;
            }
        }
        if( in.eof() ) {
            in.setstate( std::ios::failbit );
            break;
        }
        str.push_back( ch );
    }
    if( !in.eof() ) {
        if( ch != '\n' && ch != ',' ) {
            in.setstate( std::ios::failbit );
        }
    }
    return in;
}

std::istream& recCsvRead( std::istream& in, wxString& str )
{
    std::string stdstr;
    recCsvRead( in, stdstr );
    str = stdstr;
    return in;
}

std::istream& recCsvRead( std::istream& in, idt& id )
{
    std::string str;
    char ch;
    for( ;;) {
        in.get( ch );
        if( ch == ',' || ch == '\n' || in.eof() || !in ) {
            break;
        }
        str.push_back( ch );
    }
    id = recGetID( str );
    return in;
}

std::istream& recCsvRead( std::istream& in, int& num )
{
    idt id;
    recCsvRead( in, id );
    num = (int)id;
    return in;
}

std::istream& recCsvRead( std::istream& in, unsigned& num )
{
    idt id;
    recCsvRead( in, id );
    num = (unsigned)id;
    return in;
}

std::istream& recCsvRead( std::istream& in, long& num )
{
    idt id;
    recCsvRead( in, id );
    num = (long)id;
    return in;
}

std::istream& recCsvRead( std::istream& in, double& dbl )
{
    std::string str;
    char ch;
    for( ;;) {
        in.get( ch );
        if( ch == ',' || ch == '\n' || in.eof() || !in ) {
            break;
        }
        str.push_back( ch );
    }
    dbl = std::stod( str );
    return in;
}

std::ostream& recCsvWrite( std::ostream& out, const std::string& str, char term )
{
    out.put( '"' );
    for( auto ch : str ) {
        if( ch == '"' ) {
            out.put( '"' );
        }
        out.put( ch );
    }
    out.put( '"' );
    out.put( term );
    return out;
}

std::ostream& recCsvWrite( std::ostream& out, const wxString& str, char term )
{
    return recCsvWrite( out, str.ToStdString(), term );
}

std::ostream& recCsvWrite( std::ostream& out, idt id, char term )
{
    out << id << term;
    return out;
}

std::ostream& recCsvWrite( std::ostream& out, int num, char term )
{
    out << num << term;
    return out;
}

std::ostream& recCsvWrite( std::ostream& out, unsigned num, char term )
{
    out << num << term;
    return out;
}

std::ostream& recCsvWrite( std::ostream& out, double num, char term )
{
    out << num << term;
    return out;
}

static wxString ucharToHex( unsigned char num )
{
    return wxString::Format( "%02X", num );
}

wxString recCreateUid()
{
    wxString uid;
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> dis( 0, 255 );
    unsigned char num = 0;
    unsigned char checkA = 0;
    unsigned char checkB = 0;
    for( auto i = 0; i < 16; i++ ) {
        num = static_cast<unsigned char>(dis( gen ));
        wxString hex = ucharToHex( num );
        uid += hex;
        checkA += num;
        checkB += checkA;
    }
    uid += ucharToHex( checkA );
    uid += ucharToHex( checkB );
    return uid;
}

bool recCheckUid( const wxString& uid )
{
    if( uid.size() != 36 ) {
        return false;
    }
    unsigned char num = 0;
    unsigned char checkA = 0;
    unsigned char checkB = 0;
    long val = 0;
    for( size_t pos = 0; pos < 32; pos++, pos++ ) {
        uid.substr( pos, 2 ).ToLong( &val, 16 );
        num = static_cast<unsigned char>( val );
        checkA += num;
        checkB += checkA;
    }
    wxString check = ucharToHex( checkA );
    check += ucharToHex( checkB );
    wxString uidcheck = uid.substr( 32, 4 );
    return check.compare( uidcheck ) == 0;
}

recRecordId recGetRecordId( const std::string& str )
{
    size_t pos = 0;
    for( auto ch : str ) {
        if( isalpha( ch ) ) pos++;
        else break;
    }
    recRecordId rid;
    for( size_t i = 0; i < recTablesSize; i++ ) {
        if( str.compare( 0, pos, recTablePrefixes[i] ) == 0 ) {
            rid.table = static_cast<recTable>(i);
            break;
        }
    }
    rid.id = recGetID( str.substr( pos, std::string::npos ) );
    return rid;
}

recRecordIdVec recGetRecordIDs( const wxString& str )
{
    recRecordIdVec rids;
    std::string records = std::string( str ) + ' ';
    std::string s;
    for( auto ch : records ) {
        if( ch == ' ' ) {
            recRecordId rid = recGetRecordId( s );
            rids.push_back( rid );
            s.clear();
        }
        else {
            s += ch;
        }
    }
    return rids;
}


// End of src/rec/recHelper.cpp file
