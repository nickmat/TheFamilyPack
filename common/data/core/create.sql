PRAGMA foreign_keys=OFF;
BEGIN;
CREATE TABLE Version (
  id INTEGER PRIMARY KEY,
  major INTEGER,
  minor INTEGER,
  revision INTEGER,
  test INTEGER
);
COMMIT;
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
INSERT INTO Version (id, major, minor, revision, test) VALUES(2, 0, 0, 0, 4);
COMMIT;
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
INSERT INTO ContactType (id, name, uid, changed) VALUES(0, '', '', 0);
CREATE TABLE Date (
  id INTEGER PRIMARY KEY,
  jdn INTEGER NOT NULL,
  range INTEGER NOT NULL,
  rel_id INTEGER NOT NULL REFERENCES RelativeDate(id),
  type INTEGER NOT NULL,
  descrip TEXT NOT NULL,
  record_sch INTEGER NOT NULL,
  display_sch INTEGER NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO Date (
  id, jdn, range, rel_id, type, descrip, record_sch, display_sch, uid, changed)
  VALUES(0,0,0,0,0,'',0,0,'',0);
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
  date1_id INTEGER NOT NULL REFERENCES Date(id),
  date2_id INTEGER NOT NULL REFERENCES Date(id),
  place_id INTEGER NOT NULL REFERENCES Place(id),
  note TEXT NOT NULL,
  date_pt INTEGER NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO Eventa (
  id, title, ref_id, type_id, date1_id, date2_id, place_id, note, date_pt, uid, changed)
  VALUES(0,'',0,0,0,0,0,'',0,'',0);
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
  grp INTEGER NOT NULL,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO EventType (id, grp, name, uid, changed) VALUES(0,0,'','',0);
CREATE TABLE EventTypeRole (
  id INTEGER PRIMARY KEY,
  type_id INTEGER NOT NULL REFERENCES EventType(id),
  prime INTEGER NOT NULL,
  official INTEGER NOT NULL,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO EventTypeRole (id, type_id, prime, official, name, uid, changed) VALUES(0,0,0,0,'','',0);
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
  note TEXT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO Media (
  id, data_id, ass_id, ref_id, ref_seq, privacy, title, note, uid, changed)
  VALUES(0,0,0,0,0,0,'','','',0);
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
INSERT INTO NamePartType (id, grp, name, uid, changed) VALUES( 0, 0, '', '', 0);
CREATE TABLE NameStyle (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO NameStyle (id, name, uid, changed) VALUES(0, 'Default', '', 0);
CREATE TABLE Persona (
  id INTEGER PRIMARY KEY,
  sex INTEGER NOT NULL,
  ref_id INTEGER NOT NULL REFERENCES Reference(id),
  note TEXT,
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO Persona (id, sex, ref_id, note, uid, changed) VALUES(0,0,0,'','',0);
CREATE TABLE Place (
  id INTEGER PRIMARY KEY,
  date1_id INTEGER NOT NULL REFERENCES Date(id),
  date2_id INTEGER NOT NULL REFERENCES Date(id),
  uid TEXT NOT NULL,
  changed INT NOT NULL
);
INSERT INTO Place (id, date1_id, date2_id, uid, changed)
  VALUES(0,0,0,'',0);
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
CREATE TABLE Researcher (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  comment TEXT,
  con_list_id INTEGER REFERENCES ContactList(id),
  uid TEXT NOT NULL,
  changed INTEGER NOT NULL
);
INSERT INTO Researcher (id, name, comment, con_list_id, uid, changed)
  VALUES(0, '', NULL, NULL, '', 0);
CREATE TABLE System (
  id INTEGER PRIMARY KEY,
  val TEXT NOT NULL
);
CREATE TABLE User (
  id INTEGER PRIMARY KEY,
  res_id INTEGER NOT NULL REFERENCES Researcher(id)
);
CREATE TABLE UserSetting (
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES User(id),
  property INTEGER NOT NULL,
  val TEXT NOT NULL
);
INSERT INTO Version (id, major, minor, revision, test) VALUES(1, 0, 0, 10, 44);
COMMIT;
