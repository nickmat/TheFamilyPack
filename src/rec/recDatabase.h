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

class wxSQLite3Database;

class recDb {
public:
    enum CreateFlags {
        CREATE_DB_STD_EXT = 0x0001,
        CREATE_DB_ENUM_FN = 0x0002
    };
private:
    static wxSQLite3Database* m_db;

public:
    id_t   f_id;

    recDb() : f_id(0) {}
    recDb( id_t id ) { f_id = id; Read(); }

    static bool CreateDb( wxString& fname, unsigned flags );
    static void SetDb( wxSQLite3Database* db ) { m_db = db; }
    static wxSQLite3Database* GetDb() { return m_db; }

    virtual const wxString GetTableName() const = 0;
    virtual void Clear() = 0;
    virtual void Save() = 0;
    virtual bool Read() = 0;

    bool Delete() { Delete( f_id ); }
    bool Delete( id_t id );
};

#endif // RECDATABASE_H
