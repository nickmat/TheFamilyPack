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
INSERT INTO AttributeType (id, grp, name) VALUES(-1, 1,'Given name');
INSERT INTO AttributeType (id, grp, name) VALUES(-2, 1,'Surname');
INSERT INTO AttributeType (id, grp, name) VALUES(-3, 1,'Post name');
INSERT INTO AttributeType (id, grp, name) VALUES(-4, 3,'Occupation');

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
  type_id, INTEGER,
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
  type INTEGER,
  desc TEXT,
  record_sch INTEGER,
  display_sch INTEGER
);

CREATE TABLE Event (
  id INTEGER PRIMARY KEY,
  title TEXT,
  type_id INTEGER,
  date1_id INTEGER,
  date2_id INTEGER,
  place_id INTEGER,
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
  name TEXT
);

INSERT INTO EventType (id) VALUES(0);
INSERT INTO EventTypeRole (id) VALUES(0);

INSERT INTO EventType (id, grp, name) VALUES(-1, 1, 'Birth');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-1, -1, 'Born');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-2, -1, 'Mother');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-3, -1, 'Midwife');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-4, -1, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-2, 5, 'Death');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-5, -2, 'Died');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-6, -2, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-3, 3, 'Marriage');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-7, -3, 'Groom');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-8, -3, 'Bride');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-9, -3, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-10, -3, 'Witness');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-11, -3, 'Father of Groom');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-12, -3, 'Mother of Groom');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-13, -3, 'Father of Bride');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-14, -3, 'Mother of Bride');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-15, -3, 'Give away Bride');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-16, -3, 'Maid of Honour');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-17, -3, 'Bridesmaid');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-18, -3, 'Best Man');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-19, -3, 'Pageboy');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-20, -3, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-4, 2, 'Baptism');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-21, -4, 'Baptised');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-22, -4, 'Parent');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-23, -4, 'God Parent');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-24, -4, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-25, -4, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-5, 6, 'Burial');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-26, -5, 'Deceased');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-27, -5, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-28, -5, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-6, 7, 'Adult Baptism');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-29, -6, 'Baptised');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-30, -6, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-31, -6, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-7, 7, 'Census');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-32, -7, 'Listed');

INSERT INTO EventType (id, grp, name) VALUES(-8, 7, 'Confirmation');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-33, -8, 'Confirmed');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-34, -8, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-35, -8, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-9, 7, 'Divorce');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-36, -9, 'Husband');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-37, -9, 'Wife');

INSERT INTO EventType (id, grp, name) VALUES(-10, 7, 'Emigration');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-38, -10, 'Emigrant');

INSERT INTO EventType (id, grp, name) VALUES(-11, 7, 'Immigration');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-39, -11, 'Immigrant');

INSERT INTO EventType (id, grp, name) VALUES(-12, 7, 'Graduation');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-40, -12, 'Graduate');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-41, -12, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-13, 7, 'Probate');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-42, -13, 'Deceased');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-43, -13, 'Executor');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-44, -13, 'Adjudicator');

INSERT INTO EventType (id, grp, name) VALUES(-14, 7, 'Will');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-45, -14, 'Subject');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-46, -14, 'Executor');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-47, -14, 'Beneficiary');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-48, -14, 'Solicitor');
INSERT INTO EventTypeRole (id, type_id, name) VALUES(-49, -14, 'Witness');

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

CREATE TABLE Persona (
  id INTEGER PRIMARY KEY,
  sex INTEGER,
  note TEXT
);

CREATE TABLE PersonaEvent (
  id INTEGER PRIMARY KEY,
  per_id INTEGER,
  event_id INTEGER,
  role_id INTEGER,
  note TEXT
);

CREATE TABLE IndividualPersona (
  id INTEGER PRIMARY KEY,
  per_id INTEGER,
  ind_id INTEGER,
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
  sub_place_id INTEGER,
  sub_date_id INTEGER,
  loc_place_id INTEGER,
  res_id INTEGER,
  comments TEXT
);

CREATE TABLE SourceGroup (
  id INTEGER PRIMARY KEY,
  name TEXT
);

CREATE TABLE SourceGroupSource (
  id INTEGER PRIMARY KEY,
  source_id INTEGER,
  group_id INTEGER
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
  revision INTEGER
);

/* The Version table has only this one row */
INSERT INTO Version (id, major, minor, revision) VALUES(1, 0, 0, 7);

/* End of create.sql */
