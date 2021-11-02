/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * Copyright:   Copyright (c) 2010 .. 2021, Nick Matthews.
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
protected:
    static wxSQLite3Database* s_db;
    static DbType             s_dbtype;
    static long               s_change;
    static long               s_spnumber;
    static recAssMap          s_assmap;

public:
    /*! Delete the given record in the given table.
     */
    static bool DeleteRecord( const char* table, idt id );

    /*! Return true if the given record exists in the given table.
     */
    static bool RecordExists( const char* table, idt id, const wxString& dbname );

    /*! Return the number of User (above 0) records in the given table.
     */
    static int GetUserCount( const char* table );

    /*! Return the total number of records (incl. system and the null record)
     *  in the given table.
     */
    static int GetCount( const char* table );

    /*! Return a list of all user (positive) id records in the given table.
     */
    static recIdVec GetPositiveIDs( const char* table, const wxString& dbname );

    idt   f_id;

    /*! Default constructor, does nothing. */
    recDb() {}
    /*! Constructor with id, reads the record for the given id. */
    recDb( idt id ) : f_id(id) {}

    static void SetDb( wxSQLite3Database* db ) { s_db = db; }
    static wxSQLite3Database* GetDb() { return s_db; }

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

    /*! Attach fname to database as dbname.
    */
    static bool AttachDb( const wxString& fname, const wxString& dbname );

    /*! Detach dbname from database.
    */
    static bool DetachDb( const wxString& dbname );

    /*! Get a list of attached databases.
    */
    static StringVec GetAttachedDbList();

    /*! Get a list of all databases, including "main".
    */
    static StringVec GetDatabaseList();

    /*! Get Associate ID of attached database.
    */
    static idt GetAttachedDbAssID( const wxString& dbname );

    /*! Closes the existing database file.
     */
    static void CloseDb();

    /*! Add entry to the attached Associate database map.
     */
    static void AddAssociateMap( idt assID, const wxString& path ) { s_assmap[assID] = path; }

    /*! Do a global systems check and update.
     *  Could take a while.
     */
    static bool GlobalUpdate();

    /*! Returns true if the database is currently open.
    */
    static bool IsOpen() { return s_db->IsOpen(); }

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
    bool ReadID( idt id ) { f_id = id; return Read(); }

    idt FGetID() const { return f_id; }
    void FSetID( idt id ) { f_id = id; }

    bool EqualID( const recDb& r2 ) const { return f_id == r2.f_id; }

    static int ExecuteInt( const wxSQLite3StatementBuffer& sql );
    static int ExecuteInt( const char* format, idt id );
    static idt ExecuteID( const wxSQLite3StatementBuffer& sql );
    static idt ExecuteID( const char* format, idt id );
    static recIdVec ExecuteIdVec( const wxSQLite3StatementBuffer& sql );
    static recIdVec ExecuteIdVec( const char* format, idt id );
    static wxString ExecuteStr( const wxSQLite3StatementBuffer& sql );
    static wxString ExecuteStr( const char* format, idt id );
};

#define TABLE_NAME_MEMBERS( T )                                                \
    static constexpr const char* s_tablename = T;                              \
    bool Delete() const { return DeleteRecord( s_tablename, f_id ); }          \
    static bool Delete( idt id ) { return DeleteRecord( s_tablename, id ); }   \
    bool Exists( const wxString& dbname = "Main" ) const {                     \
        return RecordExists( s_tablename, f_id, dbname ); }                    \
    static bool Exists( idt id, const wxString& dbname = "Main"  ) {           \
        return RecordExists( s_tablename, id, dbname ); }                      \
    static int UserCount() { return GetUserCount( s_tablename ); }             \
    static int Count() { return GetCount( s_tablename ); }                     \
    static bool TableExists( const wxString& db = wxEmptyString ) {            \
        return  s_db->TableExists( s_tablename, db ); }                        \
    static recIdVec PositiveIDs( const wxString& dbname = "Main" ) {           \
        return GetPositiveIDs( s_tablename, dbname ); }

#endif // RECDATABASE_H
