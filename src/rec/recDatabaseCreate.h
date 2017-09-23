/* ../recDatabaseCreate.h - File created by file2cpp 1.0.0 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/rec/embed/recDatabaseCreate.f2c
 * Project:     The Family Pack: Genealogy data storage and display program.
 * Purpose:     SQL text compiled from SQL files. Format file for file2cpp.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     10th April 2008
 * Copyright:   Copyright (c) 2008 - 2017, Nick Matthews.
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

static const char* createdb =  /* recCreate.sql */
 "PRAGMA legacy_file_format=OFF;\n"
 "PRAGMA foreign_keys=ON;\n"
 "BEGIN;\n"
 "CREATE TABLE CitationPart (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  source_id INTEGER,\n"
 "  type_id INTEGER,\n"
 "  val TEXT\n"
 ");\n"
 "CREATE TABLE CitationPartType (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  name TEXT\n"
 ");\n"
 "CREATE TABLE Contact (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  type_id INTEGER NOT NULL REFERENCES ContactType(id),\n"
 "  list_id INTEGER NOT NULL REFERENCES ContactList(id),\n"
 "  val TEXT NOT NULL\n"
 ");\n"
 "CREATE TABLE ContactList (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  ind_id INTEGER REFERENCES Individual(id)\n"
 ");\n"
 "CREATE TABLE ContactType (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  name TEXT NOT NULL\n"
 ");\n"
 "CREATE TABLE Date (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  jdn INTEGER,\n"
 "  range INTEGER,\n"
 "  rel_id INTEGER,\n"
 "  type INTEGER,\n"
 "  descrip TEXT,\n"
 "  record_sch INTEGER,\n"
 "  display_sch INTEGER\n"
 ");\n"
 "CREATE TABLE Event (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  title TEXT NOT NULL,\n"
 "  higher_id INTEGER NOT NULL,\n"
 "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
 "  date1_id INTEGER NOT NULL,\n"
 "  date2_id INTEGER NOT NULL,\n"
 "  place_id INTEGER NOT NULL,\n"
 "  note TEXT NOT NULL,\n"
 "  date_pt INTEGER NOT NULL,\n"
 "  user_ref TEXT\n"
 ");\n"
 "CREATE TABLE Eventa (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  title TEXT NOT NULL,\n"
 "  type_id INTEGER NOT NULL REFERENCES EventType(id),\n"
 "  date1_id INTEGER NOT NULL,\n"
 "  date2_id INTEGER NOT NULL,\n"
 "  place_id INTEGER NOT NULL,\n"
 "  note TEXT NOT NULL,\n"
 "  date_pt INTEGER NOT NULL\n"
 ");\n"
 "CREATE TABLE EventaPersona (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
 "  per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
 "  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),\n"
 "  note TEXT NOT NULL,\n"
 "  per_seq INTEGER NOT NULL\n"
 ");\n"
 "CREATE TABLE EventEventa (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  event_id INTEGER NOT NULL REFERENCES Event(id),\n"
 "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
 "  conf FLOAT NOT NULL,\n"
 "  note TEXT\n"
 ");\n"
 "CREATE TABLE EventType (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  grp INTEGER,\n"
 "  name TEXT\n"
 ");\n"
 "CREATE TABLE EventTypeRole (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  type_id INTEGER,\n"
 "  prime INTEGER,\n"
 "  official INTEGER,\n"
 "  name TEXT\n"
 ");\n"
 "INSERT INTO EventType (id) VALUES(0);\n"
 "INSERT INTO EventTypeRole (id) VALUES(0);\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-1, 1, 'Birth');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-1, -1, 1, 0, 'Born');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-2, -1, 0, 0, 'Mother');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-3, -1, 0, 1, 'Midwife');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-4, -1, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-2, 5, 'Death');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-5, -2, 1, 0, 'Died');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-6, -2, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-3, 3, 'Marriage');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-7, -3, 1, 0, 'Groom');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-8, -3, 2, 0, 'Bride');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-9, -3, 0, 1, 'Officiator');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-10, -3, 0, 0, 'Witness');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-11, -3, 0, 0, 'Father of Groom');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-12, -3, 0, 0, 'Mother of Groom');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-13, -3, 0, 0, 'Father of Bride');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-14, -3, 0, 0, 'Mother of Bride');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-15, -3, 0, 0, 'Give away Bride');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-16, -3, 0, 0, 'Maid of Honour');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-17, -3, 0, 0, 'Bridesmaid');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-18, -3, 0, 0, 'Best Man');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-19, -3, 0, 0, 'Pageboy');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-20, -3, 0, 0, 'Present');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-59, -3, 3, 0, 'Spouse');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-4, 2, 'Baptism');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-21, -4, 1, 0, 'Baptised');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-22, -4, 0, 0, 'Parent');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-23, -4, 0, 0, 'God Parent');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-24, -4, 0, 1, 'Officiator');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-25, -4, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-5, 6, 'Burial');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-26, -5, 1, 0, 'Deceased');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-27, -5, 0, 1, 'Officiator');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-28, -5, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-6, 7, 'Adult Baptism');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-29, -6, 1, 0, 'Baptised');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-30, -6, 0, 1, 'Officiator');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-31, -6, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-7, 7, 'Census');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-32, -7, 1, 0, 'Listed');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-8, 7, 'Confirmation');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-33, -8, 1, 0, 'Confirmed');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-34, -8, 0, 1, 'Officiator');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-35, -8, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-9, 4, 'Divorce');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-36, -9, 1, 0, 'Husband');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-37, -9, 2, 0, 'Wife');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-10, 7, 'Emigration');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-38, -10, 1, 0, 'Emigrant');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-11, 7, 'Immigration');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-39, -11, 1, 0, 'Immigrant');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-12, 7, 'Graduation');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-40, -12, 1, 0, 'Graduate');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-41, -12, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-13, 7, 'Probate');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-42, -13, 1, 0, 'Deceased');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-43, -13, 0, 0, 'Executor');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-44, -13, 0, 1, 'Adjudicator');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-14, 7, 'Will');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-45, -14, 1, 0, 'Subject');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-46, -14, 0, 0, 'Executor');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-47, -14, 0, 0, 'Beneficiary');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-48, -14, 0, 1, 'Solicitor');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-49, -14, 0, 0, 'Witness');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-15, 2, 'Register Birth');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-50, -15, 1, 0, 'Born');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-51, -15, 0, 0, 'Parent');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-52, -15, 0, 0, 'Registrant');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-53, -15, 0, 1, 'Registrar');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-54, -15, 0, 0, 'Mentioned');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-60, -15, 0, 0, 'Mother');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-16, 6, 'Register Death');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-55, -16, 1, 0, 'Died');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-56, -16, 0, 0, 'Registrant');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-57, -16, 0, 1, 'Registrar');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-58, -16, 0, 0, 'Mentioned');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-17, 8, 'Residence');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-77, -17, 1, 0, 'Summary');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-61, -17, 1, 0, 'Family');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-62, -17, 1, 0, 'Visitor');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-63, -17, 1, 0, 'Lodger');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-64, -17, 1, 0, 'Boarder');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-85, -17, 1, 0, 'Staff');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-86, -17, 1, 0, 'Inmate');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-87, -17, 1, 0, 'Resident');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-18, 8, 'Occupation');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-65, -18, 1, 0, 'Summary');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-66, -18, 0, 0, 'Employer');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-19, 8, 'Condition');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-67, -19, 1, 0, 'Summary');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-78, -19, 1, 0, 'Single');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-79, -19, 1, 0, 'Married');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-80, -19, 1, 0, 'Partner');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-81, -19, 1, 0, 'Civil Partner');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-82, -19, 1, 0, 'Widowed');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-83, -19, 1, 0, 'Divorced');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-84, -19, 1, 0, 'Separated');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-20, 3, 'Civl Partnership');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-68, -20, 3, 0, 'Partner');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-69, -20, 0, 1, 'Officiator');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-70, -20, 0, 0, 'Witness');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-71, -20, 0, 0, 'Present');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-21, 9, 'Relation');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-72, -21, 1, 0, 'Subject');\n"
 "INSERT INTO EventType (id, grp, name) VALUES(-22, 10, 'Family');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-73, -22, 1, 0, 'Husband');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-74, -22, 2, 0, 'Wife');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-75, -22, 3, 0, 'Partner');\n"
 "INSERT INTO EventTypeRole (id, type_id, prime, official, name) VALUES(-76, -22, 0, 0, 'Child');\n"
 "CREATE TABLE Family (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  husb_id INTEGER,\n"
 "  wife_id INTEGER\n"
 ");\n"
 "CREATE TABLE FamilyEvent (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  fam_id INTEGER NOT NULL REFERENCES Family(id),\n"
 "  event_id INTEGER NOT NULL REFERENCES Event(id),\n"
 "  note TEXT,\n"
 "  fam_seq INTEGER NOT NULL\n"
 ");\n"
 "CREATE TABLE FamilyEventa (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  fam_id INTEGER NOT NULL REFERENCES Family(id),\n"
 "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
 "  conf FLOAT NOT NULL,\n"
 "  note TEXT\n"
 ");\n"
 "CREATE TABLE FamilyIndEventa (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  fam_ind_id INTEGER NOT NULL REFERENCES FamilyIndividual(id),\n"
 "  eventa_id INTEGER NOT NULL REFERENCES Eventa(id),\n"
 "  conf FLOAT NOT NULL,\n"
 "  note TEXT\n"
 ");\n"
 "CREATE TABLE FamilyIndividual (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  fam_id INTEGER NOT NULL,\n"
 "  ind_id INTEGER NOT NULL,\n"
 "  seq_child INTEGER NOT NULL,\n"
 "  seq_parent INTEGER NOT NULL\n"
 ");\n"
 "CREATE TABLE Individual (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  sex INTEGER NOT NULL,\n"
 "  fam_id INTEGER NOT NULL,\n"
 "  note TEXT NOT NULL,\n"
 "  privacy INTEGER NOT NULL,\n"
 "  name TEXT,\n"
 "  surname TEXT,\n"
 "  epitaph TEXT\n"
 ");\n"
 "CREATE TABLE IndividualEvent (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  higher_id INTEGER NOT NULL,\n"
 "  ind_id INTEGER NOT NULL REFERENCES Individual(id),\n"
 "  event_id INTEGER NOT NULL REFERENCES Event(id),\n"
 "  role_id INTEGER NOT NULL REFERENCES EventTypeRole(id),\n"
 "  note TEXT NOT NULL,\n"
 "  ind_seq INTEGER NOT NULL\n"
 ");\n"
 "CREATE TABLE IndividualPersona (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  ind_id INTEGER NOT NULL REFERENCES Individual(id),\n"
 "  per_id INTEGER NOT NULL REFERENCES Persona(id),\n"
 "  conf FLOAT NOT NULL,\n"
 "  note TEXT\n"
 ");\n"
 "CREATE TABLE Name (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  ind_id INTEGER NOT NULL,\n"
 "  per_id INTEGER NOT NULL,\n"
 "  style_id INTEGER NOT NULL REFERENCES NameStyle(id),\n"
 "  sequence INTEGER\n"
 ");\n"
 "CREATE TABLE NamePart (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  name_id INTEGER NOT NULL REFERENCES Name(id),\n"
 "  type_id INTEGER NOT NULL REFERENCES NamePartType(id),\n"
 "  val TEXT,\n"
 "  sequence INTEGER NOT NULL\n"
 ");\n"
 "CREATE TABLE NamePartType (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  grp INTEGER NOT NULL,\n"
 "  name TEXT NOT NULL\n"
 ");\n"
 "INSERT INTO NamePartType (id, grp, name) VALUES( 0, 0, '');\n"
 "INSERT INTO NamePartType (id, grp, name) VALUES(-1, 1, 'Given name');\n"
 "INSERT INTO NamePartType (id, grp, name) VALUES(-2, 1, 'Surname');\n"
 "INSERT INTO NamePartType (id, grp, name) VALUES(-3, 1, 'Post name');\n"
 "CREATE TABLE NameStyle (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  name TEXT NOT NULL\n"
 ");\n"
 "INSERT INTO NameStyle (id, name) VALUES(0,'Default');\n"
 "INSERT INTO NameStyle (id, name) VALUES(-1,'Birth name');\n"
 "INSERT INTO NameStyle (id, name) VALUES(-2,'Married name');\n"
 "INSERT INTO NameStyle (id, name) VALUES(-3,'Alias');\n"
 "CREATE TABLE Persona (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  sex INTEGER,\n"
 "  ref_id INTEGER,\n"
 "  note TEXT\n"
 ");\n"
 "CREATE TABLE Place (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  date1_id INTEGER,\n"
 "  date2_id INTEGER\n"
 ");\n"
 "CREATE TABLE PlacePart (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  type_id INTEGER,\n"
 "  place_id INTEGER,\n"
 "  val TEXT,\n"
 "  sequence INTEGER\n"
 ");\n"
 "CREATE TABLE PlacePartType (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  name TEXT\n"
 ");\n"
 "INSERT INTO PlacePartType (id) VALUES(0);\n"
 "INSERT INTO PlacePartType (id, name) VALUES(-1, 'Address');\n"
 "CREATE TABLE Reference (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  title TEXT NOT NULL,\n"
 "  statement TEXT NOT NULL,\n"
 "  user_ref TEXT\n"
 ");\n"
 "CREATE TABLE ReferenceEntity (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  ref_id INTEGER,\n"
 "  entity_type INTEGER,\n"
 "  entity_id INTEGER,\n"
 "  sequence INTEGER\n"
 ");\n"
 "CREATE TABLE RelativeDate (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  val INTEGER,\n"
 "  range INTEGER,\n"
 "  unit INTEGER,\n"
 "  base_id INTEGER NOT NULL REFERENCES Date(id),\n"
 "  type INTEGER,\n"
 "  scheme INTEGER\n"
 ");\n"
 "CREATE TABLE Repository (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  name TEXT NOT NULL,\n"
 "  access TEXT,\n"
 "  comments TEXT,\n"
 "  con_list_id INTEGER NOT NULL REFERENCES ContactList(id)\n"
 ");\n"
 "CREATE TABLE RepositorySource (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  repos_id INTEGER,\n"
 "  source_id INTEGER,\n"
 "  call_num TEXT,\n"
 "  desc TEXT\n"
 ");\n"
 "CREATE TABLE Researcher (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  name TEXT NOT NULL,\n"
 "  comments TEXT,\n"
 "  con_list_id INTEGER NOT NULL REFERENCES ContactList(id)\n"
 ");\n"
 "CREATE TABLE Source (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  higher_id INTEGER,\n"
 "  sub_date1_id INTEGER,\n"
 "  sub_date2_id INTEGER,\n"
 "  sub_place_id INTEGER,\n"
 "  loc_place_id INTEGER,\n"
 "  res_id INTEGER,\n"
 "  comments TEXT\n"
 ");\n"
 "CREATE TABLE System (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  val TEXT NOT NULL\n"
 ");\n"
 "CREATE TABLE User (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  res_id INTEGER NOT NULL REFERENCES Researcher(id)\n"
 ");\n"
 "CREATE TABLE UserSetting (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  user_id INTEGER NOT NULL REFERENCES User(id),\n"
 "  property INTEGER NOT NULL,\n"
 "  val TEXT NOT NULL\n"
 ");\n"
 "CREATE TABLE Version (\n"
 "  id INTEGER PRIMARY KEY,\n"
 "  major INTEGER,\n"
 "  minor INTEGER,\n"
 "  revision INTEGER,\n"
 "  test INTEGER\n"
 ");\n"
 "INSERT INTO ContactType (id, name) VALUES(0, '');\n"
 "INSERT INTO ContactType (id, name) VALUES(-1, 'Address');\n"
 "INSERT INTO ContactType (id, name) VALUES(-2, 'Telephone');\n"
 "INSERT INTO ContactType (id, name) VALUES(-3, 'Mobile');\n"
 "INSERT INTO ContactType (id, name) VALUES(-4, 'Email');\n"
 "INSERT INTO ContactType (id, name) VALUES(-5, 'Website');\n"
 "INSERT INTO ContactType (id, name) VALUES(-6, 'Fax');\n"
 "INSERT INTO ContactList (id) VALUES(0);\n"
 "INSERT INTO ContactList (id) VALUES(1);\n"
 "INSERT INTO Researcher (id, name, comments, con_list_id) VALUES(0, '', '', 0);\n"
 "INSERT INTO Researcher (id, name, comments, con_list_id) VALUES(1, 'Anonymous', '', 1);\n"
 "INSERT INTO User (id, res_id) VALUES(0, 0);\n"
 "INSERT INTO User (id, res_id) VALUES(1, 1);\n"
 "INSERT INTO System (id, val) VALUES(1, '1');\n"
 "INSERT INTO UserSetting (id, user_id, property, val) VALUES(1, 0, 1, 'F1');\n"
 "INSERT INTO UserSetting (id, user_id, property, val) VALUES(2, 1, 1, 'F1');\n"
 "INSERT INTO Version (id, major, minor, revision, test) VALUES(1, 0, 0, 10, 14);\n"
 "COMMIT;\n";

/* End of recDatabaseCreate.f2c */


