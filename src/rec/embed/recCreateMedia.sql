/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/embed/recCreateMedia.sql
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     SQL text to create a Media only database.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     5th December 2018
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

/* Run recCreateCommon.sql script first. */

BEGIN;

CREATE TABLE MediaData (
  id INTEGER PRIMARY KEY,
  title TEXT NULL,
  data BLOB NOT NULL,
  type INTEGER NOT NULL,
  privacy INTEGER NOT NULL,
  copyright TEXT NULL,
  file TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO MediaData (id, title, data, type, privacy, copyright, file, uid, changed)
  VALUES(0,'',0,0,'','',0,'',0);


/* The Version table id=2 for MediaData section of database */
INSERT INTO Version (id, major, minor, revision, test) VALUES(2, 0, 0, 0, 4);

COMMIT;

/* End of src/rec/embed/recCreateMedia.sql */
