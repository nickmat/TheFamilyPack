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

extern wxString recGetHomeDisplay( const wxString& dbname );
using stringmap = std::map<int, int>;

extern wxString recGetDateStr( long jdn );

class recDb
{
public:
    enum class DbType {
        db_null,
        full,
        media_data_only,
        db_max
    };
    enum class CreateReturn {
        OK,
        FileExists,
        CannotOpen,
        UnknownType
    };
    enum CreateFlags {
        CREATE_DB_STD_EXT = 0x0001,
        CREATE_DB_ENUM_FN = 0x0002
    };
    enum class Coverage {
        user, common, all
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

    static bool DoesTableExist( const char* table, const wxString& dbname );

    /*! Return a list of all user (positive) id records in the given table.
     */
    static recIdVec GetPositiveIDs( const char* table, const wxString& dbname );

    /*! Only for records that have a 'uid' field. Other records will cause exception.
     */
    static idt DoFindUid( const wxString& uid, const char* table, const wxString& dbname );

    /*! Only for records that have a 'changed' field. Return a string of the changed date.
     */
    static wxString DoGetChangedDate( idt id, const char* table, const wxString& dbname );

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

    /*! Creates a new database with the given filename. If the flag
    *  CREATE_DB_STD_EXT is set, the standard file extension ".tfpd"
    *  is used. If CREATE_DB_ENUM_FN is set, then if the filename
    *  already exists then a new name is created by appending (n) to
    *  the name, where n is the lowest number (starting from 2) that
    *  gives a unique name.
    */
    static bool CreateDb( const wxString& fname, unsigned flags );

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
    static int ExecuteInt( const char* format, idt id, const wxString& dbname = "Main" );
    static int ExecuteInt( const char* format, const wxString& dbname, idt id );
    static idt ExecuteID( const wxSQLite3StatementBuffer& sql );
    static idt ExecuteID( const char* format, idt id, const wxString& dbname = "Main" );
    static idt ExecuteID( const char* format, const wxString& dbname, idt id );
    static recIdVec ExecuteIdVec( const wxSQLite3StatementBuffer& sql );
    static recIdVec ExecuteIdVec( const char* format, idt id, const wxString& dbname = "Main" );
    static recIdVec ExecuteIdVec( const char* format, const wxString& dbname, idt id );
    static wxString ExecuteStr( const wxSQLite3StatementBuffer& sql );
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
        return GetCount( T::s_tablename, dbname ); }
    static bool TableExists( const wxString& dbname = "Main" ) {
        return DoesTableExist( T::s_tablename, dbname );
    }
    static recIdVec PositiveIDs( const wxString& dbname = "Main" ) {
        return GetPositiveIDs( T::s_tablename, dbname );
    }
    static idt FindUid( const wxString& uid, const wxString& dbname ) {
        return DoFindUid( uid, T::s_tablename, dbname );
    }
    static idt FindUid( idt id, const wxString& source_db, const wxString& target_db ) {
        T rec( id, source_db );
        return DoFindUid( rec.FGetUid(), T::s_tablename, target_db );
    }
    wxString GetChangedDate() const { 
        return recGetDateStr( ( (T*) this )->FGetChanged() );
    }
    static wxString GetChangedDate_( idt refID, const wxString& dbname ) {
        return DoGetChangedDate( idt id, T::s_tablename, dbname );
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
};

#endif // RECDATABASE_H
