/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        recCreate.sql
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     SQL text to create initial database.
 * Author:      Nick Matthews
 * Modified by:
 * Website:     http://thefamilypack.org
 * Created:     22nd March 2008
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2008 - 2010, Nick Matthews.
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

CREATE TABLE Attribute (
  id INTEGER PRIMARY KEY,
  per_id INTEGER,
  type_id INTEGER,
  val TEXT,
  sequence INTEGER
);

CREATE TABLE AttributeType (
  id INTEGER PRIMARY KEY,
  grp INTEGER,
  name TEXT
);

/* matches enum StdAttributeType */
INSERT INTO AttributeType (id) VALUES(0);
INSERT INTO AttributeType (id, grp, name) VALUES(-1, 1,'Occupation');

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
  ind_id INTEGER,
  res_id INTEGER,
  repos_id INTEGER,
  type_id INTEGER,
  val TEXT
);

CREATE TABLE ContactType (
  id INTEGER PRIMARY KEY,
  name TEXT
);

INSERT INTO ContactType (id) VALUES(0);
INSERT INTO ContactType (id, name) VALUES(-1, 'Place');
INSERT INTO ContactType (id, name) VALUES(-2, 'Phone');
INSERT INTO ContactType (id, name) VALUES(-3, 'Fax');
INSERT INTO ContactType (id, name) VALUES(-4, 'Mobile');
INSERT INTO ContactType (id, name) VALUES(-5, 'email');
INSERT INTO ContactType (id, name) VALUES(-6, 'VoIP');
INSERT INTO ContactType (id, name) VALUES(-7, 'Website');

CREATE TABLE Date (
  id INTEGER PRIMARY KEY,
  jdn INTEGER,
  range INTEGER,
  base_id INTEGER,
  base_unit INTEGER,
  base_style INTEGER,
  type INTEGER,
  descrip TEXT,
  record_sch INTEGER,
  display_sch INTEGER
);

CREATE TABLE Event (
  id INTEGER PRIMARY KEY,
  title TEXT,
  sort_jdn INTEGER,
  type_id INTEGER,
  date1_id INTEGER,
  date2_id INTEGER,
  place_id INTEGER,
  note TEXT
);

CREATE TABLE EventPersona (
  id INTEGER PRIMARY KEY,
  event_id INTEGER,
  per_id INTEGER,
  role_id INTEGER,
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
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-8, -3, 1, 0, 'Bride');
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

INSERT INTO EventType (id, grp, name) VALUES(-9, 7, 'Divorce');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-36, -9, 1, 0, 'Husband');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-37, -9, 1, 0, 'Wife');

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

CREATE TABLE Family (
  id INTEGER PRIMARY KEY,
  husb_id INTEGER,
  wife_id INTEGER,
  event_id INTEGER
);

CREATE TABLE FamilyIndividual (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER,
  ind_id INTEGER,
  sequence INTEGER
);

CREATE TABLE Individual (
  id INTEGER PRIMARY KEY,
  surname TEXT,
  given TEXT,
  birth_jdn INTEGER,
  epitaph TEXT,
  sex INTEGER,
  fam_id INTEGER,
  per_id INTEGER,
  birth_id INTEGER,
  nr_birth_id INTEGER,
  death_id INTEGER,
  nr_death_id INTEGER,
  occ_id INTEGER
);

CREATE TABLE IndividualPersona (
  id INTEGER PRIMARY KEY,
  per_id INTEGER,
  ind_id INTEGER,
  note TEXT
);

CREATE TABLE Name (
  id INTEGER PRIMARY KEY,
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
  name_id INTEGER,
  sex INTEGER,
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

CREATE TABLE Repository (
  id INTEGER PRIMARY KEY,
  name TEXT,
  access TEXT,
  comments TEXT
);

CREATE TABLE RepositorySource (
  id INTEGER PRIMARY KEY,
  repos_id INTEGER,
  source_id INTEGER,
  call_num TEXT,
  desc TEXT
);

CREATE TABLE Researcher (
  id INTEGER PRIMARY KEY,
  name TEXT,
  comments TEXT
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

CREATE TABLE User (
  id INTEGER PRIMARY KEY,
  res_id INTEGER,
  fam_id INTEGER
);

CREATE TABLE Version (
  id INTEGER PRIMARY KEY,
  major INTEGER,
  minor INTEGER,
  revision INTEGER,
  test INTEGER
);

/* The Version table has only this one row */
INSERT INTO Version (id, major, minor, revision, test) VALUES(1, 0, 0, 8, 3);

COMMIT;

/* End of create.sql */
