/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/embed/recCreateMedia.sql
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     SQL text to create a Media only database.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     5th December 2018
 * Copyright:   Copyright (c) 2018, Nick Matthews.
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

/* This pragma makes the database more efficient, but means the database
   can only be used by tools created with SQLite version 3.3.0 or later
   (released Jan 2006) */
PRAGMA legacy_file_format=OFF;
PRAGMA foreign_keys=ON;

BEGIN;

CREATE TABLE MediaData (
  id INTEGER PRIMARY KEY NOT NULL,
  data BLOB NOT NULL,
  privacy INT NOT NULL,
  copyright TEXT NULL,
  file TEXT NOT NULL
);

CREATE TABLE Version (
  id INTEGER PRIMARY KEY,
  major INTEGER,
  minor INTEGER,
  revision INTEGER,
  test INTEGER
);

/* The Version table id=1 for full database, id=2 for MediaData only database */
INSERT INTO Version (id, major, minor, revision, test) VALUES(2, 0, 0, 0, 1);

COMMIT;

/* End of src/rec/embed/recCreateMedia.sql */
