/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recDatabase.h
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     Manage SQLite3 database
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     3 October 2010
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2010, Nick Matthews.
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

// Some helpful defines
typedef wxLongLong      id_t;
#define ID              "%lld"
#define GET_ID( id )    (id)
#define IDtoLong( id )  (id.GetLo())
#define UTF8_(s) ((const char*)(s).utf8_str())

#include <wx/wxsqlite3.h>

class recDb {
public:
    enum CreateFlags {
        CREATE_DB_STD_EXT = 0x0001,
        CREATE_DB_ENUM_FN = 0x0002
    };
protected:
    static wxSQLite3Database* s_db;

    /*! Delete the given record in the given table.
     */
    static bool DeleteRecord( const char* table, id_t id );

    /*! Return true if the given record exists in the given table.
     */
    static bool RecordExists( const char* table, id_t id ); 

public:
    id_t   f_id;

    /*! Default constructor, does nothing. */
    recDb() {}
    /*! Constructor with id, reads the record for the given id. */
    recDb( id_t id ) { f_id = id; Read(); }

    static void SetDb( wxSQLite3Database* db ) { s_db = db; }
    static wxSQLite3Database* GetDb() { return s_db; }

    /*! Creates a new database with the given filename. If the flag
     *  CREATE_DB_STD_EXT is set, the standard file extension ".tfpd"
     *  is used. If CREATE_DB_ENUM_FN is set, then if the filename 
     *  already exists then a new name is created by appending (n) to
     *  the name, where n is the lowest number (starting from 2) that
     *  gives a unique name.
     */
    static bool CreateDb( wxString& fname, unsigned flags );

    /*! Opens an existing database file, providing there is not an existing 
     *  database open and the file exists.
     */
    static bool OpenDb( const wxString& fname );

    /*! Closes the existing database file.
     */
    static void CloseDb() { s_db->Close(); }

    /*! Return a the table name. 
     */
    virtual const char* GetTableName() const = 0;

    /*! Clear all data to default values.
     */
    virtual void Clear() = 0;

    /*! If the id field is zero, a new record is created and the id field
     *  is updated with the new value. If the id field is not zero, the 
     *  database is checked to see if the record already exists - if it 
     *  does it is updated - if not it is created.
     */
    virtual void Save() = 0;

    /*! If the record does not exist, all fields are cleared and the function
     *  returns false; If the record exists, the fields are updated and the
     *  function returns true.
     */
    virtual bool Read() = 0;
};

#define TABLE_NAME_MEMBERS( T )                                        \
    const char* GetTableName() const { return (T); }                   \
    bool Delete() { return DeleteRecord( (T), f_id ); }                \
    static bool Delete( id_t id ) { return DeleteRecord( (T), id ); }  \
    bool Exists() { return RecordExists( (T), f_id ); }                \
    static bool Exists( id_t id ) { return RecordExists( (T), id ); }


#endif // RECDATABASE_H