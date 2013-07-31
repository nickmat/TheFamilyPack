/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recCreate.sql
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     SQL text to create initial database.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     22nd March 2008
 * Copyright:   Copyright (c) 2008 - 2013, Nick Matthews.
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

CREATE TABLE CitationPart (
  id INTEGER PRIMARY KEY,
  source_id INTEGER,
  type_id INTEGER,
  val TEXT
);

CREATE TABLE CitationPartType (
  id INTEGER PRIMARY KEY,
  name TEXT
);

CREATE TABLE Contact (
  id INTEGER PRIMARY KEY,
  type_id INTEGER NOT NULL REFERENCES ContactType(id),
  list_id INTEGER NOT NULL REFERENCES ContactList(id),
  val TEXT NOT NULL
);

CREATE TABLE ContactList (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER REFERENCES Individual(id)
);

CREATE TABLE ContactType (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL
);

CREATE TABLE Date (
  id INTEGER PRIMARY KEY,
  jdn INTEGER,
  range INTEGER,
  rel_id INTEGER,
  type INTEGER,
  descrip TEXT,
  record_sch INTEGER,
  display_sch INTEGER
);

CREATE TABLE Event (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  higher_id INTEGER NOT NULL,
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  date1_id INTEGER NOT NULL,
  date2_id INTEGER NOT NULL,
  place_id INTEGER NOT NULL,
  note TEXT NOT NULL,
  date_pt INTEGER NOT NULL
);

CREATE TABLE EventEventum (
  id INTEGER PRIMARY KEY,
  event_id INTEGER NOT NULL REFERENCES Event(id),
  eventum_id INTEGER NOT NULL REFERENCES Eventum(id),
  conf FLOAT NOT NULL,
  note TEXT
);

CREATE TABLE EventType (
  id INTEGER PRIMARY KEY,
  grp INTEGER,
  name TEXT
);

CREATE TABLE EventTypeRole (
  id INTEGER PRIMARY KEY,
  type_id INTEGER,
  prime INTEGER,
  official INTEGER,
  name TEXT
);

CREATE TABLE Eventum (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  date1_id INTEGER NOT NULL,
  date2_id INTEGER NOT NULL,
  place_id INTEGER NOT NULL,
  note TEXT NOT NULL,
  date_pt INTEGER NOT NULL
);

CREATE TABLE EventumPersona (
  id INTEGER PRIMARY KEY,
  eventum_id INTEGER NOT NULL REFERENCES Eventum(id),
  per_id INTEGER NOT NULL REFERENCES Persona(id),
  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),
  note TEXT NOT NULL,
  per_seq INTEGER NOT NULL
);

INSERT INTO EventType (id) VALUES(0);
INSERT INTO EventTypeRole (id) VALUES(0);

INSERT INTO EventType (id, grp, name) VALUES(-1, 1, 'Birth');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-1, -1, 1, 0, 'Born');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-2, -1, 0, 0, 'Mother');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-3, -1, 0, 1, 'Midwife');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-4, -1, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-2, 5, 'Death');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-5, -2, 1, 0, 'Died');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-6, -2, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-3, 3, 'Marriage');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-7, -3, 1, 0, 'Groom');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-8, -3, 2, 0, 'Bride');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-9, -3, 0, 1, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-10, -3, 0, 0, 'Witness');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-11, -3, 0, 0, 'Father of Groom');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-12, -3, 0, 0, 'Mother of Groom');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-13, -3, 0, 0, 'Father of Bride');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-14, -3, 0, 0, 'Mother of Bride');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-15, -3, 0, 0, 'Give away Bride');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-16, -3, 0, 0, 'Maid of Honour');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-17, -3, 0, 0, 'Bridesmaid');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-18, -3, 0, 0, 'Best Man');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-19, -3, 0, 0, 'Pageboy');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-20, -3, 0, 0, 'Present');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-59, -3, 3, 0, 'Spouse');

INSERT INTO EventType (id, grp, name) VALUES(-4, 2, 'Baptism');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-21, -4, 1, 0, 'Baptised');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-22, -4, 0, 0, 'Parent');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-23, -4, 0, 0, 'God Parent');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-24, -4, 0, 1, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-25, -4, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-5, 6, 'Burial');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-26, -5, 1, 0, 'Deceased');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-27, -5, 0, 1, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-28, -5, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-6, 7, 'Adult Baptism');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-29, -6, 1, 0, 'Baptised');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-30, -6, 0, 1, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-31, -6, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-7, 7, 'Census');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-32, -7, 1, 0, 'Listed');

INSERT INTO EventType (id, grp, name) VALUES(-8, 7, 'Confirmation');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-33, -8, 1, 0, 'Confirmed');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-34, -8, 0, 1, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-35, -8, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-9, 4, 'Divorce');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-36, -9, 1, 0, 'Husband');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-37, -9, 2, 0, 'Wife');

INSERT INTO EventType (id, grp, name) VALUES(-10, 7, 'Emigration');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-38, -10, 1, 0, 'Emigrant');

INSERT INTO EventType (id, grp, name) VALUES(-11, 7, 'Immigration');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-39, -11, 1, 0, 'Immigrant');

INSERT INTO EventType (id, grp, name) VALUES(-12, 7, 'Graduation');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-40, -12, 1, 0, 'Graduate');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-41, -12, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-13, 7, 'Probate');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-42, -13, 1, 0, 'Deceased');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-43, -13, 0, 0, 'Executor');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-44, -13, 0, 1, 'Adjudicator');

INSERT INTO EventType (id, grp, name) VALUES(-14, 7, 'Will');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-45, -14, 1, 0, 'Subject');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-46, -14, 0, 0, 'Executor');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-47, -14, 0, 0, 'Beneficiary');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-48, -14, 0, 1, 'Solicitor');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-49, -14, 0, 0, 'Witness');

INSERT INTO EventType (id, grp, name) VALUES(-15, 2, 'Register Birth');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-50, -15, 1, 0, 'Born');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-51, -15, 0, 0, 'Parent');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-52, -15, 0, 0, 'Registrant');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-53, -15, 0, 1, 'Registrar');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-54, -15, 0, 0, 'Mentioned');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-60, -15, 0, 0, 'Mother');

INSERT INTO EventType (id, grp, name) VALUES(-16, 6, 'Register Death');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-55, -16, 1, 0, 'Died');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-56, -16, 0, 0, 'Registrant');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-57, -16, 0, 1, 'Registrar');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-58, -16, 0, 0, 'Mentioned');

INSERT INTO EventType (id, grp, name) VALUES(-17, 8, 'Residence');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-61, -17, 0, 0, 'Family');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-62, -17, 0, 0, 'Visitor');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-63, -17, 0, 0, 'Lodger');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-64, -17, 0, 0, 'Boarder');

INSERT INTO EventType (id, grp, name) VALUES(-18, 8, 'Occupation');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-65, -18, 1, 0, 'Occupation');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-66, -18, 0, 0, 'Employer');

INSERT INTO EventType (id, grp, name) VALUES(-19, 8, 'Condition');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-67, -19, 1, 0, 'Condition');

INSERT INTO EventType (id, grp, name) VALUES(-20, 3, 'Civl Partnership');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-68, -20, 3, 0, 'Partner');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-69, -20, 0, 1, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-70, -20, 0, 0, 'Witness');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-71, -20, 0, 0, 'Present');

/* Next EventTypeRole id = -72 */

CREATE TABLE Family (
  id INTEGER PRIMARY KEY,
  husb_id INTEGER,
  wife_id INTEGER
);

CREATE TABLE FamilyEvent (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL REFERENCES Family(id),
  event_id INTEGER NOT NULL REFERENCES Event(id),
  note TEXT,
  fam_seq INTEGER NOT NULL
);

CREATE TABLE FamilyIndividual (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL,
  ind_id INTEGER NOT NULL,
  seq_child INTEGER NOT NULL,
  seq_parent INTEGER NOT NULL
);

CREATE TABLE Individual (
  id INTEGER PRIMARY KEY,
  sex INTEGER NOT NULL,
  name TEXT,
  surname TEXT,
  epitaph TEXT,
  note TEXT NOT NULL,
  fam_id INTEGER NOT NULL
);

CREATE TABLE IndividualEvent (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER NOT NULL REFERENCES Individual(id),
  event_id INTEGER NOT NULL REFERENCES Event(id),
  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),
  note TEXT NOT NULL,
  ind_seq INTEGER NOT NULL
);

CREATE TABLE IndividualPersona (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER NOT NULL REFERENCES Individual(id),
  per_id INTEGER NOT NULL REFERENCES Persona(id),
  conf FLOAT NOT NULL,
  note TEXT
);

CREATE TABLE Name (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER NOT NULL,
  per_id INTEGER NOT NULL,
  style_id INTEGER NOT NULL REFERENCES NameStyle(id),
  sequence INTEGER
);

CREATE TABLE NamePart (
  id INTEGER PRIMARY KEY,
  name_id INTEGER NOT NULL REFERENCES Name(id),
  type_id INTEGER NOT NULL REFERENCES NamePartType(id),
  val TEXT,
  sequence INTEGER NOT NULL
);

CREATE TABLE NamePartType (
  id INTEGER PRIMARY KEY,
  grp INTEGER NOT NULL,
  name TEXT NOT NULL
);

/* matches enum StdNameType */
INSERT INTO NamePartType (id, grp, name) VALUES( 0, 0, '');
INSERT INTO NamePartType (id, grp, name) VALUES(-1, 1, 'Given name');
INSERT INTO NamePartType (id, grp, name) VALUES(-2, 1, 'Surname');
INSERT INTO NamePartType (id, grp, name) VALUES(-3, 1, 'Post name');

CREATE TABLE NameStyle (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL
);

/* matches enum recNameStyle::Style */
INSERT INTO NameStyle (id, name) VALUES(0,'Default');
INSERT INTO NameStyle (id, name) VALUES(-1,'Birth name');
INSERT INTO NameStyle (id, name) VALUES(-2,'Married name');
INSERT INTO NameStyle (id, name) VALUES(-3,'Alias');

CREATE TABLE Persona (
  id INTEGER PRIMARY KEY,
  sex INTEGER,
  ref_id INTEGER,
  note TEXT
);

CREATE TABLE Place (
  id INTEGER PRIMARY KEY,
  date1_id INTEGER,
  date2_id INTEGER
);

CREATE TABLE PlacePart (
  id INTEGER PRIMARY KEY,
  type_id INTEGER,
  place_id INTEGER,
  val TEXT,
  sequence INTEGER
);

CREATE TABLE PlacePartType (
  id INTEGER PRIMARY KEY,
  name TEXT
);

INSERT INTO PlacePartType (id) VALUES(0);
INSERT INTO PlacePartType (id, name) VALUES(-1, 'Address');

CREATE TABLE Reference (
  id INTEGER PRIMARY KEY,
  title TEXT,
  statement TEXT
);

CREATE TABLE ReferenceEntity (
  id INTEGER PRIMARY KEY,
  ref_id INTEGER,
  entity_type INTEGER,
  entity_id INTEGER,
  sequence INTEGER
);

CREATE TABLE Relationship (
  id INTEGER PRIMARY KEY,
  per1_id INTEGER NOT NULL REFERENCES Persona(id),
  per2_id INTEGER NOT NULL REFERENCES Persona(id),
  descrip TEXT NOT NULL
);

CREATE TABLE RelativeDate (
  id INTEGER PRIMARY KEY,
  val INTEGER,
  range INTEGER,
  unit INTEGER,
  base_id INTEGER NOT NULL REFERENCES Date(id),
  type INTEGER,
  scheme INTEGER
);

CREATE TABLE Repository (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  access TEXT,
  comments TEXT,
  con_list_id INTEGER NOT NULL REFERENCES ContactList(id)
);

CREATE TABLE RepositorySource (
  id INTEGER PRIMARY KEY,
  repos_id INTEGER,
  source_id INTEGER,
  call_num TEXT,
  desc TEXT
);

CREATE TABLE Researcher (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  comments TEXT,
  con_list_id INTEGER NOT NULL REFERENCES ContactList(id)
);

CREATE TABLE Source (
  id INTEGER PRIMARY KEY,
  higher_id INTEGER,
  sub_date1_id INTEGER,
  sub_date2_id INTEGER,
  sub_place_id INTEGER,
  loc_place_id INTEGER,
  res_id INTEGER,
  comments TEXT
);

CREATE TABLE System (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  val TEXT NOT NULL
);

CREATE TABLE User (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  res_id INTEGER NOT NULL REFERENCES Researcher(id)
);

CREATE TABLE UserSetting (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES User(id),
  property INTEGER NOT NULL,
  val TEXT NOT NULL
);

CREATE TABLE Version (
  id INTEGER PRIMARY KEY,
  major INTEGER,
  minor INTEGER,
  revision INTEGER,
  test INTEGER
);

/* Create default settings */
INSERT INTO ContactType (id, name) VALUES(0, '');
INSERT INTO ContactType (id, name) VALUES(-1, 'Address');
INSERT INTO ContactType (id, name) VALUES(-2, 'Telephone');
INSERT INTO ContactType (id, name) VALUES(-3, 'Mobile');
INSERT INTO ContactType (id, name) VALUES(-4, 'Email');
INSERT INTO ContactType (id, name) VALUES(-5, 'Website');
INSERT INTO ContactType (id, name) VALUES(-6, 'Fax');

INSERT INTO ContactList (id) VALUES(0);
INSERT INTO ContactList (id) VALUES(1);

INSERT INTO Researcher (id, name, comments, con_list_id) VALUES(0, '', '', 0);
INSERT INTO Researcher (id, name, comments, con_list_id) VALUES(1, 'Anonymous', '', 1);

INSERT INTO User (id, res_id) VALUES(0, 0);
INSERT INTO User (id, res_id) VALUES(1, 1);

INSERT INTO System (id, val) VALUES(1, '1');

INSERT INTO UserSetting (id, user_id, property, val) VALUES(1, 0, 1, 'F1');
INSERT INTO UserSetting (id, user_id, property, val) VALUES(2, 1, 1, 'F1');

/* The Version table has only this one row */
INSERT INTO Version (id, major, minor, revision, test) VALUES(1, 0, 0, 10, 6);

COMMIT;

/* End of create.sql */
