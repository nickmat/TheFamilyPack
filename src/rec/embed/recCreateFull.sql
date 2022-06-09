/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/embed/recCreateFull.sql
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     SQL text to create initial database.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     22nd March 2008
 * Copyright:   Copyright (c) 2008..2022, Nick Matthews.
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

    27 Mar 2019  File rename from recCreate.sql to recCreateFull.sql
*/

/* Run recCreateCommon.sql and recCreateMedia.sql script first. */


BEGIN;

CREATE TABLE Associate (
  id INTEGER PRIMARY KEY,
  path TEXT NULL,
  comment TEXT NULL
);

INSERT INTO Associate (id) VALUES(0);

CREATE TABLE Citation (
  id INTEGER PRIMARY KEY,
  higher_id INTEGER NOT NULL,
  ref_id INTEGER NOT NULL REFERENCES Reference(id),
  ref_seq INTEGER NOT NULL,
  rep_id INTEGER NOT NULL REFERENCES Repository(id),
  comment TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Citation (id, higher_id, ref_id, ref_seq, rep_id, uid, changed)
  VALUES(0,0,0,0,0,'',0);

CREATE TABLE CitationPart (
  id INTEGER PRIMARY KEY,
  cit_id INTEGER NOT NULL REFERENCES Citation(id),
  type_id INTEGER NOT NULL REFERENCES CitationPartType(id),
  val TEXT NOT NULL,
  cit_seq INTEGER NOT NULL,
  comment TEXT NULL
);

INSERT INTO CitationPart (id, cit_id, type_id, val, cit_seq) VALUES(0,0,0,'',0);

CREATE TABLE CitationPartType (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  style INTEGER NOT NULL,
  comment TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO CitationPartType (id, name, style, comment, uid, changed)
  VALUES(0, '', 0, '', '', 0);

CREATE TABLE Contact (
  id INTEGER PRIMARY KEY,
  type_id INTEGER NOT NULL REFERENCES ContactType(id),
  list_id INTEGER NOT NULL REFERENCES ContactList(id),
  list_seq INTEGER NOT NULL,
  val TEXT NOT NULL
);

INSERT INTO Contact (id, type_id, list_id, list_seq, val) VALUES(0,0,0,0,'');

CREATE TABLE ContactList (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER REFERENCES Individual(id)
);

CREATE TABLE ContactType (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
/* See below for id=0 */

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

INSERT INTO Date (id) VALUES(0);

CREATE TABLE Event (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  higher_id INTEGER NOT NULL,
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  date1_id INTEGER NOT NULL,
  date2_id INTEGER NOT NULL,
  place_id INTEGER NOT NULL,
  note TEXT NOT NULL,
  date_pt INTEGER NOT NULL,
  user_ref TEXT
);

INSERT INTO Event (
    id, title, higher_id, type_id, date1_id, date2_id, place_id, note, date_pt)
    VALUES(0,'',0,0,0,0,0,'',0);

CREATE TABLE Eventa (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  ref_id INTEGER NOT NULL REFERENCES Reference(id),
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  date1_id INTEGER NOT NULL,
  date2_id INTEGER NOT NULL,
  place_id INTEGER NOT NULL,
  note TEXT NOT NULL,
  date_pt INTEGER NOT NULL
);

INSERT INTO Eventa (
    id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt)
    VALUES(0,'',0,0,0,0,0,'',0);

CREATE TABLE EventaPersona (
  id INTEGER PRIMARY KEY,
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  per_id INTEGER NOT NULL REFERENCES Persona(id),
  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),
  note TEXT NOT NULL,
  per_seq INTEGER NOT NULL
);

INSERT INTO EventaPersona (
    id, eventa_id, per_id, role_id, note, per_seq)
    VALUES(0,0,0,0,'',0);

CREATE TABLE EventEventa (
  id INTEGER PRIMARY KEY,
  event_id INTEGER NOT NULL REFERENCES Event(id),
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO EventEventa (id, event_id, eventa_id, conf) VALUES(0,0,0,'');

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
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-77, -17, 1, 0, 'Summary');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-61, -17, 1, 0, 'Family');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-62, -17, 1, 0, 'Visitor');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-63, -17, 1, 0, 'Lodger');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-64, -17, 1, 0, 'Boarder');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-85, -17, 1, 0, 'Staff');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-86, -17, 1, 0, 'Inmate');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-87, -17, 1, 0, 'Resident');


INSERT INTO EventType (id, grp, name) VALUES(-18, 8, 'Occupation');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-65, -18, 1, 0, 'Summary');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-66, -18, 0, 0, 'Employer');

INSERT INTO EventType (id, grp, name) VALUES(-19, 8, 'Condition');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-67, -19, 1, 0, 'Summary');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-78, -19, 1, 0, 'Single');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-79, -19, 1, 0, 'Married');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-80, -19, 1, 0, 'Partner');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-81, -19, 1, 0, 'Civil Partner');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-82, -19, 1, 0, 'Widowed');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-83, -19, 1, 0, 'Divorced');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-84, -19, 1, 0, 'Separated');

INSERT INTO EventType (id, grp, name) VALUES(-20, 3, 'Civl Partnership');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-68, -20, 3, 0, 'Partner');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-69, -20, 0, 1, 'Officiator');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-70, -20, 0, 0, 'Witness');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-71, -20, 0, 0, 'Present');

INSERT INTO EventType (id, grp, name) VALUES(-21, 9, 'Relation');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-72, -21, 1, 0, 'Subject');

INSERT INTO EventType (id, grp, name) VALUES(-22, 10, 'Family');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-73, -22, 1, 0, 'Husband');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-74, -22, 2, 0, 'Wife');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-75, -22, 3, 0, 'Partner');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-76, -22, 0, 0, 'Child');

INSERT INTO EventType (id, grp, name) VALUES(-23, 7, 'Media');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-88, -23, 1, 0, 'Subject');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-89, -23, 0, 0, 'Producer');
INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-90, -23, 0, 0, 'Commentator');

/* Next EventTypeRole id = -91 */

CREATE TABLE Family (
  id INTEGER PRIMARY KEY,
  husb_id INTEGER,
  wife_id INTEGER
);

INSERT INTO Family (id) VALUES(0);

CREATE TABLE FamilyEvent (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL REFERENCES Family(id),
  event_id INTEGER NOT NULL REFERENCES Event(id),
  note TEXT,
  fam_seq INTEGER NOT NULL
);

INSERT INTO FamilyEvent (id, fam_id, event_id, fam_seq) VALUES(0,0,0,0);

CREATE TABLE FamilyEventa (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL REFERENCES Family(id),
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO FamilyEventa (id, fam_id, eventa_id, conf) VALUES(0,0,0,0);

CREATE TABLE FamilyIndEventa (
  id INTEGER PRIMARY KEY,
  fam_ind_id INTEGER NOT NULL REFERENCES FamilyIndividual(id),
  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO FamilyIndEventa (id, fam_ind_id, eventa_id, conf) VALUES(0,0,0,0);

CREATE TABLE FamilyIndividual (
  id INTEGER PRIMARY KEY,
  fam_id INTEGER NOT NULL,
  ind_id INTEGER NOT NULL,
  seq_child INTEGER NOT NULL,
  seq_parent INTEGER NOT NULL
);

INSERT INTO FamilyIndividual (
    id, fam_id, ind_id, seq_child,seq_parent) VALUES(0,0,0,0,0);

CREATE TABLE Gallery (
  id INTEGER PRIMARY KEY,
  title TEXT NOT NULL,
  note TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Gallery (id, title, note, uid, changed) VALUES(0,'','','',0);

CREATE TABLE GalleryMedia (
  id INTEGER PRIMARY KEY,
  title TEXT NULL,
  gal_id INT NOT NULL REFERENCES Gallery(id),
  med_id INT NOT NULL REFERENCES Media(id),
  med_seq INT NOT NULL
);

INSERT INTO GalleryMedia (id, gal_id, med_id, med_seq) VALUES(0,0,0,0);

CREATE TABLE Individual (
  id INTEGER PRIMARY KEY,
  sex INTEGER NOT NULL,
  fam_id INTEGER NOT NULL,
  note TEXT NOT NULL,
  privacy INTEGER NOT NULL,
  name TEXT,
  surname TEXT,
  epitaph TEXT
);

INSERT INTO Individual (id, sex, fam_id, note, privacy) VALUES(0,0,0,'',0);

CREATE TABLE IndividualEvent (
  id INTEGER PRIMARY KEY,
  higher_id INTEGER NOT NULL,
  ind_id INTEGER NOT NULL REFERENCES Individual(id),
  event_id INTEGER NOT NULL REFERENCES Event(id),
  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),
  note TEXT NOT NULL,
  ind_seq INTEGER NOT NULL
);

INSERT INTO IndividualEvent (
    id, higher_id, ind_id, event_id, role_id, note, ind_seq)
    VALUES(0,0,0,0,0,'',0);

CREATE TABLE IndividualPersona (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER NOT NULL REFERENCES Individual(id),
  per_id INTEGER NOT NULL REFERENCES Persona(id),
  conf FLOAT NOT NULL,
  note TEXT
);

INSERT INTO IndividualPersona (id, ind_id, per_id, conf) VALUES(0,0,0,0);

CREATE TABLE Media (
  id INTEGER PRIMARY KEY,
  data_id INT NOT NULL REFERENCES MediaData(id),
  ass_id INT NOT NULL REFERENCES Associate(id),
  ref_id INT NOT NULL REFERENCES Reference(id),
  ref_seq INT NOT NULL,
  privacy INT NOT NULL,
  title TEXT NULL,
  note, TEXT NULL
);

INSERT INTO Media (
    id, data_id, ass_id, ref_id, ref_seq, privacy)
    VALUES(0,0,0,0,0,0);

/* Table MediaData created in recCreateMedia.sql */

CREATE TABLE Name (
  id INTEGER PRIMARY KEY,
  ind_id INTEGER NOT NULL,
  per_id INTEGER NOT NULL,
  style_id INTEGER NOT NULL REFERENCES NameStyle(id),
  sequence INTEGER
);

INSERT INTO Name (id, ind_id, per_id, style_id) VALUES(0,0,0,0);

CREATE TABLE NamePart (
  id INTEGER PRIMARY KEY,
  name_id INTEGER NOT NULL REFERENCES Name(id),
  type_id INTEGER NOT NULL REFERENCES NamePartType(id),
  val TEXT,
  sequence INTEGER NOT NULL
);

INSERT INTO NamePart (id, name_id, type_id, sequence) VALUES(0,0,0,0);

CREATE TABLE NamePartType (
  id INTEGER PRIMARY KEY,
  grp INTEGER NOT NULL,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

/* matches enum StdNameType */
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES( 0, 0, '', '', 0);
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES(-1, 1, 'Given name', 'D078B79DEA7D7C5E6954D9BD9A3F77951583', 2459715);
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES(-2, 1, 'Surname', 'C8FA1239479F03CE5A4A9D9462DA1074599E', 2459715 );
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES(-3, 1, 'Post name', 'B4FC970919A55CBD630EC6A9109F692342B8', 2459715);

CREATE TABLE NameStyle (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

/* matches enum recNameStyle::Style */
INSERT INTO NameStyle (id, name, uid, changed) VALUES(0, 'Default', '', 0);
INSERT INTO NameStyle (id, name, uid, changed) VALUES(-1, 'Birth name', '9E8D131956EFBA85EE89134A9EBD43004DF8', 2459715);
INSERT INTO NameStyle (id, name, uid, changed) VALUES(-2, 'Married name', 'CCEF089DAD05903B8825EF5FC8F5A5DA140B', 2459715);
INSERT INTO NameStyle (id, name, uid, changed) VALUES(-3, 'Alias', '67F2C0CDB179EE99E6D3C4B82C9BAAAEEB5B', 2459715);

CREATE TABLE Persona (
  id INTEGER PRIMARY KEY,
  sex INTEGER,
  ref_id INTEGER,
  note TEXT
);

INSERT INTO Persona (id) VALUES(0);

CREATE TABLE Place (
  id INTEGER PRIMARY KEY,
  date1_id INTEGER,
  date2_id INTEGER
);

INSERT INTO Place (id) VALUES(0);

CREATE TABLE PlacePart (
  id INTEGER PRIMARY KEY,
  type_id INTEGER,
  place_id INTEGER,
  val TEXT,
  sequence INTEGER
);

INSERT INTO PlacePart (id) VALUES(0);

CREATE TABLE PlacePartType (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INT NOT NULL
);

INSERT INTO PlacePartType (id, name, uid, changed) VALUES(0, '', '', 0);
INSERT INTO PlacePartType (id, name, uid, changed) VALUES(-1, 'Address', '73D067F49E86C542C3E237AFC50BE77F8A11', 0);

CREATE TABLE Reference (
  id INTEGER PRIMARY KEY,
  higher_id INTEGER,
  title TEXT NOT NULL,
  statement TEXT NOT NULL,
  res_id INTEGER NULL REFERENCES Researcher(id),
  user_ref TEXT NULL,
  uid TEXT NOT NULL,
  changed INT NOT NULL
);

INSERT INTO Reference (id, title, statement, uid, changed)
    VALUES(0,'','','',0);

CREATE TABLE ReferenceEntity (
  id INTEGER PRIMARY KEY,
  ref_id INTEGER,
  entity_type INTEGER,
  entity_id INTEGER,
  sequence INTEGER
);

INSERT INTO ReferenceEntity (id) VALUES(0);

CREATE TABLE RelativeDate (
  id INTEGER PRIMARY KEY,
  val INTEGER,
  range INTEGER,
  unit INTEGER,
  base_id INTEGER NOT NULL REFERENCES Date(id),
  type INTEGER,
  scheme INTEGER
);

INSERT INTO RelativeDate (id, base_id) VALUES(0,0);

CREATE TABLE Repository (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  note TEXT NULL,
  con_list_id INTEGER NULL REFERENCES ContactList(id),
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);

INSERT INTO Repository (id, name, uid, changed) VALUES(0,'','',0);

CREATE TABLE Researcher (  /* See System Settings below for initial entries */
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  comment TEXT,
  con_list_id INTEGER REFERENCES ContactList(id),
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
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

/* Create default settings */
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(0, '', '', 0);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-1, 'Address', '88815CB7641A5C15A6B47B40E69DE654DD52', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-2, 'Telephone', '7143E6D4D916C849F2B4FC6554AE5B421483', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-3, 'Mobile', 'D5914CBACD1E86412EB4771C1E015BCBD882', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-4, 'Email', '2A56952B37D688AD0F795B059A82619E857A', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-5, 'Website', '0913E9393D6F676F74252E9F18516D201CFD', 2459664);
INSERT INTO ContactType (id, name, uid, changed)
  VALUES(-6, 'Fax', 'D717ACECD3D1DF6E663C9788BFB330350F50', 2459664);

INSERT INTO Researcher (id, name, comment, con_list_id, uid, changed) VALUES
  (0, '', NULL, NULL, '', 0);
INSERT INTO Researcher (id, name, comment, con_list_id, uid, changed) VALUES
  (-1, 'Anonymous', NULL, NULL, 'E16C3575699D77C1BABD0C582A44C6FA3E4A', 2459675);

INSERT INTO User (id, res_id) VALUES(1, -1); /* Set User U1 to Anomymous */

INSERT INTO System (id, val) VALUES(1, '1'); /* User U1 */

INSERT INTO UserSetting (id, user_id, property, val) VALUES(1, 1, 1, 'NI');

/* Table Version created in recCreateCommon.sql */

/* The Version table row 1 is the full TFPD database */
INSERT INTO Version (id, major, minor, revision, test) VALUES(1, 0, 0, 10, 39);

COMMIT;

/* End of src/rec/embed/recCreateFull.sql */
