/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010 .. 2022, Nick Matthews.
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

#ifndef RECDATABASE_H
#define RECDATABASE_H

#include <rec/recHelper.h>
#include <rec/recInterface.h>

extern void recInitialize();
extern void recUninitialize();

class recDb
{
public:
    enum class DbType {
        db_null,
        full,
        media_data_only,
        db_max
    };
    // The actions allowed when creating a new database
    // and a filename clash occurs.
    enum class CreateProtocol {
        disallow,
        ask,
        rename
    };
    enum class CreateReturn {
        OK,
        FileExists,
        CannotOpen,
        UnknownType
    };
    enum CreateFlags : unsigned {
        CREATE_DB_STD_EXT = 0x0001, // Redundant, we always force .tfpd extention
        CREATE_DB_ENUM_FN    = 0x0002,
        CREATE_DB_ASK_REPLACE = 0x0004
    };
    enum class Coverage {
        user,      // Positive IDs
        common,    // Negative IDs
        notzero,   // All except zero IDs
        rnotzero,  // All except zero in reverse order IDs
        userfirst, // Pos + Neg IDs
        all        // Neg Zero Pos IDs
    };

protected:
    static wxSQLite3Database* s_db;
    static DbType             s_dbtype;
    static long               s_change;
    static long               s_spnumber;

    static recExternalDbMap   s_extdbs; // Details of External and Associated db's
    static StringMap          s_attdbs; // List of attached db's

public:
    /*! Delete the given record in the given table.
     */
    static bool DeleteRecord( const char* table, idt id, const wxString& dbname );

    /*! Return true if the given record exists in the given table.
     */
    static bool RecordExists( const char* table, idt id, const wxString& dbname );

    /*! Return the number of User (above 0) records in the given table.
     */
    static int GetUserCount( const char* table, const wxString& dbname = "Main" );

    /*! Return the total number of records (incl. system and the null record)
     *  in the given table.
     */
    static int GetCount( const char* table, const wxString& dbname = "Main" );

    /*! Return the total number of records of type required by Coverage argument.
     */
    static int GetCount( Coverage cover, const char* table, const wxString& dbname = "Main" );

    static bool DoesTableExist( const char* table, const wxString& dbname );

    /*! Return a list of all user (positive) id records in the given table.
     */
    static recIdVec GetPositiveIDs( const char* table, const wxString& dbname );

    /*! Return a list of id records in the given table.
     */
    static recIdVec GetIdVec( Coverage cover, const char* table, const wxString& dbname );

    idt   f_id;

    /*! Default constructor, does nothing. */
    recDb() : f_id(0) {}
    /*! Constructor with id, reads the record for the given id. */
    recDb( idt id ) : f_id(id) {}

    static void SetDb( wxSQLite3Database* db ) { s_db = db; }
    static wxSQLite3Database* GetDb() { return s_db; }
    static DbType GetDbType() { return s_dbtype; }

    /*! Create a new database file and then close it.
    *  Returns CR_OK if the file is successfully created.
    */
    static CreateReturn CreateDbFile( const wxString& fname, DbType type );

    /*! Creates a new database with the given filename.
    The standard extension ".tfpd" is always forced.
    If the filename already exists and neither the flags CREATE_DB_ASK_REPLACE
    nor CREATE_DB_ENUM_FN are set, the function returns false;
    Returns true if a database is created.
    */
    static bool CreateDb( const wxString& fname, DbType type, unsigned flags );

    /*! Add all core data records to database
    */
    static bool AddCommonCoreData( const wxString& dbname = "Main" );

    /*! Opens an existing database file, providing there is not an existing
     *  database open and the file exists.
     */
    static DbType OpenDb( const wxString& fname );

    /*! Returns true if the database is currently open.
    */
    static bool IsOpen() { return s_db->IsOpen(); }

    /*! Closes the existing database file.
     */
    static void CloseDb();

    /*! Opens an existing database file as an External Database,
     */
    static bool OpenExternalDb( const wxString& fname, const wxString& dbname );

    /*! Get a list of External databases.
    */
    static StringVec GetExternalDbList();

    /*! Closes an attached External database file.
     */
    static void CloseExternalDb( const wxString& dbname );

    /*! Opens an existing database file as an Associate Database,
     */
    static wxString OpenAssociateDb(
        const wxString& extdb, const wxString& fname, const wxString& dbname );

    /*! Get a list of Associated databases.
    */
    static StringVec GetAssociatedDbList( const wxString& extdb );

    /*! Get Associate ID of attached database.
    */
    static idt GetAssociateDbAssID( const wxString& extdb, const wxString& dbname );

    /*! Closes an attached Associate database file.
     */
    static void CloseAssociateDb( const wxString& extdb, const wxString& dbname );

    /*! Attach fname to database as dbname.
    */
    static bool AttachDb( const wxString& extdb, const wxString& fname, const wxString& dbname );

    /*! Attach fname to database as dbname.
    */
    static bool IsAttachedDb( const wxString& dbname );

    /*! Detach dbname from database.
    */
    static bool DetachDb( const wxString& dbname );

    /*! Get a list of attached databases.
    */
    static StringVec GetAttachedDbList();
    static StringMap GetAttachedDbMap() { return s_attdbs; }

    /*! Get a list of all databases, including "main".
    */
    static StringVec GetDatabaseList();

    /*! Returns the full file name of the currently open database.
     */
    static wxString GetFileName();

    /*! Return the database type 
    */
    static DbType GetDatabaseType( const wxString& dbname );

    /* Return a short text description of the database type
    */
    static wxString GetDatabaseTypeDesc( DbType type );

    static bool WriteCreateScript( const std::string& fname, DbType type );
    static bool WriteCreateScript( const std::string& fname, const wxString& dbname = "Main" );

    /*! Returns the current change value.
     */
    static long GetChange() { return s_change; }

    static void Begin() { s_db->Begin(); }
    static void Commit() { s_db->Commit(); ++s_change; }
    static void Rollback() { if( !s_db->GetAutoCommit() ) s_db->Rollback(); }
    static void ErrorMessage( wxSQLite3Exception& e );
    static wxString GetSavepointStr() { return wxString::Format( "sp%ld", ++s_spnumber ); }
    static void Savepoint( const wxString& str ) { s_db->Savepoint( str ); }
    static void ReleaseSavepoint( const wxString& str )
        { s_db->ReleaseSavepoint( str ); }
    static void Rollback( const wxString& str ) { s_db->Rollback( str ); }
    static void Vacuum() { s_db->Vacuum(); }

    /*! Clear all data to default values.
     */
    virtual void Clear() = 0;

    /*! If the id field is zero, a new record is created and the id field
     *  is updated with the new value. If the id field is not zero, the
     *  database is checked to see if the record already exists - if it
     *  does it is updated - if not it is created.
     */
    virtual void Save() { Save( "Main" ); }
    virtual void Save( const wxString& dbname ) { wxASSERT( false ); } /* TODO: make pure virtual member function? */

    /*! If the record does not exist, all fields are cleared and the function
     *  returns false; If the record exists, the fields are updated and the
     *  function returns true.
     */
    virtual bool Read() { return Read( "Main" ); }
    virtual bool Read( const wxString& dbname ) { Clear(); return false; } /* TODO: make pure virtual member function? */
    bool ReadID( idt id, const wxString& dbname = "Main" ) { f_id = id; return Read( dbname ); }

    idt FGetID() const { return f_id; }
    void FSetID( idt id ) { f_id = id; }

    bool EqualID( const recDb& r2 ) const { return f_id == r2.f_id; }

    static int ExecuteInt( const wxSQLite3StatementBuffer& sql );
    static int ExecuteInt( const char* format, const wxString& dbname = "Main" );
    static int ExecuteInt( const char* format, idt id, const wxString& dbname = "Main" );
    static int ExecuteInt( const char* format, const wxString& dbname, idt id );
    static idt ExecuteID( const wxSQLite3StatementBuffer& sql );
    static idt ExecuteID( const char* format, const wxString& dbname = "Main" );
    static idt ExecuteID( const char* format, idt id, const wxString& dbname = "Main" );
    static idt ExecuteID( const char* format, const wxString& dbname, idt id );
    static recIdVec ExecuteIdVec( const wxSQLite3StatementBuffer& sql );
    static recIdVec ExecuteIdVec( const char* format, const wxString& dbname = "Main" );
    static recIdVec ExecuteIdVec( const char* format, idt id, const wxString& dbname = "Main" );
    static recIdVec ExecuteIdVec( const char* format, const wxString& dbname, idt id );
    static wxString ExecuteStr( const wxSQLite3StatementBuffer& sql );
    static wxString ExecuteStr( const char* format, const wxString& dbname = "Main" );
    static wxString ExecuteStr( const char* format, idt id, const wxString& dbname = "Main" );
    static wxString ExecuteStr( const char* format, const wxString& dbname, idt id );
};


template <class T>
class recDbT : public recDb
{
public:
    recDbT<T>() : recDb() {}
    recDbT<T>( int id ) : recDb( id ) {}

    static const char* TableName() { return T::s_tablename; }
    const char* GetTableName() const { return T::s_tablename; }

    static recTable Table() { return T::s_table; }

    static std::string PrefixId( idt id ) {
        return recTablePrefixes[static_cast<size_t>(T::s_table)] + std::to_string( id );
    }
    std::string PrefixId() const { return PrefixId( FGetID() ); }

    bool Delete( const wxString& dbname = "Main" )  { 
        return DeleteRecord( T::s_tablename, f_id, dbname ); }
    static bool Delete( idt id, const wxString& dbname = "Main" ) { 
        return DeleteRecord( T::s_tablename, id, dbname ); }
    bool Exists( const wxString& dbname = "Main" ) const {
        return RecordExists( T::s_tablename, f_id, dbname );
    }
    static bool Exists( idt id, const wxString& dbname = "Main" ) {
        return RecordExists( T::s_tablename, id, dbname );
    }
    static int UserCount( const wxString& dbname = "Main" ) {
        return GetUserCount( T::s_tablename, dbname ); }
    static int Count( const wxString& dbname = "Main" ) {
        return GetCount( T::s_tablename, dbname );
    }
    static int Count( Coverage cover, const wxString& dbname = "Main" ) {
        return GetCount( cover, T::s_tablename, dbname );
    }
    static bool TableExists( const wxString& dbname = "Main" ) {
        return DoesTableExist( T::s_tablename, dbname );
    }
    static recIdVec PositiveIDs( const wxString& dbname = "Main" ) {
        return GetPositiveIDs( T::s_tablename, dbname );
    }
    static recIdVec IdVec( Coverage cover = Coverage::notzero, const wxString& dbname = "Main" ) {
        return GetIdVec( cover, T::s_tablename, dbname );
    }

    virtual bool Equivalent( const T& ) const {
        wxASSERT( false ); // Equivalent is not needed for all record types.
        return false;
    }

    bool operator==( const T& record ) const {
        return Equivalent( record ) && EqualID( record );
    }
    bool operator!=( const T& record ) const {
        return !Equivalent( record ) || !EqualID( record );
    }

    static bool CsvReadTable( std::istream& in, const wxString& dbname = "Main" )
    {
        std::string titles;
        std::getline( in, titles ); // Get rid of the title line
        // We could check titles here to detect change in format

        while( in.peek() != EOF ) {
            T record( 0 );
            bool ret = record.CsvRead( in );
            if( ret ) {
                record.Save( dbname );
            }
        }
        return true;
    }
    static bool CsvReadTableFile( const std::string& path, const wxString& dbname = "Main" )
    {
        std::string fname = recEndWithFileSep( path ) + T::s_tablename + ".csv";
        std::ifstream ifile( fname );
        if( !ifile ) {
            return true; // Not an error if it doesn't exist
        }
        return T::CsvReadTable( ifile, dbname );
    }
    static bool CsvReadTableString( const char* str, const wxString& dbname = "Main" )
    {
        std::istringstream in( str );
        return T::CsvReadTable( in, dbname );
    }

    static void CsvWriteTable(
        std::ostream& out,
        Coverage cover = Coverage::rnotzero,
        const wxString& dbname = "Main" )
    {
        recIdVec list = T::IdVec( cover, dbname );
        if( !list.empty() ) {
            out << T::CsvTitles();
            for( idt id : list ) {
                T::CsvWrite( out, id, dbname );
            }
        }
    }
    static bool CsvWriteTableFile(
        const std::string& path,
        Coverage cover = Coverage::rnotzero,
        const wxString& dbname = "Main" )
    {
        if( T::Count( cover, dbname ) == 0 ) {
            return true;
        }
        std::string fname = recEndWithFileSep( path ) + T::s_tablename + ".csv";
        std::ofstream ofile( fname, std::ios::trunc );
        if( !ofile ) {
            return false;
        }
        T::CsvWriteTable( ofile, cover, dbname );
        return true;
    }
};

class recUid
{
protected:
    wxString f_uid;
    long f_changed;

    static idt DoFindUid( const wxString& uid, const char* table, const wxString& dbname );
    static wxString DoGetChangedDate( idt id, const char* table, const wxString& dbname );

public:
    recUid() : f_changed( 0 ) {}

    wxString FGetUid() const { return f_uid; }
    long FGetChanged() const { return f_changed; }

    void FSetUid( const wxString& uid ) { f_uid = uid; }
    void FSetChanged( long jdn ) { f_changed = jdn; }

    void CreateUidChanged();
};

template <class T>
class recUidT : public recUid
{
public:
    recUidT<T>() : recUid() {}

    static idt FindUid( const wxString& uid, const wxString& dbname ) {
        return DoFindUid( uid, T::s_tablename, dbname );
    }
    static idt FindUid( idt id, const wxString& source_db, const wxString& target_db ) {
        T rec( id, source_db );
        return DoFindUid( rec.FGetUid(), T::s_tablename, target_db );
    }

    wxString GetChangedDate() const {
        return recGetDateStr( FGetChanged() );
    }
    static wxString GetChangedDate( idt id, const wxString& dbname ) {
        return DoGetChangedDate( idt id, T::s_tablename, dbname );
    }

    recMatchUID CompareUID( const T& record ) const {
        if( f_uid != record.f_uid ) return recMatchUID::unequal;
        if( f_changed < record.f_changed ) return recMatchUID::older;
        if( f_changed > record.f_changed ) return recMatchUID::younger;
        return recMatchUID::equal;
    }
};

extern wxString recGetHomeDisplay( const wxString& dbname );
extern recDb::CreateProtocol recGetCreateProtocol();
extern unsigned recGetCreateProtocolFlag();

extern wxString recGetDateStr( long jdn );

#endif // RECDATABASE_H
